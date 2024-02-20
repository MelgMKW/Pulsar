using PulsarPackCreator;
using System;
using System.Buffers.Binary;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Documents;
using static PulsarPackCreator.MainWindow;
using static PulsarPackCreator.MsgWindow;
using static System.Windows.Forms.Design.AxImporter;

namespace PulsarPackCreator.IO
{
    class Builder : IOBase
    {
        public enum BuildParams
        {
            ConfigOnly,
            ConfigAndXML,
            Full
        }
        public Builder(MainWindow window, BuildParams buildParams) : base(window)
        {
            modFolder = $"output/{parameters.modFolderName}";
            cups = window.cups.AsReadOnly();

            date = window.dateSelector.SelectedDate;
            regsExperts = window.regsExperts;
            this.buildParams = buildParams;

            string[] info = Directory.GetFiles("input/", "*", SearchOption.AllDirectories);
            inputFiles = info.Select(s => s.ToLowerInvariant()).ToArray();
        }


        BigEndianWriter bin = null;
        StreamWriter bmgSW = null;
        StreamWriter fileSW = null;
        StreamWriter crcToFile = null;
        BigEndianWriter textSW = null;
        ushort[] trophyCount;
        public List<(string, int)> stringPool = new List<(string, int)>();

        ReadOnlyCollection<MainWindow.Cup> cups;
        readonly string[,,] regsExperts;

        readonly BuildParams buildParams;
        readonly string[] inputFiles;
        readonly string modFolder;
        readonly DateTime? date;


