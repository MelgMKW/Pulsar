#ifndef _KMPCONTROLLER_
#define _KMPCONTROLLER_
#include <kamek.hpp>
#include <game/System/Archive.hpp>
#include <game/KMP/KMP.hpp>

/*
Contributors:
-kHacker35000vr (main documentation)
-Melg
*/

union SpeedModConv {
    float speedMod;
    u32 kmpValue;
};

namespace KMP {

template<class T, class Section>
struct SectionHolder {
    T **pointArray;
    u16 pointCount;
    u16 unknown_0x6;
    Section *rawSection;
};

struct Header {
    KMPHeader *rawKMP;
    u32 *offsetToSections;
    u32 versionNumber;
    u32 mainHeaderLength;
}; //total size 0x10

template<class T>
struct EntryHolder {
    T *raw;
};

struct KTPTHolder : EntryHolder<KTPT> {
    void CalcCoordinates_0Indexed(Vec3 &position, Vec3 &rotation, u32 playerPosition, u32 playerCount);
    void CalcCoordinates(Vec3 &position, Vec3 &rotation, u32 playerPosition, u32 playerCount); //80514b24
    u8 enemyLink;
    u8 unknown_0x5[3];
}; //total size 0x8

struct ENPHHolder : EntryHolder<ENPH> {
    u32 unknown_0x4;
    u32 unknown_0x8;
}; //total size 0x10

class ENPTHolder {
    virtual void func_vtable();
    ENPT *raw; //0x4
    u8 *prevLinks[6]; //0x8
    u8 *nextLinks[6]; //0xC
    u8 inCount; //0x10
    u8 outCount; //0x11
    u8 inCount2;
    u8 outCount2;
    u8 unknown_0x14[4];
}; //total size 0x18

struct ITPTHolder : EntryHolder<ITPT> {
    u8 prevLinks[6];
    u8 nextLinks[6];
    u8 inCount;
    u8 outCount;
    u8 unknown_0x12[2];
}; //total size 0x14

struct CKPTHolder : EntryHolder <CKPH> {
    u8 layer;
    u8 unknown_0x3;
    float invLength;
};

struct CKPHSectionHolder : SectionHolder<CKPTHolder, CKPH> {
    float invLayerSize;
};

struct CheckPoint {
    CKPT *raw;
    u16 nextCKTPTCount;
    u16 prevCKPTCount;
    float midpointX;
    float midpointZ;
    float boxProportions[2];
    u16 scanned;
    s16 id;
    u8 type;
    u8 unknown_0x1D[3];
    CheckPoint *prevCKPTs[6];
    CheckPoint *nextCKTPTs[6];
};

class AREAHolder {
public:
    virtual void vf_0x8(); //805163f4 vtable 808b2c54
    bool IsPointInAREA(Vec3 *position); //805160b0
    AREA *rawData;
    Vec3 xVector;
    Vec3 yVector;
    Vec3 zVector;
    float halfWidth;
    float height;
    float halfLength;
    float unknown_0x38[2];
    float radius;
    u16 id;
    u8 unknown_0x46[0x48 - 0x46];
}; //total size 0x48

struct AREASectionHolder : SectionHolder<AREAHolder, AREA> {
    AREAHolder **sortedArray;
}; //total size 0x14

struct JPGTHolder : EntryHolder<JGPT> {
    Vec3 rotation;
    Vec3 zScale;
    Vec3 xScale;
    u8 enemyLink;
    u8 itemLink;
    u16 range;
    u16 rangeScale;
    u16 unknown_0x2E;
}; //total size 0x30

typedef EntryHolder<ITPH> ITPHHolder;


typedef EntryHolder<POTI> POTIHolder;
typedef EntryHolder<CAME> CAMEHolder;
typedef EntryHolder<CNPT> CNPTHolder;
typedef EntryHolder<STGI> STGIHolder;
typedef EntryHolder<MSPT> MSPTHolder;

struct GOBJHolder : EntryHolder<GOBJ> {
    POTIHolder *GetRoute() const; //80514194
};

class Controller {
public:
    static Controller *sInstance;
    static Controller *GetStaticInstance(); //80512694
    static void DestroyStaticInstance(); //8051271c
    Controller(); //8051276c inlined
    virtual ~Controller(); //805127ac vtable 808B2C30
    void Init(); //805127ec
    POTIHolder *GetPOTIHolder(u32 idx) const; //80515e04
    GOBJHolder *GetGOBJHolder(u32 idx) const; //80514148
    AREAHolder *GetAREAHolder(u32 idx) const; //80516768
    KTPTHolder *GetKTPTHolder(u32 idx) const; //80514b30


    Header *header; //4
    SectionHolder<KTPTHolder, KTPT> *kartPoint;     //8
    SectionHolder<ENPHHolder, ENPH> *enemyGroup;    //c
    SectionHolder<ENPTHolder, ENPT> *enemyPoint;    //10
    SectionHolder<ITPHHolder, ITPH> *itemGroup;      //14
    SectionHolder<ITPTHolder, ITPT> *itemPoint;      //18
    CKPHSectionHolder *checkGroup;       //1c
    SectionHolder<CheckPoint, CKPT> *checkPoint;    //20
    SectionHolder<POTIHolder, POTI> *pointInfo;      //24
    SectionHolder<GOBJHolder, GOBJ> *gobj;           //28
    AREASectionHolder *area;                        //2c
    SectionHolder<CAMEHolder, CAME> *camera;
    SectionHolder<JPGTHolder, JGPT> *respawn;     //34
    SectionHolder<CNPTHolder, CNPT> *cannonPoint;  //38
    SectionHolder<STGIHolder, STGI> *stageInfo; //3c
    SectionHolder<MSPTHolder, MSPT> *missionSuccessPoint; //40
    CAMEHolder *goalCamera; //44
    CAMEHolder *msptCamera; //48
    CAMEHolder *openingCam; //4c
    u32 unknown_0x50; //50
};
size_assert(Controller, 0x54);

static KMPHeader *GetKMPFromU8(ArchiveSource source, const char *kmpName); //80512c10
}//namespace KMP



#endif
