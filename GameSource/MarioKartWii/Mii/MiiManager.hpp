#ifndef _MII_MANAGER_
#define _MII_MANAGER_
#include <kamek.hpp>
#include <core/rvl/RFL/RFL.hpp>
#include <MarioKartWii/System/Random.hpp>
#include <MarioKartWii/Mii/Mii.hpp>
#include <MarioKartWii/Mii/MiiCreationParams.hpp>

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

class MiiManagerSub2 {
    u8 _[0x8];
};

class MiiManager {
    enum Status {
        STATUS_OK
    };
    static MiiManager* sInstance; //809bd710
    static MiiManager* CreateInstance(); //80526bfc
    MiiManager(); //80526c80
    void Init(EGG::Heap* heap); //80526d94
    static Status GetStatus(); //805276e0
    static bool IsOfficialOrDefaultMii(const RFL::CreateID* id); //80527700
    void CountOfficialMiis(); //80527298

    static bool AllowMiiDisplay(); //80528290

    Mii* CreateStoreMii(const RFL::CreateID* id, EGG::Heap* heap); //80527b0c for both default and official miis
    Mii* CreateOfficialMii(RFL::IDX rflIdx, EGG::Heap* heap); //80527d60 checks that id is valid and will return nullptr if it isn't
    Mii* CreateOfficialMii(const RFL::CreateID* id, EGG::Heap* heap); //80527e84 gets rflIdx from id, inlined in create store mii
    Mii* CreateDefaultMii(RFL::IDX rflIdx, EGG::Heap* heap); //80527f84
    Mii* CreateDefaultMii(const RFL::CreateID* id, EGG::Heap* heap); //880528068 gets rflIdx from id, inlined in create store mii

    Mii* CreateOfficialMii(EGG::Heap* heap, MiiCreationParams& params, Random* random, RFL::IDX* idxArray, u32 arrayLength); //8052816c the params are updated but not used

    Mii* CreateMii(const RFL::StoreData* storeData, EGG::Heap* heap); //80529330
    Mii* CreateMii(MiiCreationParams& params, Random* random, EGG::Heap* heap); //805287bc
    Mii* CreateMiddleDBMii(EGG::Heap& heap, MiiCreationParams& params, Random* random); //805282b0
    Mii* CreateRandomMii(EGG::Heap& heap, MiiCreationParams& params, Random* random); //80528598 random CreateID
    Mii* CreatePlayerMiiFromMiddleDB(u32 playerId, RFL::IDX rflId, EGG::Heap* heap); //80529640 rflId is essentially hudSlotId since this is how the playerMiddleDBs work
    Mii* CreatePlayerMiiFromOfficial(u32 playerId, EGG::Heap* heap); //80527778 copy createID from racedataplayer
    Mii* CreateMii(RFL::IDX rflIdx, u32 middleDBIdx, EGG::Heap* heap); //80529420 no checking is done
    Mii* CreateControllerMii(s32 channel, u8 index); //80529420
    Mii* CreateMiddleDB2Mii(MiiCreationParams2& params2, Random* random, EGG::Heap* heap); //80529074


    static void PrepareRFLWiFiPacket(RFL::WiFiPacket* packet, Mii& mii, u16 hudSlotId); //80529730
    bool RFLWiFiInfo2MiddleDB(RFL::MiddleDB* dest, const RFL::WiFiInformation* info, u16 aid, u32 hudSlotId); //80529748
    bool RFLWiFiInfo2StoreData(RFL::StoreData* dest, const RFL::WiFiInformation* info, u16 aid, u32 hudSlotId); //80529798

    RFL::MiddleDB& GetMiddleDB3(); //80527514



    EGG::TDisposer<MiiManager> disposer; //80526b64 vtable 808b316c
    virtual ~MiiManager(); //80527158 vtable 808b3154
    void* buffer;
    RFL::Res* res;
    u32 resSize; //0x1C
    void* middleDBStores[2]; //0x20
    void* middleDBStores2[3]; //0x28
    void* middleDBStores3; //0x34
    void* middleDBStores4[12]; //0x38

    RFL::MiddleDB middleDB[2]; //0x68
    RFL::MiddleDB middleDB2[3]; //0x98
    RFL::MiddleDB middleDB3; //0xe0
    RFL::MiddleDB playerMiddleDB[12]; //0xf8 one per player
    MiiManagerSub subs[2]; //0x218
    u8 middleDBStoredMiisCount[2]; //0x260
    u8 unknown_0x262[0x268 - 0x262]; //0x262
    Status status; //0x268 status?
    EGG::Heap* heap; //0x26c
    s8 officialMiiIdxs[100]; //0x270, the array is separated in half, first for non-favourite miis, then resets for favourite miis
    u32 officialMiisCount; //0x2d4
    u8 unknown_0x2d8[0x2f0 - 0x2d8];
    Random random; //0x2f0
};
size_assert(MiiManager, 0x308);

#endif