        public Result Build()
        {
            if (date == null) return Result.NoDate;
            if (parameters.modFolderName == null || parameters.modFolderName == "") return Result.NoModName;
            if (parameters.wiimmfiRegion == -1) return Result.NoWiimmfi;

            if (Directory.Exists(modFolder))
            {
                try { Directory.Delete(modFolder, true); }
                catch { return Result.AlreadyInUse; }
            }
            Directory.CreateDirectory("output");
            Directory.CreateDirectory(modFolder);
            Directory.CreateDirectory($"{modFolder}/Binaries");
            Directory.CreateDirectory($"{modFolder}/Tracks");
            Directory.CreateDirectory($"{modFolder}/Ghosts");
            Directory.CreateDirectory("output/Riivolution");

            try
            {
                string[] bmgLines = File.ReadAllLines("temp/PulsarBMG.txt");
                string cc = parameters.has200cc ? "200" : "100";
                for (int i = 0; i < bmgLines.Length; i++)
                {
                    bmgLines[i] = bmgLines[i].Replace("{CC}", cc);
                }
                File.WriteAllLines("temp/BMG.txt", bmgLines);

                //CreateBin
                using (bin = new BigEndianWriter(File.Create("temp/Config.pul")))
                {
                    using (bmgSW = new StreamWriter("temp/BMG.txt", true))
                    using (fileSW = new StreamWriter("temp/files.txt"))
                    using (crcToFile = new StreamWriter($"{modFolder}/Ghosts/FolderToTrackName.txt"))
                    using (textSW = new BigEndianWriter(File.Create("temp/cupText.txt"), Encoding.Unicode))
                    {
                        bmgSW.WriteLine(bmgSW.NewLine);
                        bmgSW.WriteLine($"  {0x2847:X}    = Version created {date}");
                        fileSW.WriteLine("FILE");

                        bin.Write(binMagic); //"PULS"
                        bin.Write(CONFIGVERSION);

                        //Header

                        string gameFolderName = $"/{parameters.modFolderName}";
                        bin.Write(gameFolderName.ToArray());
                        bin.BaseStream.Position += 14 - gameFolderName.Length;

                        long infoPosition = 0x40; //INFO Offset, right after header
                        bin.BaseStream.Position = 0x18;
                        bin.Write((int)infoPosition);
                        bin.BaseStream.Position = infoPosition;
                        WriteInfo();

                        long cupPosition = RoundUp(bin.BaseStream.Position, 4); //Cup Offset
                        bin.BaseStream.Position = 0x1C;
                        bin.Write((int)cupPosition);
                        bin.BaseStream.Position = cupPosition;
                        Result cupRet = WriteCups();
                        if (cupRet != Result.Success) return cupRet;
                    }
                    using (BigEndianReader cupTextReader = new BigEndianReader(File.Open("temp/cupText.txt", FileMode.Open)))
                    {
                        long textConfigPosition = RoundUp(bin.BaseStream.Position, 4); //Cup Offset
                        bin.BaseStream.Position = 0x20;
                        bin.Write((int)textConfigPosition);
                        bin.BaseStream.Position = textConfigPosition;
                        bin.Write(textMagic);
                        bin.Write(TEXTVERSION);
                        bin.Write((int)cupTextReader.BaseStream.Length - 2);
                        cupTextReader.BaseStream.Position += 2;
                        bin.Write(cupTextReader.ReadBytes((int)cupTextReader.BaseStream.Length - 2));
                    }

                    RequestBMGAction(true);
                    using (BigEndianReader bmgReader = new BigEndianReader(File.Open("temp/bmg.bmg", FileMode.Open)))
                    {
                        long bmgPosition = RoundUp(bin.BaseStream.Position, 4); ; //BMG Offset
                        bin.BaseStream.Position = 0x24;
                        bin.Write((int)bmgPosition);
                        bin.BaseStream.Position = bmgPosition;
                        bin.Write(bmgReader.ReadBytes((int)bmgReader.BaseStream.Length));
                    }

                    using (BigEndianReader fileReader = new BigEndianReader(File.Open("temp/files.txt", FileMode.Open)))
                    {
                        bin.Write(fileReader.ReadBytes((int)fileReader.BaseStream.Length));
                    }
                }
                File.Copy("temp/Config.pul", $"{modFolder}/Binaries/Config.pul", true);

                if (buildParams == BuildParams.ConfigAndXML || buildParams == BuildParams.Full) CreateXML();
                if (buildParams == BuildParams.Full)
                {

                    Directory.CreateDirectory($"{modFolder}/Assets");
                    Directory.CreateDirectory($"{modFolder}/CTBRSTM");
                    Directory.CreateDirectory($"{modFolder}/My Stuff");
                    File.WriteAllBytes($"{modFolder}/Binaries/Code.pul", PulsarRes.Code);
                    File.WriteAllBytes($"{modFolder}/Binaries/Loader.pul", PulsarRes.Loader);
                    File.WriteAllBytes($"{modFolder}/Assets/RaceAssets.szs", PulsarRes.RaceAssets);
                    File.WriteAllBytes($"{modFolder}/Assets/CommonAssets.szs", PulsarRes.CommonAssets);

                    bool hasCustomIcons = false;
                    Process wimgtProcess = new Process();
                    ProcessStartInfo wimgtProcessInfo = new ProcessStartInfo();
                    wimgtProcessInfo.FileName = @"temp/wimgt.exe";
                    //wimgtProcessInfo.WorkingDirectory = @"temp/";
                    wimgtProcessInfo.CreateNoWindow = true;
                    wimgtProcessInfo.WindowStyle = ProcessWindowStyle.Hidden;
                    wimgtProcessInfo.UseShellExecute = false;
                    wimgtProcess.StartInfo = wimgtProcessInfo;

                    for (int i = 0; i < Math.Min(ctsCupCount, (ushort)100); i++)
                    {
                        MainWindow.Cup cup = cups[i];
                        if (cup.iconName != $"{MainWindow.Cup.defaultNames[i]}.png")
                        {
                            hasCustomIcons = true;
                            bool isDefault = MainWindow.Cup.defaultNames.Contains(cup.iconName.Remove(cup.iconName.Length - 4));
                            string realIconName = isDefault ? $"temp/{cup.iconName}" : $"input/CupIcons/{cup.iconName}";
                            if (!File.Exists(realIconName))
                            {
                                throw new Exception($"{realIconName} does not exist.");
                            }
                            using (Image image = Image.FromFile(realIconName))
                            {
                                new Bitmap(image, 128, 128).Save($"temp/{i}.png");
                            }
                            wimgtProcessInfo.Arguments = $"encode temp/{i}.png --dest temp/UIAssets.d/button/timg/icon_{i:D2}.tpl --transform CMPR -o";
                            wimgtProcess.Start();
                            wimgtProcess.WaitForExit();
                        }
                    }
                    if (hasCustomIcons)
                    {
                        ProcessStartInfo wszstProcessInfo = new ProcessStartInfo();
                        wszstProcessInfo.FileName = @"wszst.exe";
                        wszstProcessInfo.Arguments = $"create temp/UIAssets.d --dest \"{modFolder}/Assets/UIAssets.szs\" -o";
                        wszstProcessInfo.CreateNoWindow = true;
                        wszstProcessInfo.WindowStyle = ProcessWindowStyle.Hidden;
                        wszstProcessInfo.UseShellExecute = false;
                        Process wszstProcess = new Process();
                        wszstProcess.StartInfo = wszstProcessInfo;
                        wszstProcess.Start();
                        wszstProcess.WaitForExit();
                    }
                    else File.Copy("temp/UIAssets.szs", $"{modFolder}/Assets/UIAssets.szs");
                }
                
            }
            catch (Exception ex)
            {
                error = ex.ToString();
                return Result.UnknownError;
            }
            finally
            {
                File.Delete("temp/bmg.bmg");
                File.Delete("temp/bmg.txt");
                File.Delete("temp/Config.pul");
                File.Delete("temp/files.txt");
            }

            return Result.Success;

        }

