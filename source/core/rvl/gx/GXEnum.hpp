#ifndef _GXENUM_
#define _GXENUM_

#include <types.hpp>
#include <core/rvl/mtx/mtx.hpp>

typedef union _wgpipe
{
    volatile u8 U8;
    volatile s8 S8;
    volatile u16 U16;
    volatile s16 S16;
    volatile u32 U32;
    volatile s32 S32;
    volatile float F32;
} WGPipe;

#define wgPipe ((WGPipe *)0xCC008000)

static inline void GX_Position3f32(float x, float y, float z)
{
    wgPipe->F32 = x;
    wgPipe->F32 = y;
    wgPipe->F32 = z;
}

static inline void GX_Position3u16(u16 x, u16 y, u16 z)
{
    wgPipe->U16 = x;
    wgPipe->U16 = y;
    wgPipe->U16 = z;
}

static inline void GX_Position3s16(s16 x, s16 y, s16 z)
{
    wgPipe->S16 = x;
    wgPipe->S16 = y;
    wgPipe->S16 = z;
}

static inline void GX_Position3u8(u8 x, u8 y, u8 z)
{
    wgPipe->U8 = x;
    wgPipe->U8 = y;
    wgPipe->U8 = z;
}

static inline void GX_Position3s8(s8 x, s8 y, s8 z)
{
    wgPipe->S8 = x;
    wgPipe->S8 = y;
    wgPipe->S8 = z;
}

static inline void GX_Position2f32(float x, float y)
{
    wgPipe->F32 = x;
    wgPipe->F32 = y;
}

static inline void GX_Position2u16(u16 x, u16 y)
{
    wgPipe->U16 = x;
    wgPipe->U16 = y;
}

static inline void GX_Position2s16(s16 x, s16 y)
{
    wgPipe->S16 = x;
    wgPipe->S16 = y;
}

static inline void GX_Position2u8(u8 x, u8 y)
{
    wgPipe->U8 = x;
    wgPipe->U8 = y;
}

static inline void GX_Position2s8(s8 x, s8 y)
{
    wgPipe->S8 = x;
    wgPipe->S8 = y;
}

static inline void GX_Position1x8(u8 index)
{
    wgPipe->U8 = index;
}

static inline void GX_Position1x16(u16 index)
{
    wgPipe->U16 = index;
}

static inline void GX_Normal3f32(float nx, float ny, float nz)
{
    wgPipe->F32 = nx;
    wgPipe->F32 = ny;
    wgPipe->F32 = nz;
}

static inline void GX_Normal3s16(s16 nx, s16 ny, s16 nz)
{
    wgPipe->S16 = nx;
    wgPipe->S16 = ny;
    wgPipe->S16 = nz;
}

static inline void GX_Normal3s8(s8 nx, s8 ny, s8 nz)
{
    wgPipe->S8 = nx;
    wgPipe->S8 = ny;
    wgPipe->S8 = nz;
}

static inline void GX_Normal1x8(u8 index)
{
    wgPipe->U8 = index;
}

static inline void GX_Normal1x16(u16 index)
{
    wgPipe->U16 = index;
}

static inline void GX_Color4u8(u8 r, u8 g, u8 b, u8 a)
{
    wgPipe->U8 = r;
    wgPipe->U8 = g;
    wgPipe->U8 = b;
    wgPipe->U8 = a;
}

static inline void GX_Color3u8(u8 r, u8 g, u8 b)
{
    wgPipe->U8 = r;
    wgPipe->U8 = g;
    wgPipe->U8 = b;
}

static inline void GX_Color3f32(float r, float g, float b)
{
    wgPipe->U8 = (u8)(r * 255.0);
    wgPipe->U8 = (u8)(g * 255.0);
    wgPipe->U8 = (u8)(b * 255.0);
}

static inline void GX_Color1u32(u32 clr)
{
    wgPipe->U32 = clr;
}

static inline void GX_Color1u16(u16 clr)
{
    wgPipe->U16 = clr;
}

static inline void GX_Color1x8(u8 index)
{
    wgPipe->U8 = index;
}

static inline void GX_Color1x16(u16 index)
{
    wgPipe->U16 = index;
}

static inline void GX_TexCoord2f32(float s, float t)
{
    wgPipe->F32 = s;
    wgPipe->F32 = t;
}

static inline void GX_TexCoord2u16(u16 s, u16 t)
{
    wgPipe->U16 = s;
    wgPipe->U16 = t;
}

static inline void GX_TexCoord2s16(s16 s, s16 t)
{
    wgPipe->S16 = s;
    wgPipe->S16 = t;
}

static inline void GX_TexCoord2u8(u8 s, u8 t)
{
    wgPipe->U8 = s;
    wgPipe->U8 = t;
}

static inline void GX_TexCoord2s8(s8 s, s8 t)
{
    wgPipe->S8 = s;
    wgPipe->S8 = t;
}

static inline void GX_TexCoord1f32(float s)
{
    wgPipe->F32 = s;
}

static inline void GX_TexCoord1u16(u16 s)
{
    wgPipe->U16 = s;
}

static inline void GX_TexCoord1s16(s16 s)
{
    wgPipe->S16 = s;
}

static inline void GX_TexCoord1u8(u8 s)
{
    wgPipe->U8 = s;
}

static inline void GX_TexCoord1s8(s8 s)
{
    wgPipe->S8 = s;
}

static inline void GX_TexCoord1x8(u8 index)
{
    wgPipe->U8 = index;
}

static inline void GX_TexCoord1x16(u16 index)
{
    wgPipe->U16 = index;
}

static inline void GX_MatrixIndex1x8(u8 index)
{
    wgPipe->U8 = index;
}

struct TexMap {};

typedef struct ColorS10 {
    s16    r, g, b, a;
} ColorS10;

typedef struct _Color {
    u8  r, g, b, a;
} Color;

#define GXEnd()

#define GX_FALSE			0
#define GX_TRUE				1
#define GX_DISABLE			0
#define GX_ENABLE			1

/*clipmode Clipping mode*/
typedef enum _GXClipMode {
    GX_CLIP_ENABLE = 0,
    GX_CLIP_DISABLE = 1
} GXClipMode;


#define GX_FIFO_MINSIZE		(64*1024)			/*Smallest usable graphics FIFO size. */
#define GX_FIFO_HIWATERMARK	(16*1024)			/*Default hi watermark for FIFO buffer control. */
#define GX_FIFO_OBJSIZE		128

typedef enum _GXProjectionType {
    GX_PERSPECTIVE,
    GX_ORTHOGRAPHIC
} GXProjectionType;

typedef enum _GXMiscToken {
    GX_MT_XF_FLUSH = 1,
    GX_MT_DL_SAVE_CONTEXT = 2,
    GX_MT_ABORT_WAIT_COPYOUT = 3,
    GX_MT_NULL = 0
} GXMiscToken;

typedef enum _GXXFFlushVal {
    GX_XF_FLUSH_NONE = 0,
    GX_XF_FLUSH_SAFE = 8
} GXXFFlushVal;

