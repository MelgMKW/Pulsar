#ifndef _EGG_SHADOW_
#define _EGG_SHADOW_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
namespace EGG {
class ShadowTextureManager {
    ShadowTextureManager(); //8023ff24
    u8 unknown_0x0;
    u8 padding;
    u16 unknown_0x2;
    u32 unknown_0x4[16];
    virtual ~ShadowTextureManager(); //0x44 8023c7e8 vtable 802a3f40
}; //0x48
}//namespace EGG
#endif