        private void WriteInfo()
        {
            bin.Write(infoMagic); //INFO
            bin.Write(INFOVERSION);
            long sizePosition = bin.BaseStream.Position;
            bin.Write(0);
            Random random = new Random();
            byte[] randBytes = new byte[4];
            random.NextBytes(randBytes);
            bin.Write(BitConverter.ToUInt32(randBytes, 0));
            bin.Write(parameters.prob100cc);
            bin.Write(parameters.prob150cc);
            bin.Write(parameters.wiimmfiRegion);
            bin.Write(parameters.trackBlocking);

            bin.Write(parameters.hasTTTrophies);
            bin.Write(parameters.has200cc);
            bin.Write(parameters.hasUMTs);
            bin.Write(parameters.hasFeather);
            bin.Write(parameters.hasMegaTC);


            //reserved in case it is needed 
            //bin.BaseStream.Position = (bin.BaseStream.Position + (32 - 1)) & ~(32 - 1);
            bin.BaseStream.Position += 43; //reserved space

            long curPosition = bin.BaseStream.Position;
            bin.BaseStream.Position = sizePosition;
            bin.Write((int)(curPosition - sizePosition - 4));
            bin.BaseStream.Position = curPosition;
        }

        private Result WriteCups()
        {
            trophyCount = new ushort[4] { 0, 0, 0, 0 };
            bin.Write(cupsMagic); //CUPS
            bin.Write(CUPSVERSION);
            long sizePosition = bin.BaseStream.Position;
            bin.Write(0);
            bin.Write(ctsCupCount);
            bin.Write(parameters.regsMode);
            bin.BaseStream.Position += 1; //padding
            long trophyPos = bin.BaseStream.Position;
            bin.BaseStream.Position += 8;

            for (int id = 0; id < ctsCupCount; id++)
            {
                MainWindow.Cup cup = cups[id];
                Result cupRet = WriteCup(cup);
                if (cupRet != Result.Success) return cupRet;
            }
            if (ctsCupCount % 2 == 1)
            {
                uint idx = cups[0].idx;
                cups[0].idx = ctsCupCount;
                Result cupRet = WriteCup(cups[0], true);
                cups[0].idx = idx;
                if (cupRet != Result.Success) return cupRet;
            }

            WriteRegsExperts();

            long curPosition = bin.BaseStream.Position;
            bin.BaseStream.Position = trophyPos;
            for (int i = 0; i < 4; i++)
            {
                ushort count = parameters.hasTTTrophies ? trophyCount[i] : (ushort)0;
                bin.Write(count);
            }
            bin.BaseStream.Position = sizePosition;
            bin.Write((int)(curPosition - sizePosition - 4));
            bin.BaseStream.Position = curPosition;

            return Result.Success;
        }

