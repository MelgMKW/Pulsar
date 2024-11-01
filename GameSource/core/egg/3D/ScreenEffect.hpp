#ifndef _EGG_SCREEN_EFFECT_
#define _EGG_SCREEN_EFFECT_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>

namespace EGG {

class ScreenEffect {
public:
    ScreenEffect(); //8023e724
    void SetupGX(bool cache); //80240988
    bool Release(u32 type); //80240844

    u8 bitfield;
    u8 padding[3];
    virtual ~ScreenEffect(); //0x4 8021c330 vtable 802a3f20
}; //0x8
}//namespace EGG
#endif