#ifndef _EGG_GXUTILITY_
#define _EGG_GXUTILITY_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>

namespace EGG {

struct ResTIMG {
    u8 texFormat; //0x0
    u16 width; //0x2
    u16 height; //0x4
    u8 wrapS; //0x6
    u8 wrapT; //0x7
    u8 padding[2];
    bool mipmap; //0x10
    u8 edgeLodEnable; //0x11
    u8 biasClampEnable; //0x12
    u8 anisotropy; //0x13
    u8 minFilt; //0x14
    u8 magFilt; //0x15
    s8 minLod; //0x16
    s8 maxLod; //0x17
    u8 unknown_0x18[2];
    s16 lodBias; //0x1A
    s32 imageOffset; //0x1C
};

class GXUtility {
public:
    static void SetScaleOffsetPerspective(float* dest, float xScale, float yScale, float xOffset, float yOffset); //80228dd8 

    static u8 GetTexMtxID(u32 idx); //80228dcc converts 0-8 to GX::TexMtx enum (30,33,36,39 etc...)
    static void GetTexObj(GX::TexObj* dest, const ResTIMG& timg); //80228e18

    static const u8 texMtxID[8]; //80388d30

    /*
    dest[1] *= 1/xScale
    dest[2] += xOffset
    dest[3] *= 1/yScale
    dest[4] += yOffset
    */
};

}//namespace EGG
#endif