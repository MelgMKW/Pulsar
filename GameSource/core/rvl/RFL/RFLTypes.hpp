#ifndef _RFL_TYPES_
#define _RFL_TYPES_
#include <types.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <core/rvl/MEM/MEMexpHeap.hpp>

//Revolution Face Library
namespace RFL {

enum ErrCode {
    RFLErrcode_Success 			= 0,
    RFLErrcode_NotAvailable,
    RFLErrcode_NANDCommandfail,
    RFLErrcode_Loadfail,
    RFLErrcode_Savefail,
    RFLErrcode_Fatal,
    RFLErrcode_Busy,
    RFLErrcode_Broken,
    RFLErrcode_Exist,
    RFLErrcode_DBFull,
    RFLErrcode_DBNodata,
    RFLErrcode_Controllerfail,
    RFLErrcode_NWC24Fail,
    RFLErrcode_MaxFiles,
    RFLErrcode_MaxBlocks,
    RFLErrcode_WrongParam,
    RFLErrcode_NoFriends,
    RFLErrcode_Isolation,
    RFLErrcode_Unknown			= 255
};

enum DataSource {
    RFLDataSource_Official, //table DB, store data, user miis are here
    RFLDataSource_Hidden,
    RFLDataSource_Controller1,
    RFLDataSource_Controller2,
    RFLDataSource_Controller3,
    RFLDataSource_Controller4,
    RFLDataSource_Default, //default player miis
    RFLDataSource_Middle, //middleDBStore
    RFLDataSource_Max
};

enum Resolution {
    RFLResolution_64	= 0x40,
    RFLResolution_128	= 0x80,
    RFLResolution_256	= 0x100,
    //M = mipmap
    RFLResolution_64M	= 0x60,
    RFLResolution_128M	= 0xe0,
    RFLResolution_256M	= 0x1e0
};

enum FavoriteColor {
    RFLFavoriteColor_Red,
    RFLFavoriteColor_Orange,
    RFLFavoriteColor_Yellow,
    RFLFavoriteColor_YellowGreen,
    RFLFavoriteColor_Green,
    RFLFavoriteColor_Blue,
    RFLFavoriteColor_SkyBlue,
    RFLFavoriteColor_Pink,
    RFLFavoriteColor_Purple,
    RFLFavoriteColor_Brown,
    RFLFavoriteColor_White,
    RFLFavoriteColor_Black,
    RFLFavoriteColor_Max
};

enum Expression {
    RFLExp_Normal = 0,
    RFLExp_Smile,
    RFLExp_Anger,
    RFLExp_Sorrow,
    RFLExp_Surprise,
    RFLExp_Blink,
    RFLExp_OpenMouth,

