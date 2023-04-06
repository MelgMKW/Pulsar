#ifndef _AREA_
#define _AREA_
#include <game/KMP/SectionBase.hpp>

struct AREA {
    u8 shape; //0 box 1 cylinder
    u8 type;
    u8 camera;
    u8 priority;
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
    u16 setting1; //0x28
    u16 setting2; //0x2a
    u8 routeId; //0x2c
    u8 enemyRouteId; //0x2d
    u16 unknown_0x2e;
}; //total size 0x30

typedef struct KMPSection<AREA> AREASection;

#endif