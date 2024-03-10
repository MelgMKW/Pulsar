using Pulsar_Pack_Creator;
using System;
using System.Linq;
using System.Runtime.InteropServices;

public class PulsarGame
{
    public class MarioKartWii
    {
        public static readonly string[] idxToAbbrev =
        {
            "LC", "MMM", "MG", "TF",
            "MC","CM","DKS","WGM",
            "DC","KC","MT","GV",
            "DDR","MH","BC","RR",
            "rPB","rYF","rGV2","rMR",
            "rSL","rSGB","rDS","rWS",
            "rDH","rBC3","rDKJP","rMC",
            "rMC3","rPG","rDKM","rBC",
            //"aBP","aDP","aFS","aCCW","aTD",
            //"arBC4","arBC3","arS","arCL","arTH"
        };

        public static readonly string[] idxToFullNames =
        {
            "Luigi Circuit", "Moo Moo Meadows", "Mushroom Gorge", "Toad's Factory",
            "Mario Circuit", "Coconut Mall", "DK Summit", "Wario's Gold Mine",
            "Daisy Circuit", "Koopa Cape", "Maple Treeway", "Grumble Volcano",
            "Dry Dry Ruins", "Moonview Highway", "Bowser's Castle", "Rainbow Road",
            "GCN Peach Beach", "DS Yoshi Falls", "SNES Ghost Valley 2", "N64 Mario Raceway",
            "N64 Sherbet Land", "GBA Shy Guy Beach", "DS Delfino Square", "GCN Waluigi Stadium",
            "DS Desert Hills", "GBA Bowser Castle 3", "N64 DK's Jungle Parkway", "GCN Mario Circuit",
            "SNES Mario Circuit 3", "DS Peach Gardens", "GCN DK Mountain", "N64 Bowser's Castle",
            //"Block Plaza", "Delfino Pier", "Funky Stadium", "Chain Chomp Wheel", "Thwomp Desert",
            //"SNES Battle Course 4", "GBA Battle Course 3", "N64 Skyscraper", "GCN Cookie Land", "DS Twilight House"
        };

        public static readonly byte[] idxToCourseId =
         {
            0x08,0x01,0x02,0x04,
            0x00,0x05,0x06,0x07,
            0x09,0x0f,0x0b,0x03,
            0x0e,0x0a,0x0c,0x0d,
            0x10,0x14,0x19,0x1a,
            0x1b,0x1f,0x17,0x12,
            0x15,0x1e,0x1d,0x11,
            0x18,0x16,0x13,0x1c,
            //0x21,0x20,0x23,0x22,0x24,
            //0x27,0x28,0x29,0x25,0x26
        };

        public static readonly string[] musicIdxToAbbrev =
        {
            "LC", "MMM", "MG", "TF",
            "MC","CM","DKS","WGM",
            "DC","KC","MT","GV",
            "DDR","MH","BC","RR",
            "rPB","rYF","rGV2","rMR",
            "rSL","rSGB","rDS","rWS",
            "rDH","rBC3","rDKJP","rMC",
            "rMC3","rPG","rDKM","rBC",
            "aBP","aDP","aFS","aCCW","aTD",
            "arBC4","arBC3","arS","arCL","arTH",
            "GC"
        };

        public static readonly string[] musicIdxToFullNames =
        {
            "Luigi Circuit", "Moo Moo Meadows", "Mushroom Gorge", "Toad's Factory",
            "Mario Circuit", "Coconut Mall", "DK Summit", "Wario's Gold Mine",
            "Daisy Circuit", "Koopa Cape", "Maple Treeway", "Grumble Volcano",
            "Dry Dry Ruins", "Moonview Highway", "Bowser's Castle", "Rainbow Road",
            "GCN Peach Beach", "DS Yoshi Falls", "SNES Ghost Valley 2", "N64 Mario Raceway",
            "N64 Sherbet Land", "GBA Shy Guy Beach", "DS Delfino Square", "GCN Waluigi Stadium",
            "DS Desert Hills", "GBA Bowser Castle 3", "N64 DK's Jungle Parkway", "GCN Mario Circuit",
            "SNES Mario Circuit 3", "DS Peach Gardens", "GCN DK Mountain", "N64 Bowser's Castle",
            "Block Plaza", "Delfino Pier", "Funky Stadium", "Chain Chomp Wheel", "Thwomp Desert",
            "SNES Battle Course 4", "GBA Battle Course 3", "N64 Skyscraper", "GCN Cookie Land", "DS Twilight House",
            "Galaxy Colosseum"
        };


