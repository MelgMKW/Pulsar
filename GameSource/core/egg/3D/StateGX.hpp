#ifndef _EGG_STATEGX_
#define _EGG_STATEGX_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/mem/Heap.hpp>

namespace EGG {


class StateGX {
public:
    struct CachedState {
        enum Status { //if any if set, when the corresponding func is called, it checks if the old values are the same as the one the user is trying to set, which prevents useless calls
            CACHED_STATUS_PROJECTIONV = 0x1,
            CACHED_STATUS_VIEWPORT = 0x2,
            CACHED_STATUS_SCISSOR = 0x4,
            CACHED_STATUS_SCISSOR_BOX = 0x8,
            CACHED_STATUS_DITHER = 0x10,
            CACHED_STATUS_COLOR_UPDATE = 0x20,
            CACHED_STATUS_ALPHA_UPDATE = 0x40,
        };
        u32 statusBitfield; //0x0 see enum
        s32 scissorX; //0x4
        s32 scissorY; //0x8
        bool colorUpdate; //0xC
        bool alphaUpdate; //0xD
        bool dither; //0xE
    };
    enum State {
        USE_TMEM = 0x10,
        VALID_CACHE = 0x20
    };
    static CachedState cachedState; //80384520

    static u16 stateBitfield; //80385FB8

    static GX::PixelFmt pixelFormat; //80386F4C
    static GX::ZFmt16 zFormat; //80386f50


    void Initialize(); //80240e18
    void InitFrame(); //80240eb4
    void ResetGX(); //80240f68
    void ResetVtx(); //80240fb0
    void ResetChannels(); //802410ec
    void ResetIndirect(); //802411c8
    void ResetTextures(); //80241240
    void ResetTexCoordGen(); //802412c8
    void ResetTevs(); //80241380
    void ResetPE(); //80241530
    void ResetCachedState(); //802415e8
    void SetPixelFmt(GX::PixelFmt pix_fmt, GX::ZFmt16 z_fmt); //80241668
    void SetProjection(Mtx44 projMtx, GX::ProjectionType projType); //802416fc
    void SetProjectionv(const float* p); //802417fc first float is GX::ProjectionType as a float
    //offset 1: mtx[0][0]
    //offset 2: mtx[0][3] (ortho) or mtx[0][2] (persp)
    //offset 3: mtx[1][1]
    //offset 4: mtx[1][3] (ortho) or mtx[1][2] (persp)
    //offset 5: mtx[2][2]
    //offset 6: mtx[2][3]
    void SetViewport(float xOrigin, float yOrigin, float width, float height, float near, float far); //802418d0
    void SetScissor(u32 left, u32 top, u32 width, u32 heigh); //802419fc
    void SetScissorBoxOffset(s32 xOffset, s32 yOffset); //80241acc
};

}//namespace EGG
#endif