#ifndef _GXSTRUCT_
#define _GXSTRUCT_
#include <types.hpp>
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
} GXTexObj;

typedef struct _GXTlutObj {
    u32 dummy[3];
} GXTlutObj;

typedef struct _GXLightObj {
    u32 dummy[16];
} GXLightObj;

#endif