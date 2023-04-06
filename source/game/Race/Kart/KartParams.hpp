#ifndef _KARTPARAMS_
#define _KARTPARAMS_

#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
#include <game/File/StatsParam.hpp>
#include <game/File/BSP.hpp>




typedef StatsParamEntry KartStats;

class StatsAndBsp {
public:
    static KartStats *Compute(KartId kartId, CharacterId characterId); //80591fa4
    KartStats *stats; //http://wiki.tockdom.com/wiki/KartParam.bin
    BSP *bsp; //http://wiki.tockdom.com/wiki/BSP_(File_Format)
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

class KartValues {
public:
    KartValues(u32 playerIdx, KartId kart, CharacterId character, bool isBike, StatsAndBsp *statsAndBsp,
        void *unknown, UnkType *kartDriverDispParams, UnkType *kartPartsDispParams,
        UnkType *bikePartsDispParams, UnkType *driverDispParams); //80592fc0
    u32 isBike;
    KartId kart;
    CharacterId character;
    u16 wheelCount0;
    u16 wheelCount1;
    u8 playerIdx;
    u8 unknown_0x11[2];
    StatsAndBsp *statsAndBsp;
    int *unknown_0x18;
    UnkType *kartDriverDispParams;
    UnkType *kartPartsDispParams; //http://wiki.tockdom.com/wiki/KartPartsDispParam.bin
    UnkType *bikePartsDispParams; //http://wiki.tockdom.com/wiki/BikePartsDispParam.bin
    UnkType *driverDispParams;
    float wheelCountRecip;
    float wheelCountPlusOneRecip; //1.0f / (wheelCount + 1.0f)
    GpStats *gpStats;
    u8 unknown_0x38[0x3C - 0x38];
}; //Total size 0x3c

class DriverParams {
public:
    static DriverParams *sInstance; //809c191c
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
    static KartParams *sInstance; //809c1918
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
#endif