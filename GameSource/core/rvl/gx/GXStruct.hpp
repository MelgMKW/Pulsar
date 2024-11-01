#ifndef _GXSTRUCT_
#define _GXSTRUCT_
#include <types.hpp>
#include <core/rvl/VI/VI.hpp>


namespace GX {

typedef void* FifoObj;

struct Color {
    union {
        struct { u8 r, g, b, a; };
        u32 rgba;
    };
};

struct ColorS10 {
    s16 r, g, b, a;
}; //0x8

struct TexObj {
    u32 mode0;
    u32 mode1; //0x4
    u32 image0; //0x8
    u32 image3; //0xc
    void* userData; //0x10
    TexFmt format; //0x14
    u32 tlutName; //0x18
    u16 loadCnt; //0x1c
    u8  loadFmt; //0x1e
    u8  flags; //0x1f
    //u32 dummy[8];
}; //0x20

struct TlutObj {
    u32 tlut;
    u32 loadTlut0;
    u16 numEntries;
    u8 padding[2];
    //u32 dummy[3];
};

struct LightObj {
    u32 reserved[3];
    u32 color;
    float a[3];
    float k[3];
    float lpos[3];
    float ldir[3];
    //u32 dummy[16];
};

struct  RenderModeObj {
    VI::TVMode viTVmode;
    u16 efbWidth; //0x4 xfb has the same width, it can only scale y dimension
    u16 efbHeight; //0x6
    u16 xfbHeight; //0x8
    u16 viXOrigin;
    u16 viYOrigin;
    u16 viWidth;
    u16 viHeight;
    VI::XFBMode xFBmode;
    u8 field_rendering;
    u8 aa;
    u8 sample_pattern[12][2]; //aa sample pattern
    u8 vfilter[7]; //vertical filter coeffs
};

}//namespace GX

#endif