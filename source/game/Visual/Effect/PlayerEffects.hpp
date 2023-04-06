#ifndef _PLAYER_EFFECTS_
#define _PLAYER_EFECTS_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <game/Race/Kart/Kart.hpp>

class UnkEffectClass {
public:
    UnkEffectClass(); //8068e844 just a blr
    ~UnkEffectClass(); //8068e848
    u8 unknown[4];
}; //total size 0x4

class PlayerEffects {
public:
    explicit PlayerEffects(Kart *kart); //0x8068df98
    virtual ~PlayerEffects(); //0x8068e888 vtable 808c1f64
    void LoadEffects(); //8068f044 4932 lines long
    void DisplayPrimaryEffects(EGG::Effect **effectsArray, u32 firstEffectIndex, u32 lastEffectIndex, Mtx34 *playerMat2, Vec3 *wheelPos, bool r9); //r5 first Id and r6 second Id maybe?
    void DisplaySecondaryEffects(EGG::Effect **effectsArray, u32 firstEffectIndex, u32 lastEffectIndex, Mtx34 *playerMat2, Vec3 *wheelPos, bool r9);
    void FadeEffects(EGG::Effect **effectsArray, u32 firstEffectIndex, u32 lastEffectIndex, Mtx34 *playerMat2, Vec3 *wheelPos, bool r9); //80697788
    void DisplayEffects2(EGG::Effect **effectsArray, u32 firstEffectIndex, u32 lastEffectIndex, bool r7);
    void FadeEffects2(EGG::Effect **effectsArray, u32 firstEffectIndex, u32 lastEffectIndex, bool r7);
    bool unknown_0x4;
    u8 unknown_0x5[0xB - 0x5]; //0x8068ea78, init func maybe
    bool hasOnlyOnePage; //ScnManager pageCoutn if <2 then true
    bool unknown_0xC;
    bool isInsideDrift; //0xd
    bool isAutomaticDrift; //0xe
    bool isHumanPlayer; //0xF
    u8 unknown_0x10[0x15 - 0x10]; //806b26c
    bool hasGottenStartBoost;
    u16 frameTimer; //0x16 up to 1000, seems to only trigger for certain effects 0x16
    u16 startBoostDuration; //0x18
    u16 boostDuration; //0x1A
    u32 frameTimer2; //same, 0x1C
    bool isBoosting; //0x20 from kartStatus
    bool isOnBoostRamp; //0x21
    bool isOnJumpPad; //0x22 same
    bool hasMTBoost; //0x23
    bool isOverZipper; //0x24
    u8 unknown_0x25[0x2B - 0x25]; //8068eb04 same as above but 1 frame delayed most likely
    bool hasMushroomBoost; //0x2B
    u8 unknown_0x2C[2]; //8068eb04
    bool isInExplosion; //0x2E
    bool unknown_0x2F;
    u8 unknown_0x30;
    u8 unknown_0x31; //8068eb2c
    u8 unknown_0x32[0x34 - 0x32];
    u32 smtCharge; //0x34 80698650 
    u8 unknown_0x38; //mess at 0x8068eec4
    u8 unknown_0x39; //mess at 0x8068eec4
    u8 unknown_0x3A;
    u8 unknown_0x3B;
    u16 unknown_0x3C; //set to 0x3
    u16 unknown_0x3E; //set to 0x28
    u16 unknown_0x40; //80694b58
    bool isGoingBackwards; //0x42
    bool unknown_0x43; //bitfield 1 0x2000000
    bool isBrakingAndBackwards; //0x44
    bool unknown_0x45; //8068eb50
    bool isInStar; //0x46
    bool isInMega; //0x47
    bool hasTC; //0x48
    u8 unknown_0x49; //80693fa8
    u8 unknown_0x4A[0x4C - 0x4A];
    u32 unknown_0x4C; //set to 0x2b2 8068ec18
    u32 unknown_0x50; //set to 0x21C
    u32 frameTimer3; //0x54
    u32 frameTimer4; //0x58
    bool isInCannon; //0x5C
    u8 unknown_0x5D[0x60 - 0x5D]; //padding?
    u32 unknown_0x60; //set to 0x23 8068eb54
    u32 unknown_0x64; //set to -1
    u8 unknown_0x68; //806950d0
    u8 unknown_0x69;
    u8 unknown_0x6A;
    u8 unknown_0x6B; //8068eb5c
    u8 unknown_0x6C; //8068eb5c
    u8 unknown_0x6D[3];
    float unknown_0x70; //8068eb64
    float initialYPos;
    u8 unknown_0x78;
    u8 unknown_0x79;
    u8 unknown_0x7A;
    u8 unknown_0x7B;
    u8 unknown_0x7C;
    bool isInBullet; //0x7D
    bool isInBullet1framedelayed; //0x7E 8069daf8
    u8 unknown_0x7F; //padding?
    u32 unknown_0x80; //8068eb80
    u32 unknown_0x84;
    bool unknown_0x88; //bitfield 1 0x20000000
    bool unknown_0x89; //related to MT sparks 8069bad4
    u8 unknown_0x8A[0x8C - 0x8A];
    u32 unknown_0x8C; //set to -1
    u8 unknown_0x90; //8068eb94
    u8 unknown_0x91;
    u8 unknown_0x92;
    u8 unknown_0x93;
    u8 unknown_0x94;
    u8 unknown_0x95;
    bool isInPreRespawn; //0x96
    bool isInPreRespawn1framedelayed; //0x97
    u8 unknown_0x98; //80694528
    u8 unknown_0x99[0xA0 - 0x99];
    u8 unknown_0xA0[0xA8 - 0xA0];
    u8 unknown_0xA8; //8068ebc4 
    u8 unknown_0xA9;
    bool isManualDrifting; //0xAA
    bool unknown_0xAB; //0x80694ad8
    u8 unknown_0xAC;
    u8 unknown_0xAD;
    bool hasTrickBoost; //0xAE
    u8 unknown_0xAF; //8069abcc
    u8 unknown_0xB0; //806b3520
    u8 unknown_0xB1;
    u8 unknown_0xB2;
    u8 unknown_0xB3;
    u8 unknown_0xB4;
    u8 unknown_0xB5;
    u8 unknown_0xB6;
    u8 unknown_0xB7;
    u8 unknown_0xB8;
    bool hasHitItem; //0xB9
    u8 unknown_0xBA[0xC0 - 0XBA];
    bool unknown_0xC0; //related to cameras, 0x80694568
    u8 unknown_0xC1[0xc4 - 0xC1];
    Mtx34 playerMat2; //might be one frame delayed, copy of the one at 6f4 80694c6c 
    u8 unknown_0xF4; //806945bc
    bool hasVanished; //80693dc0
    u8 unknown_0xF6; //80694660 related to cameras
    u8 unknown_0xF7[0x100 - 0xF7];
    float float_0x100; //0x8069ec94
    float float_0x104;
    float float_0x108;
    u8 unknown_0x10C; //8069eca8
    u8 unknown_0x10D;
    bool isAcceleratingAtStart; //0x10e
    u8 unknown_0x10F[0x118 - 0x10f];
    Kart *kart; //0x118
    KartId kartId; //0x11c
    CharacterId characterId; //0x120
    u32 isBike; //yes it's a word 124
    bool isBlueFalcon; //0x128
    bool isRealPlayer; //0x219
    u8 unknown_0x12A;
    bool isGhost; //0x12b
    bool isTTReplay; //0x12c
    bool isRealOrNotGhost; //0x12D
    u8 playerId; //0x12e
    u8 unknown_0x12f; //0x8068ee44
    u8 unknown_0x130[0x134 - 0x130];
    u32 playerIdPlus2; //0x134 0x8068f064
    bool isCPURace; //0x138
    bool isReplay; //0x139
    bool isGameType2or3or4; //0x13a 8068e0b0
    bool isLiveView; //0x13B
    bool isModeFlag4; //0x13C
    bool isVsRace; //0x13D
    bool isDKSC;
    bool isGV;
    bool isMT;
    bool isMG;
    bool isDDR;
    bool isDKM;
    bool isDC;
    bool isCM;
    bool isTF;
    bool isBC64;
    bool isBC3;
    bool isDKJP;
    bool isDelfinoPier;
    bool isGalaxyColosseum;
    bool hasPocha; //0x14C
    bool hasPochaYogan;
    bool hasEntry;
    bool hasEpropeller; //0x14F
    u8 unknown_0x150; //related to objects 8068e284
    bool isSL; //0x151
    bool hasEnvFire;
    bool hasKareha;
    bool isRedTeam; //0x154
    bool isBlueTeam; //0x155
    bool isBattle; //0x156 
    bool effectHolder_0x1A; //0x157
    ModelDirector *pochaModel; //0x158
    ModelDirector *pochaYoganModel; //0x15C
    ModelDirector *iceModel; //for rSL 0x160
    u32 unknown_0x164[12]; //ends at 0x194
    UnkEffectClass class_0x194[16];
    UnkEffectClass class_0x1d4[4]; //0x1d4
    UnkEffectClass class_0x1e4[2];
    UnkEffectClass class_0x1ec[1];


