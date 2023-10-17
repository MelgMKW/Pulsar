#ifndef _KARTPARTSDISPPARAM_
#define _KARTPARTSDISPPARAM_
#include <kamek.hpp>

class KartPartsDispParam { //https://wiki.tockdom.com/wiki/KartPartsDispParam.bin
public:
    struct Entry {
        float cameraYDist;
        float tiresFwRotSpeed;
        float tiresBwRotSpeed;
        float unknown_0xC[12];
        Vec3 rearTiresScale;
        Vec3 frontSwingArmsPos;
        Vec3 frontSwingArmsRot;
        Vec3 rearSwingArmsPos;
        float rearSwingArmsXRot;
        float unknown_0x70[14];
        Vec3 frontSuspensionsTopPos;
        Vec3 frontSuspensionsInvBottomPos;
        Vec3 rearSuspensionsTopPos;
        Vec3 rearSuspensionsInvBottomPos;
        float unknown_0xD0[10];
        ExhaustParticleSet sets[2];
        Vec3 iceSize;
        Vec3 icePos;
        Vec2 balloonsYZPos;
        float unknown_0x148[2];
    }; //0x150

    u32 kartsCount;
    Entry entries[1];
};

#endif