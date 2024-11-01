#ifndef _KARTVALUES_
#define _KARTVALUES_

#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/File/StatsParam.hpp>
#include <MarioKartWii/File/BSP.hpp>
#include <MarioKartWii/File/DispParams/BikePartsDisp.hpp>
#include <MarioKartWii/File/DispParams/KartPartsDisp.hpp>
#include <MarioKartWii/File/DispParams/DriverDisp.hpp>
#include <MarioKartWii/File/DispParams/KartDriverDisp.hpp>
#include <MarioKartWii/Kart/KartFunctions.hpp>

namespace Kart {

class StatsAndBsp {
public:
    Stats* stats; //http://wiki.tockdom.com/wiki/KartParam.bin
    BSP* bsp; //http://wiki.tockdom.com/wiki/BSP_(File_Format)
}; //Total size 0x8

class GpStats {
public:
    bool startBoostSuccessful;
    u8 unknown_0x1[0x4 - 0x1];
    u32 mtCount;
    u32 offroadFrames;
    u32 unknown_0xC;
    u32 objectCollisionCount;
    u32 oobCount;
    u16 unknown_0x18;
    u8 unknown_0x1a[2];
}; //Total size 0x1cf

class Values {
public:
    Values(u32 playerIdx, KartId kart, CharacterId character, bool isBike, const StatsAndBsp& statsAndBsp, void* unknown,
        KartDriverDispParam::Entry* kartDriverDispEntry, KartPartsDispParam::Entry* kartPartsDispEntry,
        BikePartsDispParam::Entry* bikePartsDispEntry, DriverDispParam::Entry* driverDispEntry); //80592fc0

    struct Tallies {
        float totalDistance; //speednorm added every frame
        float totalDistanceIn1st; //speednorm added every frame
        u32 itemsHitCount; //0x8 on others
        u32 itemsCollisionCount; //0xc
        u32 tricksCount;
    }; //0x14

    u32 isBike;
    KartId kart;
    CharacterId character; //0x8
    u16 wheelCount0; //0xc
    u16 wheelCount1; //0xe
    u8 playerIdx; //0x10
    u8 unknown_0x11[2];
    const StatsAndBsp& statsAndBsp; //0x14
    int* unknown_0x18; //0x18 808b63b8
    KartDriverDispParam::Entry* kartDriverDispEntry; //0x1c
    KartPartsDispParam::Entry* kartPartsDispEntry; //0x20
    BikePartsDispParam::Entry* bikePartsDispEntry; //0x24
    DriverDispParam::Entry* driverDispEntry; //0x28
    float wheelCountReciprocal; //0x2c
    float wheelCountPlus1Reciprocal; //1.0f / (wheelCount + 1.0f)
    GpStats* gpStats; //0x34
    Tallies* tallies;
}; //Total size 0x3c

class DriverParams {
public:
    static DriverParams* sInstance; //809c191c
    u32 wheelCount;
    KartType type;
    u32 weightClass;
    float unknown_0xC;
    float weight;
    float bumpDeviationLevel;
    float baseSpeed;
    float handlingSpeedMultiplier;
    float tilt;
    float standard_acceleration_as[4];
    float standard_acceleration_ts[3];
    float drift_acceleration_as[2];
    float drift_acceleration_ts[1];
    float manualHandling;
    float autoHandling;
    float handlingReactivity;
    float manualDrift;
    float automaticDrift;
    float driftReactivity;
    float targetAngle;
    float unknown_0x68;
    u32 mt;
    float speedFactors[32];
    float handlingFactors[32];
    float rotatingItemObjParams[4];
    float vertical_tilt;
    float megaScale;
    float unknown_0x188;

}; //total size 0x18c

class KartParams {
public:
    static KartParams* sInstance; //809c1918
    u32 wheelCount;
    KartType type;
    u32 weightClass;
    float unknown_0xC;
    float weight;
    float bumpDeviationLevel;
    float baseSpeed;
    float handlingSpeedMultiplier;
    float tilt;
    float standard_acceleration_as[4];
    float standard_acceleration_ts[3];
    float drift_acceleration_as[2];
    float drift_acceleration_ts[1];
    float manualHandling;
    float autoHandling;
    float handlingReactivity;
    float manualDrift;
    float automaticDrift;
    float driftReactivity;
    float targetAngle;
    float unknown_0x68;
    u32 mt;
    float speedFactors[32];
    float handlingFactors[32];
    float rotatingItemObjParams[4];
    float vertical_tilt;
    float megaScale;
    float unknown_0x188;
}; //total size 0x18c

}//namespace kart

#endif