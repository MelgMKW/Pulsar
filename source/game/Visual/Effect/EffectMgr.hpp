#ifndef _EFFECT_
#define _EFFECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <core/egg/Effect/EffectResource.hpp>
#include <core/egg/mem/Heap.hpp>
#include <game/Visual/Model/ModelDirector.hpp>
#include <game/Visual/Effect/PlayerEffects.hpp>

/*
Contributors:
-Melg
*/

//duplicated effects are for each side/wheels
//https://wiki.tockdom.com/wiki/BREFF_(File_Format)

enum RaceEffects {
    rk_crash, //0x1f0
    rk_wave, //0x1f4
    rk_uchiage, //0x1f8
    rk_slipStreamPre, //0x1fc
    rk_slipStream, //0x200
    rk_star, //0x204
    rk_killer, //0x208
    rk_killer1T, //0x20C
    rk_thunder, //0x210
    rk_kaminariGumo, //0x214
    rk_thunderBiri, //0x218
    rk_thunderBiri_2, //0x21C
    rk_epropellerBiri, //0x220
    rk_kurokoge, //0x224
    rk_effect_0x228, //0x228
    rk_kyodai, //0x22C
    rk_pow, //0x230
    rk_pow1, //0x234
    rk_powUp, //0x238
    rk_powReduce, //0x23C
    rk_niseBoxBiri, //0x240
    rk_niseBoxVan, //0x244
    rk_niseBox, //0x248
    rk_pochaWaterMini, //0x24C
    rk_effect_0x250,
    rk_effect_0x254,
    rk_startMiss, //0x258
    rk_effect_0x25c,
    rk_spinHalfL, //0x260
    rk_spinL,
    rk_spinHalfL_2, //0x268
    rk_spinL_2,
    rk_crashWater, //0x270
    rk_spinWaterHalf, //0x274
    rk_spinWater, //0x278
    rk_itemBox, //0x27C
    rk_housiJmp, //0x280
    rk_jumpSeikou, //0x284
    rk_jumpTailB, //0x288
    rk_effect_0x28c,
    rk_weedWall, //0x290
    rk_oil, //0x294
    rk_effect_0x298,
    rk_hitA, //0x29C
    rk_koukasen, //0x2A0
    rk_koukasenM, //0x2A4
    rk_koukasenS, //0x2A8
    //items dependent on how many local players
    rk_gessoA_1P, //0x2AC
    rk_gessoB_1P, //0x2b0
    rk_gessoA0_1P,
    rk_gessoB0_1P,
    rk_gessoC0_1P,
    rk_moyaW2D, //0x2C0
    rk_housi2D, //0x2C4
    rk_housi2Ddemo, //0x2C8
    rk_effect_0x2CC,
    rk_effect_0x2D0,
    rk_effect_0x2D4,
    rk_gasSmoke, //0x2D8
    rk_gasSmoke_2,
    rk_gasSmoke_3,
    rk_gasSmoke_4,
    rk_gasSmokeOneT, //0x2E8
    rk_gasSmokeOneT_2, //0x2EC
    rk_gasSmokeOneT_3, //0x2F0
    rk_gasSmokeOneT_4, //0x2F4
    rk_miniTurbo1T, //0x2F8
    rk_miniTurbo1T_2, //0x2FC
    rk_miniTurbo1T_3, //0x300
    rk_miniTurbo1T_4, //0x304
    rk_miniTurbo, //0x308
    rk_miniTurbo_2, //0x30C
    rk_miniTurbo_3, //0x310
    rk_miniTurbo_4, //0x314
    rkdirtSmokeA, //0x318
    rkdirtSmokeA_2, //0x31C
    rk_weed, //0x320
    rk_weed_2, //0x324
    rk_snowHDirt, //0x328 
    rk_water, //0x330
    rk_water_2, //0x334
    rk_snowRoad0, //0x338
    rk_snowRoad0_2, //0x33c
    rk_snowRoad1, //0x340
    rk_snowRoad1_2, //0x344
    rk_mud, //0x348
    rk_mud2, //0x34c
    rk_flower, //0x350
    rk_flower2, //0x354
    rk_stone, //0x358
    rk_stone2 //0x35C 
};