        public static readonly byte[] musicIdxToCourseId =
        {
            0x08,0x01,0x02,0x04,
            0x00,0x05,0x06,0x07,
            0x09,0x0f,0x0b,0x03,
            0x0e,0x0a,0x0c,0x0d,
            0x10,0x14,0x19,0x1a,
            0x1b,0x1f,0x17,0x12,
            0x15,0x1e,0x1d,0x11,
            0x18,0x16,0x13,0x1c,
            0x21,0x20,0x23,0x22,0x24,
            0x27,0x28,0x29,0x25,0x26,
            0x36
        };

        public static readonly string[] regsGhostFolders =
        {
            "LC","MMM","MG","TF",
            "MC","CM","DKS","WGM",
            "DC","KC","MT","GV",
            "DDR","MH","BC","RR",
            "rPB","rYF","rGV","rMR",
            "rSL","SGB","rDS","rWS",
            "rDH","BC3","rDK","rMC",
            "MC3","rPG","DKM","rBC",
        };


        public enum CourseId : uint
        {
            COURSEID_NONE = 0xFFFFFFFF,

            LUIGI_CIRCUIT = 0x08,
            MOO_MOO_MEADOWS = 0x01,
            MUSHROOM_GORGE = 0x02,
            TOADS_FACTORY = 0x04,

            MARIO_CIRCUIT = 0x00,
            COCONUT_MALL = 0x05,
            DK_SUMMIT = 0x06,
            WARIOS_GOLD_MINE = 0x07,

            DAISY_CIRCUIT = 0x09,
            KOOPA_CAPE = 0x0F,
            MAPLE_TREEWAY = 0x0B,
            GRUMBLE_VOLCANO = 0x03,

            DRY_DRY_RUINS = 0x0E,
            MOONVIEW_HIGHWAY = 0x0A,
            BOWSERS_CASTLE = 0x0C,
            RAINBOW_ROAD = 0x0D,

            GCN_PEACH_BEACH = 0x10,
            DS_YOSHI_FALLS = 0x14,
            SNES_GHOST_VALLEY_2 = 0x19,
            N64_MARIO_RACEWAY = 0x1A,

            N64_SHERBET_LAND = 0x1B,
            GBA_SHY_GUY_BEACH = 0x1F,
            DS_DELFINO_SQUARE = 0x17,
            GCN_WALUIGI_STADIUM = 0x12,

            DS_DESERT_HILLS = 0x15,
            GBA_BOWSER_CASTLE_3 = 0x1E,
            N64_DKS_JUNGLE_PARKWAY = 0x1D,
            GCN_MARIO_CIRCUIT = 0x11,

            SNES_MARIO_CIRCUIT_3 = 0x18,
            DS_PEACH_GARDENS = 0x16,
            GCN_DK_MOUNTAIN = 0x13,
            N64_BOWSERS_CASTLE = 0x1C,

            BLOCK_PLAZA = 0x21,
            DELFINO_PIER = 0x20,
            FUNKY_STADIUM = 0x23,
            CHAIN_CHOMP_WHEEL = 0x22,
            THWOMP_DESERT = 0x24,

