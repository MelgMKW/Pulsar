#ifndef _LINKED_3D_POINTS_
#define _LINKED_3D_POINTS_
#include <kamek.hpp>
#include <core/nw4r/ut.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>

//This class is used for 3D points that physically linked to each other, the best example being Hanachan's parts
class Linked3DPoints {
public:
    class Sub {
    public:
        float distance; //0x8
        float unknown_0xC[0x5c - 0xC];
        u8 unknown_0x60;
        u8 padding[3];
        float unknown_0x64[0x70 - 0x64];
        u32 unknown_0x74[2];
    }; //0x7c
    Linked3DPoints(u8 totalPartCount, float* distBtwParts); //806f2fe8
    ~Linked3DPoints(); //806f31f4
    nw4r::ut::List subsList; //0x0
    Sub* subs; //4xpointsCount
    u8 pointsCount; //0x10 simply totalPartCount
    u8 unknown_0x14[0x24 - 0x14];
    Vec3ZeroInit* points; //0x24 count pointsCount
    float unknown_0x28[2];
    float* distBtwEachPoints; //0x48 copy of arg
    float totalLength; //0x4c
}; //0x50


#endif