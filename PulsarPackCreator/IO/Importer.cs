using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;


namespace Pulsar_Pack_Creator.IO
{
    class Importer : IOBase
    {
        public Importer(MainWindow window, in byte[] raw) : base(window)
        {
            cups = window.cups;
            this.raw = raw;
            regsExperts = window.regsExperts;
        }

        readonly byte[] raw;
        List<MainWindow.Cup> cups;
        public new ushort ctsCupCount { get; private set; }
        uint configVersion;
        uint cupVersion;
        public string date { get; private set; }
        public string[,,] regsExperts { get; private set; }

        public Result ImportV3()
        {
            PulsarGame.BinaryHeader header = PulsarGame.BytesToStruct<PulsarGame.BinaryHeader>(raw.ToArray());

            //Read HEADER
            parameters.modFolderName = header.modFolderName.TrimStart('/');

            Result ret;
            //INFO Reading
            ret = ReadInfo(CreateSubCat<PulsarGame.InfoHolder>(raw, header.offsetToInfo));
            if (ret != Result.Success) return ret;

            //CUPS reading
            ret = ReadCups(CreateSubCat<PulsarGame.CupsHolderV3>(raw, header.offsetToCups));
            if (ret != Result.Success) return ret;

            nint tracksOffset = header.offsetToCups
                + Marshal.OffsetOf(typeof(PulsarGame.CupsHolderV3), "totalVariantCount")
                + Marshal.SizeOf(typeof(int));
            nint trackSize = Marshal.SizeOf(typeof(PulsarGame.TrackV3));
            nint variantsOffset = tracksOffset + trackSize * ctsCupCount * 4;
            nint variantSize = Marshal.SizeOf(typeof(PulsarGame.Variant));

            PulsarGame.TrackV3[] curCup = new PulsarGame.TrackV3[4];
            PulsarGame.Variant[] variants = new PulsarGame.Variant[8]; //max 8 variants
            for (int i = 0; i < ctsCupCount; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    curCup[j] = CreateSubCat<PulsarGame.TrackV3>(raw, (int)tracksOffset);
                    for (int k = 0; k < curCup[j].variantCount; k++)
                    {
                        variants[k] = CreateSubCat<PulsarGame.Variant>(raw, (int)variantsOffset);
                        variantsOffset += variantSize;
                    }
                    tracksOffset += trackSize;
                }
                ReadCup(curCup, variants);

            }

            //BMG reading
            int bmgSize;
            ret = ReadBMG(raw.Skip(header.offsetToBMG).Take(raw.Length - header.offsetToBMG).ToArray(), out bmgSize);
            if (ret != Result.Success) return ret;

            //FILE reading
            ret = ReadFile(raw.Skip(header.offsetToBMG + bmgSize).Take(raw.Length - header.offsetToBMG).ToArray());
            if (ret != Result.Success) return ret;

            RequestBMGAction(false);
            using StreamReader bmgSR = new StreamReader("temp/BMG.txt");
            using StreamReader fileSR = new StreamReader("temp/files.txt");

            ParseBMGAndFILE(bmgSR, fileSR);

            return Result.Success;
        }

