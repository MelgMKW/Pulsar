#ifndef _EGG_POSTEFFECTOUTLINE_
#define _EGG_POSTEFFECTOUTLINE_
#include <types.hpp>
#include <core/egg/3D/PostEffects/PostEffect.hpp>

using namespace nw4r;

namespace EGG {

class PostEffectOutline : public PostEffect { //https://imgur.com/mgtzqwD outline
public:

    PostEffectOutline(); //80236250
    ~PostEffectOutline() override; //80236bd8 vtable 802a3c30
    void Draw(float width, float height) override; //0xc 80236448
    void PreDraw() override; //0x10 8023671c
    u32 unknown_0x28[2];
    u8 unknown_0x30[4];
    u16 unknown_0x34;
    u8 padding[2];
    float unknown_0x38[5];
    CpuTexture* cpuTexture; //0x4c
}; //0x50



}//namespace EGG
#endif