            SNES_BATTLE_COURSE_4 = 0x27,
            GBA_BATTLE_COURSE_3 = 0x28,
            N64_SKYSCRAPER = 0x29,
            GCN_COOKIE_LAND = 0x25,
            DS_TWILIGHT_HOUSE = 0x26,

            GALAXY_COLOSSEUM = 0x36,
            SUNSET_LUIGI_CIRCUIT = 0x3A,

            WINNING_DEMO = 0x37,
            LOSING_DEMO = 0x38,
            DRAW_DEMO = 0x39,
            NO_TRACK_SELECTED = 0x43,
            RANDOM = 0xFF
        }
        public enum KartId : uint
        {
            STANDARD_KART_S = 0x00,
            STANDARD_KART_M = 0x01,
            STANDARD_KART_L = 0x02,
            BABY_BOOSTER = 0x03,
            CLASSIC_DRAGSTER = 0x04,
            OFFROADER = 0x05,
            MINI_BEAST = 0x06,
            WILD_WING = 0x07,
            FLAME_FLYER = 0x08,
            CHEEP_CHARGER = 0x09,
            SUPER_BLOOPER = 0x0A,
            PIRANHA_PROWLER = 0x0B,
            RALLY_ROMPER = 0x0C,
            ROYAL_RACER = 0x0D,
            JETSETTER = 0x0E,
            BLUE_FALCON = 0x0F,
            SPRINTER = 0x10,
            HONEYCOUPE = 0x11,
            STANDARD_BIKE_S = 0x12,
            STANDARD_BIKE_M = 0x13,
            STANDARD_BIKE_L = 0x14,
            BULLET_BIKE = 0x15,
            MACH_BIKE = 0x16,
            BOWSER_BIKE = 0x17,
            BIT_BIKE = 0x18,
            BON_BON = 0x19,
            WARIO_BIKE = 0x1A,
            QUACKER = 0x1B,
            RAPIDE = 0x1C,
            SHOOTING_STAR = 0x1D,
            MAGIKRUISER = 0x1E,
            NITROCYCLE = 0x1F,
            SPEAR = 0x20,
            JET_BUBBLE = 0x21,
            DOLPHIN_DASHER = 0x22,
            PHANTOM = 0x23
        }

        public enum CharacterId : uint
        {
            MARIO = 0x00,
            BABY_PEACH = 0x01,
            WALUIGI = 0x02,
            BOWSER = 0x03,
            BABY_DAISY = 0x04,
            DRY_BONES = 0x05,
            BABY_MARIO = 0x06,
            LUIGI = 0x07,
            TOAD = 0x08,
            DONKEY_KONG = 0x09,
            YOSHI = 0x0A,
            WARIO = 0x0B,
            BABY_LUIGI = 0x0C,
            TOADETTE = 0x0D,
            KOOPA_TROOPA = 0x0E,
            DAISY = 0x0F,
            PEACH = 0x10,
            BIRDO = 0x11,
            DIDDY_KONG = 0x12,
            KING_BOO = 0x13,
            BOWSER_JR = 0x14,
            DRY_BOWSER = 0x15,
            FUNKY_KONG = 0x16,
            ROSALINA = 0x17,
            MII_S_A_MALE = 0x18,
            MII_S_A_FEMALE = 0x19,
            MII_S_B_MALE = 0x1A,
            MII_S_B_FEMALE = 0x1B,
            MII_S_C_MALE = 0x1C,
            MII_S_C_FEMALE = 0x1D,
            MII_M_A_MALE = 0x1E,
            MII_M_A_FEMALE = 0x1F,
            MII_M_B_MALE = 0x20,
            MII_M_B_FEMALE = 0x21,
            MII_M_C_MALE = 0x22,
            MII_M_C_FEMALE = 0x23,
            MII_L_A_MALE = 0x24,
            MII_L_A_FEMALE = 0x25,
            MII_L_B_MALE = 0x26,
            MII_L_B_FEMALE = 0x27,
            MII_L_C_MALE = 0x28,
            MII_L_C_FEMALE = 0x29,
            MII_M = 0x2A,
            MII_S = 0x2B,
            MII_L = 0x2C,
            PEACH_BIKER = 0x2D,
            DAISY_BIKER = 0x2E,
            ROSALINA_BIKER = 0x2F,
            CHARACTER_NONE = 0xFFFFFFFF
        }
    } //class Mario Kart Wii

