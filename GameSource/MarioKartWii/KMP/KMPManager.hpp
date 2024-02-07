#ifndef _KMPCONTROLLER_
#define _KMPCONTROLLER_
#include <kamek.hpp>
#include <MarioKartWii/Archive/ArchiveRoot.hpp>
#include <MarioKartWii/KMP/KMP.hpp>

/*
Contributors:
-kHacker35000vr (main documentation)
-Melg
*/

namespace KMP {

template<class T>
struct Holder {
    T* raw;
};

template<class T>
class Section {
public:
    Holder<T>** holdersArray;
    u16 pointCount; //0x4
    u16 padding; //0x6
    KMPBlock<T>* rawKMPBlock; //0x8
};

struct RawHolder {
    RawHolder(const KMPHeader& raw); //80512c2c
    u32 GetVersion() const; //80512c94
    const KMPHeader& rawKMP;
    u32* offsetToSections;
    u32 versionNumber;
    u32 headerSize;
}; //total size 0x10

template<>
class Holder<KTPT> {
public:
    void InitLinks(); //805148a0
    void CalcCoordinates_0Indexed(Vec3& position, Vec3& rotation, u32 playerPosition, u32 playerCount);
    void CalcCoordinates(Vec3& position, Vec3& rotation, u32 playerPosition, u32 playerCount); //80514b24
    KTPT* raw;
    u8 enemyLink; //0x4
    u8 padding[3];
}; //total size 0x8

template<>
class Holder<ENPH> {
public:
    void CalcExtremes(); //80514c30
    ENPH* raw;
    float lowestENPT;
    float highestENPT;
}; //total size 0x10

template<>
class Holder<ENPT> {
public:
    virtual ~Holder(); //80518c40 vtable 808b2c6c
    void InitLinks(u16 idx); //80516d74
    void AddPrevLink(u16 idx); //80517ce4 inlined
    void AddNextLink(u16 idx); //80517d38 inlined
    void AddLink(u16 idx); //80517d8c inlined
    ENPT* raw; //0x4
    u8* prevLinks; //0x8
    u8* nextLinks; //0xC
    u8 prevCount; //0x10
    u8 nextCount; //0x11
    u8 prevLinkArraySize;
    u8 nextLinksArraySize;
    u8 unknown_0x14[4];
}; //total size 0x18

template<>
class Holder<ITPT> {
public:
    void InitLinks(u16 idx); //80517e88
    ITPT* raw;
    u8 prevLinks[6];
    u8 nextLinks[6];
    u8 prevCount;
    u8 nextCount;
    u8 padding[2];
}; //total size 0x14

class CKPHSection;
template<>
class Holder<CKPH> {
public:
    void CalcDepthRecursive(u8 depth, const CKPHSection* section); //805150e0
    void Init(CKPH* raw); //80515098 inlined
    CKPH* raw;
    u8 depth; //0x4
    u8 unknown_0x5[3];
    float invLength; //0x8
};

struct LinkedCKPT {
    LinkedCKPT(); //805155e0
    ~LinkedCKPT(); //805155e4
    Holder<CKPT>* holder;
    Vec2 firstPointDiff;
    Vec2 secondPointDiff;
    float distance;
};

class CKPTSection;
template<>
class Holder<CKPT> {
public:
    Holder(const CKPT& raw); //805154e4
    void InitLinks(CKPTSection& section, u16 id); //80515624
    void SetTypeRecursive(u8 type); //80515a6c
    u32 CalcCompletion(const Vec3& playerPosition, Vec3& completion); //80510d7c fills completion
    u32 CalcExactFinishTime(const Vec2& playerPos, const Vec2& prevPlayerPos); //80511ec8 returns ms