    RFLExp_Max
};

enum Sex {
    RFLSex_Male,
    RFLSex_Female,
    RFLSex_All
};

enum Age {
    RFLAge_Child,
    RFLAge_Adult,
    RFLAge_Elder,
    RFLAge_All
};

enum Race {
    RFLRace_Black,
    RFLRace_White,
    RFLRace_Asian,
    RFLRace_All
};

enum ExpressionFlag {
    RFLExpFlag_Normal = 0x1 << RFLExp_Normal,
    RFLExpFlag_Smile = 0x1 << RFLExp_Smile,
    RFLExpFlag_Anger = 0x1 << RFLExp_Anger,
    RFLExpFlag_Sorrow = 0x1 << RFLExp_Sorrow,
    RFLExpFlag_Surprise = 0x1 << RFLExp_Surprise,
    RFLExpFlag_Blink = 0x1 << RFLExp_Blink,
    RFLExpFlag_OpenMouth = 0x1 << RFLExp_OpenMouth
};

#pragma pack(push, 1)
struct CreateID {
    union {
        struct {
            u32 miiId;
            u32 systemId;
        };
        struct {
            u8 miiID0; //0x1a
            u8 miiID1;
            u8 miiID2;
            u8 miiID3;
            u8 systemID0; //0x1a
            u8 systemID1;
            u8 systemID2;
            u8 systemID3;
        };
    };
};
size_assert(CreateID, 0x8);
#pragma pack(pop)

typedef u16 IDX;

struct AdditionalInfo { //rlwinm (dolphin masks)
    wchar_t	name[11];       //0x0
    wchar_t	creator[11];    //0x16
    CreateID createID;      //0x2c
    u32	gender : 1;         //0x34    (1,31,31)
    u32	birth_month : 4;    //0x34:1  (5,28,31)
    u32	birth_day : 5;      //0x34:5  (10,28,31)
    u32	favoriteColor : 4;  //0x34:9  (14,28,31)
    u32	favorite : 1;       //0x34:13 (15,31,31)
    u32	height : 7;         //0x34:14 (22,25,31, 0x1fc)
    u32	build : 7;          //0x34:21 (29,25,31, 0x3f8)
    u32	reserved : 3;       //0x34:24
    GX::Color skinColor;    //0x38
}; //0x38

struct ResSection {
    u16 filesCount;
    u16 biggestFileSize;
    u32 offsetsToFiles[1]; //fileCount
    //u32 sectionSize;
};
struct Res { //https://wiki.tockdom.com/wiki/RFL_Res.dat_(File_Format)
    u16 sectionCount;
    u16 unknown_0x2;
    u32 offsetsToSections[1]; //sectionCount
    //ResSection sections[sectionCount];
};

struct DBManager {
    u8 unknown[0x4];
};

struct Loader {
    u8 unknown[0x4];
};
struct HDBManager {
    u8 unknown[0x4];
};

#pragma pack(push, 1)
struct StoreData { //http://wiibrew.org/wiki/Mii_data#Mii_format
    u16 invalid : 1; // doesn't seem to have any effect?
    u16 isGirl : 1;
    u16 month : 4;
    u16 day : 5;
    u16 favColor : 4;
    u16 isFavorite : 1;
    wchar_t miiName[10]; //0x2
    //addr: 0x16 - 0x17
    u8 height;
    u8 weight;
    //addr: 0x18 - 0x1B ultimately what constitude a RFL::CreateID
    RFL::CreateID createID; //0x18
    //addr: 0x20 & 0x21
    u16 faceShape : 3;
    u16 skinColor : 3;
    u16 facialFeature : 4;
    u16 unknown1 : 3;
    u16 mingleOff : 1;
    u16 unknown2 : 1;
    u16 downloaded : 1;
    //addr: 0x22 & 0x23
    u16 hairType : 7;
    u16 hairColor : 3;
    u16 hairPart : 1;
    u16 unknown3 : 5;
    //addr: 0x24 through 0x27
    u32 eyebrowType : 5;
    u32 unknown4 : 1;
    u32 eyebrowRotation : 4;
    u32 unknown5 : 6;
    u32 eyebrowColor : 3;
    u32 eyebrowSize : 4;
    u32 eyebrowVertPos : 5;
    u32 eyebrowHorizSpacing : 4;
    //addr: 0x28 through 0x2B
    u32 eyeType : 6;
    u32 unknown6 : 2;
    u32 eyeRotation : 3;
    u32 eyeVertPos : 5;
    u32 eyeColor : 3;
    u32 unknown7 : 1;
    u32 eyeSize : 3;
    u32 eyeHorizSpacing : 4;
    u32 unknown8 : 5;
    //addr: 0x2C & 0x2D
    u16 noseType : 4;
    u16 noseSize : 4;
    u16 noseVertPos : 5;
    u16 unknown9 : 3;
    //addr: 0x2E & 2F
    u16 lipType : 5;
    u16 lipColor : 2;
    u16 lipSize : 4;
    u16 lipVertPos : 5;
    //addr: 0x30 & 0x31
    u16 glassesType : 4;
    u16 glassesColor : 3;
    u16 unknown10 : 1;
    u16 glassesSize : 3;
    u16 glassesVertPos : 5;
    //addr: 0x32 & 33
    u16 mustacheType : 2;
    u16 beardType : 2;
    u16 facialHairColor : 3;
    u16 mustacheSize : 4;
    u16 mustacheVertPos : 5;
    //addr: 0x34 & 0x35
    u16 moleOn : 1;
    u16 moleSize : 4;
    u16 moleVertPos : 5;
    u16 moleHorizPos : 5;
    u16 unknown11 : 1;
    wchar_t creatorName[10]; //0x36
    u16 crc16; //0x4a
}; //total size 0x4C
size_assert(StoreData, 0x4c);
#pragma pack(pop)

struct Manager {

    void* startAddr;
    MEM::HeapHandle* expHeap; //0x4 size 0x620e0
    MEM::HeapHandle* expHeap2; //0x8 size 0x24800
    MEM::HeapHandle* userHeap; //0xC size remaining 1st heap
    DBManager dbManager; //0x10
    u8 unknown_0x14[0xc0 - 0x14];
    Loader loader; //0xc0
    u8 unknown_0xc4[0x16c - 0xc4];
    HDBManager hdbManager; //0x16c
    u8 unknown_0x170[0x1b34 - 0x170];
    BOOL working; //0x1B34
    MEM::iHeapHead heap; //0x1f20 start addr
    u8 heapBuffer[0x620A4]; //heap of size 0x620e0
};

struct WiFiInformation {
    u8 miiPerAid;
    u8 maxAid;
    u16 localAid;
    u32 unknown_0x4[2];
    void* buffer; //0xc just an array of WiFiPackets
};

struct WiFiPacket {
    u32 presentMiis; //bitfield
    u16 maxMiiCount; //0x4
    u16 unknown_0x6;
    RFL::StoreData rawMiis[2]; //0x8 technically not 2 but in mariokartwii, exclusively 2
}; //0xa0
size_assert(WiFiPacket, 0xa0);

}//namespace RFL



#endif