        private Result WriteCup(MainWindow.Cup cup, bool isFake = false)
        {
            cup.idx = 0;
            uint idx = cup.idx;
            bin.Write(idx);
            if (!isFake)
            {
                AppendText(cup.name);
                //bmgSW.WriteLine($"  {0x10000 + idx:X}    = {cup.name}");

                string iconName = cup.iconName;
                string finalIconName = "";
                if (idx < 100 && iconName.Length > 4 && iconName.Remove(iconName.Length - 4) != MainWindow.Cup.defaultNames[cup.idx])
                {
                    finalIconName = iconName;
                }
                fileSW.WriteLine($"{idx:X}?{finalIconName}");
            }

            for (int i = 0; i < 4; i++)
            {
                string name = cup.fileNames[i];
                string curFile = $"input/{name}.szs".ToLowerInvariant();
                if (!inputFiles.Contains(curFile))
                {
                    error = $"{curFile}";
                    return Result.FileNotFound;
                }

                bin.Write(cup.slots[i]);
                bin.Write(cup.musicSlots[i]);
                int crc32 = BitConverter.ToInt32(System.IO.Hashing.Crc32.Hash(File.ReadAllBytes(curFile)), 0);
                bin.Write(crc32);
                if (!isFake)
                {
                    


                    File.Copy($"input/{name}.szs", $"{modFolder}/Tracks/{idx * 4 + i}.szs", true);
                    crcToFile.WriteLine($"{name} = {crc32:X8}");
                    string crc32Folder = $"{modFolder}/Ghosts/{crc32:X8}";

                    Directory.CreateDirectory(crc32Folder);
                    for (int mode = 0; mode < 4; mode++)
                    {
                        string expertName = cup.expertFileNames[i, mode];
                        if (expertName != "RKG File" && expertName != "")
                        {
                            string rkgName = $"input/{PulsarGame.ttModeFolders[mode, 1]}\\{expertName}.rkg".ToLowerInvariant();
                            if (!inputFiles.Contains(rkgName))
                            {
                                error = $"{rkgName}";
                                return Result.FileNotFound;
                            }

                            using BigEndianReader rkg = new BigEndianReader(File.Open(rkgName, FileMode.Open));
                            rkg.BaseStream.Position = 0xC;
                            ushort halfC = rkg.ReadUInt16();
                            ushort newC = (ushort)((halfC & ~(0x7F << 2)) + (0x26 << 2)); //change ghostType to expert

                            rkg.BaseStream.Position = 0;
                            byte[] rkgBytes = rkg.ReadBytes((int)(rkg.BaseStream.Length - 4)); //-4 to remove crc32
                            Directory.CreateDirectory($"{crc32Folder}/{PulsarGame.ttModeFolders[mode, 0]}");
                            using BigEndianWriter finalRkg = new BigEndianWriter(File.Create($"{crc32Folder}/{PulsarGame.ttModeFolders[mode, 0]}/expert.rkg"));
                            rkgBytes[0xC] = (byte)(newC >> 8);
                            rkgBytes[0xD] = (byte)(newC & 0xFF);
                            finalRkg.Write(rkgBytes);
                            int rkgCrc32 = BitConverter.ToInt32(System.IO.Hashing.Crc32.Hash(rkgBytes), 0);
                            finalRkg.Write(rkgCrc32);

                            trophyCount[mode]++;
                        }
                    }

                }

                string trackName = cup.trackNames[i];
                if (cup.versionNames[i] != "" && cup.versionNames[i] != "Version")
                {
                    trackName += $" \\c{{red3}}{cup.versionNames[i]}\\c{{off}}";
                }

                AppendText(trackName);
                AppendText(cup.authorNames[i]);
                //bmgSW.WriteLine($"  {0x20000 + idx * 4 + i:X}    = {trackName}");
                //bmgSW.WriteLine($"  {0x30000 + idx * 4 + i:X}    = {cup.authorNames[i]}");
                fileSW.WriteLine($"{idx * 4 + i:X}={cup.fileNames[i]}|" +
                $"{cup.expertFileNames[i, 0]}|{cup.expertFileNames[i, 1]}|{cup.expertFileNames[i, 2]}|{cup.expertFileNames[i, 3]}");
            }
            return Result.Success;
        }