/*channelid Color channel ID*/
typedef enum _GXChannelID {
    GX_COLOR0,
    GX_COLOR1,
    GX_ALPHA0,
    GX_ALPHA1,
    GX_COLOR0A0,          // Color 0 + Alpha 0
    GX_COLOR1A1,          // Color 1 + Alpha 1
    GX_COLOR_ZERO,        // RGBA = 0
    GX_ALPHA_BUMP,        // bump alpha 0-248, RGB=0
    GX_ALPHA_BUMPN,       // normalized bump alpha, 0-255, RGB=0
    GX_COLOR_NULL = 0xff
} GXChannelID;

/*mtxtype Matrix type*/
typedef enum _GXTexMtxType {
    GX_MTX3x4 = 0,
    GX_MTX2x4
} GXTexMtxType;

/*vtxfmt Vertex format index*/
typedef enum _GXVtxFmt {
    GX_VTXFMT0 = 0,
    GX_VTXFMT1,
    GX_VTXFMT2,
    GX_VTXFMT3,
    GX_VTXFMT4,
    GX_VTXFMT5,
    GX_VTXFMT6,
    GX_VTXFMT7,
    GX_MAX_VTXFMT
} GXVtxFmt;




/*vtxattrin Vertex data input type*/
typedef enum _GXAttrType {
    GX_NONE = 0,
    GX_DIRECT,
    GX_INDEX8,
    GX_INDEX16
} GXAttrType;




/*compsize Number of components in an attribute*/

typedef enum _GXCompType {
    GX_U8 = 0,				/*Unsigned 8-bit integer */
    GX_S8 = 1,				/*Signed 8-bit integer */
    GX_U16 = 2,				/*Unsigned 16-bit integer */
    GX_S16 = 3,				/*Signed 16-bit integer */
    GX_F32 = 4,				/*32-bit floating-point */
    GX_RGB565 = 0,			/*16-bit RGB */
    GX_RGB8 = 1,			/*24-bit RGB */
    GX_RGBX8 = 2,			/*32-bit RGBX */
    GX_RGBA4 = 3,			/*16-bit RGBA */
    GX_RGBA6 = 4,			/*24-bit RGBA */
    GX_RGBA8 = 5			/*32-bit RGBA */
} GXCompType;


/*comptype Attribute component type*/

typedef enum _GXCompCnt {
    GX_POS_XY = 0,	/*X,Y position */
    GX_POS_XYZ = 1,	/*X,Y,Z position */
    GX_NRM_XYZ = 0,	/*X,Y,Z normal */
    GX_NRM_NBT = 1, 	// one index per NBT
    GX_NRM_NBT3 = 2, 	// one index per each of N/B/T
    GX_CLR_RGB = 0,	/*RGB color */
    GX_CLR_RGBA = 1,	/*RGBA color */
    GX_TEX_S = 0,	/*One texture dimension */
    GX_TEX_ST = 1	/*Two texture dimensions */

} GXCompCnt;



/*vtxattr Vertex attribute array type*/
typedef enum _GXAttr {
    GX_VA_PNMTXIDX = 0,    // position/normal matrix index
    GX_VA_TEX0MTXIDX,      // texture 0 matrix index
    GX_VA_TEX1MTXIDX,      // texture 1 matrix index
    GX_VA_TEX2MTXIDX,      // texture 2 matrix index
    GX_VA_TEX3MTXIDX,      // texture 3 matrix index
    GX_VA_TEX4MTXIDX,      // texture 4 matrix index
    GX_VA_TEX5MTXIDX,      // texture 5 matrix index
    GX_VA_TEX6MTXIDX,      // texture 6 matrix index
    GX_VA_TEX7MTXIDX,      // texture 7 matrix index
    GX_VA_POS = 9,    // position
    GX_VA_NRM,             // normal
    GX_VA_CLR0,            // color 0
    GX_VA_CLR1,            // color 1
    GX_VA_TEX0,            // input texture coordinate 0
    GX_VA_TEX1,            // input texture coordinate 1
    GX_VA_TEX2,            // input texture coordinate 2
    GX_VA_TEX3,            // input texture coordinate 3
    GX_VA_TEX4,            // input texture coordinate 4
    GX_VA_TEX5,            // input texture coordinate 5
    GX_VA_TEX6,            // input texture coordinate 6
    GX_VA_TEX7,            // input texture coordinate 7

    GX_POS_MTX_ARRAY,      // position matrix array pointer
    GX_NRM_MTX_ARRAY,      // normal matrix array pointer
    GX_TEX_MTX_ARRAY,      // texture matrix array pointer
    GX_LIGHT_ARRAY,        // light parameter array pointer
    GX_VA_NBT,             // normal, bi-normal, tangent
    GX_VA_MAX_ATTR,        // maximum number of vertex attributes

    GX_VA_NULL = 0xff  // NULL attribute (to mark end of lists)
} GXAttr;


/*primtype Primitive type
Collection of primitive types that can be drawn by the GP.
Which type you use depends on your needs; however, performance can increase by using triangle strips or fans instead of discrete triangles.*/
typedef enum _GXPrimitive {
    GX_POINTS = 0xb8,	/*Draws a series of points. Each vertex is a single point. */
    GX_LINES = 0xa8,	/*Draws a series of unconnected line segments. Each pair of vertices makes a line. */
    GX_LINESTRIP = 0xb0,	/*Draws a series of lines. Each vertex (besides the first) makes a line between it and the previous. */
    GX_TRIANGLES = 0x90,	/*Draws a series of unconnected triangles. Three vertices make a single triangle. */
    GX_TRIANGLESTRIP = 0x98,	/*Draws a series of triangles. Each triangle (besides the first) shares a side with the previous triangle.* Each vertex (besides the first two) completes a triangle. */
    GX_TRIANGLEFAN = 0xa0,	/*Draws a single triangle fan. The first vertex is the "centerpoint". The second and third vertex complete* the first triangle. Each subsequent vertex completes another triangle which shares a side with the previous* triangle (except the first triangle) and has the centerpoint vertex as one of the vertices. */
    GX_QUADS = 0x80		/*Draws a series of unconnected quads. Every four vertices completes a quad. Internally, each quad is* translated into a pair of triangles. */
} GXPrimitive;


typedef enum _GXColorSrc {
    GX_SRC_REG = 0,
    GX_SRC_VTX
} GXColorSrc;

/*lightid Light ID*/
typedef enum _GXLightID {
    GX_LIGHT0 = 0x001,
    GX_LIGHT1 = 0x002,
    GX_LIGHT2 = 0x004,
    GX_LIGHT3 = 0x008,
    GX_LIGHT4 = 0x010,
    GX_LIGHT5 = 0x020,
    GX_LIGHT6 = 0x040,
    GX_LIGHT7 = 0x080,
    GX_MAX_LIGHT = 0x100,
    GX_LIGHT_NULL = 0x000
} GXLightID;


/*difffn Diffuse function*/
typedef enum _GXDiffuseFn {
    GX_DF_NONE = 0,
    GX_DF_SIGN,
    GX_DF_CLAMP
} GXDiffuseFn;


/*attenfunc Attenuation function*/
typedef enum _GXAttnFn {
    GX_AF_SPEC = 0,    // use specular attenuation
    GX_AF_SPOT = 1,    // use distance/spotlight attenuation
    GX_AF_NONE         // attenuation is off
} GXAttnFn;


