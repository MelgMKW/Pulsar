#ifndef _TPL_HEADER_
#define _TPL_HEADER_

#include <types.hpp>
#include <core/rvl/gx/GX.hpp>

typedef struct {
    u16             numEntries;
    u8              unpacked;
    u8              pad8;
    GX::TlutFmt       format;
    void* data;
} TPLClutHeader, * TPLClutHeaderPtr;


typedef struct {
    u16             height;
    u16             width;
    u32             format;
    void* data;
    GX::TexWrapMode   wrapS;
    GX::TexWrapMode   wrapT;
    GX::TexFilter     minFilter;
    GX::TexFilter     magFilter;
    float           LODBias;
    u8              edgeLODEnable;
    u8              minLOD;
    u8              maxLOD;
    u8              unpacked;
} TPLHeader, * TPLHeaderPtr;


typedef struct {
    TPLHeaderPtr        textureHeader;
    TPLClutHeaderPtr    CLUTHeader;
} TPLDescriptor, * TPLDescriptorPtr;


typedef struct {
    u32                 versionNumber;
    u32                 numDescriptors;
    TPLDescriptorPtr    descriptorArray;
} TPLPalette, * TPLPalettePtr;

void TPLBind(TPLPalettePtr pal);
TPLDescriptorPtr TPLGet(TPLPalettePtr pal, u32 id);
void TPLGetGXTexObjFromPalette(TPLPalettePtr pal, GX::TexObj* to, u32 id);
void TPLGetGXTexObjFromPaletteCI(TPLPalettePtr pal, GX::TexObj* to, GX::TlutObj* tlo, GX::Tlut tluts, u32 id);

#endif