enum kartEffects {
    rk_jumpSmoke,
    rk_jumpSmokeMini,
    rk_wheelSpin0_L,
    rk_wheelSpin1_L,
    rk_wheelSpin2_L,
    rk_wheelSpin0_R,
    rk_wheelSpin1_R,
    rk_wheelSpin2_R,
};

enum bikeEffects {
    rk_jumpSmokeBikeL,
    rk_jumpSmokeBikeS,
    rk_jumpSmokeBikeS_2,
    rk_jumpSmokeBikeLMini,
    rk_wheelSpin0,
    rk_wheelSpin1,
    rk_wheelSpin2,
    rk_wheelie,
};

enum kartDriftEffects { //_L and _R aren't part of the actual emitter name
    rk_driftSmoke_L = 0,
    rk_driftSmoke_R = 1,
    rk_driftSpark1L_Spark00 = 2,
    rk_driftSpark1L_Spark01 = 3,
    rk_driftSpark1R_Spark00 = 4,
    rk_driftSpark1R_Spark01 = 5,
    rk_driftSpark2L_Spark00 = 6,
    rk_driftSpark2L_Spark01 = 7,
    rk_driftSpark2R_Spark00 = 8,
    rk_driftSpark2R_Spark01 = 9,
    rk_driftSpark1L1T_Chip00 = 10,
    rk_driftSpark1L1T_Spark00 = 11,
    rk_driftSpark1L1T_Spark01 = 12,
    rk_driftSpark1R1T_Chip00 = 13,
    rk_driftSpark1R1T_Spark00 = 14,
    rk_driftSpark1R1T_Spark01 = 15,
    rk_driftSpark2L1T_Chip00 = 16,
    rk_driftSpark2L1T_Spark00 = 17,
    rk_driftSpark2L1T_Spark01 = 18,
    rk_driftSpark2R1T_Chip00 = 19,
    rk_driftSpark2R1T_Spark00 = 20,
    rk_driftSpark2R1T_Spark01 = 21,
    rk_driftSpark1L_Chip00 = 22,
    rk_driftSpark1R_Chip00 = 23,
    rk_driftSpark2L_Chip00 = 24,
    rk_driftSpark2R_Chip00 = 25,
    rk_start0_L = 26,
    rk_start1_L = 27,
    rk_start2_L = 28,
    rk_start0_R = 29,
    rk_start1_R = 30,
    rk_start2_R = 31,
    rk_driftEffect_32 = 32,
    rk_driftEffect_33 = 33,
    rk_brakeSmk_L = 34,
    rk_brakeSmk_R = 35
};

enum bikeDriftEffects { //_L and _R aren't part of the actual emitter name
    rk_driftSmoke,
    rk_driftSpark1LB_Spark00,
    rk_driftSpark1LB_Spark01,
    rk_driftSpark1RB_Spark00,
    rk_driftSpark1RB_Spark01,
    rk_driftSpark1CB_Spark00,
    rk_driftSpark1CB_Spark01,
    rk_driftSpark1LB1T_Chip00,
    rk_driftSpark1LB1T_Spark00,
    rk_driftSpark1LB1T_Spark01,
    rk_driftSpark1RB1T_Chip00,
    rk_driftSpark1RB1T_Spark00,
    rk_driftSpark1RB1T_Spark01,
    rk_driftSpark1CB1T_Chip00,
    rk_driftSpark1CB1T_Spark00,
    rk_driftSpark1CB1T_Spark01,
    rk_driftSpark1LB_Chip00,
    rk_driftSpark1RB_Chip00,
    rk_hangOnL,
    rk_hangOnR,
    rk_hangOnLTail,
    rk_hangOnRTail,
    rk_start0,
    rk_start1,
    rk_start2,
    rk_brakeSmk,
    rk_driftEffect_27,
    rk_driftEffect_28,
};




