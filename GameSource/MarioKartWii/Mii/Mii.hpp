#ifndef _MII_
#define _MII_
#include <kamek.hpp>
#include <core/rvl/RFL/RFL.hpp>
#include <core/rvl/gx/GX.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/System/ScnRfl.hpp>
#include <MarioKartWii/System/Random.hpp>
#include <MarioKartWii/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

enum MiiId { //simply charId - 6
    MIIID_S_A_MALE   =  MII_S_A_MALE - 6,
    MIIID_S_A_FEMALE =  MII_S_A_FEMALE - 6,
    MIIID_S_B_MALE   =  MII_S_B_MALE - 6,
    MIIID_S_B_FEMALE =  MII_S_B_FEMALE - 6,
    MIIID_S_C_MALE   =  MII_S_C_MALE - 6,
    MIIID_S_C_FEMALE =  MII_S_C_FEMALE - 6,
    MIIID_M_A_MALE   =  MII_M_A_MALE - 6,
    MIIID_M_A_FEMALE =  MII_M_A_FEMALE - 6,
    MIIID_M_B_MALE   =  MII_M_B_MALE - 6,
    MIIID_M_B_FEMALE =  MII_M_B_FEMALE - 6,
    MIIID_M_C_MALE   =  MII_M_C_MALE - 6,
    MIIID_M_C_FEMALE =  MII_M_C_FEMALE - 6,
    MIIID_L_A_MALE   =  MII_L_A_MALE - 6,
    MIIID_L_A_FEMALE =  MII_L_A_FEMALE - 6,
    MIIID_L_B_MALE   =  MII_L_B_MALE - 6,
    MIIID_L_B_FEMALE =  MII_L_B_FEMALE - 6,
    MIIID_L_C_MALE   =  MII_L_C_MALE - 6,
    MIIID_L_C_FEMALE =  MII_L_C_FEMALE - 6
};

enum MiiBuild {
    MII_SMALL_BUILD,
    MII_MEDIUM_BUILD, //if (104 - height) > build
    MII_HEAVY_BUILD   //if (150 - height) > build
};

enum MiiType {
    MII_TYPE_OFFICIAL = 0,
    MII_TYPE_DEFAULT = 3,
    MII_TYPE_USER = 6,
    MII_TYPE_COPY = 7
};

class Mii {
public:

    Mii() {}
    virtual ~Mii(); //80529034 vtable 808b3148
    void Init(u32 type); //80525f88 could be reset
    static bool ComputeRFLStoreData(RFL::StoreData& dest, const RFL::CreateID* createId); //8052758c
    static bool IsMiiId(CharacterId character); //805275ec
    static bool GetMiiId(const RFL::CreateID* createId, u32* r4, u16* id); //80527604
    void Load(RFL::IDX rflId, u32 r5); //80526020 rflId == 0 leads to empty mii
    bool InitMiddleDB(RFL::IDX rflId, u32 r5, u32 type); //80526460

    //rflId stored to idx if type == 3, presumably normal mii
    bool GetRFLArgs(RFL::IDX rflIdx, u32 r5, u32 type, RFL::MiddleDB* dbDest, RFL::DataSource* sourceDest, RFL::IDX* idxDest); //80526460
    nw4r::g3d::ScnRfl* CreateScnRfl(EGG::Allocator* allocator, RFL::Resolution resolution, u32 expressionFlag,
        nw4r::g3d::ScnRfl* copyFrom, u32 sizeUserData); //8052663c copies copyFrom CharInfo if not null

