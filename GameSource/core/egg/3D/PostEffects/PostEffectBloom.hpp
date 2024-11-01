#ifndef _EGG_POSTEFFECTBLOOM_
#define _EGG_POSTEFFECTBLOOM_
#include <types.hpp>
#include <core/nw4r/ut.hpp>
#include <core/egg/3D/PostEffects/PostEffect.hpp>

using namespace nw4r;

namespace EGG {

class PostEffectBloom : public PostEffect {
public:
    struct BloomData {
        u32 unknown_0x0[2];
        ut::Color color; //0x8
        float unknown_0xC;
        u8 unknown_0x10;
        u8 padding[3];
    }; //0x14

    PostEffectBloom(); //80235980
    ~PostEffectBloom() override; //8021c944 vtable 802a3bf0
    void PreDraw() override; //0x10 80235a40
    u8 bloomDataCount; //0x28
    u8 padding[3];
    float colorScale; //0x2c
    BloomData datas[3]; //0x30
}; //0x6c

}//namespace EGG
#endif