    CKPT* raw;
    u16 nextCKTPTCount; //0x4
    u16 prevCKPTCount; //0x6
    Vec2 midPoint; //0x8
    float boxProportions[2]; //0x10
    u16 scanned; //0x18
    s16 id; //0x1a
    u8 type; //0x1c
    u8 unknown_0x1D[3]; //0x1d
    Holder* prevHolders[6];
    LinkedCKPT next[6]; //0x20
};

template<>
class Holder<AREA> {
public:
    Holder<AREA>(AREA* raw); //80516220
    virtual bool IsPointInAREAShape(const Vec3& subjectPosition); //805163f4 vtable 808b2c54
    bool IsPointInAREA(const Vec3& position); //805160b0 calls func above + a distance check
    void SetId(u16 id); //80512cac
    s8 GetRouteId(); //80516138
    Holder<POTI>* GetRoute(); //80516168
    AREA* raw; //0x4
    Vec3 xVector; //0x8
    Vec3 yVector; //0x14
    Vec3 zVector; //0x20
    float halfWidth; //0x24
    float height;
    float halfLength;
    float unknown_0x38[2];
    float radius; //0x40
    u16 id;
    u8 unknown_0x46[0x48 - 0x46];
}; //total size 0x48

template<>
class Holder<JGPT> {
public:
    Holder(const JGPT& raw); //805183a8
    void InitLinks(); //805184fc
    void GetPosition(Vec& dest, u8 playerId); //8051896c
    JGPT* raw;
    Vec3 rotation;
    Vec3 zScale;
    Vec3 xScale;
    u8 enemyLink;
    u8 itemLink;
    u16 userData;
    u16 rangeScale; //0x2a
    u16 unknown_0x2E;
}; //total size 0x30

template<>
class Holder<CAME> {
public:
    u8 GetType() const; //80512c6c
    s8 GetOpeningCamIdx() const; //80512c9c
    Holder<CAME> GetNext(); //80516cd4
    CAME* raw;
};

template<>
class Holder<STGI> {
public:
    bool IsNarrowGrid() const; //80512d40
    u32 GetLensFlareColor() const; //80512d4c
    u8 GetLensFlareAlpha() const; //80518bb0
    bool HasLensFlare() const; //80512d58
    STGI* raw;
};

template<>
class Holder<GOBJ> {
public:
    const Holder<POTI>* GetRoute() const; //80514194
    GOBJ* raw;
};


//SECTIONS
class KTPTSection : public Section<KTPT> {
public:
    static KTPTBlock* GetBlock(RawHolder* rawKMP, u32 ktptMagic); //80514208 inlined
    KTPTSection(KTPTBlock* raw); //80514258 inlined
    Holder<KTPT>* GetHolder(u16 idx); //80514124 part of section
};

class JGPTSection : public Section<JGPT> {
public:
    Holder<JGPT>* GetHolder(u16 idx) const; //80514100 part of Section
};

class CKPTSection : public Section<CKPT> {
public:
    void Init(); //80515244
    void CalcTotalDistance(); //80512370
    void CalcDistanceFromCPRecursive(u16 cpIdx); //80512064
    u8 lastCKPTIdx; //0xc
    u8 padding;
    u16 startCKPTIdx;
    float totalDistance; //0x10
};

class CKPHSection : public Section<CKPH> {
public:
    void Init(); //80514df0 inlined
    Holder<CKPH>* GetHolder(u16 cp); //80515014
    float invLayerSize;
};

class AREASection : public Section<AREA> {
public:
    AREASection(const AREABlock& rawBlock); //80515e50
    Holder<AREA>* GetHolder(u16 idx) const; //805140dc
    void SortByPriority(); //80515f8c
    Holder<AREA>** sortedPriorityArray; //0x10
}; //total size 0x14

class POTISection : public Section<POTI> {
public:
    POTISection(POTIBlock* raw); //80515d3c inlined
    Holder<POTI>* GetHolder(u16 idx); //80514124 part of section
};

typedef Section<ENPH> ENPHSection;
typedef Section<ENPT> ENPTSection;
typedef Section<ITPH> ITPHSection;
typedef Section<ITPT> ITPTSection;
typedef Section<GOBJ> GOBJSection;
typedef Section<CAME> CAMESection;
typedef Section<CNPT> CNPTSection;
typedef Section<STGI> STGISection;
typedef Section<MSPT> MSPTSection;

class Manager {
public:
    static Manager* sInstance;
    static Manager* CreateInstance(); //80512694
    static void DestroyInstance(); //8051271c

    Manager(); //8051276c inlined
    virtual ~Manager(); //805127ac vtable 808B2C30
    void Init(); //805127ec
    static KMPHeader* GetRawKMP(ArchiveSource source, const char* kmpName); //80512c10

    Section<STGI>* ParseSTGI(u32 stgiMagic) const; //80512d64
    Section<MSPT>* ParseMSPT(u32 msptMagic) const; //80512e84
    Section<CNPT>* ParseCNPT(u32 cnptMagic) const; //80512fa4
    JGPTSection* ParseJGPT(u32 jgptMagic) const; //805130c4
    Section<CAME>* ParseCAME(u32 cameMagic) const; //805131e4
    AREASection* ParseAREA(u32 areaMagic) const; //80513304
    Section<POTI>* ParsePOTI(u32 potiMagic) const; //80513398
    Section<GOBJ>* ParseGOBJ(u32 gobjMagic) const; //805134c8
    CKPTSection* ParseCKPT(u32 ckptMagic) const; //80513640
    CKPHSection* ParseCKPH(u32 ckphMagic) const; //8051377c
    Section<ITPT>* ParseITPT(u32 itptMagic) const; //80513adc
    Section<ITPH>* ParseITPH(u32 itphMagic) const; //80513bfc
    Section<ENPT>* ParseENPT(u32 enptMagic) const; //80513d18
    Section<ENPH>* ParseENPH(u32 enphMagic) const; //80513e40
    KTPTSection* ParseKTPT(u32 ktptMagic)  const; //80513f5c

