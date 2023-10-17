#ifndef _BIKEPARTSDISPPARAM_
#define _BIKEPARTSDISPPARAM_
#include <kamek.hpp>
#include <game/File/DispParams/CommonDisp.hpp>

class BikePartsDispParam { //https://wiki.tockdom.com/wiki/BikePartsDispParam.bin
public:
    struct Entry {
        float cameraYDist;
        float tiresFwRotSpeed;
        float tiresBwRotSpeed;
        Vec3 handlePos;
        Vec3 handleRot;
        float unknown_0x24[13];
        ExhaustParticleSet exhaustParticles[2];
        Vec3 iceSize;
        Vec3 icePos;
        Vec2 balloonsYZPos;
        float unknown_0xA8[2];
    }; //0xB0

    u32 bikesCount;
    Entry entries[1];
};

#endif