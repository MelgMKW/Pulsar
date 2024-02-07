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
    u32 dummy[8];
}; //0x24

struct TlutObj {
    u32 dummy[3];
};

struct LightObj {
    u32 dummy[16];
};

struct RenderModeObj {
    VI::TVMode viTVmode;
    u16 efbWidth;
    u16 efbHeight;
    u16 xfbHeight;
    u16 viXOrigin;
    u16 viYOrigin;
    u16 viWidth;
    u16 viHeight;
    VI::XFBMode xFBmode;
    u8 field_rendering;
    u8 aa;
    u8 sample_pattern[12][2];
    u8 vfilter[7];
};

}//namespace GX

#endif