    u16 GetCAMECount() const; //80512c78
    u16 GetAREACount() const; //80512cb4
    u16 GetENPTCount() const; //80512cd0
    u16 GetITPTCount() const; //80512cec
    u16 GetJGPTCount() const; //80512d08
    u16 GetKTPTCount() const; //80512d24

    template<class T>
    Holder<T>* GetHolder(u16 idx) const;
    /*
        80514148 = GOBJ
        80514b30 = KTPT
        80514b7c = ENPT
        80514bc8 = ENPH
        80514d3c = ITPT
        80514d88 = ITPH
        80515c24 = CKPT
        80515c70 = CKPH
        80515e04 = POTI
        80516768 = AREA
        80516bb0 = CAME
        80518920 = JGPT
        80518ae0 = CNPT
        80518b2c = MSPT

    */
    Holder<STGI>* GetSTGIHolder() const;       //80518b78

    s16 CalcNextCP(u8 playerId, const Vec3& playerPosition, u32 curCP, float& completion, bool isOnline); //80511500 fills completion
    s16 CalcNextCPRecursive(u8 playerId, const Vec& playerPosition, u32 depth, bool r7, Holder<CKPT>* ckptSection,
        float& completion, u16 flags); //80511110

    void ResetCKPTScannedState() const; //80511e00

    u32 CalcExactFinishTime(u16 cpIdx, const Vec3& playerPos, const Vec3& prevPlayerPos); //80511e7c returns ms



    Holder<CKPH>* GetCKPHHolderByCP(u16 cpIdx); //80515cbc

    Holder<AREA>* GetAREAHolderByPriority(u8 priority) const; //805167b4
    s16 FindAREA(const Vec& position, u32 areaIdToTestFirst, u8 areaType); //80516808 if areaIdToTest is not -1, will test it first
    bool GetMiniMapAREAParams(Vec3& bottomleft, Vec& topRight); //80516a60
    Holder<CAME>* GetCAMEHolderFromAREAId(u16 areaIdx); //80516bfc

    s8 GetNextENPTCount(const u8& curENPT); //8051760c
    s8 GetNextENPT(const u8& curENPT, u8 linkIdx); //80517590
    s8 GetPrevENPTCount(const u8& curENPT); //805176ec
    s8 GetPrevENPT(const u8& curENPT, u8 linkIdx); //80517670
    void ToggleENPH(u8 enphId, bool isActivated); //80517750 used by eline to "turn off" a given ENPH
    u8 GetNextITPT(const u8& curItpt, u8 linkIdx); //805181f0 
    u8 GetITPTNextCount(const u8& itpt); //80518268
    u8 GetPrevITPT(const u8& curitpt, u8 linkIdx); //805182cc
    u8 GetITPTPrevCount(const u8& itpt); //80518344


    RawHolder* rawHolder;     //0x4
    KTPTSection* ktptSection; //0x8
    ENPHSection* enphSection; //0xc
    ENPTSection* enptSection; //0x10
    ITPHSection* itphSection; //0x14
    ITPTSection* itptSection; //0x18
    CKPHSection* ckphSection; //0x1c
    CKPTSection* ckptSection; //0x20
    POTISection* potiSection; //0x24
    GOBJSection* gobjSection; //0x28
    AREASection* areaSection; //0x2c
    CAMESection* cameSection; //0x30
    JGPTSection* jgptSection; //0x34
    CNPTSection* cnptSection; //0x38
    STGISection* stgiSection; //0x3c
    MSPTSection* msptSection; //0x40
    Holder<CAME>* goalCAME;   //0x44
    Holder<CAME>* msptCAME;   //0x48
    Holder<CAME>* openingCAME;//0x4c
    u32 unknown_0x50;         //0x50


    static float startGridWidth; //808b2c20
    static float startGridRowLength; //808b2c24
    static float startGridSlotLength; //808b2c28
    static const u32 ktptMagic = 'KTPT';
    static const u32 enphMagic = 'ENPH';
    static const u32 enptMagic = 'ENPT';
    static const u32 itphMagic = 'ITPH';
    static const u32 itptMagic = 'ITPT';
    static const u32 ckphMagic = 'CKPH';
    static const u32 ckptMagic = 'CKPT';
    static const u32 gobjMagic = 'GOBJ';
    static const u32 potiMagic = 'POTI';
    static const u32 areaMagic = 'AREA';
    static const u32 cameMagic = 'CAME';
    static const u32 jgptMagic = 'JGPT';
    static const u32 cnptMagic = 'CNPT';
    static const u32 msptMagic = 'MSPT';
    static const u32 stgiMagic = 'STGI';


};
size_assert(Manager, 0x54);


}//namespace KMP



#endif
