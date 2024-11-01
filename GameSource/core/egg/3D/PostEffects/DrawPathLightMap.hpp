#ifndef _EGG_DRAWPATH_LIGHTMAP_
#define _EGG_DRAWPATH_LIGHTMAP_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/PostEffects/DrawPathBase.hpp>

using namespace nw4r;

namespace EGG {

class DrawPathLightMap : public DrawPathBase {
public:
    DrawPathLightMap(); //8022183c

    //ScreenEffect vtable 802a2d70 at 0x4
    ~DrawPathLightMap() override; //802222b4
    //IScnProc vtable 802a2d7c at 0x10
    //~DrawPathBase() override; //thunk 80222314 func 802222b4
    u32 GetScnProcCount() override; //0x10 802222ac
    void CalcImpl() override; //0x14 802218b0
    void DrawImpl(u16 scnProcIdx) override; //0x18 802218ec
    void FreeFirstTwoTexBuffers(); //80222250
    u8 unknown_0x14; //0x14
    u8 unknown_0x15; //0x15
    u8 padding[2];
    u32 unknown_0x18[2];
    TextureBuffer* buffers[3]; //0x24
    u32 unknown_0x30; //0x30
}; //0x34

}//namespace EGG
#endif