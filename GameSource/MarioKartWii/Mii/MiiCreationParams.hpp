#ifndef _MII_CREATION_PARAMS_
#define _MII_CREATION_PARAMS_
#include <kamek.hpp>
#include <core/rvl/RFL/RFL.hpp>
#include <MarioKartWii/System/Random.hpp>
#include <MarioKartWii/Mii/Mii.hpp>


class MiiCreationParams2 {
    virtual ~MiiCreationParams2(); //805f9f18 vtable 808b9f74
    void Init(u16 r4, u16 r5, u16 r6, u8 r7); //8052993c
    void Reset(); //80529978

    u8 unknown_0x4[0xd];
    u8 unknown_0x11[0xd];
    u8 unknown_0x1e[0xd];
    u16 r5;
    u16 r4;
    u16 r6;
    u8 r7;
    u8 padding;
};

class MiiCreationParams {

    virtual ~MiiCreationParams(); //806b8f4c vtable 808c2368

    void InitAndReset(u16 maxCreatedMiis, bool preventRepetition, bool allowCurPlayersMiis, bool allowRandomMiiOnNoIdx,
        bool doubleProbOfFavouriteMiis, RFL::Sex allowedSex, bool isGameChar); //805297e4
    void Init(u16 maxCreatedMiis, bool preventRepetition, bool allowCurPlayersMiis, bool allowRandomMiiOnNoIdx,
        bool doubleProbOfFavouriteMiis, RFL::Sex allowedSex, bool isGameChar); //80529804
    void Reset(); //80529824

    u16 maxCreatedMiis; //0x4
    bool preventRepetition; //0x6
    bool allowCurPlayersMiis; //0x7
    bool allowRandomMiiOnNoIdx; //0x8 if no idx is left/found, can a random mii be created or should nullptr be returned
    bool doubleProbOfFavouriteMiis; //0x9
    u8 padding[3];
    RFL::Sex allowedSex; //0xc
    bool isGameChar; //0x10
    //(0xd << 3) < 0x64, therefore by shifting an official miiIdx by 3 (which manager only contains up to 100), the array is big enough
    //idx is RFL::Idx / 8, val is RFL::Idx & 8, so it works like a big bitfield array
    //when a mii is created, the bitfield corresponding to its creation type is updated accordingly; this is how repetitions are prevented
    u8 officialStoreBitfields[0xd];
    u8 middleDBBitfields[0xd];
    u8 unknown_0x2B[0xd];
    u8 randomCreatedBitfields[0xd][3]; //0x38/45/52
    u8 padding2; //0x5F
}; //0x60

#endif