/*os,nrm,tex,dtt matrix */
/*pnmtx Position-normal matrix index*/
typedef enum _GXPosNrmMtx {
    GX_PNMTX0 = 0,
    GX_PNMTX1 = 3,
    GX_PNMTX2 = 6,
    GX_PNMTX3 = 9,
    GX_PNMTX4 = 12,
    GX_PNMTX5 = 15,
    GX_PNMTX6 = 18,
    GX_PNMTX7 = 21,
    GX_PNMTX8 = 24,
    GX_PNMTX9 = 27
} GXPosNrmMtx;



/*texmtx Texture matrix index*/
typedef enum _GXTexMtx {
    GX_TEXMTX0 = 30,
    GX_TEXMTX1 = 33,
    GX_TEXMTX2 = 36,
    GX_TEXMTX3 = 39,
    GX_TEXMTX4 = 42,
    GX_TEXMTX5 = 45,
    GX_TEXMTX6 = 48,
    GX_TEXMTX7 = 51,
    GX_TEXMTX8 = 54,
    GX_TEXMTX9 = 57,
    GX_IDENTITY = 60
} GXTexMtx;


typedef enum _GXPTTexMtx {
    GX_PTTEXMTX0 = 64,
    GX_PTTEXMTX1 = 67,
    GX_PTTEXMTX2 = 70,
    GX_PTTEXMTX3 = 73,
    GX_PTTEXMTX4 = 76,
    GX_PTTEXMTX5 = 79,
    GX_PTTEXMTX6 = 82,
    GX_PTTEXMTX7 = 85,
    GX_PTTEXMTX8 = 88,
    GX_PTTEXMTX9 = 91,
    GX_PTTEXMTX10 = 94,
    GX_PTTEXMTX11 = 97,
    GX_PTTEXMTX12 = 100,
    GX_PTTEXMTX13 = 103,
    GX_PTTEXMTX14 = 106,
    GX_PTTEXMTX15 = 109,
    GX_PTTEXMTX16 = 112,
    GX_PTTEXMTX17 = 115,
    GX_PTTEXMTX18 = 118,
    GX_PTTEXMTX19 = 121,
    GX_PTIDENTITY = 125
} GXPTTexMtx;

/* tex coord id
   used by: XF: 0x1040,0x1050BP: 0x30
*/
/*texcoordid texture coordinate slot*/
typedef enum _GXTexCoordID {
    GX_TEXCOORD0 = 0x0,
    GX_TEXCOORD1,
    GX_TEXCOORD2,
    GX_TEXCOORD3,
    GX_TEXCOORD4,
    GX_TEXCOORD5,
    GX_TEXCOORD6,
    GX_TEXCOORD7,
    GX_MAX_TEXCOORD = 8,
    GX_TEXCOORD_NULL = 0xff
} GXTexCoordID;


/*texfmt Texture format*/
typedef enum _GXTexFmt {
#define _GX_TF_CTF     0x20 /* copy-texture-format only */
#define _GX_TF_ZTF     0x10 /* Z-texture-format */
    GX_TF_I4 = 0x0,
    GX_TF_I8 = 0x1,
    GX_TF_IA4 = 0x2,
    GX_TF_IA8 = 0x3,
    GX_TF_RGB565 = 0x4,
    GX_TF_RGB5A3 = 0x5,
    GX_TF_RGBA8 = 0x6,
    GX_TF_CMPR = 0xE,
    GX_CTF_R4 = 0x0 | _GX_TF_CTF,		/*For copying 4 bits from red */
    GX_CTF_RA4 = 0x2 | _GX_TF_CTF,		/*For copying 4 bits from red, 4 bits from alpha */
    GX_CTF_RA8 = 0x3 | _GX_TF_CTF,		/*For copying 8 bits from red, 8 bits from alpha */
    GX_CTF_YUVA8 = 0x6 | _GX_TF_CTF,
    GX_CTF_A8 = 0x7 | _GX_TF_CTF,		/*For copying 8 bits from alpha */
    GX_CTF_R8 = 0x8 | _GX_TF_CTF,		/*For copying 8 bits from red */
    GX_CTF_G8 = 0x9 | _GX_TF_CTF,		/*For copying 8 bits from green */
    GX_CTF_B8 = 0xA | _GX_TF_CTF,		/*For copying 8 bits from blue */
    GX_CTF_RG8 = 0xB | _GX_TF_CTF,		/*For copying 8 bits from red, 8 bits from green */
    GX_CTF_GB8 = 0xC | _GX_TF_CTF,		/*For copying 8 bits from green, 8 bits from blue */
    GX_TF_Z8 = 0x1 | _GX_TF_ZTF,		/*For texture copy, specifies upper 8 bits of Z */
    GX_TF_Z16 = 0x3 | _GX_TF_ZTF,		/*For texture copy, specifies upper 16 bits of Z */
    GX_TF_Z24X8 = 0x6 | _GX_TF_ZTF,		/*For texture copy, copies 24 Z bits and 0xFF */
    GX_CTF_Z4 = 0x0 | _GX_TF_ZTF | _GX_TF_CTF,	/*For copying 4 upper bits from Z */
    GX_CTF_Z8M = 0x9 | _GX_TF_ZTF | _GX_TF_CTF,	/*For copying the middle 8 bits of Z */
    GX_CTF_Z8L = 0xA | _GX_TF_ZTF | _GX_TF_CTF,	/*For copying the lower 8 bits of Z */
    GX_CTF_Z16L = 0xC | _GX_TF_ZTF | _GX_TF_CTF,	/*For copying the lower 16 bits of Z */
    GX_TF_A8 = GX_CTF_A8
} GXTexFmt;

typedef enum _GXCITexFmt {
    GX_TF_C4 = 0x8,
    GX_TF_C8 = 0x9,
    GX_TF_C14X2 = 0xa
} GXCITexFmt;

typedef enum _GXTlutFmt {
    GX_TL_IA8 = 0x0,
    GX_TL_RGB565 = 0x1,
    GX_TL_RGB5A3 = 0x2,
    GX_MAX_TLUTFMT
} GXTlutFmt;

/* gx tlut size */
typedef enum _GXTlutSize {
    GX_TLUT_16 = 1, // number of 16 entry blocks.
    GX_TLUT_32 = 2,
    GX_TLUT_64 = 4,
    GX_TLUT_128 = 8,
    GX_TLUT_256 = 16,
    GX_TLUT_512 = 32,
    GX_TLUT_1K = 64,
    GX_TLUT_2K = 128,
    GX_TLUT_4K = 256,
    GX_TLUT_8K = 512,
    GX_TLUT_16K = 1024
} GXTlutSize;

/*ztexop Z Texture operator*/
typedef enum _GXZTexOp {
    GX_ZT_DISABLE,
    GX_ZT_ADD,				/*Add a Z texel to reference Z */
    GX_ZT_REPLACE,			/*Replace reference Z with Z texel */
    GX_MAX_ZTEXOP
} GXZTexOp;




