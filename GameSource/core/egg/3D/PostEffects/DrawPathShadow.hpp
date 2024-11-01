#ifndef _EGG_DRAWPATH_SHADOW_
#define _EGG_DRAWPATH_SHADOW_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/PostEffects/DrawPathBase.hpp>

using namespace nw4r;

namespace EGG {

class DrawPathShadowVolume : public DrawPathBase {
public:
    DrawPathShadowVolume(); //80220ce8
    //ScreenEffect vtable 802a2d40 at 0x4
    ~DrawPathShadowVolume() override; //802217d4

    //IScnProc vtable 802a2d4c at 0x10
    //~DrawPathBase() override; //thunk 80221834 func 80221834
    u32 GetScnProcCount() override; //0x10 802217cc
    void DrawImpl(u16 scnProcIdx) override; //0x18 80220d7c

    u8 unknown_0x14[0x4];
    TextureBuffer* buffers[2]; //0x18
    u8 unknown_0x20[0x14];
}; //0x34

}//namespace EGG
#endif