#ifndef _EGG_POSTEFFECT_
#define _EGG_POSTEFFECT_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/nw4r/ut.hpp>
#include <core/egg/3D/Texture.hpp>

using namespace nw4r;

namespace EGG {

class PostEffect {
public:
    PostEffect(); //80234a54


    void SetVtxState(); //80234ba4
    u16 bitfield; //0x0
    GX::BlendMode blendMode; //0x4
    CapTexture* capTexture; //0x8
    Vector2f pos; //0xC
    Vector2f scale; //0x14
    u8 unknown_0x1c[8];
    virtual ~PostEffect(); //8021c904 vtable 802a3bb4 at 0x24
    virtual void Draw(float width, float height); //0xc 80234aac
    virtual void PreDraw(); //0x10 80234b40
    virtual void LoadTexObj(); //0x14 80234c38
    virtual void DrawDL(float posX, float posY, float width, float height); //0x18 80234bac sends DL to GPU 
}; //0x24

class PostEffectSimple : public PostEffect {
public:
    PostEffectSimple(); //80236250
    ~PostEffectSimple() override; //8021c9c4 vtable 802a3c10
    void PreDraw() override; //0x10 80235e80
    float unknown_0x28;
    ut::Color color; //0x2c;
    u8 unknown_0x30;
    u8 padding[3];
    u32 unknown_0x34;
    u8 unknown_0x38;
    u8 padding2[3];
}; //0x3C

}//namespace EGG
#endif