/*texgentyp Texture coordinate generation type*/
typedef enum _GXTexGenType {
    GX_TG_MTX3x4 = 0,	/*3x4 matrix multiply on the input attribute and generate S,T,Q coordinates; S,T are then divided * by Q to produce the actual 2D texture coordinates. */
    GX_TG_MTX2x4,		/*2x4 matrix multiply on the input attribute and generate S,T texture coordinates. */
    GX_TG_BUMP0,		/*Use light 0 in the bump map calculation. */
    GX_TG_BUMP1,		/*Use light 1 in the bump map calculation. */
    GX_TG_BUMP2,		/*Use light 2 in the bump map calculation. */
    GX_TG_BUMP3,		/*Use light 3 in the bump map calculation. */
    GX_TG_BUMP4,		/*Use light 4 in the bump map calculation. */
    GX_TG_BUMP5,		/*Use light 5 in the bump map calculation. */
    GX_TG_BUMP6,		/*Use light 6 in the bump map calculation. */
    GX_TG_BUMP7,		/*Use light 7 in the bump map calculation. */
    GX_TG_SRTG			/*Coordinates generated from vertex lighting results; one of the color channel results is converted* into texture coordinates. */
} GXTexGenType;



/*texgensrc Texture coordinate source*/
typedef enum _GXTexGenSrc {
    GX_TG_POS = 0,
    GX_TG_NRM,
    GX_TG_BINRM,
    GX_TG_TANGENT,
    GX_TG_TEX0,
    GX_TG_TEX1,
    GX_TG_TEX2,
    GX_TG_TEX3,
    GX_TG_TEX4,
    GX_TG_TEX5,
    GX_TG_TEX6,
    GX_TG_TEX7,
    GX_TG_TEXCOORD0,
    GX_TG_TEXCOORD1,
    GX_TG_TEXCOORD2,
    GX_TG_TEXCOORD3,
    GX_TG_TEXCOORD4,
    GX_TG_TEXCOORD5,
    GX_TG_TEXCOORD6,
    GX_TG_COLOR0,
    GX_TG_COLOR1
} GXTexGenSrc;



/*compare Compare type*/
typedef enum _GXCompare {
    GX_NEVER,
    GX_LESS,
    GX_EQUAL,
    GX_LEQUAL,
    GX_GREATER,
    GX_NEQUAL,
    GX_GEQUAL,
    GX_ALWAYS
} GXCompare;


/* Text Wrap Mode */
typedef enum _GXTexWrapMode {
    GX_CLAMP,
    GX_REPEAT,
    GX_MIRROR,
    GX_MAX_TEXWRAPMODE
} GXTexWrapMode;

/*blendmode Blending type*/
typedef enum _GXBlendMode {
    GX_BM_NONE,			/*Write input directly to EFB */
    GX_BM_BLEND,		/*Blend using blending equation */
    GX_BM_LOGIC,		/*Blend using bitwise operation */
    GX_BM_SUBTRACT,		/*Input subtracts from existing pixel */
    GX_MAX_BLENDMODE
} GXBlendMode;


/*blendfactor Blending control
Each pixel (source or destination) is multiplied by any of these controls.*/
typedef enum _GXBlendFactor {
    GX_BL_ZERO,				/*0.0 */
    GX_BL_ONE,				/*1.0 */
    GX_BL_SRCCLR,			/*source color */
    GX_BL_INVSRCCLR,		/*1.0 - (source color) */
    GX_BL_SRCALPHA,			/*source alpha */
    GX_BL_INVSRCALPHA,		/*1.0 - (source alpha) */
    GX_BL_DSTALPHA,			/*framebuffer alpha */
    GX_BL_INVDSTALPHA,		/*1.0 - (FB alpha) */
    GX_BL_DSTCLR = GX_BL_SRCCLR,
    GX_BL_INVDSTCLR = GX_BL_INVSRCCLR
} GXBlendFactor;


/*logicop Logical operation type
Destination (dst) acquires the value of one of these operations, given in C syntax.*/
typedef enum _GXLogicOp {
    GX_LO_CLEAR,     /*0 */
    GX_LO_AND,       /*src & dst */
    GX_LO_REVAND,    /*src & ~dst */
    GX_LO_COPY,      /*src */
    GX_LO_INVAND,    /*~src & dst */
    GX_LO_NOOP,      /*dst */
    GX_LO_XOR,       /*src ^ dst */
    GX_LO_OR,        /*src | dst */
    GX_LO_NOR,       /*~(src | dst) */
    GX_LO_EQUIV,     /*~(src ^ dst) */
    GX_LO_INV,    	 /*~dst */
    GX_LO_REVOR,     /*src | ~dst */
    GX_LO_INVCOPY,   /*~src */
    GX_LO_INVOR,     /*~src | dst */
    GX_LO_NAND,      /*~(src & dst) */
    GX_LO_SET        /*1 */
} GXLogicOp;


/*texoff Texture offset value
Used for texturing points or lines.*/

typedef enum _GXTexOffset {
    GX_TO_ZERO,
    GX_TO_SIXTEENTH,
    GX_TO_EIGHTH,
    GX_TO_FOURTH,
    GX_TO_HALF,
    GX_TO_ONE,
    GX_MAX_TEXOFFSET
} GXTexOffset;




/*tevdefmode TEV combiner operation
Color/Alpha combiner modes for GX_SetTevOp().
For these equations, <i>Cv</i> is the output color for the stage, <i>Cr</i> is the output color of previous stage, and <i>Ct</i> is the texture color. <i>Av</i> is the output alpha for a stage, <i>Ar</i> is the output alpha of previous stage, and <i>At</i> is the texture alpha. As a special case, rasterized color (<tt>GX_CC_RASC</tt>) is used as <i>Cr</i> and rasterized alpha (<tt>GX_CA_RASA</tt>) is used as <i>Ar</i> at the first TEV stage because there is no previous stage.*/
typedef enum _GXTevMode {
    GX_MODULATE,		/*<i>Cv</i>=<i>CrCt</i>; <i>Av</i>=<i>ArAt</i> */
    GX_DECAL,			/*<i>Cv</i>=(1-<i>At</i>)<i>Cr</i> + <i>AtCt</i>; <i>Av</i>=<i>Ar</i> */
    GX_BLEND,			/*<i>Cv=(1-<i>Ct</i>)<i>Cr</i> + <i>Ct</i>; <i>Av</i>=<i>AtAr</i> */
    GX_REPLACE,			/*<i>Cv=<i>Ct</i>; <i>Ar=<i>At</i> */
    GX_PASSCLR			/*<i>Cv=<i>Cr</i>; <i>Av=<i>Ar</i> */
} GXTevMode;




/*tevcolorarg TEV color combiner input*/

typedef enum _GXTevColorArg {
    GX_CC_CPREV,	/*Use the color value from previous TEV stage */
    GX_CC_APREV,	/*Use the alpha value from previous TEV stage */
    GX_CC_C0,		/*Use the color value from the color/output register 0 */
    GX_CC_A0,		/*Use the alpha value from the color/output register 0 */
    GX_CC_C1,		/*Use the color value from the color/output register 1 */
    GX_CC_A1,		/*Use the alpha value from the color/output register 1 */
    GX_CC_C2,		/*Use the color value from the color/output register 2 */
    GX_CC_A2,		/*Use the alpha value from the color/output register 2 */
    GX_CC_TEXC,		/*Use the color value from texture */
    GX_CC_TEXA,		/*Use the alpha value from texture */
    GX_CC_RASC,		/*Use the color value from rasterizer */
    GX_CC_RASA,		/*Use the alpha value from rasterizer */
    GX_CC_ONE,
    GX_CC_HALF,
    GX_CC_KONST,
    GX_CC_ZERO		/*Use to pass zero value */
} GXTevColorArg;