        private void AppendText(string text)
        {
            (string, int) element = stringPool.Find(t => t.Item1 == text);
            if (element != default)
            {
                bin.Write(element.Item2);
            }
            else
            {
                stringPool.Add(((string, int))(text, textSW.BaseStream.Position - 2));
                bin.Write((int)textSW.BaseStream.Position - 2);
                if (text.Contains(@"\"))
                {
                    textSW.Write(text);
                }
                else
                {
                    byte[] raw =  System.Text.Encoding.Unicode.GetBytes(text);
                    byte[] utf8 = Encoding.Convert(Encoding.Unicode, Encoding.UTF8, raw);
                    textSW.Write(utf8);
                }              
                textSW.Write(char.MinValue);
            }
        }
        private void WriteRegsExperts()
        {
            for (int cup = 0; cup < 8; cup++)
            {
                for (int idx = 0; idx < 4; idx++)
                {
                    for (int mode = 0; mode < 4; mode++)
                    {
                        string folderName = PulsarGame.MarioKartWii.regsGhostFolders[cup * 4 + idx];
                        string expertName = regsExperts[cup, idx, mode];
                        if (expertName != "RKG File" && expertName != "" && expertName != null)
                        {
                            string rkgName = $"input/{PulsarGame.ttModeFolders[mode, 1]}\\{expertName}.rkg".ToLowerInvariant();
                            if (!inputFiles.Contains(rkgName))
                            {
                                throw new FileNotFoundException($"Regs Expert ghost {expertName}.rkg does not exist. Failed creating config.");
                            }
                            using BigEndianReader rkg = new BigEndianReader(File.Open(rkgName, FileMode.Open));
                            rkg.BaseStream.Position = 0xC;
                            ushort halfC = rkg.ReadUInt16();
                            ushort newC = (ushort)((halfC & ~(0x7F << 2)) + (0x26 << 2)); //change ghostType to expert

                            rkg.BaseStream.Position = 0;
                            byte[] rkgBytes = rkg.ReadBytes((int)(rkg.BaseStream.Length - 4)); //-4 to remove crc32
                            Directory.CreateDirectory($"{folderName}/{PulsarGame.ttModeFolders[mode, 0]}");
                            using BigEndianWriter finalRkg = new BigEndianWriter(File.Create($"{folderName}/{PulsarGame.ttModeFolders[mode, 0]}/expert.rkg"));
                            rkgBytes[0xC] = (byte)(newC >> 8);
                            rkgBytes[0xD] = (byte)(newC & 0xFF);
                            finalRkg.Write(rkgBytes);
                            int rkgCrc32 = BitConverter.ToInt32(System.IO.Hashing.Crc32.Hash(rkgBytes), 0);
                            finalRkg.Write(rkgCrc32);
                            trophyCount[mode]++;
                        }
                    }
                    fileSW.WriteLine($"{cup * 4 + idx:X}=" +
                        $"{regsExperts[cup, idx, 0]}:{regsExperts[cup, idx, 1]}:{regsExperts[cup, idx, 2]}:{regsExperts[cup, idx, 3]}");
                }

            }
        }

        private void CreateXML()
        {
            char[] delims = new[] { '\r', '\n' };
            string[] xml = PulsarRes.XML.Split(delims, StringSplitOptions.RemoveEmptyEntries);

            xml[3] = xml[3].Replace("{$pack}", parameters.modFolderName);
            xml[28] = xml[28].Replace("{$pack}", parameters.modFolderName);
            xml[29] = xml[29].Replace("{$pack}", parameters.modFolderName);
            xml[30] = xml[30].Replace("{$pack}", parameters.modFolderName);
            xml[31] = xml[31].Replace("{$pack}", parameters.modFolderName);
            xml[32] = xml[32].Replace("{$pack}", parameters.modFolderName);
            xml[38] = xml[38].Replace("{$pack}", parameters.modFolderName);

            uint rand = (uint)new Random().Next(1 << 8); ;
            xml[6] = xml[6].Replace("{$pack}", $"{parameters.modFolderName}{rand}");
            xml[14] = xml[14].Replace("{$pack}", $"{parameters.modFolderName}{rand}");
            xml[19] = xml[19].Replace("{$pack}", $"{parameters.modFolderName}{rand}");
            xml[37] = xml[37].Replace("{$pack}", $"{parameters.modFolderName}{rand}");
            File.WriteAllLines($"output/Riivolution/{parameters.modFolderName}.xml", xml);
        }

    }



}
