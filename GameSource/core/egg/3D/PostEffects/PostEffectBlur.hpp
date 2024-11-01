#ifndef _EGG_POSTEFFECTBLUR_
#define _EGG_POSTEFFECTBLUR_
#include <types.hpp>
#include <core/nw4r/ut.hpp>
#include <core/egg/3D/PostEffects/PostEffect.hpp>

using namespace nw4r;

namespace EGG {

class PostEffectBlur : public PostEffect {
public:
    struct BlurData {
        u8 unknown_0x0;
        ut::Color color;
        u8 padding[3];
        float unknown_0x8;
        float Radius;
    }; //0x10

    PostEffectBlur(); //802351f0
    ~PostEffectBlur() override; //8021c984 vtable 802a3bd0 
    void Draw(float width, float height) override; //0xc 8023533c
    u8 blurDataCount; //0x28
    u8 padding[3];
    float colorScale; //0x2c
    BlurData mBlurData[4]; //0x30
};

}//namespace EGG
#endif