/*tevalphaarg TEV alpha combiner input*/

typedef enum _GXTevAlphaArg {
    GX_CA_APREV,	/*Use the alpha value from previous TEV stage */
    GX_CA_A0,		/*Use the alpha value from the color/output register 0 */
    GX_CA_A1,		/*Use the alpha value from the color/output register 1 */
    GX_CA_A2,		/*Use the alpha value from the color/output register 2 */
    GX_CA_TEXA,		/*Use the alpha value from texture */
    GX_CA_RASA,		/*Use the alpha value from rasterizer */
    GX_CA_KONST,
    GX_CA_ZERO		/*Use to pass zero value */
} GXTevAlphaArg;




/*tevstage TEV stage
The GameCube's Graphics Processor (GP) can use up to 16 stages to compute a texel for a particular surface. By default, each texture will use two stages, but it can be configured through various functions calls.
This is different from \ref texmapid s, where textures are loaded into.*/

typedef enum _GXTevStageID {
    GX_TEVSTAGE0,
    GX_TEVSTAGE1,
    GX_TEVSTAGE2,
    GX_TEVSTAGE3,
    GX_TEVSTAGE4,
    GX_TEVSTAGE5,
    GX_TEVSTAGE6,
    GX_TEVSTAGE7,
    GX_TEVSTAGE8,
    GX_TEVSTAGE9,
    GX_TEVSTAGE10,
    GX_TEVSTAGE11,
    GX_TEVSTAGE12,
    GX_TEVSTAGE13,
    GX_TEVSTAGE14,
    GX_TEVSTAGE15,
    GX_MAX_TEVSTAGE
} GXTevStageID;




/*tevop TEV combiner operator*/
typedef enum _GXTevOp {
    GX_TEV_ADD = 0,
    GX_TEV_SUB = 1,
    GX_TEV_COMP_R8_GT = 8,
    GX_TEV_COMP_R8_EQ = 9,
    GX_TEV_COMP_GR16_GT = 10,
    GX_TEV_COMP_GR16_EQ = 11,
    GX_TEV_COMP_BGR24_GT = 12,
    GX_TEV_COMP_BGR24_EQ = 13,
    GX_TEV_COMP_RGB8_GT = 14,
    GX_TEV_COMP_RGB8_EQ = 15,
    GX_TEV_COMP_A8_GT = GX_TEV_COMP_RGB8_GT, // for alpha channel
    GX_TEV_COMP_A8_EQ = GX_TEV_COMP_RGB8_EQ  // for alpha channel
} GXTevOp;

typedef enum _GXTevBias {
    GX_TB_ZERO,
    GX_TB_ADDHALF,
    GX_TB_SUBHALF,
    GX_MAX_TEVBIAS
} GXTevBias;



typedef enum _GXTevClampMode {
    GX_TC_LINEAR,
    GX_TC_GE,
    GX_TC_EQ,
    GX_TC_LE,
    GX_MAX_TEVCLAMPMODE
} GXTevClampMode;




/*tevscale TEV scale value*/

typedef enum _GXTevScale {
    GX_CS_SCALE_1,
    GX_CS_SCALE_2,
    GX_CS_SCALE_4,
    GX_CS_DIVIDE_2,
    GX_MAX_TEVSCALE
} GXTevScale;




/*tevcoloutreg TEV color/output register*/

typedef enum _GXTevRegID {
    GX_TEVPREV = 0,
    GX_TEVREG0,
    GX_TEVREG1,
    GX_TEVREG2,
    GX_MAX_TEVREG
} GXTevRegID;




/*cullmode Backface culling mode*/
typedef enum _GXCullMode {
    GX_CULL_NONE,		/*Do not cull any primitives. *
    GX_CULL_FRONT,		/*Cull front-facing primitives.
    GX_CULL_BACK,		/*Cull back-facing primitives.
    GX_CULL_ALL			/*Cull all primitives. */
} GXCullMode;


/*texmapid texture map slot
Texture map slots to hold textures in.
The GameCube's Graphics Processor (GP) can apply up to eight textures to a single surface. Those textures are assigned one of these slots. Various operations used on or with a particular texture will also take one of these items, including operations regarding texture coordinate generation (although not necessarily on the same slot).
This is different from \ref tevstage s, which are the actual quanta for work with textures.*/
typedef enum _GXTexMapID {
    GX_TEXMAP0,				/*Texture map slot 0 */
    GX_TEXMAP1,				/*Texture map slot 1 */
    GX_TEXMAP2,				/*Texture map slot 2 */
    GX_TEXMAP3,				/*Texture map slot 3 */
    GX_TEXMAP4,				/*Texture map slot 4 */
    GX_TEXMAP5,				/*Texture map slot 5 */
    GX_TEXMAP6,				/*Texture map slot 6 */
    GX_TEXMAP7,				/*Texture map slot 7 */
    GX_MAX_TEXMAP,
    GX_TEXMAP_NULL = 0xff,	/*No texmap */
    GX_TEX_DISABLE = 0x100 	/*Disable texmap lookup for this texmap slot (use bitwise OR with a texture map slot). */
} GXTexMapID;



/*alphaop Alpha combine control*/
typedef enum _GXAlphaOp {
    GX_AOP_AND,
    GX_AOP_OR,
    GX_AOP_XOR,
    GX_AOP_XNOR,
    GX_MAX_ALPHAOP
} GXAlphaOp;


typedef enum _GXTevKColorID {
    GX_KCOLOR0,
    GX_KCOLOR1,
    GX_KCOLOR2,
    GX_KCOLOR3,
    GX_MAX_KCOLOR
} GXTevKColorID;

/*tevkcolorsel TEV constant color selection*/

typedef enum _GXTevKColorSel {
    GX_TEV_KCSEL_8_8 = 0x00,
    GX_TEV_KCSEL_7_8 = 0x01,
    GX_TEV_KCSEL_6_8 = 0x02,
    GX_TEV_KCSEL_5_8 = 0x03,
    GX_TEV_KCSEL_4_8 = 0x04,
    GX_TEV_KCSEL_3_8 = 0x05,
    GX_TEV_KCSEL_2_8 = 0x06,
    GX_TEV_KCSEL_1_8 = 0x07,

    GX_TEV_KCSEL_1 = GX_TEV_KCSEL_8_8,
    GX_TEV_KCSEL_3_4 = GX_TEV_KCSEL_6_8,
    GX_TEV_KCSEL_1_2 = GX_TEV_KCSEL_4_8,
    GX_TEV_KCSEL_1_4 = GX_TEV_KCSEL_2_8,

    GX_TEV_KCSEL_K0 = 0x0C,
    GX_TEV_KCSEL_K1 = 0x0D,
    GX_TEV_KCSEL_K2 = 0x0E,
    GX_TEV_KCSEL_K3 = 0x0F,
    GX_TEV_KCSEL_K0_R = 0x10,
    GX_TEV_KCSEL_K1_R = 0x11,
    GX_TEV_KCSEL_K2_R = 0x12,
    GX_TEV_KCSEL_K3_R = 0x13,
    GX_TEV_KCSEL_K0_G = 0x14,
    GX_TEV_KCSEL_K1_G = 0x15,
    GX_TEV_KCSEL_K2_G = 0x16,
    GX_TEV_KCSEL_K3_G = 0x17,
    GX_TEV_KCSEL_K0_B = 0x18,
    GX_TEV_KCSEL_K1_B = 0x19,
    GX_TEV_KCSEL_K2_B = 0x1A,
    GX_TEV_KCSEL_K3_B = 0x1B,
    GX_TEV_KCSEL_K0_A = 0x1C,
    GX_TEV_KCSEL_K1_A = 0x1D,
    GX_TEV_KCSEL_K2_A = 0x1E,
    GX_TEV_KCSEL_K3_A = 0x1F
} GXTevKColorSel;

