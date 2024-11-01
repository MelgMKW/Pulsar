#ifndef _MII_
#define _MII_
#include <kamek.hpp>
#include <core/rvl/RFL/RFL.hpp>
#include <core/rvl/gx/GX.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/System/ScnRfl.hpp>
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
    MII_TYPE_PLAYERMIDDLEDB = 1,
    MII_TYPE_CONTROLLER = 2,
    MII_TYPE_DEFAULT = 3,
    MII_TYPE_MIDDLEDB1 = 5,
    MII_TYPE_MIDDLEDB2 = 5,
    MII_TYPE_USER = 6,
    MII_TYPE_COPY = 7
};

class Mii { //online, rflId is hudSlotId and middleDBIdx is aid
public:
    Mii() {}
    virtual ~Mii(); //80529034 vtable 808b3148
    void Init(u32 type); //80525f88 could be reset
    static bool ComputeRFLStoreData(RFL::StoreData& dest, const RFL::CreateID* createId); //8052758c
    static bool IsMiiId(CharacterId character); //805275ec
    static bool GetMiiId(const RFL::CreateID* createId, u32* r4, u16* id); //80527604
    void Load(RFL::IDX rflIdx, u32 middleDBIdx); //80526020 rflId == 0 leads to empty mii

    //rflId stored to idx if type == 3, presumably normal mii, middleDBIdx is most often playerId
    bool GetRFLArgs(RFL::IDX rflIdx, u32 middleDBIdx, MiiType type, RFL::MiddleDB* dbDest, RFL::DataSource* sourceDest, RFL::IDX* idxDest); //80526460
    nw4r::g3d::ScnRfl* CreateScnRfl(EGG::Allocator* allocator, RFL::Resolution resolution, u32 expressionFlag,
        nw4r::g3d::ScnRfl* copyFrom, u32 sizeUserData); //8052663c copies copyFrom CharInfo if not null

    MiiType type;
    u8 rflIdx; //0x8
    u8 playerId; //0x9 only set for online non-local players?
    u8 padding[2];
    RFL::DataSource source; //0xc
    RFL::StoreData rawStoreMii; //0x10 used when the mii was loaded from the official store (player miis) or a file (rkg, etc...)
    RFL::MiddleDB* middleDB; //0x5c
    GX::Color rflToGXFavoriteColor; //0x60
    RFL::FavoriteColor favoriteColor; //0x64
    RFL::AdditionalInfo info; //0x68 CreateID at 0x94 (info + 0x2c)
    bool isLoaded; //0xa4
    bool isUserMii; //0xa5
    u8 unknown_0xa6[2]; //0xa6
    MiiBuild weight; //0xa8
    u8 unknown_0xac[0xae - 0xac]; //0xac
    u8 unknown_0xae; //0xae
    u8 padding2; //0xaf
    u32 unknown_0xb0[2];
}; //total size 0xB8
size_assert(Mii, 0xb8);

#endif