    u32 type;
    u8 rflIdx; //0x8
    u8 padding[2];
    RFL::DataSource source; //0xc some kind of rfl param GetMiiId matches that
    RFL::StoreData rawStoreMii; //0x10 used when the mii was loaded from the official store (player miis) or a file (rkg, etc...)
    RFL::MiddleDB* middleDB; //0x5c
    GX::Color rflToGXFavoriteColor; //0x60
    RFL::FavoriteColor favoriteColor; //0x64
    RFL::AdditionalInfo info; //0x68
    bool isLoaded; //0xa4
    bool isUserMii;
    u8 unknown_0xa6[2]; //0xa6
    MiiBuild weight; //0xa8
    u8 unknown_0xac[0xae - 0xac]; //0xac
    u8 unknown_0xae; //0xae
    u8 padding2; //0xaf
    u32 unknown_0xb0[2];
}; //total size 0xB8
size_assert(Mii, 0xb8);

class MiiManagerSub {
public:
    MiiManagerSub(); //80526d3c
    virtual ~MiiManagerSub(); //80526d54 vtable 808b3160
    void* middleDBBuffer; //0x4
    RFL::MiddleDB middleDB; //0x8
    u16 unknown_0x20;
    u8 padding[2];
};
size_assert(MiiManagerSub, 0x24);

struct MiiCreationParams {
    struct Sub {

    };
    virtual ~MiiCreationParams(); //806b8f4c vtable 808c2368

    void Init(u16 r4, u8 r5, u8 r6, u8 r7, u8 r8, u32 r9, bool isGameChar); //805297e4
    void Reset(); //80529824

    u16 r4;
    u8 r5;
    u8 r6;
    u8 r7;
    u8 r8; //0x9
    u8 padding[3];
    u32 r9;
    bool isGameChar; //0x10
    u8 unknown_0x11[13];
    u8 unknown_0x1E[13];
    u8 unknown_0x2B[13];
    u8 unknown_0x38[14];
    u8 unknown_0x52[14];
    u8 padding2; //0x5F
}; //0x60

class MiiManager {
    enum Status {
        STATUS_OK
    };
    static MiiManager* sInstance; //809bd710
    static MiiManager* CreateInstance(); //80526bfc
    MiiManager(); //80526c80
    void Init(EGG::Heap* heap); //80526d94
    static Status GetStatus(); //805276e0

    Mii* CreateStoreMii(const RFL::CreateID* id, EGG::Heap* heap); //80527b0c for official miis
    Mii* CreateOfficialMii(RFL::IDX rflIdx, EGG::Heap* heap); //80527d60 checks that id is valid and will return nullptr if it isn't
    Mii* CreateDefaultMii(RFL::IDX rflId, EGG::Heap* heap); //80527f84
    Mii* CreateMii(const RFL::StoreData* storeData, EGG::Heap* heap); //80529330
    Mii* CreateMii(MiiCreationParams* params, Random* random, EGG::Heap* heap); //805287bc
    Mii* CreateRandomMii(EGG::Heap* heap, MiiCreationParams* params, Random* random); //805282b0
    RFL::MiddleDB& GetMiddleDB3(); //80527514

    EGG::TDisposer<MiiManager> disposer; //80526b64 vtable 808b316c
    virtual ~MiiManager(); //80527158 vtable 808b3154
    void* buffer;
    RFL::Res* res;
    u32 resSize; //0x1C
    void* middleDBBuffers[2]; //0x20
    void* middleDBBuffers2[3]; //0x28
    void* middleDBBuffers3; //0x34
    void* middleDBBuffers4[12]; //0x38

    RFL::MiddleDB middleDB[2]; //0x68
    RFL::MiddleDB middleDB2[3]; //0x98
    RFL::MiddleDB middleDB3; //0xe0
    RFL::MiddleDB middleDB4[12]; //0xf8
    MiiManagerSub subs[2]; //0x218
    u8 middleDBSize[2]; //0x260
    u8 unknown_0x262[0x268 - 0x262]; //0x262
    Status status; //0x268 status?
    EGG::Heap* heap; //0x26c
    u8 unknown_0x270[0x2f0 - 0x270];
    Random random; //0x2f0
};
size_assert(MiiManager, 0x308);
#endif