typedef enum _GXTevKAlphaSel {
    GX_TEV_KASEL_8_8 = 0x00,
    GX_TEV_KASEL_7_8 = 0x01,
    GX_TEV_KASEL_6_8 = 0x02,
    GX_TEV_KASEL_5_8 = 0x03,
    GX_TEV_KASEL_4_8 = 0x04,
    GX_TEV_KASEL_3_8 = 0x05,
    GX_TEV_KASEL_2_8 = 0x06,
    GX_TEV_KASEL_1_8 = 0x07,
    GX_TEV_KASEL_1 = GX_TEV_KASEL_8_8,
    GX_TEV_KASEL_3_4 = GX_TEV_KASEL_6_8,
    GX_TEV_KASEL_1_2 = GX_TEV_KASEL_4_8,
    GX_TEV_KASEL_1_4 = GX_TEV_KASEL_2_8,
    GX_TEV_KASEL_K0_R = 0x10,
    GX_TEV_KASEL_K1_R = 0x11,
    GX_TEV_KASEL_K2_R = 0x12,
    GX_TEV_KASEL_K3_R = 0x13,
    GX_TEV_KASEL_K0_G = 0x14,
    GX_TEV_KASEL_K1_G = 0x15,
    GX_TEV_KASEL_K2_G = 0x16,
    GX_TEV_KASEL_K3_G = 0x17,
    GX_TEV_KASEL_K0_B = 0x18,
    GX_TEV_KASEL_K1_B = 0x19,
    GX_TEV_KASEL_K2_B = 0x1A,
    GX_TEV_KASEL_K3_B = 0x1B,
    GX_TEV_KASEL_K0_A = 0x1C,
    GX_TEV_KASEL_K1_A = 0x1D,
    GX_TEV_KASEL_K2_A = 0x1E,
    GX_TEV_KASEL_K3_A = 0x1F
} GXTevKAlphaSel;

typedef enum _GXTevSwapSel {
    GX_TEV_SWAP0 = 0,
    GX_TEV_SWAP1,
    GX_TEV_SWAP2,
    GX_TEV_SWAP3,
    GX_MAX_TEVSWAP
} GXTevSwapSel;



typedef enum _GXTevColorChan {
    GX_CH_RED = 0,
    GX_CH_GREEN,
    GX_CH_BLUE,
    GX_CH_ALPHA
} GXTevColorChan;

/*indtexstage Indirect texture stage*/
typedef enum _GXIndTexStageID {
    GX_INDTEXSTAGE0,
    GX_INDTEXSTAGE1,
    GX_INDTEXSTAGE2,
    GX_INDTEXSTAGE3,
    GX_MAX_INDTEXSTAGE
} GXIndTexStageID;


/*indtexformat Indirect texture format
Bits for the indirect offsets are extracted from the high end of each component byte. Bits for the bump alpha are extraced off the low end of the byte. For <tt>GX_ITF_8</tt>, the byte is duplicated for the offset and the bump alpha.*/
typedef enum _GXIndTexFormat {
    GX_ITF_8,       // 8 bit texture offsets.
    GX_ITF_5,       // 5 bit texture offsets.
    GX_ITF_4,       // 4 bit texture offsets.
    GX_ITF_3,       // 3 bit texture offsets.
    GX_MAX_ITFORMAT
} GXIndTexFormat;


/*indtexbias Indirect texture bias select
Indicates which components of the indirect offset should receive a bias value.
The bias is fixed at -128 for <tt>GX_ITF_8</tt> and +1 for the other formats. The bias happens prior to the indirect matrix multiply.*/
typedef enum _GXIndTexBiasSel {
    GX_ITB_NONE,
    GX_ITB_S,
    GX_ITB_T,
    GX_ITB_ST,
    GX_ITB_U,
    GX_ITB_SU,
    GX_ITB_TU,
    GX_ITB_STU,
    GX_MAX_ITBIAS
} GXIndTexBiasSel;


/*indtexmtx Indirect texture matrix*/
typedef enum _GXIndTexMtxID {
    GX_ITM_OFF,				/*Specifies a matrix of all zeroes. */
    GX_ITM_0,				/*Specifies indirect matrix 0, indirect scale 0. */
    GX_ITM_1,				/*Specifies indirect matrix 1, indirect scale 1. */
    GX_ITM_2,				/*Specifies indirect matrix 2, indirect scale 2. */
    GX_ITM_S0 = 5,			/*Specifies dynamic S-type matrix, indirect scale 0. */
    GX_ITM_S1,				/*Specifies dynamic S-type matrix, indirect scale 1. */
    GX_ITM_S2,				/*Specifies dynamic S-type matrix, indirect scale 2. */
    GX_ITM_T0 = 9,			/*Specifies dynamic T-type matrix, indirect scale 0. */
    GX_ITM_T1,				/*Specifies dynamic T-type matrix, indirect scale 1. */
    GX_ITM_T2				/*Specifies dynamic T-type matrix, indirect scale 2. */
} GXIndTexMtxID;


/*indtexwrap Indirect texture wrap value
Indicates whether the regular texture coordinate should be wrapped before being added to the offset.
<tt>GX_ITW_OFF</tt> specifies no wrapping. <tt>GX_ITW_0</tt> will zero out the regular texture coordinate.*/
typedef enum _GXIndTexWrap {
    GX_ITW_OFF,     // no wrapping
    GX_ITW_256,     // wrap 256
    GX_ITW_128,     // wrap 128
    GX_ITW_64,      // wrap 64
    GX_ITW_32,      // wrap 32
    GX_ITW_16,      // wrap 16
    GX_ITW_0,       // wrap 0
    GX_MAX_ITWRAP
} GXIndTexWrap;


/*indtexalphasel Indirect texture bump alpha select
Indicates which offset component should provide the "bump" alpha output for the given TEV stage.
Bump alpha is not available for TEV stage 0.*/
typedef enum _GXIndTexAlphaSel {
    GX_ITBA_OFF,
    GX_ITBA_S,
    GX_ITBA_T,
    GX_ITBA_U,
    GX_MAX_ITBALPHA
} GXIndTexAlphaSel;


