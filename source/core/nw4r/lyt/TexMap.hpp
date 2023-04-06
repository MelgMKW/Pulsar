#ifndef _NW4R_LYTTEXMAP_
#define _NW4R_LYTTEXMAP_
#include <types.hpp>
#include <core/rvl/gx/GX.hpp>
#include <core/rvl/tpl.hpp>

namespace nw4r {
namespace lyt {
class TexMap {
public:
    void ReplaceImage(TPLPalettePtr pal, u32 id = 0); //80082550
    void Set(const GXTexObj &texObj); //80082400
    void *image; //0
    void *palette; //4
    u16   width; //8
    u16   height;
    float   minLOD; //c
    float   maxLOD; //10
    u16   LODBias; //14
    u16   paletteEntryNum;
    struct { //18
        u32  textureFormat : 4;
        u32  mipmap : 1;
        u32  wrapS : 2;
        u32  wrapT : 2;
        u32  minFilter : 3;
        u32  magFilter : 1;
        u32  biasClampEnable : 1;
        u32  edgeLODEnable : 1;
        u32  anisotropy : 2;
        u32  paletteFormat : 2;
    } bits;
};
}//namespace lyt
}//namespace nw4r
#endif