    public static string[] ttModes = { "150cc:", "200cc:", "150cc Feather:", "200cc Feather:" };
    public static string[,] ttModeFolders = { { "150", "150Experts" }, { "200", "200Experts" }, { "150F", "150FeaExperts" }, { "200F", "200FeaExperts" } };


    [AttributeUsage(AttributeTargets.Field)]
    public class EndianAttribute : Attribute
    {
        public Endianness Endianness { get; private set; }

        public EndianAttribute(Endianness endianness)
        {
            this.Endianness = endianness;
        }
    }

    public enum Endianness
    {
        BigEndian,
        LittleEndian
    }

    private static void RespectEndianness(Type type, byte[] data, int offSet = 0)
    {
        var fields = type.GetFields().Where(f => f.IsDefined(typeof(EndianAttribute), false))
            .Select(f => new
            {
                Field = f,
                Attribute = (EndianAttribute)f.GetCustomAttributes(typeof(EndianAttribute), false)[0],
                Offset = Marshal.OffsetOf(type, f.Name).ToInt32()
            }).ToList();
        foreach (var field in fields)
        {
            if (field.Field.FieldType.IsArray)
            {
                //handle arrays, assuming fixed length
                object attr = field.Field.GetCustomAttributes(typeof(MarshalAsAttribute), false).FirstOrDefault();
                MarshalAsAttribute marshalAsAttribute = attr as MarshalAsAttribute;
                if (marshalAsAttribute == null || marshalAsAttribute.SizeConst == 0)
                    throw new NotSupportedException(
                        "Array fields must be decorated with a MarshalAsAttribute with SizeConst specified.");

                int arrayLength = marshalAsAttribute.SizeConst;
                Type elementType = field.Field.FieldType.GetElementType();
                int elementSize = Marshal.SizeOf(elementType);
                int arrayOffset = field.Offset + offSet;
                if (elementType.IsPrimitive)
                {
                    for (int i = 0; i < arrayLength; i++)
                    {
                        Array.Reverse(data, arrayOffset + i * elementSize, elementSize);
                    }                       
                }
                else for (int i = arrayOffset; i < arrayOffset + elementSize * arrayLength; i += elementSize)
                {
                    RespectEndianness(elementType, data, i);
                }
            }
            else if (!field.Field.FieldType.IsPrimitive) //or !field.Field.FiledType.GetFields().Length == 0
            {
                //handle nested structs
                RespectEndianness(field.Field.FieldType, data, field.Offset);
            }
            else
            {
                //handle primitive types
                Array.Reverse(data, offSet + field.Offset, Marshal.SizeOf(field.Field.FieldType));
            }
        }
    }

    public static T BytesToStruct<T>(byte[] rawData) where T : struct
    {
        T result = default(T);

        RespectEndianness(typeof(T), rawData);

        GCHandle handle = GCHandle.Alloc(rawData, GCHandleType.Pinned);

        try
        {
            IntPtr rawDataPtr = handle.AddrOfPinnedObject();
            result = (T)Marshal.PtrToStructure(rawDataPtr, typeof(T));
        }
        finally
        {
            handle.Free();
        }

        return result;
    }

    
    public static byte[] BytesFromStruct<T>(T structure, bool respectEndianness = true) where T : struct
    {
        int size = Marshal.SizeOf(structure);
        byte[] bytes = new byte[size];
        nint ptr = Marshal.AllocHGlobal(size);

        Marshal.StructureToPtr(structure, ptr, true);
        Marshal.Copy(ptr, bytes, 0, size);
        Marshal.FreeHGlobal(ptr);

        if (respectEndianness) RespectEndianness(typeof(T), bytes);

        return bytes;
    }


