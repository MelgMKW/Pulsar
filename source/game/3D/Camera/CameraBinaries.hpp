#ifndef _CAMERABINARIES_
#define _CAMERABINARIES_
#include <kamek.hpp>

struct BCP { //https://wiki.tockdom.com/wiki/BCP_(File_Format)
    u32 unknown;
    u16 idxPointToIgnore; //0x4
    u8 padding[2];
    float speedBias; //0x8
    Vec3 scale; //0xC
    Vec3 rot; //0x18
    Vec3 startDist; //0x24
    Vec3 positions[10]; //of each point
    float speedDiffs[10]; //btw each point
};

struct CameraParamBin { //https://wiki.tockdom.com/wiki/KartCameraParam.bin
    struct Entry {
        float fovy;
        float cameraDist;
        float yPosition;
        float yTargetPos;
    }; //0x10
    Entry camerasParam[9][4];
};

class BCPInfo {
public:
    void Load(const BCP& raw); //805a6e40
    u32 bcp0x0;
    u16 idxPointToIgnore;
    Vec3 scale;
    Vec3 rot;
    Vec3 startDist;
    Vec3* positions; //0x30
    Vec3* speedDiffs; //0x34
};

#endif