    EGG::Effect *rk_raceEffects[92]; //use enum

    bool hasLoaded_1[0x38c - 0x360]; //0x360 check from crash to hitA
    bool hasLoaded_2[0x39A - 0x38C]; //rk_koukasen to rk_effect_0x2D4
    bool hasLoaded_3[0x3AA - 0x39A]; //806b0e50 check from gasSmoke to miniTurbo_4
    bool hasLoaded_4[0x3BC - 0x3AA]; //806b0ec8 check from dirtSmoke to stone2

    float unk_emission_value_0x3BC[44]; //related from crash to hitA ends at 46c, corresponds to unknown emission value on the wiki
    float unk_emission_value_0x46C[14]; //0x46C from rk_koukasen to rk_effect_0x2D4,
    float unk_emission_value_0x4A4[16]; //806b0e5c related to gasSmoke ends at 4E4
    float unk_emission_value_0x4E4[18]; //related to dirtSmoke to stone2 ends at 52c

    EGG::Effect **kartEffects; //0x52c 8069188c 8 elements use kartEffects enum
    EGG::Effect **kartDriftEffects; //8069189c 36 elements use driftEffects enum
    bool hasLoaded_5[8]; //0x534 8 elements in the 52c array
    bool hasLoaded_6[36]; //0x53C 36 elements in the 530 array
    float unk_emission_value_0x560[8]; //ends at 580
    float unk_emission_value_0x580[36]; // ends at 610
    EGG::Effect **bikeEffects; //0x610
    EGG::Effect **bikeDriftEffects; //0x614
    bool hasLoaded_7[8]; //0x618 for the array above 600
    bool hasLoaded_8[28]; //0x620, for the array at 614
    float unk_emission_value_0x63C[8]; //0x63C ends at 65c
    float unk_emission_value_0x65C[28]; //ends at 0x6CC, for the array at 614