        public Result Import()
        {

            try
            {
                PulsarGame.BinaryHeader header = PulsarGame.BytesToStruct<PulsarGame.BinaryHeader>(raw.ToArray());
                //PulsarGame.InfoHolder infoHolder = CreateSubCat<PulsarGame.InfoHolder>(raw, header.offsetToInfo);
                //PulsarGame.CupsHolder cupsHolder = CreateSubCat<PulsarGame.CupsHolder>(raw, header.offsetToCups);

                //Read HEADER
                configVersion = (uint)Math.Abs(header.version);
                if (header.magic != configMagic || header.version > CONFIGVERSION) return Result.InvalidConfigFile;

                Result ret = Result.UnknownError;
                if (configVersion == 1) ret = ImportV1();
                else if (configVersion == 2) ret = ImportV2();
                else ret = ImportV3();

                return ret;
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
        }

        private Result ReadInfo(PulsarGame.InfoHolder raw)
        {
            uint magic = raw.header.magic;
            uint infoVersion = raw.header.version;
            if (magic != infoMagic || infoVersion != INFOVERSION) return Result.BadInfo;

            PulsarGame.Info info = raw.info;
            parameters.prob100cc = info.prob100cc;
            parameters.prob150cc = info.prob150cc;
            parameters.probMirror = 100 - (parameters.prob100cc + parameters.prob150cc);
            parameters.wiimmfiRegion = info.wiimmfiRegion;
            parameters.trackBlocking = info.trackBlocking;
            parameters.hasTTTrophies = info.hasTTTrophies == 1 ? true : false;
            parameters.has200cc = info.has200cc == 1 ? true : false;
            parameters.hasUMTs = info.hasUMTs == 1 ? true : false;
            parameters.hasFeather = info.hasFeather == 1 ? true : false;
            parameters.hasMegaTC = info.hasMegaTC == 1 ? true : false;
            int timer = info.chooseNextTrackTimer;
            parameters.chooseNextTrackTimer = (byte)(timer == 0 ? 10 : timer);
            return Result.Success;
        }

        private Result ReadCups(PulsarGame.CupsHolderV3 raw)
        {
            uint magic = raw.header.magic;
            cupVersion = raw.header.version;
            if (magic != cupsMagic || cupVersion > CUPSVERSION) return Result.BadCups;
            cups.Clear();
            //PulsarGame.Cups rawCups = raw.cups;
            ctsCupCount = raw.ctsCupCount;
            parameters.regsMode = raw.regsMode;
            return Result.Success;
        }
        private Result ReadCups(PulsarGame.CupsHolderV2 raw)
        {
            uint magic = raw.header.magic;
            cupVersion = raw.header.version;
            if (magic != cupsMagic || cupVersion > CUPSVERSION) return Result.BadCups;
            cups.Clear();
            PulsarGame.Cups rawCups = raw.cups;
            ctsCupCount = rawCups.ctsCupCount;
            parameters.regsMode = rawCups.regsMode;
            return Result.Success;
        }

        private Result ReadCups(PulsarGame.CupsHolderV1 raw)
        {
            uint magic = raw.header.magic;
            cupVersion = raw.header.version;
            if (magic != cupsMagic || cupVersion > CUPSVERSION) return Result.BadCups;
            cups.Clear();
            PulsarGame.CupsV1 rawCups = raw.cups;
            ctsCupCount = rawCups.ctsCupCount;
            parameters.regsMode = rawCups.regsMode;
            return Result.Success;
        }
        private void ReadCup(PulsarGame.TrackV3[] tracks, PulsarGame.Variant[] variants)
        {
            cups.Add(new MainWindow.Cup(tracks, variants));
        }
        private void ReadCup(PulsarGame.CupV2 raw)
        {
            cups.Add(new MainWindow.Cup(raw));
        }
        private void ReadCup(PulsarGame.CupV1 raw)
        {
            cups.Add(new MainWindow.Cup(raw));
        }

        private Result ReadBMG(byte[] raw, out int bmgSize)
        {
            bmgSize = 0;
            using (BigEndianReader bin = new BigEndianReader(new MemoryStream(raw)))
            {

                ulong magic = bin.ReadUInt64();
                if (magic != bmgMagic) return Result.BadBMG;
                bmgSize = bin.ReadInt32();
                bin.BaseStream.Position -= 12;
                using (BigEndianWriter bmg = new BigEndianWriter(File.Create("temp/bmg.bmg")))
                {
                    bmg.Write(bin.ReadBytes(bmgSize));
                }

                return Result.Success;
            }
        }

        private Result ReadFile(byte[] raw)
        {
            using (BigEndianReader bin = new BigEndianReader(new MemoryStream(raw)))
            {
                uint magic = bin.ReadUInt32();
                if (magic != fileMagic) return Result.BadFile;
                bin.BaseStream.Position -= 4;
                using (BigEndianWriter file = new BigEndianWriter(File.Create("temp/files.txt")))
                {
                    file.Write(bin.ReadBytes((int)bin.BaseStream.Length));
                }
            }
            return Result.Success;
        }


        private void ParseBMGAndFILE(StreamReader bmgSR, StreamReader fileSR)
        {
            bmgSR.ReadLine(); //#BMG
            string curLine = bmgSR.ReadLine();

            while (curLine != null)
            {
                if (curLine != "")
                {
                    uint bmgId;
                    bool ret = uint.TryParse(curLine.Substring(1, 5), NumberStyles.HexNumber, CultureInfo.InvariantCulture, out bmgId);
                    if (!ret)
                    {
                        ret = uint.TryParse(curLine.Substring(2, 4), NumberStyles.HexNumber, CultureInfo.InvariantCulture, out bmgId);
                    }
                    if (ret)
                    {
                        if (bmgId == 0x2847) date = curLine.Split(' ')[curLine.Split(' ').Length - 1];
                        else if (bmgId >= 0x10000 && bmgId < 0x60000)
                        {
                            string content = "";
                            try
                            {
                                content = curLine.Split('=')[1].TrimStart(' ');
                            }
                            catch
                            {
                                ret = false;
                            }
                            if (ret)
                            {
                                uint type = bmgId & 0xFFFF0000;
                                uint rest = bmgId & 0xFFFF;
                                uint variantIdx = (rest & 0xf000) >> 12;
                                int cupIdx = (int)(rest & 0xFFF) / 4;
                                if (cupIdx < ctsCupCount)
                                {
                                    int trackIdx = (int)(rest & 0xFFF) % 4;
                                    MainWindow.Cup.Track track = cups[cupIdx].tracks[trackIdx];
                                    switch (type)
                                    {
                                        case (uint)BMGIds.BMG_CUPS:
                                            if ((int)rest < ctsCupCount) cups[(int)rest].name = content;
                                            break;
                                        case (uint)BMGIds.BMG_TRACKS:
                                        case (uint)BMGIds.BMG_AUTHORS:
                                            {
                                                if (variantIdx >= 8)
                                                {
                                                    track.commonName = content;
                                                    break;
                                                }
                                                MainWindow.Cup.Track.Variant variant;
                                                if (variantIdx == 0)
                                                {
                                                    variant = track.main;
                                                }
                                                else
                                                {
                                                    variant = track.variants[(int)(variantIdx - 1)];
                                                }
                                                if (type == (uint)BMGIds.BMG_AUTHORS)
                                                {
                                                    variant.authorName = content;
                                                    break;
                                                }
                                                else
                                                {
                                                    if (content.Contains("\\c{red3}"))
                                                    {
                                                        string[] split = content.Split("\\c{red3}");
                                                        variant.trackName = split[0].Trim();
                                                        variant.versionName = split[1].Split("\\c{off}")[0];
                                                    }
                                                    else cups[cupIdx].tracks[trackIdx].main.trackName = content.Trim();
                                                }
                                            }
                                            break;
                                    }
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
                        if (uint.TryParse(split[0], NumberStyles.HexNumber, null, out uint idx))
                        {
                            if (split.Length > 1 && split[1] != "") cups[(int)idx].iconName = split[1];
                        }
                    }
                    else if (curLine.Contains("*"))
                    {
                        string[] split = curLine.Split("=");
                        if (uint.TryParse(split[0], NumberStyles.HexNumber, null, out uint id))
                        {
                            int cupIdx = (int)id / 4;
                            if (cupIdx < 8)
                            {
                                int trackIdx = (int)id % 4;
                                string[] names = split[1].Split("*");
                                if (names.Length > 0 && names.Length <= 4)
                                {
                                    for (int i = 0; i < names.Length; i++)
                                    {
                                        regsExperts[cupIdx, trackIdx, i] = names[i];
                                    }
                                }
                            }
                        }
                    }
                    else if (curLine.Contains("|"))
                    {
                        string[] split = curLine.Split("=");
                        if (uint.TryParse(split[0], NumberStyles.HexNumber, null, out uint id))
                        {
                            int cupIdx = (int)(id & 0xFFF) / 4;
                            int variantIdx = (int)(id & 0xf000) >> 12;
                            if (cupIdx < ctsCupCount)
                            {
                                int trackIdx = (int)(id & 0xFFF) % 4;
                                string[] names = split[1].Split("|");
                                if (names.Length > 0)
                                {
                                    if (variantIdx == 0)
                                    {
                                        cups[cupIdx].tracks[trackIdx].main.fileName = names[0];
                                        for (int i = 1; i < names.Length; i++)
                                        {
                                            cups[cupIdx].tracks[trackIdx].expertFileNames[i - 1] = names[i];
                                        }
                                    }
                                    else if (variantIdx <= 7) cups[cupIdx].tracks[trackIdx].variants[variantIdx - 1].fileName = names[0];
                                }
                            }
                        }
                    }
                }
                curLine = fileSR.ReadLine();
            }
        }

        public Result ImportV2()
        {
            PulsarGame.BinaryHeader header = PulsarGame.BytesToStruct<PulsarGame.BinaryHeader>(raw.ToArray());

            //Read HEADER
            parameters.modFolderName = header.modFolderName.TrimStart('/');

            Result ret;
            //INFO Reading
            ret = ReadInfo(CreateSubCat<PulsarGame.InfoHolder>(raw, header.offsetToInfo));
            if (ret != Result.Success) return ret;

            //CUPS reading
            ret = ReadCups(CreateSubCat<PulsarGame.CupsHolderV2>(raw, header.offsetToCups));
            if (ret != Result.Success) return ret;

            nint offset = header.offsetToCups + Marshal.OffsetOf(typeof(PulsarGame.CupsHolderV2), "cups") + Marshal.OffsetOf(typeof(PulsarGame.Cups), "cupsArray");
            nint size = Marshal.SizeOf(typeof(PulsarGame.CupV2));


            for (int i = 0; i < ctsCupCount; i++)
            {
                PulsarGame.CupV2 cup = CreateSubCat<PulsarGame.CupV2>(raw, (int)offset);
                ReadCup(cup);
                offset += size;
            }

            //BMG reading
            int bmgSize;
            ret = ReadBMG(raw.Skip(header.offsetToBMG).Take(raw.Length - header.offsetToBMG).ToArray(), out bmgSize);
            if (ret != Result.Success) return ret;

            //FILE reading
            ret = ReadFile(raw.Skip(header.offsetToBMG + bmgSize).Take(raw.Length - header.offsetToBMG).ToArray());
            if (ret != Result.Success) return ret;

            RequestBMGAction(false);
            using StreamReader bmgSR = new StreamReader("temp/BMG.txt");
            using StreamReader fileSR = new StreamReader("temp/files.txt");

            ParseBMGAndFILE(bmgSR, fileSR);

            return Result.Success;
        }
        public Result ImportV1()
        {
            PulsarGame.BinaryHeader header = PulsarGame.BytesToStruct<PulsarGame.BinaryHeader>(raw.ToArray());

            //Read HEADER
            parameters.modFolderName = header.modFolderName.TrimStart('/');

            Result ret;
            //INFO Reading
            ret = ReadInfo(CreateSubCat<PulsarGame.InfoHolder>(raw, header.offsetToInfo));
            if (ret != Result.Success) return ret;

            //CUPS reading
            ret = ReadCups(CreateSubCat<PulsarGame.CupsHolderV1>(raw, header.offsetToCups));
            if (ret != Result.Success) return ret;

            nint offset = header.offsetToCups + Marshal.OffsetOf(typeof(PulsarGame.CupsHolderV1), "cups") + Marshal.OffsetOf(typeof(PulsarGame.CupsV1), "cupsArray");
            nint size = Marshal.SizeOf(typeof(PulsarGame.CupV1));


            for (int i = 0; i < ctsCupCount; i++)
            {
                PulsarGame.CupV1 cup = CreateSubCat<PulsarGame.CupV1>(raw, (int)offset);
                ReadCup(cup);
                offset += size;
            }

            //BMG reading
            int bmgSize;
            ret = ReadBMG(raw.Skip(header.offsetToBMG).Take(raw.Length - header.offsetToBMG).ToArray(), out bmgSize);
            if (ret != Result.Success) return ret;

            //FILE reading
            ret = ReadFile(raw.Skip(header.offsetToBMG + bmgSize).Take(raw.Length - header.offsetToBMG).ToArray());
            if (ret != Result.Success) return ret;

            RequestBMGAction(false);
            using StreamReader bmgSR = new StreamReader("temp/BMG.txt");
            using StreamReader fileSR = new StreamReader("temp/files.txt");

            ParseBMGAndFILE(bmgSR, fileSR);

            return Result.Success;
        }

    }



}
