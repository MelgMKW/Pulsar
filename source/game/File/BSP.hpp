#ifndef _BSP_
#define _BSP_
#include <kamek.hpp>

//BSP (Binary Settings and Physics) is a file format that contains kart collision data. BSP files are found in the bsp directory in Common.szs.

struct BSP { //https://wiki.tockdom.com/wiki/BSP_(File_Format)
    struct Hitbox {
        u16 enableFlag;
        u8 padding[2];
        Vec3 center; //of the sphere
        float radius;
        u16 onlyCollideWalls;
        u16 wheelColIdx;
    };
    struct Wheel {
        u16 enableFlag;
        u8 adding[2];
        float suspensionPos;
        float suspensionSpeed;
        float maxYDistance; //topmost - bottommost of the wheel
        Vec3 center;
        float xRotation;
        float radius;
        float sphereRadius;
        u32 unknown;
    };
    float initialYPos;
    Hitbox hitbox[16];
    Vec3 cuboidInertiaTensor1;
    Vec3 cuboidInertiaTensor2;
    float rotSpeedFactor;
    float unknown;
    Wheel front; //right for kart, left is obtained via symmetry
    Wheel back;
    Wheel unused[2];
    float maxYDistanceRumble;
    float rumbleAnimSpeed;
};

#endif