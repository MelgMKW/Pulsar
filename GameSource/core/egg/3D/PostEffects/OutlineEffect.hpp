#ifndef _EGG_OUTLINEEFFECT_
#define _EGG_OUTLINEEFFECT_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/3D/ScreenEffect.hpp>
#include <core/egg/3D/PostEffects/PostEffectOutline.hpp>
#include <core/egg/3D/PostEffects/PostEffectBlur.hpp>
#include <core/egg/3D/TextureBuffer.hpp>
namespace EGG {

class OutlineEffect : public ScreenEffect { //non-official name, outline with a bit of blur, used for minimap borders
public:
    OutlineEffect(); //8023e748
    ~OutlineEffect() override; //8023e86c vtable 802a3f30
    void SetupDraw(); //8023e90c
    void Draw(); //8023ef90
    u8 unknown_0x8[2];
    u8 padding2[2];
    u32 unknown_0xC;
    float unknown_0x14[6];
    u8 unknown_0x2c[4];
    PostEffectOutline* outline; //0x30
    PostEffectBlur* blur; //0x34
    TextureBuffer* buffer; //0x38
}; //0x3c

}//namespace EGG
#endif