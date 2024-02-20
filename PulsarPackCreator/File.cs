
/*
using PulsarPackCreator;
using System;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Versioning;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Shapes;
using static PulsarPackCreator.MsgWindow;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace PulsarPackCreator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private long RoundUp(long value, UInt32 aligment)
        {
            return (value + (aligment - 1)) & ~(aligment - 1);
        }

        private void ImportConfigFile(byte[] raw)
        {

            try
            {
                curCup = 0;
                PulsarGame.BinaryHeader header = PulsarGame.BytesToStruct<PulsarGame.BinaryHeader>(raw.ToArray());
                PulsarGame.InfoHolder infoHolder = CreateSubCat<PulsarGame.InfoHolder>(raw, header.offsetToInfo);
                PulsarGame.CupsHolder cupsHolder = CreateSubCat<PulsarGame.CupsHolder>(raw, header.offsetToCups);

                //Read HEADER

                if (header.magic != 0x50554C53 || header.version != CONFIGVERSION) throw new OperationCanceledException();
                parameters.modFolderName = header.modFolderName.TrimStart('/');

                //INFO Reading
                ReadInfo(CreateSubCat<PulsarGame.InfoHolder>(raw, header.offsetToInfo));

                //CUPS reading
                ReadCups(CreateSubCat<PulsarGame.CupsHolder>(raw, header.offsetToCups));
                nint offset = header.offsetToCups + Marshal.OffsetOf(typeof(PulsarGame.CupsHolder), "cups") + Marshal.OffsetOf(typeof(PulsarGame.Cups), "cupsArray");
                nint size = Marshal.SizeOf(typeof(PulsarGame.Cup));
                for (int i = 0; i < ctsCupCount; i++)
                {
                    PulsarGame.Cup cup = CreateSubCat<PulsarGame.Cup>(raw, (int)offset);
                    ReadCup(cup);
                    offset += size;
                }

                //BMG reading
                int bmgSize = ReadBMG(raw.Skip(header.offsetToBMG).Take(raw.Length - header.offsetToBMG).ToArray());

                //FILE reading
                ReadFile(raw.Skip(header.offsetToBMG + bmgSize).Take(raw.Length - header.offsetToBMG).ToArray());

                RequestBMGAction(false);
                using StreamReader bmgSR = new StreamReader("temp/BMG.txt");
                using StreamReader fileSR = new StreamReader("temp/files.txt");

                ParseBMGAndFILE(bmgSR, fileSR);

                //Clear
                CC100.Text = "0";
                CC150.Text = "0";

                CupCount.Text = $"{ctsCupCount}";
                Regs.SelectedIndex = parameters.regsMode;
                TTTrophies.IsChecked = parameters.hasTTTrophies;
                CC200.IsChecked = parameters.has200cc;
                UMT.IsChecked = parameters.hasUMTs;
                Feather.IsChecked = parameters.hasFeather;
                MegaTC.IsChecked = parameters.hasMegaTC;
                CC100.Text = $"{parameters.prob100cc}";
                if (parameters.has200cc) CC100Label.Text = "% 200cc";
                else CC100Label.Text = "% 100cc";
                CC150.Text = $"{parameters.prob150cc}";
                CCMirror.Text = $"{parameters.probMirror}";
                ModFolder.Text = $"{parameters.modFolderName}";
                Wiimmfi.Text = $"{parameters.wiimmfiRegion}";
                TrackBlocking.SelectedValue = blockingValues[Array.IndexOf(blockingValues, (UInt16)parameters.trackBlocking)];
                dateSelector.SelectedDate = DateTime.Parse(date);
                UpdateCurCup(0);
                MsgWindow.Show("Configuration successfully imported.");
            }
            catch (OperationCanceledException)
            {
                MsgWindow.Show("Invalid Config File.");
            }
            catch (Exception ex)
            {
                MsgWindow.Show(ex.ToString());
            }
            finally
            {
                File.Delete("temp/bmg.bmg");
                File.Delete("temp/bmg.txt");
                File.Delete("temp/Config.pul");
                File.Delete("temp/files.txt");
            }
        }
        private void OnImportConfigClick(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog openFile = new Microsoft.Win32.OpenFileDialog();
            openFile.DefaultExt = ".pul";
            openFile.Filter = "Pulsar Config File(*.pul) | *.pul";
            if (openFile.ShowDialog() == true)
            {
                ImportConfigFile(File.ReadAllBytes(openFile.FileName));
            }
        }

        private void ReadInfo(PulsarGame.InfoHolder raw)
        {
            UInt32 infoMagic = raw.header.magic;
            UInt32 infoVersion = raw.header.version;
            if (infoMagic != 0x494E464F || infoVersion != INFOVERSION) throw new Exception();

            PulsarGame.Info info = raw.info;
            parameters.prob100cc = (int)info.prob100cc;
            parameters.prob150cc = (int)info.prob150cc;
            parameters.probMirror = 100 - (parameters.prob100cc + parameters.prob150cc);
            parameters.wiimmfiRegion = (int)info.wiimmfiRegion;
            parameters.trackBlocking = (int)info.trackBlocking;
            parameters.hasTTTrophies = info.hasTTTrophies == 1 ? true : false;
            parameters.has200cc = info.has200cc == 1 ? true : false;
            parameters.hasUMTs = info.hasUMTs == 1 ? true : false;
            parameters.hasFeather = info.hasFeather == 1 ? true : false; ;
            parameters.hasMegaTC = info.hasMegaTC == 1 ? true : false; ;
        }

        private void ReadCups(PulsarGame.CupsHolder raw)
        {


            UInt32 cupMagic = raw.header.magic;
            UInt32 cupVersion = raw.header.version;
            if (cupMagic != 0x43555053 || cupVersion != CUPSVERSION) throw new Exception();
            cups.Clear();
            PulsarGame.Cups rawCups = raw.cups;
            ctsCupCount = rawCups.ctsCupCount;
            parameters.regsMode = rawCups.regsMode;
        }

        private void ReadCup(PulsarGame.Cup raw)
        {
            cups.Add(new Cup(raw));
        }
        private int ReadBMG(byte[] raw)
        {
            using (BigEndianReader bin = new BigEndianReader(new MemoryStream(raw)))
            {
                UInt64 bmgMagic = bin.ReadUInt64();
                if (bmgMagic != 0x4D455347626D6731) throw new Exception();
                int bmgSize = bin.ReadInt32();
                bin.BaseStream.Position -= 12;
                using (BigEndianWriter bmg = new BigEndianWriter(File.Create("temp/bmg.bmg")))
                {
                    bmg.Write(bin.ReadBytes(bmgSize));
                }
                
                return bmgSize;
            }
        }

        private void ReadFile(byte[] raw)
        {
            using (BigEndianReader bin = new BigEndianReader(new MemoryStream(raw)))
            {
                UInt32 fileMagic = bin.ReadUInt32();
                if (fileMagic != 0x46494C45) throw new Exception();
                bin.BaseStream.Position -= 4;
                using (BigEndianWriter file = new BigEndianWriter(File.Create("temp/files.txt")))
                { 
                    file.Write(bin.ReadBytes((int)bin.BaseStream.Length));                   
                }
            }
        }

        public bool BuildConfigImpl()
        {
            if (dateSelector.SelectedDate == null)
            {
                MsgWindow.Show("Please select a date.");
                TabController.SelectedItem = Options;
                ((TabItem)TabController.SelectedItem).Focus();
                return false;
            }
            if (parameters.modFolderName == null || parameters.modFolderName == "")
            {
                MsgWindow.Show("Please specify a mod folder name.");
                TabController.SelectedItem = Options;
                ((TabItem)TabController.SelectedItem).Focus();
                return false;
            }
            if (parameters.wiimmfiRegion == -1)
            {
                MsgWindow.Show("Please specify a Wiimmfi region.");
                TabController.SelectedItem = Options;
                ((TabItem)TabController.SelectedItem).Focus();
                return false;
            }

            string modFolder = $"output/{parameters.modFolderName}";
            if (Directory.Exists(modFolder))
            {
                try
                {
                    Directory.Delete(modFolder, true);
                }
                catch
                {
                    MsgWindow.Show("Mod Folder is already in use.");
                    return false;
                }
            }
            Directory.CreateDirectory("output");
            Directory.CreateDirectory(modFolder);
            Directory.CreateDirectory($"{modFolder}/Binaries");
            Directory.CreateDirectory($"{modFolder}/Tracks");
            Directory.CreateDirectory($"{modFolder}/Ghosts");
            Directory.CreateDirectory("output/Riivolution");

            try
            {
                File.WriteAllBytes("temp/BMG.txt", parameters.has200cc ? PulsarRes.BMG200 : PulsarRes.BMG100);
                using (BigEndianWriter bin = new BigEndianWriter(File.Create("temp/Config.pul"))) 
                { 
                    using (StreamWriter bmgSW = new StreamWriter("temp/BMG.txt", true))
                    using (StreamWriter fileSW = new StreamWriter("temp/files.txt"))
                    using (StreamWriter crcToFile = new StreamWriter($"{modFolder}/Ghosts/FolderToTrackName.txt"))
                    {
                        bmgSW.WriteLine(bmgSW.NewLine);
                        bmgSW.WriteLine($"  {0x2847:X}    = Version created {date}");
                        fileSW.WriteLine("FILE");

                        bin.Write(0x50554C53); //"PULS"
                        bin.Write(CONFIGVERSION);

                        //Offsets
                        bin.BaseStream.Position += SECTIONCOUNT * 4; //OFFSETS

                        string gameFolderName = $"/{parameters.modFolderName}";
                        bin.Write(gameFolderName.ToArray());
                        bin.BaseStream.Position += 14 - gameFolderName.Length;

                        long infoPosition = RoundUp(bin.BaseStream.Position, 4); //INFO Offset
                        bin.BaseStream.Position = 0x8;
                        bin.Write((int)infoPosition);
                        bin.BaseStream.Position = infoPosition;
                        WriteInfo(bin);

                        long cupPosition = RoundUp(bin.BaseStream.Position, 4); //Cup Offset
                        bin.BaseStream.Position = 0xC;
                        bin.Write((int)cupPosition);
                        bin.BaseStream.Position = cupPosition;
                        WriteCups(bin, bmgSW, fileSW, crcToFile);
                    }

                    RequestBMGAction(true);

                    using (BigEndianReader bmgReader = new BigEndianReader(File.Open("temp/bmg.bmg", FileMode.Open)))
                    {
                        long bmgPosition = RoundUp(bin.BaseStream.Position, 4); ; //BMG Offset
                        bin.BaseStream.Position = 0x10;
                        bin.Write((int)bmgPosition);
                        bin.BaseStream.Position = bmgPosition;
                        bin.Write(bmgReader.ReadBytes((int)bmgReader.BaseStream.Length));
                    }

                    using (BigEndianReader fileReader = new BigEndianReader(File.Open("temp/files.txt", FileMode.Open)))
                    {
                        bin.Write(fileReader.ReadBytes((int)fileReader.BaseStream.Length));
                    }
                }
                char[] delims = new[] { '\r', '\n' };
                string[] xml = PulsarRes.XML.Split(delims, StringSplitOptions.RemoveEmptyEntries);

                xml[3] = xml[3].Replace("{$pack}", parameters.modFolderName);
                xml[28] = xml[28].Replace("{$pack}", parameters.modFolderName);
                xml[29] = xml[29].Replace("{$pack}", parameters.modFolderName);
                xml[30] = xml[30].Replace("{$pack}", parameters.modFolderName);
                xml[31] = xml[31].Replace("{$pack}", parameters.modFolderName);
                xml[32] = xml[32].Replace("{$pack}", parameters.modFolderName);
                xml[37] = xml[39].Replace("{$pack}", parameters.modFolderName);
            
                File.Copy("temp/Config.pul", $"{modFolder}/Binaries/Config.pul", true);
                File.WriteAllLines($"output/Riivolution/{parameters.modFolderName}.xml", xml);
                return true;
            }
            catch(FileNotFoundException ex)
            {
                //Directory.Delete(modFolder, true);
                MsgWindow.Show(ex.Message);
                return false;
            }
            catch (Exception ex)
            {
                MsgWindow.Show(ex.ToString()) ;
                return false;
            }
            finally
            {
                File.Delete("temp/bmg.bmg");
                File.Delete("temp/bmg.txt");
                File.Delete("temp/Config.pul");
                File.Delete("temp/files.txt");
            }

        }

        private void OnBuildConfigClick(object sender, RoutedEventArgs e)
        {
            bool ret = BuildConfigImpl();
            if(ret){
                MsgWindowResult result = MsgWindow.Show("Pack successfully created. Do you want to open the output folder?", "Pack created", MsgWindowButton.YesNo);
                if (result == MsgWindowResult.Yes)
                {
                    OpenDir($"{Directory.GetCurrentDirectory()}\\output");
                }
            }
        }

        [SupportedOSPlatform("windows")]
        private void OnBuildFullPackClick(object sender, RoutedEventArgs e)
        {
            bool ret = BuildConfigImpl();
            try
            {
                if (ret)
                {
                    string modFolder = $"output/{parameters.modFolderName}";
                    File.WriteAllBytes($"{modFolder}/Binaries/Code.pul", PulsarRes.Code);
                    Directory.CreateDirectory($"{modFolder}/Assets");
                    Directory.CreateDirectory($"{modFolder}/CTsBRSTMs");
                    Directory.CreateDirectory($"{modFolder}/My Stuff");
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
                        Cup cup = cups[i];
                        if (cup.iconName != $"{Cup.defaultNames[i]}.png")
                        {
                            hasCustomIcons = true;
                            bool isDefault = Cup.defaultNames.Contains(cup.iconName.Remove(cup.iconName.Length - 4));
                            string realIconName = isDefault ? $"temp/{cup.iconName}" : $"input/CupIcons/{cup.iconName}";
                            if(!File.Exists(realIconName))
                            {
                                throw new Exception($"{realIconName} does not exist.");
                            }
                            using (System.Drawing.Image image = System.Drawing.Image.FromFile(realIconName))
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
                    MsgWindowResult result = MsgWindow.Show("Pack successfully created. Do you want to open the output folder?", "Pack created", MsgWindowButton.YesNo);
                    if (result == MsgWindowResult.Yes)
                    {
                        OpenDir($"{Directory.GetCurrentDirectory()}\\output");
                    }
                }
            }
            catch (Exception ex)
            {
                MsgWindow.Show(ex.ToString());
            }

        }

        private void RequestBMGAction(bool isEncode) //else will decode
        {
            File.WriteAllBytes("temp/wbmgt.exe", PulsarRes.wbmgt);
            ProcessStartInfo processInfo = new ProcessStartInfo();
            processInfo.FileName = @"wbmgt.exe";
            processInfo.Arguments = isEncode ? "encode BMG.txt" : "decode bmg.bmg --no-header --export";
            processInfo.WorkingDirectory = @"temp/";
            processInfo.CreateNoWindow = true;
            processInfo.WindowStyle = ProcessWindowStyle.Hidden;
            processInfo.UseShellExecute = false;

            Process process = new Process();
            process.StartInfo = processInfo;
            process.Start();
            process.WaitForExit();
        }

        private void WriteInfo(BigEndianWriter bin)
        {
            bin.Write(0x494E464F); //INFO
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

        private void WriteCups(BigEndianWriter bin, StreamWriter bmgSW, StreamWriter fileSW, StreamWriter crcToFile)
        {
            bin.Write(0x43555053); //CUPS
            bin.Write(CUPSVERSION);
            long sizePosition = bin.BaseStream.Position;
            bin.Write(0);
            bin.Write(ctsCupCount);
            bin.Write(parameters.regsMode);
            bin.BaseStream.Position += 1; //padding
            long trophyPos = bin.BaseStream.Position;
            bin.BaseStream.Position += 8;

            UInt16[] trophyCount = new UInt16[4] { 0, 0, 0, 0 };
            for (int id = 0; id < ctsCupCount; id++)
            {
                Cup cup = cups[id];
                WriteCup(cup, bin, bmgSW, fileSW, crcToFile, false, ref trophyCount);
            }
            if (ctsCupCount % 2 == 1)
            {
                UInt32 idx = cups[0].idx;
                cups[0].idx = ctsCupCount;
                WriteCup(cups[0], bin, bmgSW, fileSW, crcToFile, true, ref trophyCount);
                cups[0].idx = idx;
            }
            long curPosition = bin.BaseStream.Position;
            bin.BaseStream.Position = trophyPos;
            for (int i = 0; i < 4; i++)
            {
                UInt16 count = parameters.hasTTTrophies ? trophyCount[i] : (UInt16)0;
                bin.Write(count);
            }
            bin.BaseStream.Position = sizePosition;
            bin.Write((int)(curPosition - sizePosition - 4));
            bin.BaseStream.Position = curPosition;
        }
        private void WriteCup(Cup cup, BigEndianWriter bin, StreamWriter bmgSW, StreamWriter fileSW, StreamWriter crcToFile, bool isFake, ref UInt16[] trophyCount)
        {
            string modFolder = $"output/{parameters.modFolderName}";
            UInt32 idx = cup.idx;
            string[] fileInfo = Directory.GetFiles("input/", "*", SearchOption.AllDirectories);
            fileInfo = fileInfo.Select(s => s.ToLowerInvariant()).ToArray();
            bin.Write(idx);
            if (!isFake)
            {
                string iconName = cup.iconName;
                string finalIconName = "";
                if (idx < 100 && iconName.Length > 4 && iconName.Remove(iconName.Length - 4) != Cup.defaultNames[cup.idx])
                {
                    finalIconName = iconName;
                }
                bmgSW.WriteLine($"  {0x10000 + idx:X}    = {cup.name}");
                fileSW.WriteLine($"{idx:X}?{iconName}");
            }
                
            for (int i = 0; i < 4; i++)
            {
                string name = cup.fileNames[i];
                string curFile = $"input/{name}.szs".ToLowerInvariant();
                if (!fileInfo.Contains(curFile))
                {
                    throw new FileNotFoundException($"Track {name} does not exist. Failed creating cups.");
                }
                bin.Write(cup.slots[i]);
                bin.Write(cup.musicSlots[i]);
                int crc32 = BitConverter.ToInt32(System.IO.Hashing.Crc32.Hash(File.ReadAllBytes(curFile)), 0);
                bin.Write(crc32);
                if (!isFake)
                {
                    File.Copy($"input/{name}.szs", $"{modFolder}/Tracks/{idx * 4 + i}.szs", true);
                    crcToFile.WriteLine($"{name} = {crc32:X8}");
                    string crc32Folder = $"{modFolder}/Ghosts/{crc32.ToString("X")}";

                    Directory.CreateDirectory(crc32Folder);
                    for (int expert = 0; expert < 4; expert++)
                    {
                        string expertName = cup.expertFileNames[i, expert];
                        if (expertName != "RKG File" && expertName != "")
                        {
                            string rkgName = $"input/{PulsarGame.ttModeFolders[expert, 1]}\\{expertName}.rkg".ToLowerInvariant();
                            if (!fileInfo.Contains(rkgName))
                            {
                                throw new FileNotFoundException($"Expert ghost {expertName}.rkg does not exist. Failed creating cups.");
                            }
                            using BigEndianReader rkg = new BigEndianReader(File.Open(rkgName, FileMode.Open));
                            rkg.BaseStream.Position = 0xC;
                            UInt16 halfC = rkg.ReadUInt16();
                            UInt16 newC = (UInt16)((halfC & ~(0x7F << 2)) + (0x26 << 2)); //change ghostType to expert

                            rkg.BaseStream.Position = 0;
                            byte[] rkgBytes = rkg.ReadBytes((int)(rkg.BaseStream.Length - 4)); //-4 to remove crc32
                            Directory.CreateDirectory($"{crc32Folder}/{PulsarGame.ttModeFolders[expert, 0]}");
                            using BigEndianWriter finalRkg = new BigEndianWriter(File.Create($"{crc32Folder}/{PulsarGame.ttModeFolders[expert, 0]}/expert.rkg"));
                            rkgBytes[0xC] = (byte)(newC >> 8);
                            rkgBytes[0xD] = (byte)(newC & 0xFF);
                            finalRkg.Write(rkgBytes);
                            int rkgCrc32 = BitConverter.ToInt32(System.IO.Hashing.Crc32.Hash(rkgBytes), 0);
                            finalRkg.Write(rkgCrc32);

                            trophyCount[expert]++;
                        }
                    }

                }

                string trackName = cup.trackNames[i];
                if (cup.versionNames[i] != "" && cup.versionNames[i] != "Version")
                {
                    trackName += $" \\c{{red3}}{cup.versionNames[i]}\\c{{off}}";
                }

                bmgSW.WriteLine($"  {0x20000 + idx * 4 + i:X}    = {trackName}");
                bmgSW.WriteLine($"  {0x30000 + idx * 4 + i:X}    = {cup.authorNames[i]}");
                fileSW.WriteLine($"{idx * 4 + i:X}={cup.fileNames[i]}|" +
                $"{cup.expertFileNames[i, 0]}|{cup.expertFileNames[i, 1]}|{cup.expertFileNames[i, 2]}|{cup.expertFileNames[i, 3]}");
            }
        }

        private void ParseBMGAndFILE(StreamReader bmgSR, StreamReader fileSR)
        {
            bmgSR.ReadLine(); //#BMG
            string curLine = bmgSR.ReadLine();

            while (curLine != null)
            {
                if (curLine != "")
                {
                    UInt32 bmgId;
                    bool ret = UInt32.TryParse(curLine.Substring(1, 5), NumberStyles.HexNumber, CultureInfo.InvariantCulture, out bmgId);
                    if (!ret)
                    {
                        ret = UInt32.TryParse(curLine.Substring(2, 4), NumberStyles.HexNumber, CultureInfo.InvariantCulture, out bmgId);
                    }
                    if (ret)
                    {
                        if (bmgId == 0x2847) date = curLine.Split(' ')[curLine.Split(' ').Length - 1];
                        else if (bmgId >= 0x10000 && bmgId < 0x60000)
                        {
                            string content = curLine.Split('=')[1].TrimStart(' ');
                            UInt32 type = bmgId & 0xFFFF0000;
                            UInt32 rest = bmgId & 0xFFFF;
                            int cupIdx = (int)rest / 4;
                            if (cupIdx < ctsCupCount)
                            {
                                int trackIdx = (int)rest % 4;
                                switch (type)
                                {
                                    case (0x10000):
                                        if((int)rest < ctsCupCount) cups[(int)rest].name = content;
                                        break;
                                    case (0x20000):
                                        if (content.Contains("\\c{red3}"))
                                        {
                                            string[] split = content.Split("\\c{red3}");

                                            cups[cupIdx].trackNames[trackIdx] = split[0];
                                            cups[cupIdx].versionNames[trackIdx] = split[1].Split("\\c{off}")[0];
                                        }
                                        else cups[cupIdx].trackNames[trackIdx] = content;
                                        break;
                                    case (0x30000):
                                        cups[cupIdx].authorNames[trackIdx] = content;
                                        break;
                                }
                            }

                        }
                    }
                }
                curLine = bmgSR.ReadLine();
            }
            fileSR.ReadLine();
            curLine = fileSR.ReadLine(); //FILE
            while (curLine != null)
            {
                if (curLine != "")
                {
                    if (curLine.Contains("?"))
                    {
                        string[] split = curLine.Split("?");
                        UInt32 idx = UInt32.Parse(split[0], NumberStyles.HexNumber);
                        if (split.Length > 1 && split[1] != "") cups[(int)idx].iconName = split[1];
                    }
                    else
                    {
                        string[] split = curLine.Split("=");
                        UInt32 id = UInt32.Parse(split[0], NumberStyles.HexNumber);

                        int cupIdx = (int)id / 4;
                        if (cupIdx < ctsCupCount)
                        {
                            int trackIdx = (int)id % 4;
                            string[] names = split[1].Split("|");
                            if (names.Length > 0)
                            {
                                cups[cupIdx].fileNames[trackIdx] = names[0];
                                for (int i = 1; i < names.Length; i++)
                                {
                                    cups[cupIdx].expertFileNames[trackIdx, i - 1] = names[i];
                                }
                            }
                        }
                    }
                }
                curLine = fileSR.ReadLine();
            }
        }
        private void OnOpenInputClick(object sender, RoutedEventArgs e)
        {
            OpenDir($"{Directory.GetCurrentDirectory()}\\input");
        }

        private void OpenDir(string path) => Process.Start("explorer.exe", path);

        private async Task ExtractDefaultTPLs()
        {
            await File.WriteAllBytesAsync("temp/wszst.exe", PulsarRes.wszst);
            await File.WriteAllBytesAsync("temp/wimgt.exe", PulsarRes.wimgt);
            await File.WriteAllBytesAsync("temp/UIAssets.szs", PulsarRes.UIAssets);

            ProcessStartInfo wszstProcessInfo = new ProcessStartInfo();
            wszstProcessInfo.FileName = @"wszst.exe";
            wszstProcessInfo.Arguments = "extract UIAssets.szs";
            wszstProcessInfo.WorkingDirectory = @"temp/";
            wszstProcessInfo.CreateNoWindow = true;
            wszstProcessInfo.WindowStyle = ProcessWindowStyle.Hidden;
            wszstProcessInfo.UseShellExecute = false;

            Process wszstProcess = new Process();
            wszstProcess.StartInfo = wszstProcessInfo;
            wszstProcess.Start();
            await wszstProcess.WaitForExitAsync();

            ProcessStartInfo wimgtProcessInfo = new ProcessStartInfo();
            wimgtProcessInfo.FileName = @"temp/wimgt.exe";
            wimgtProcessInfo.CreateNoWindow = true;
            wimgtProcessInfo.WindowStyle = ProcessWindowStyle.Hidden;
            wimgtProcessInfo.UseShellExecute = false;

            Process wimgtProcess = new Process();
            wimgtProcess.StartInfo = wimgtProcessInfo;

            for (int i = 0; i < Cup.maxCupIcons; i++)
            {
                if (cancelToken.IsCancellationRequested)
                {
                    return;
                }
                wimgtProcessInfo.Arguments = $"decode temp/UIAssets.d/button/timg/icon_{i:D2}.tpl --dest \"temp/{Cup.defaultNames[i]}.png\" -o";
                wimgtProcess.Start();
                if (i == 0)
                {
                    wimgtProcess.WaitForExit();
                    DisplayImage(CupIcon.Text);
                }
                else await wimgtProcess.WaitForExitAsync(cancelToken.Token);
                                     
            }

        }

        private bool DisplayImage(string path)
        {
            if (path == "") return false;
            bool isDefault = Cup.defaultNames.Contains(path.Remove(path.Length - 4));
            string filePath = isDefault ? $"temp/{path}" : $"input/CupIcons/{path}";

            if (!File.Exists(filePath))
            {
                if (isDefault) //has not finished extracting all default tpls
                {
                    return false;
                }
                else
                {
                    MsgWindow.Show($"{path} does not exist.");
                    return false;
                }
            }
            BitmapImage src = new BitmapImage();
            src.BeginInit();
            src.UriSource = new Uri(filePath, UriKind.Relative);
            src.CacheOption = BitmapCacheOption.OnLoad;
            src.EndInit();
            IconDisplay.Source = src;
            IconDisplay.Stretch = Stretch.Uniform;
            return true;

        }




    }
}

*/