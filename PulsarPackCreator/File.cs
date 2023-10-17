using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using Pulsar_Pack_Creator;
using System.Buffers.Binary;
using System.Runtime.Serialization.Formatters.Binary;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Globalization;
using System.Reflection.Metadata;
using System.Security.Cryptography;

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

        private void ImportPulsarBin(BigEndianReader bin)
        {
            Directory.CreateDirectory("temp/");
            try
            {
                curCup = 0;
                //Read HEADER
                UInt32 binMagic = bin.ReadUInt32();
                UInt32 binVersion = bin.ReadUInt32();
                if (binMagic != 0x50554C53 || binVersion != BINVERSION) throw new Exception();
                int offsetToInfo = bin.ReadInt32();
                int offsetToCups = bin.ReadInt32();
                int offsetToBMG = bin.ReadInt32();
                byte[] modFolder = new byte[14];
                for (int i = 0; i < 14; i++)
                {
                    modFolder[i] = bin.ReadByte();
                }
                parameters.modFolderName = System.Text.Encoding.UTF8.GetString(modFolder).TrimStart('/').TrimEnd('\0');

                //INFO Reading
                bin.BaseStream.Position = offsetToInfo;
                ReadInfo(bin);

                //CUPS reading
                bin.BaseStream.Position = offsetToCups;
                ReadCups(bin);
                
                //BMG reading
                bin.BaseStream.Position = offsetToBMG;
                int bmgSize = ReadBMG(bin);
               
                //FILE reading
                bin.BaseStream.Position = offsetToBMG + bmgSize;
                ReadFile(bin);
                bin.Close();

                RequestBMGAction(false);
                using StreamReader bmgSR = new StreamReader("temp/BMG.txt");
                using StreamReader fileSR = new StreamReader("temp/files.txt");

                ParseBMGAndFILE(bmgSR, fileSR);
                bmgSR.Close();
                fileSR.Close();

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
                MessageBox.Show("Bin successfully imported.");
            }
            catch
            {
                bin.Close();
                MessageBox.Show("Invalid Bin File.");
            }
            finally
            {
                Directory.Delete("temp/", true);
            }
        }
        private void OnImportBinClick(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog();
            if (openFile.ShowDialog() == true)
            {
                using BigEndianReader bin = new BigEndianReader(File.Open(openFile.FileName, FileMode.Open));
                ImportPulsarBin(bin);
            }
        }

        private void ReadInfo(BigEndianReader bin)
        {
            UInt32 infoMagic = bin.ReadUInt32();
            UInt32 infoVersion = bin.ReadUInt32();
            if (infoMagic != 0x494E464F || infoVersion != INFOVERSION) throw new Exception();
            bin.BaseStream.Position += 8; //datasize + roomKey
            parameters.prob100cc = bin.ReadInt32();
            parameters.prob150cc = bin.ReadInt32();
            parameters.probMirror = 100 - (parameters.prob100cc + parameters.prob150cc);
            parameters.wiimmfiRegion = bin.ReadInt32();
            parameters.trackBlocking = bin.ReadInt32();
            parameters.hasTTTrophies = bin.ReadBoolean();
            parameters.has200cc = bin.ReadBoolean();
            parameters.hasUMTs = bin.ReadBoolean();
            parameters.hasFeather = bin.ReadBoolean();
            parameters.hasMegaTC = bin.ReadBoolean();
        }

        private void ReadCups(BigEndianReader bin)
        {
            UInt32 cupMagic = bin.ReadUInt32();
            UInt32 cupVersion = bin.ReadUInt32();
            if (cupMagic != 0x43555053 || cupVersion != CUPSVERSION) throw new Exception();
            bin.BaseStream.Position += 4;
            
            cups.Clear();
            ctsCupCount = bin.ReadUInt16();
            parameters.regsMode = bin.ReadByte();
            bin.BaseStream.Position += 1;     
            for (int i = 0; i < 4; i++)
            {
                trophyCount[i] = bin.ReadUInt16();
            }
            for (int i = 0; i < ctsCupCount; i++)
            {
                cups.Add(new Cup(bin));
            }
        }
        private int ReadBMG(BigEndianReader bin)
        {
            UInt64 bmgMagic = bin.ReadUInt64();
            if (bmgMagic != 0x4D455347626D6731) throw new Exception();
            int bmgSize = bin.ReadInt32();
            bin.BaseStream.Position -= 12;
            using BigEndianWriter bmg = new BigEndianWriter(File.Create("temp/bmg.bmg"));
            bmg.Write(bin.ReadBytes(bmgSize));
            bmg.Close();
            return bmgSize;
        }

        private void ReadFile(BigEndianReader bin)
        {
            UInt32 fileMagic = bin.ReadUInt32();
            if (fileMagic != 0x46494C45) throw new Exception();
            bin.BaseStream.Position -= 4;
            using BigEndianWriter file = new BigEndianWriter(File.Create("temp/files.txt"));
            file.Write(bin.ReadBytes((int)bin.BaseStream.Length));
            file.Close();
        }

        private bool BuildBinImpl()
        {
            if (dateSelector.SelectedDate == null)
            {
                MessageBox.Show("Please select a date.");
                TabController.SelectedItem = Options;
                ((TabItem)TabController.SelectedItem).Focus();
                return false;
            }
            if (parameters.modFolderName == null || parameters.modFolderName == "")
            {
                MessageBox.Show("Please specify a mod folder name.");
                TabController.SelectedItem = Options;
                ((TabItem)TabController.SelectedItem).Focus();
                return false;
            }
            if (parameters.wiimmfiRegion == -1)
            {
                MessageBox.Show("Please specify a Wiimmfi region.");
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
                    MessageBox.Show("Mod Folder is already in use.");
                    return false;
                }
            }
            Directory.CreateDirectory("output");
            Directory.CreateDirectory(modFolder);
            Directory.CreateDirectory($"{modFolder}/Binaries");
            Directory.CreateDirectory($"{modFolder}/Tracks");
            Directory.CreateDirectory($"{modFolder}/Ghosts");
            Directory.CreateDirectory("output/Riivolution");
            Directory.CreateDirectory("temp/");

            File.WriteAllBytes("temp/BMG.txt", parameters.has200cc ? PulsarRes.BMG200 : PulsarRes.BMG100);
            using StreamWriter bmgSW = new StreamWriter("temp/BMG.txt", true);
            using StreamWriter fileSW = new StreamWriter("temp/files.txt");
            using StreamWriter crcToFile = new StreamWriter($"{modFolder}/Ghosts/FolderToTrackName.txt");
            using BigEndianWriter bin = new BigEndianWriter(File.Create("temp/Pulsar.bin"));
            bmgSW.WriteLine(bmgSW.NewLine);
            bmgSW.WriteLine($"  {0x2847:X}    = Version created {date}");
            fileSW.WriteLine("FILE");

            bin.Write(0x50554C53); //"PULS"
            bin.Write(BINVERSION);

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
            bool ret = WriteCups(bin, bmgSW, fileSW, crcToFile);
            if (!ret)
            {
                bin.Close();
                bmgSW.Close();
                fileSW.Close();
                crcToFile.Close();
                MessageBox.Show("Failed Creating Cups");
                Directory.Delete($"{modFolder}", true);
                Directory.Delete("temp", true);
                return false;
            }
            bmgSW.Close();
            fileSW.Close();
            crcToFile.Close();
            RequestBMGAction(true);

            using BigEndianReader bmgReader = new BigEndianReader(File.Open("temp/bmg.bmg", FileMode.Open));
            long bmgPosition = RoundUp(bin.BaseStream.Position, 4); ; //BMG Offset
            bin.BaseStream.Position = 0x10;
            bin.Write((int)bmgPosition);
            bin.BaseStream.Position = bmgPosition;
            bin.Write(bmgReader.ReadBytes((int)bmgReader.BaseStream.Length));
            using BigEndianReader fileReader = new BigEndianReader(File.Open("temp/files.txt", FileMode.Open));
            bin.Write(fileReader.ReadBytes((int)fileReader.BaseStream.Length));
            bin.Close();

            char[] delims = new[] { '\r', '\n' };
            string[] xml = PulsarRes.XML.Split(delims, StringSplitOptions.RemoveEmptyEntries);

            xml[3] = xml[3].Replace("{$pack}", parameters.modFolderName);
            xml[6] = xml[6].Replace("{$pack}", parameters.modFolderName);
            xml[11] = xml[11].Replace("{$pack}", parameters.modFolderName);
            xml[14] = xml[14].Replace("{$pack}", parameters.modFolderName);
            xml[19] = xml[19].Replace("{$pack}", parameters.modFolderName);
            xml[24] = xml[24].Replace("{$pack}", parameters.modFolderName);
            xml[25] = xml[25].Replace("{$pack}", parameters.modFolderName);
            xml[26] = xml[26].Replace("{$pack}", parameters.modFolderName);
            xml[27] = xml[27].Replace("{$pack}", parameters.modFolderName);
            xml[30] = xml[30].Replace("{$pack}", parameters.modFolderName);
            xml[34] = xml[34].Replace("{$pack}", parameters.modFolderName);
            xml[35] = xml[34].Replace("{$pack}", parameters.modFolderName);
            xml[36] = xml[35].Replace("{$pack}", parameters.modFolderName);

            bmgReader.Close();
            fileReader.Close();
            File.Copy("temp/Pulsar.bin", $"{modFolder}/Binaries/Pulsar.bin", true);
            File.WriteAllLines($"output/Riivolution/{parameters.modFolderName}.xml", xml);
            Directory.Delete("temp/", true);
            MessageBox.Show("Pack Created");
            return true;
        }

        private void OnBuildBinClick(object sender, RoutedEventArgs e)
        {
            BuildBinImpl();
        }
        private void OnBuildFullPackClick(object sender, RoutedEventArgs e)
        {
            bool ret = BuildBinImpl();
            if (ret)
            {
                string modFolder = $"output/{parameters.modFolderName}";
                File.WriteAllBytes($"{modFolder}/Binaries/P.bin", PulsarRes.P);
                File.WriteAllBytes($"{modFolder}/Binaries/E.bin", PulsarRes.E);
                File.WriteAllBytes($"{modFolder}/Binaries/J.bin", PulsarRes.J);
                File.WriteAllBytes($"{modFolder}/Binaries/K.bin", PulsarRes.K);
                Directory.CreateDirectory($"{modFolder}/Assets");
                File.WriteAllBytes($"{modFolder}/Binaries/Loader.bin", PulsarRes.Loader);
                File.WriteAllBytes($"{modFolder}/Assets/PulsarUI.szs", PulsarRes.PulsarUI);
                File.WriteAllBytes($"{modFolder}/Assets/PulsarRace.szs", PulsarRes.PulsarRace);
                File.WriteAllBytes($"{modFolder}/Assets/PulsarCommon.szs", PulsarRes.PulsarCommon);
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

        private bool WriteCups(BigEndianWriter bin, StreamWriter bmgSW, StreamWriter fileSW, StreamWriter crcToFile)
        {
            bin.Write(0x43555053); //CUPS
            bin.Write(CUPSVERSION);
            long sizePosition = bin.BaseStream.Position;
            bin.Write(0);
            bin.Write(ctsCupCount);
            bin.Write(parameters.regsMode);
            bin.BaseStream.Position += 1; //padding
            for (int i = 0; i < 4; i++)
            {
                UInt16 count = parameters.hasTTTrophies ? trophyCount[i] : (UInt16)0;
                bin.Write(count);
            }

            bool ret = true;
            for (int id = 0; id < ctsCupCount; id++)
            {
                Cup cup = cups[id];
                ret = WriteCup(cup, bin, bmgSW, fileSW, crcToFile, false);
                if (!ret) return false;
            }
            if (ctsCupCount % 2 == 1)
            {
                UInt32 idx = cups[0].idx;
                cups[0].idx = ctsCupCount;
                ret = WriteCup(cups[0], bin, bmgSW, fileSW, crcToFile, true);
                cups[0].idx = idx;
            }
            long curPosition = bin.BaseStream.Position;
            bin.BaseStream.Position = sizePosition;
            bin.Write((int)(curPosition - sizePosition - 4));
            bin.BaseStream.Position = curPosition;
            return ret;
        }
        private bool WriteCup(Cup cup, BigEndianWriter bin, StreamWriter bmgSW, StreamWriter fileSW, StreamWriter crcToFile, bool isFake)
        {
            string modFolder = $"output/{parameters.modFolderName}";
            UInt32 idx = cup.idx;
            string[] fileInfo = Directory.GetFiles("input/");
            fileInfo = fileInfo.Select(s => s.ToLowerInvariant()).ToArray();
            bin.Write(idx);
            for (int i = 0; i < 4; i++)
            {
                string name = cup.fileNames[i];
                string curFile = $"input/{name}.szs".ToLowerInvariant();
                if (!fileInfo.Contains(curFile))
                {
                    MessageBox.Show($"Track {name} does not exist.");
                    return false;
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
                            string rkgName = $"input/{expertName}.rkg".ToLowerInvariant();
                            if (!fileInfo.Contains(rkgName))
                            {
                                MessageBox.Show($"Expert ghost {expertName}.rkg does not exist.");
                                return false;
                            }                       
                            using BigEndianReader rkg = new BigEndianReader(File.Open(rkgName, FileMode.Open));
                            rkg.BaseStream.Position = 0xC;
                            UInt16 halfC = rkg.ReadUInt16();
                            UInt16 newC = (UInt16)((halfC & ~(0x7F << 2)) + (0x26 << 2)); //change ghostType to expert

                            rkg.BaseStream.Position = 0;
                            byte[] rkgBytes = rkg.ReadBytes((int)(rkg.BaseStream.Length - 4)); //-4 to remove crc32
                            Directory.CreateDirectory($"{crc32Folder}/{ttModeFolders[expert]}");
                            using BigEndianWriter finalRkg = new BigEndianWriter(File.Create($"{crc32Folder}/{ttModeFolders[expert]}/expert.rkg"));
                            rkgBytes[0xC] = (byte)(newC >> 8);
                            rkgBytes[0xD] = (byte)(newC & 0xFF);
                            finalRkg.Write(rkgBytes);
                            int rkgCrc32 = BitConverter.ToInt32(System.IO.Hashing.Crc32.Hash(rkgBytes), 0);
                            finalRkg.Write(rkgCrc32);
                        }
                    }

                }


                bmgSW.WriteLine($"  {0x20000 + idx * 4 + i:X}    = {cup.trackNames[i]}");
                bmgSW.WriteLine($"  {0x30000 + idx * 4 + i:X}    = {cup.authorNames[i]}");
                fileSW.WriteLine($"{idx * 4 + i:X}={cup.fileNames[i]}|" +
                $"{cup.expertFileNames[i, 0]}|{cup.expertFileNames[i, 1]}|{cup.expertFileNames[i, 2]}|{cup.expertFileNames[i, 3]}");
            }
            return true;
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
                        else if (bmgId >= 0x20000 && bmgId < 0x60000)
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
                                    case (0x20000):
                                        cups[cupIdx].trackNames[trackIdx] = content;
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
                curLine = fileSR.ReadLine();
            }
        }
    }

}
