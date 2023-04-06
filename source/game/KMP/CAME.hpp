#ifndef _CAME_
#define _CAME_
#include <game/KMP/SectionBase.hpp>

struct CAME {
    u8 type;
    u8 nextCam;
    u8 shake;
    u8 routeId;
    u16 speed;
    u16 zoomSpeed;
    u16 viewSpeed;
    u8 startFlag;
    u8 movieFlag;
    Vec3 position;
    Vec3 rotation;
    float zoomStart;
    float zoomEnd;
    Vec3 viewPositionStart;
    Vec3 viewPositionEnd;
    float duration;
}; //total size 0x48

typedef struct KMPSection<CAME> CAMESection;

#endif