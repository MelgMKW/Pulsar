#ifndef _GOBJ_
#define _GOBJ_
#include <MarioKartWii/KMP/KMPBlockBase.hpp>


struct GOBJ {
    u16 objID; //0
    u16 padding; //0x2 u16 for XPF
    Vec3 position; //4
    Vec3 rotation; //10
    Vec3 scale; //1c
    u16 routeID; //28
    s16 settings[8]; //2a, 2c, 2e, 30, 32, 34, 36, 38
    u16 presenceFlags; //3a
}; //0x3C

typedef KMPBlock<GOBJ> GOBJBlock;

#endif