    u32 *bikePartsAndParam_field; //0x6cc, field 0x58 if bike, 0xf8 if kart
    Vec3 playerPosition; //0x6d0 from kartPhysics 80693eb0
    Vec3 speed; //0x6dc from kartPhysics
    float speedNorm; //0x6e8 calculed from speed vector
    float speedNorm2; //might be 1 frame delayed as it's copied from 0x6E8
    float softSpeedLimitOr50; //0x6f0, set to 50.0 if softSpeedLimit inferior to it
    Mtx34 playerMat; //0x6f4 from kartPhysicsHolder
    u32 unknown_0x724; //from the unknown camera struct in kartPointers
    float kartSpeed; //0x728
    Vec3 playerScale; //0x72c from kartMovement
    Vec2 unknown_0x738; //806b3674
    Vec3 lastWheelfloorNor; //4th wheel for karts 80696eac, from wheelPhysics collision data
    Mtx34 unknown_0x74C;
    Vec3 unknown_kartParam; //from 0x6CC field 8068ef9c
    Vec3 unknown_kartParam2; //from 0x6CC field
    u8 unknown_0x794[0x79C - 0x794];
    u32 unknown_0x79C; //set to C8 8068ed88
    u16 driftState; //from kartMovement 7a0, delayed by one frame so that on the transition stuff happens
    u8 unknown_0x7A2[2];
    Vec3 vector_0x7A4;
    u32 unknown_0x7B0; //8068ed90
    u8 unknown_0x7B4[0x7B9 - 0x7B4]; //all incremented until 0x64 at 806947ac
    bool isSecondWheelOnFloor; //0x7b9
    bool isThirdWheelOnFloor; //0x7ba
    Vec3 thirdWheelPos; //0x7bc from WheelPhysics, set at 80694040
    Vec3 fourthWheelPos; //0x7c8 same
    Vec3 thirdWheelPos2; //0x7D4 might be 1 frame delayed as it's a copy of 0x7BC
    Vec3 fourthWheelPos2; //0x7E0 same
    Vec3 vector_0x7EC; //80694860
    Vec3 vector_0x7F8; //80694860 loop
    float norm_0x804; //norm of the 7EC vector
    float norm_0x808; //norm of the 7F8 vector
    Vec3 vector_0x80c; //8068ee20
    Mtx34 mat_0x818; //806b426 and 0x824, 834, 844 are x y z playerPos
    bool bool_0x848[4]; //related to params at 0x8cc 8068ee8c
    Vec3 vector_0x84C; //806a0e38 related to params
    Vec3 vector_0x858; //same
    Vec3 vector_0x864; //806a0e38 related to params, loops twice
    Vec3 vector_0x870; //same
    Vec3 vector_0x87C; //copy of 84C, 1 frame delayed?
    Vec3 vector_0x888; //copy of 858, 1 frame delayed?
    Vec3 vector_0x894; //copy of 864, 1 frame delayed?
    Vec3 vector_0x8A0; //copy of 870, 1 frame delayed?
    Mtx34 boostMat[4]; //806a0ef0
    bool isAccelerating; //0x96C
    u8 unknown_0x96D[0x971 - 0x96D]; //80694960
    u8 unknown_0x971[3];
    float float_0x974[2];
    Vec3 vector_0x97C; //806b1340
    u16 unknown_0x988[3]; //806b1390
    u8 unknown_0x98E[2];
    float float_0x990;
    u16 unknown_0x994[7]; //ends at 9a2
    u8 unknown_0x9B0[0x9B0 - 0x9A2];
    float float_0x9B0[14]; //806b146c ends at 9e8
    u8 unknown_0x9E8[0x9F0 - 0x9e8];
    float float_0x9F0[22]; //ends at 0xA48
    u8 unknown_0xA48[0xA4C - 0xA48];
    u8 unknown_0xA4C; //806b159c
    u8 unknown_0xA4D[0xA50 - 0xA4D];
    float unknown_0xA50[5];
    u8 unknown_0xA64[0xA68 - 0xA64];
    float float_0xA68[6];
    u8 unknown_0xA80[0xA84 - 0xA80]; //806b1670
    float float_0xA84[6]; //806b16d0 ends at A9C
    u8 unknown_0xA9C[0xAAC - 0xA9C];
    float float_0xAAC[2];
    u16 unknown_0xAB4[3]; //8068ed44
    u8 unknown_0xABA[2];
    float float_0xABC[5]; //8068ec2c
    u16 unknown_0xAD0[5]; //806b11bc
    u8 unknown_0xADA[0xAE0 - 0xADA];
    u8 unknown_0xAE0; //8068eb88
    u8 unknown_0xAE1[3];
    u32 unknown_0xAE4; //8068ebc8
}; //total size 0xAE8

#endif