#ifndef _STATSPARAM_
#define _STATSPARAM_
#include <kamek.hpp>
//https://wiki.tockdom.com/wiki/KartParam.bin
//https://wiki.tockdom.com/wiki/DriverParam.bin

enum WheelCount {
    WHEELS_4_COUNT,
    WHEELS_2_COUNT,
    WHEELS_2_QUACKER,
    WHEELS_3_BLUE_FALCON
};

enum KartType {
    KART = 0x0,
    OUTSIDE_BIKE = 0x1,
    INSIDE_BIKE = 0x2
};

struct StatsParamEntry { //https://wiki.tockdom.com/wiki/KartParam.bin
    WheelCount wheelCount;
    KartType type;
    u32 weightClass;
    float float_0xC;
    float weight; //10
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

struct StatsParamHeader {
    u32 entryCount; //kart/driver count
    StatsParamEntry entries; //array of size entrycount
};


#endif