/*indtexscale Indirect texture scale
Specifies an additional scale value that may be applied to the texcoord used for an indirect initial lookup (not a TEV stage regular lookup).
The scale value is a fraction; thus <tt>GX_ITS_32</tt> means to divide the texture coordinate values by 32.*/
typedef enum _GXIndTexScale {
    GX_ITS_1,       // Scale by 1.
    GX_ITS_2,       // Scale by 1/2.
    GX_ITS_4,       // Scale by 1/4.
    GX_ITS_8,       // Scale by 1/8.
    GX_ITS_16,      // Scale by 1/16.
    GX_ITS_32,      // Scale by 1/32.
    GX_ITS_64,      // Scale by 1/64.
    GX_ITS_128,     // Scale by 1/128.
    GX_ITS_256,     // Scale by 1/256.
    GX_MAX_ITSCALE
} GXIndTexScale;


/*fogtype Fog equation control*/
typedef enum _GXFogType {
    GX_FOG_NONE = 0x00,
    GX_FOG_PERSP_LIN = 0x02,
    GX_FOG_PERSP_EXP = 0x04,
    GX_FOG_PERSP_EXP2 = 0x05,
    GX_FOG_PERSP_REVEXP = 0x06,
    GX_FOG_PERSP_REVEXP2 = 0x07,
    GX_FOG_ORTHO_LIN = 0x0A,
    GX_FOG_ORTHO_EXP = 0x0C,
    GX_FOG_ORTHO_EXP2 = 0x0D,
    GX_FOG_ORTHO_REVEXP = 0x0E,
    GX_FOG_ORTHO_REVEXP2 = 0x0F,
    GX_FOG_LIN = GX_FOG_PERSP_LIN,
    GX_FOG_EXP = GX_FOG_PERSP_EXP,
    GX_FOG_EXP2 = GX_FOG_PERSP_EXP2,
    GX_FOG_REVEXP = GX_FOG_PERSP_REVEXP,
    GX_FOG_REVEXP2 = GX_FOG_PERSP_REVEXP2
} GXFogType;



/*pixel format */
typedef enum _GXPixelFmt {
    GX_PF_RGB8_Z24,
    GX_PF_RGBA6_Z24,
    GX_PF_RGB565_Z16,
    GX_PF_Z24,
    GX_PF_Y8,
    GX_PF_U8,
    GX_PF_V8,
    GX_PF_YUV420
} GXPixelFmt;

/*zfmt Compressed Z format*/
typedef enum _GXZFmt16 {
    GX_ZC_LINEAR,
    GX_ZC_NEAR,
    GX_ZC_MID,
    GX_ZC_FAR
} GXZFmt16;


/*xfbclamp XFB clamp modes*/

typedef enum _GXFBClamp {
    GX_CLAMP_NONE,
    GX_CLAMP_TOP,
    GX_CLAMP_BOTTOM
} GXFBClamp;




/*gammamode Gamma values*/

typedef enum _GXGamma {
    GX_GM_1_0,
    GX_GM_1_7,
    GX_GM_2_2
} GXGamma;




/*copymode EFB copy mode
Controls whether all lines, only even lines, or only odd lines are copied from the EFB.*/
typedef enum _GXCopyMode {
    GX_COPY_PROGRESSIVE = 0,
    GX_COPY_INTLC_EVEN = 2,
    GX_COPY_INTLC_ODD = 3
} GXCopyMode;


/*alphareadmode Alpha read mode*/
typedef enum _GXAlphaReadMode {
    GX_READ_00,			/*Always read 0x00. */
    GX_READ_FF,			/*Always read 0xFF. */
    GX_READ_NONE		/*Always read the real alpha value. */
} GXAlphaReadMode;



/*texcachesize Texture cache size
Size of texture cache regions.*/
typedef enum _GXTexCacheSize {
    GX_TEXCACHE_32K,
    GX_TEXCACHE_128K,
    GX_TEXCACHE_512K,
    GX_TEXCACHE_NONE
} GXTexCacheSize;


/*distattnfn Brightness decreasing function
Type of the brightness decreasing function by distance.*/
typedef enum _GXDistAttnFn {
    GX_DA_OFF = 0,
    GX_DA_GENTLE,
    GX_DA_MEDIUM,
    GX_DA_STEEP
} GXDistAttnFn;


/*spotfn Spot illumination distribution function*/
typedef enum _GXSpotFn {
    GX_SP_OFF = 0,
    GX_SP_FLAT,
    GX_SP_COS,
    GX_SP_COS2,
    GX_SP_SHARP,
    GX_SP_RING1,
    GX_SP_RING2
} GXSpotFn;


/*texfilter Texture filter types*/

typedef enum _GXTexFilter {
    GX_NEAR,					/*Point sampling, no mipmap */
    GX_LINEAR,					/*Bilinear filtering, no mipmap */
    GX_NEAR_MIP_NEAR,			/*Point sampling, discrete mipmap */
    GX_LIN_MIP_NEAR,			/*Bilinear filtering, discrete mipmap */
    GX_NEAR_MIP_LIN,			/*Point sampling, linear mipmap */
    GX_LIN_MIP_LIN				/*Trilinear filtering */
} GXTexFilter;



/*anisotropy Maximum anisotropy filter control*/
typedef enum _GXAnisotropy {
    GX_ANISO_1,
    GX_ANISO_2,
    GX_ANISO_4,
    GX_MAX_ANISOTROPY
} GXAnisotropy;


/*vcachemetrics Vertex cache performance counter*/
typedef enum _GXVCachePerf {
    GX_VC_POS,
    GX_VC_NRM,
    GX_VC_CLR0,
    GX_VC_CLR1,
    GX_VC_TEX0,
    GX_VC_TEX1,
    GX_VC_TEX2,
    GX_VC_TEX3,
    GX_VC_TEX4,
    GX_VC_TEX5,
    GX_VC_TEX6,
    GX_VC_TEX7,
    GX_VC_ALL = 0xf
} GXVCachePerf;


/*perf0metrics Performance counter 0 metric
Performance counter 0 is used to measure attributes dealing with geometry and primitives, such as triangle counts and clipping ratios.
<tt>GX_PERF0_XF_*</tt> measure how many GP cycles are spent in each stage of the XF.<br><br>
The triangle metrics (<tt>GX_PERF0_TRIANGLES_*</tt>) allow counting triangles under specific conditions or with specific attributes.<br><br>
<tt>GX_PERF0_TRIANGLES_*TEX</tt> count triangles based on the number of texture coordinates supplied; <tt>GX_PERF0_TRIANGLES_*CLR</tt> count triangles based on the number of colors supplied.<br><br>
The quad metrics allow you to count the number of quads (2x2 pixels) the GP processes. The term <i>coverage</i> is used to indicate how many pixels in the quad are actually part of the triangle being rasterized. For example, a coverage of 4 means all pixels in the quad intersect the triangle. A coverage of 1 indicates that only 1 pixel in the quad intersected the triangle.*/