class MenuEffects {
    MenuEffects(); //806ec7c8
    virtual ~MenuEffects(); //806ec914 vtable 808c7668
    EGG::Effect *GetEffectByIdx(u32 idx); //806ec994
    EGG::EffectResource *menuEffects; //0x4
    EGG::Effect *rk_cursors[4]; //0x8 has RKMenu BREFF and BREFT, EGG::Effects for all the relevant rk_ emitters
    EGG::Effect *effects[10];
}; //total size 0x58

class MGWhiteFogEffect { //rk_kinokoClouds
    MGWhiteFogEffect(); //8067b318
    virtual ~MGWhiteFogEffect(); //8067b388 vtable 808c0f20
    EGG::Effect *rk_kinokoClouds; //only if slot is MG
}; //total size 0x8

class ItemEffects {
    ItemEffects(); //8068cedc
    void CreateBananaEffect(const Mtx34 &mtx, float scale); //8068d848
    EGG::Effect **rk_kouraTailG; //length capacity 8068cfb8
    EGG::Effect **rk_kouraTailR; //length capacity
    EGG::Effect **rk_kouraTailB; //length capacity
    EGG::Effect **rk_bombHeiSpark; //length capacity 0xC
    EGG::Effect **rk_kaminariGumoPre; //length capacity 0x10
    EGG::Effect **rk_kaminariGumoVan; //length capacity 0x10
    EGG::Effect **rk_kaminariGumoVanS; //length capacity 0x10
    u32 greenShellCapacity; //0x1C
    u32 redShellCapacity;
    u32 blueShellCapacity; //+4 if online gamemode
    u32 bombCapacity; //0x28
    u32 tcCapacity; //0x2C
    bool unknown_0x30; //related to localplayercount //0x8068cf74
    bool unknown_0x31; //related to localplayercount
    bool unknown_0x32[2];
    float float_0x34[2];
    u16 unknown_0x3C; //8068d210
    u8 unknown_0x3E[2]; //padding?
    virtual ~ItemEffects(); //8068d234 vtable 808c1ec0
}; //total size 0x44

class EffectsMgr {
public:
    static EffectsMgr *sInstance; //809c21d0
    static EffectsMgr *CreateStaticInstance(EGG::Heap *heap); //8067b4c8
    void Init(u32 sceneId); //8067b580
    void CreatePlayerEffects(); //8067c4f4
    void Reset(); //8067b8f0
    void Update(); //8067cb88
    EGG::Effect *GetMenuEffectByIdx(u32 idx); //8067daa8
    u32 playerCount; //from racedata 8067b580
    u32 localPlayerCount; //0x4
    u16 unknown_0x8;
    u8 unknown_0xA[2];
    u32 sceneId;
    u8 unknown_0x10[2];
    u16 resourcesCount;
    bool hasPocha;
    bool hasPochaYogan;
    bool hasEntry;
    bool hasEpropeller;
    bool hasEnvFire;
    bool hasKareha;
    bool hasCoin;
    u8 unknown_0x1B;
    float float_0x1C[8]; //8067b670 same number as bools above, could be the heights of the objects, most notably pocha
    u32 unknown_0x3C; //8067b660
    bool isGV; //0x40
    bool isMT; //0x41
    u8 unknown_0x42[2];
    EGG::EffectResource *resources[9]; //0x44
    PlayerEffects **playersEffects; //0x68
    MenuEffects *menuEffect; //0x6C
    MGWhiteFogEffect *mgWhiteFog;
    ItemEffects *itemEffects; //0x74
    u8 unknown_0x78[0x9f4 - 0x78];
    //related to local playerCount 9d8 8067b6d8
}; //total size 0x9f4
#endif