    public enum OSError : uint
    {
        OSERROR_DSI = 2,
        OSERROR_ISI = 3,
        OSERROR_FLOATING_POINT = 7,
        OSERROR_FPE = 8
    }

    public struct GPR
    {
        [Endian(Endianness.BigEndian)]
        public uint name;
        [Endian(Endianness.BigEndian)]
        public uint gpr;
    }

    public struct FPR
    {
        [Endian(Endianness.BigEndian)]
        public uint name;
        [Endian(Endianness.BigEndian)]
        public double fpr;
    }

    public struct StackFrame
    {
        [Endian(Endianness.BigEndian)]
        public uint spName;
        [Endian(Endianness.BigEndian)]
        public uint sp;
        [Endian(Endianness.BigEndian)]
        public uint lrName;
        [Endian(Endianness.BigEndian)]
        public uint lr;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct ExceptionFile
    {
        [Endian(Endianness.BigEndian)]
        public uint magic;
        [Endian(Endianness.BigEndian)]
        public uint region;
        [Endian(Endianness.BigEndian)]
        public uint reserved;
        [Endian(Endianness.BigEndian)]
        public uint error;
        [Endian(Endianness.BigEndian)]
        public GPR srr0;
        [Endian(Endianness.BigEndian)]
        public GPR srr1;
        [Endian(Endianness.BigEndian)]
        public GPR msr;
        [Endian(Endianness.BigEndian)]
        public GPR cr;
        [Endian(Endianness.BigEndian)]
        public GPR lr;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32), Endian(Endianness.BigEndian)]
        public GPR[] gprs;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32), Endian(Endianness.BigEndian)]
        public FPR[] fprs;
        [Endian(Endianness.BigEndian)]
        public FPR fpscr;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10), Endian(Endianness.BigEndian)]
        public StackFrame[] frames;
    }


    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct TimeEntry
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 0x4c)]
        public byte[] mii;
        [Endian(Endianness.BigEndian)]
        public uint rkgCRC32;
        [Endian(Endianness.BigEndian)]
        public ushort minutes;
        public byte seconds;
        public byte padding;
        [Endian(Endianness.BigEndian)]
        public ushort milliseconds;
        public byte isActive;
        public byte padding2;
        [Endian(Endianness.BigEndian)]
        public uint character;
        [Endian(Endianness.BigEndian)]
        public uint kart;
        [Endian(Endianness.BigEndian)]
        public uint controller;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct Leaderboard
    {
        [Endian(Endianness.BigEndian)]
        public uint magic;
        [Endian(Endianness.BigEndian)]
        public uint version;
        [Endian(Endianness.BigEndian)]
        public uint crc32;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 48)]
        public string trackName;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public byte[] hasTrophy;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public uint[] reserved;
        [Endian(Endianness.BigEndian), MarshalAs(UnmanagedType.ByValArray, SizeConst = 44)]
        public TimeEntry[] entries;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct SectionHeader
    {
        [Endian(Endianness.BigEndian)]
        public uint magic;
        [Endian(Endianness.BigEndian)]
        public uint version;
        [Endian(Endianness.BigEndian)]
        public uint dataSize; //size without the header
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct BinaryHeader
    {
        public BinaryHeader(uint magic, int curVersion)
        {
            this.magic = magic;
            version = curVersion;
        }

        [Endian(Endianness.BigEndian)]
        public uint magic;
        [Endian(Endianness.BigEndian)]
        public int version;
        [Endian(Endianness.BigEndian)]
        public Int32 offsetToInfo; //from start of the header
        [Endian(Endianness.BigEndian)]
        public Int32 offsetToCups;
        [Endian(Endianness.BigEndian)]
        public Int32 offsetToBMG;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string modFolderName;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct Info
    {
        [Endian(Endianness.BigEndian)]
        public uint roomKey; //transmitted to other players
        [Endian(Endianness.BigEndian)]
        public uint prob100cc;
        [Endian(Endianness.BigEndian)]
        public uint prob150cc;
        [Endian(Endianness.BigEndian)]
        public int wiimmfiRegion;
        [Endian(Endianness.BigEndian)]
        public uint trackBlocking;
        public byte hasTTTrophies;
        public byte has200cc;
        public byte hasUMTs;
        public byte hasFeather;
        public byte hasMegaTC;
        [Endian(Endianness.BigEndian)]
        public ushort cupIconCount;
        [Endian(Endianness.BigEndian)]
        public ushort chooseNextTrackTimer;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
        public byte[] reservedSpace;
    }
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct InfoHolder
    {
        public InfoHolder(uint magic, uint curVersion)
        {
            this.header.magic = magic;
            this.header.version = curVersion;
        }

        [Endian(Endianness.BigEndian)]
        public SectionHeader header;
        [Endian(Endianness.BigEndian)]
        public Info info;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct Track
    {
        public byte slot;
        public byte musicSlot;
        [Endian(Endianness.BigEndian)]
        public uint crc32;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct CupV1
    {
        public CupV1(MainWindow.Cup uiCup, uint[] crc32)
        {
            tracks = new Track[4];
            idx = uiCup.idx;
            for (int i = 0; i < 4; i++) {             
                tracks[i].slot = uiCup.slots[i];
                tracks[i].musicSlot = uiCup.musicSlots[i];
                tracks[i].crc32 = crc32[i];
            }            
        }
        [Endian(Endianness.BigEndian)]
        public uint idx;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4), Endian(Endianness.BigEndian)]
        public Track[] tracks;
    }  

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct CupsV1
    {
        [Endian(Endianness.BigEndian)]
        public ushort ctsCupCount;
        public byte regsMode;
        public byte padding;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4), Endian(Endianness.BigEndian)]
        public ushort[] trophyCount;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1), Endian(Endianness.BigEndian)]
        public CupV1[] cupsArray; //CUPS
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct CupsHolderV1
    {
        public CupsHolderV1(uint magic, uint curVersion)
        {
            this.header.magic = magic;
            this.header.version = curVersion;
        }

        [Endian(Endianness.BigEndian)]
        public SectionHeader header;
        [Endian(Endianness.BigEndian)]
        public CupsV1 cups;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct Config
    {
        [Endian(Endianness.BigEndian)]
        public BinaryHeader header;
        [Endian(Endianness.BigEndian)]
        public InfoHolder infoHolder;
        [Endian(Endianness.BigEndian)]
        public CupsHolder cupsHolder;
        //BMG rawBmg;
    }


    //V2
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct Cup
    {
        public Cup(MainWindow.Cup uiCup, uint[] crc32)
        {
            tracks = new Track[4];
            for (int i = 0; i < 4; i++)
            {
                tracks[i].slot = uiCup.slots[i];
                tracks[i].musicSlot = uiCup.musicSlots[i];
                tracks[i].crc32 = crc32[i];
            }
        }
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4), Endian(Endianness.BigEndian)]
        public Track[] tracks;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct Cups
    {
        [Endian(Endianness.BigEndian)]
        public ushort ctsCupCount;
        public byte regsMode;
        public byte padding;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4), Endian(Endianness.BigEndian)]
        public ushort[] trophyCount;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1), Endian(Endianness.BigEndian)]
        public Cup[] cupsArray; //CUPS
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct CupsHolder
    {
        public CupsHolder(uint magic, uint curVersion)
        {
            this.header.magic = magic;
            this.header.version = curVersion;
        }

        [Endian(Endianness.BigEndian)]
        public SectionHeader header;
        [Endian(Endianness.BigEndian)]
        public Cups cups;
    }
}