typedef enum _GXPerf0 {
    GX_PERF0_VERTICES,					/*Number of vertices processed by the GP. */
    GX_PERF0_CLIP_VTX,					/*Number of vertices that were clipped by the GP. */
    GX_PERF0_CLIP_CLKS,					/*Number of GP clocks spent clipping. */
    GX_PERF0_XF_WAIT_IN,				/*Number of cycles the XF is waiting on input. If the XF is waiting a large percentage * of the total time, it may indicate that the CPU is not supplying data fast enough to * keep the GP busy. */
    GX_PERF0_XF_WAIT_OUT,				/*Number of cycles the XF waits to send its output to the rest of the GP pipeline. If * the XF cannot output, it may indicate that the GP is currently fill-rate limited. */
    GX_PERF0_XF_XFRM_CLKS,				/*Number of cycles the transform engine is busy. */
    GX_PERF0_XF_LIT_CLKS,				/*Number of cycles the lighting engine is busy. */
    GX_PERF0_XF_BOT_CLKS,				/*Number of cycles the bottom of the pipe (result combiner) is busy. */
    GX_PERF0_XF_REGLD_CLKS,				/*Number of cycles are spent loading XF state registers. */
    GX_PERF0_XF_REGRD_CLKS,				/*Number of cycles the XF reads the state registers. */
    GX_PERF0_CLIP_RATIO,
    GX_PERF0_TRIANGLES,					/*Number of triangles. */
    GX_PERF0_TRIANGLES_CULLED,			/*Number of triangles that <i>failed</i> the front-face/back-face culling test. */
    GX_PERF0_TRIANGLES_PASSED,			/*Number of triangles that <i>passed</i> the front-face/back-face culling test. */
    GX_PERF0_TRIANGLES_SCISSORED,		/*Number of triangles that are scissored. */
    GX_PERF0_TRIANGLES_0TEX,
    GX_PERF0_TRIANGLES_1TEX,
    GX_PERF0_TRIANGLES_2TEX,
    GX_PERF0_TRIANGLES_3TEX,
    GX_PERF0_TRIANGLES_4TEX,
    GX_PERF0_TRIANGLES_5TEX,
    GX_PERF0_TRIANGLES_6TEX,
    GX_PERF0_TRIANGLES_7TEX,
    GX_PERF0_TRIANGLES_8TEX,
    GX_PERF0_TRIANGLES_0CLR,
    GX_PERF0_TRIANGLES_1CLR,
    GX_PERF0_TRIANGLES_2CLR,
    GX_PERF0_QUAD_0CVG,					/*Number of quads having zero coverage. */
    GX_PERF0_QUAD_NON0CVG,				/*Number of quads having coverage greater than zero. */
    GX_PERF0_QUAD_1CVG,					/*Number of quads with 1 pixel coverage. */
    GX_PERF0_QUAD_2CVG,					/*Number of quads with 2 pixel coverage. */
    GX_PERF0_QUAD_3CVG,					/*Number of quads with 3 pixel coverage. */
    GX_PERF0_QUAD_4CVG,					/*Number of quads with 4 pixel coverage. */
    GX_PERF0_AVG_QUAD_CNT,				/*Average quad count; average based on what is unknown */
    GX_PERF0_CLOCKS,					/*Number of GP clocks that have elapsed since the previous call to GX_ReadGP0Metric(). */
    GX_PERF0_NONE						/*Disables performance measurement for perf0 and resets the counter. */
} GXPerf0;

/*perf1metrics Performance counter 1 metric
Performance counter 1 is used for measuring texturing and caching performance as well as FIFO performance.
<tt>GX_PERF1_TC_*</tt> can be used to compute the texture cache (TC) miss rate. The <tt>TC_CHECK*</tt> parameters count how many texture cache lines are accessed for each pixel. In the worst case, for a mipmap, up to 8 cache lines may be accessed to produce one textured pixel. <tt>GX_PERF1_TC_MISS</tt> counts how many of those accesses missed the texture cache. To compute the miss rate, divide <tt>GX_PERF1_TC_MISS</tt> by the sum of all four <tt>GX_PERF1_TC_CHECK*</tt> values.<br><br>
<tt>GX_PERF1_VC_*</tt> count different vertex cache stall conditions.*/

typedef enum _GXPerf1 {
    GX_PERF1_TEXELS,				/*Number of texels processed by the GP. */
    GX_PERF1_TX_IDLE,				/*Number of clocks that the texture unit (TX) is idle. */
    GX_PERF1_TX_REGS,				/*Number of GP clocks spent writing to state registers in the TX unit. */
    GX_PERF1_TX_MEMSTALL,			/*Number of GP clocks the TX unit is stalled waiting for main memory. */
    GX_PERF1_TC_CHECK1_2,
    GX_PERF1_TC_CHECK3_4,
    GX_PERF1_TC_CHECK5_6,
    GX_PERF1_TC_CHECK7_8,
    GX_PERF1_TC_MISS,				/*Number of texture cache misses in total? */

    GX_PERF1_VC_ELEMQ_FULL,
    GX_PERF1_VC_MISSQ_FULL,
    GX_PERF1_VC_MEMREQ_FULL,
    GX_PERF1_VC_STATUS7,
    GX_PERF1_VC_MISSREP_FULL,
    GX_PERF1_VC_STREAMBUF_LOW,
    GX_PERF1_VC_ALL_STALLS,
    GX_PERF1_VERTICES,				/*Number of vertices processed by the GP. */
    GX_PERF1_FIFO_REQ,				/*Number of lines (32B) read from the GP FIFO. */
    GX_PERF1_CALL_REQ,				/*Number of lines (32B) read from called display lists. */
    GX_PERF1_VC_MISS_REQ,			/*Number vertex cache miss request. Each miss requests a 32B transfer from main memory. */
    GX_PERF1_CP_ALL_REQ,			/*Counts all requests (32B/request) from the GP Command Processor (CP). It should be equal to * the sum of  the sum of counts returned by <tt>GX_PERF1_FIFO_REQ</tt>, <tt>GX_PERF1_CALL_REQ</tt>, and <tt>GX_PERF1_VC_MISS_REQ</tt>. */
    GX_PERF1_CLOCKS,				/*Number of GP clocks that have elapsed since the last call to GX_ReadGP1Metric(). */
    GX_PERF1_NONE					/*Disables performance measurement for perf1 and resets the counter. */
} GXPerf1;


/*tlutname TLUT name
Name of Texture Look-Up Table (TLUT) in texture memory.
Each table <tt>GX_TLUT0</tt>-<tt>GX_TLUT15</tt> contains 256 entries,16b per entry. <tt>GX_BIGTLUT0</tt>-<tt>3</tt> contains 1024 entries, 16b per entry. Used for configuring texture memory in GX_Init().*/
typedef enum _GXTlut {
    GX_TLUT0 = 0,
    GX_TLUT1,
    GX_TLUT2,
    GX_TLUT3,
    GX_TLUT4,
    GX_TLUT5,
    GX_TLUT6,
    GX_TLUT7,
    GX_TLUT8,
    GX_TLUT9,
    GX_TLUT10,
    GX_TLUT11,
    GX_TLUT12,
    GX_TLUT13,
    GX_TLUT14,
    GX_TLUT15,
    GX_BIGTLUT0,
    GX_BIGTLUT1,
    GX_BIGTLUT2,
    GX_BIGTLUT3
} GXTlut;


#define GX_MAX_VTXDESC					GX_VA_MAXATTR
#define GX_MAX_VTXDESC_LISTSIZE			(GX_VA_MAXATTR+1)

#define GX_MAX_VTXATTRFMT				GX_VA_MAXATTR
#define GX_MAX_VTXATTRFMT_LISTSIZE		(GX_VA_MAXATTR+1)

#define GX_MAX_Z24						0x00ffffff



#endif