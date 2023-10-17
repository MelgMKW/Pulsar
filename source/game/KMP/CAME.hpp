#ifndef _CAME_
#define _CAME_
#include <game/KMP/KMPBlockBase.hpp>

struct CAME {
    u8 type;
    u8 nextCam;
    u8 shake;
    u8 routeId;
    u16 speed; //0x4
    u16 zoomSpeed;
    u16 viewSpeed; //0x8
    u8 startFlag;
    u8 movieFlag;
    Vec3 position; //0xC
    Vec3 rotation; //0x18
    float zoomStart; //0x24
    float zoomEnd; //0x28
    Vec3 viewPositionStart; //0x2c
    Vec3 viewPositionEnd; //0x38
    float duration; //0x44
}; //total size 0x48

typedef struct KMPBlock<CAME> CAMEBlock;

#endif