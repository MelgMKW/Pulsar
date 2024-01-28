#ifndef _GXSTRUCT_
#define _GXSTRUCT_
#include <types.hpp>
#include <core/rvl/VI/VI.hpp>

typedef void* GXFifoObj;

typedef struct _GXColor {
    union {
        struct { u8 r, g, b, a; };
        u32 rgba;
    };
} GXColor;

typedef struct _GXColorS10 {
    s16 r, g, b, a;
} GXColorS10; //0x8

typedef struct _GXTexObj {
    u32 dummy[8];
} GXTexObj; //0x24

typedef struct _GXTlutObj {
    u32 dummy[3];
} GXTlutObj;

typedef struct _GXLightObj {
    u32 dummy[16];
} GXLightObj;

struct GXRenderModeObj {
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

#endif