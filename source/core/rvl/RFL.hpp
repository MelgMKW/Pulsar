#ifndef _RFL_
#define _RFL_
#include <types.hpp>
#include <core/rvl/MEM/MEMexpHeap.hpp>

//Riivolution Face Library
namespace RFL {

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

struct MiddleDB {
    u8 unknown[0x18];
};

typedef u32 CreateID;
typedef u16 ID;

#pragma pack(push, 1)
struct StoreData { //http://wiibrew.org/wiki/Mii_data#Mii_format
    u16 invalid : 1; // doesn't seem to have any effect?
    u16 isGirl : 1;
    u16 month : 4;
    u16 day : 5;
    u16 favColor : 4;
    u16 isFavorite : 1;
    wchar_t miiName[10]; //0x2
    // addr: 0x16 - 0x17
    u8 height;
    u8 weight;
    // addr: 0x18 - 0x1B
    u8 miiID1;
    u8 miiID2;
    u8 miiID3;
    u8 miiID4;
    // addr: 0x1C through 0x1F
    u8 systemID0;
    u8 systemID1;
    u8 systemID2;
    u8 systemID3;
    // addr: 0x20 & 0x21
    u16 faceShape : 3;
    u16 skinColor : 3;
    u16 facialFeature : 4;
    u16 unknown1 : 3;
    u16 mingleOff : 1;
    u16 unknown2 : 1;
    u16 downloaded : 1;
    // addr: 0x22 & 0x23
    u16 hairType : 7;
    u16 hairColor : 3;
    u16 hairPart : 1;
    u16 unknown3 : 5;
    // addr: 0x24 through 0x27
    u32 eyebrowType : 5;
    u32 unknown4 : 1;
    u32 eyebrowRotation : 4;
    u32 unknown5 : 6;
    u32 eyebrowColor : 3;
    u32 eyebrowSize : 4;
    u32 eyebrowVertPos : 5;
    u32 eyebrowHorizSpacing : 4;
    // addr: 0x28 through 0x2B
    u32 eyeType : 6;
    u32 unknown6 : 2;
    u32 eyeRotation : 3;
    u32 eyeVertPos : 5;
    u32 eyeColor : 3;
    u32 unknown7 : 1;
    u32 eyeSize : 3;
    u32 eyeHorizSpacing : 4;
    u32 unknown8 : 5;
    // addr: 0x2C & 0x2D
    u16 noseType : 4;
    u16 noseSize : 4;
    u16 noseVertPos : 5;
    u16 unknown9 : 3;
    // addr: 0x2E & 2F
    u16 lipType : 5;
    u16 lipColor : 2;
    u16 lipSize : 4;
    u16 lipVertPos : 5;
    // addr: 0x30 & 0x31
    u16 glassesType : 4;
    u16 glassesColor : 3;
    u16 unknown10 : 1;
    u16 glassesSize : 3;
    u16 glassesVertPos : 5;
    // addr: 0x32 & 33
    u16 mustacheType : 2;
    u16 beardType : 2;
    u16 facialHairColor : 3;
    u16 mustacheSize : 4;
    u16 mustacheVertPos : 5;
    // addr: 0x34 & 0x35
    u16 moleOn : 1;
    u16 moleSize : 4;
    u16 moleVertPos : 5;
    u16 moleHorizPos : 5;
    u16 unknown11 : 1;
    wchar_t creatorName[10]; //0x36
    u16 crc16;
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

extern Manager* manager; //80383568
u32 GetWorkSize(u32 r3); //800bbb80
u32 RFLInitRes(Manager* managerBuffer, Res* res, u32 resSize, u32 r6); //800bbf10
u32 Init(Manager* managerBuffer, Res* res, u32 resSize, u32 r6); //800bbba0
BOOL RFLAvailable(); //800bc370
void* iAlloc(u32 size); //800bc3b0
void* iAlloc32(u32 size); //800bc3b0
void iFree(void* block); //800bc3d0
DBManager* iGetDBManager(); //800bc3e0
HDBManager* iGetHDBManager(); //800bc400
Loader* iGetLoader(); //800bc420
BOOL iGetWorking(); //800bc440
Manager* iGetManager(); //800bc470
u32 RFLWaitAsync(); //800bc540
const char* GetArcFilePath(); //800bc6e0 https://wiki.tockdom.com/wiki/RFL_Res.dat_(File_Format)

bool IsAvailableOfficialData(); //800c7290
u32 GetAdditionalInfo(u32 r3, u32 r4, u32 r5, u32 r6); //800cb7e0
u32 GetMiddleDBBufferSize(u32 size); //800c8850
void InitMiddleDB(MiddleDB* middleDB, u32 r4, void* buffer, u32 r6); //800c8860
BOOL UpdateMiddleDBAsync(MiddleDB* middleDB); //800c9550
BOOL iUpdateMiddleDBAsync(MiddleDB* middleDB, u32 r4, u32 r5); //800c95b0
u32 GetMiddleDBStoredSize(MiddleDB* middleDB); //800c9710
void SetMiddleDBRandomMask(MiddleDB* middleDB, u8 r4, u8 r5, u8 r6); //800c97c0
void SetMiddleDBHiddenMask(MiddleDB* middleDB, u8 hiddenMask); //800c97e0


BOOL SearchOfficialData(CreateID createId, ID* id); //80527b5c idx is filled
BOOL GetStoreData(StoreData* dest, u32 r4, ID id); //800c7df0




}//namespace RFL



#endif