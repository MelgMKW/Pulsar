#ifndef _TPL_HEADER_
#define _TPL_HEADER_

#include <types.hpp>
#include <core/rvl/gx/GX.hpp>

typedef struct {
    u16             numEntries;
    u8              unpacked;
    u8              pad8;
    GXTlutFmt       format;
    void *data;
} TPLClutHeader, *TPLClutHeaderPtr;


typedef struct {
    u16             height;
    u16             width;
    u32             format;
    void *data;
    GXTexWrapMode   wrapS;
    GXTexWrapMode   wrapT;
    GXTexFilter     minFilter;
    GXTexFilter     magFilter;
    float           LODBias;
    u8              edgeLODEnable;
    u8              minLOD;
    u8              maxLOD;
    u8              unpacked;
} TPLHeader, *TPLHeaderPtr;


typedef struct {
    TPLHeaderPtr        textureHeader;
    TPLClutHeaderPtr    CLUTHeader;
} TPLDescriptor, *TPLDescriptorPtr;


typedef struct {
    u32                 versionNumber;
    u32                 numDescriptors;
    TPLDescriptorPtr    descriptorArray;
} TPLPalette, *TPLPalettePtr;

void TPLBind(TPLPalettePtr pal);
TPLDescriptorPtr TPLGet(TPLPalettePtr pal, u32 id);
void TPLGetGXTexObjFromPalette(TPLPalettePtr pal, GXTexObj *to, u32 id);
void TPLGetGXTexObjFromPaletteCI(TPLPalettePtr pal, GXTexObj *to, GXTlutObj *tlo, GXTlut tluts, u32 id);

#endif
