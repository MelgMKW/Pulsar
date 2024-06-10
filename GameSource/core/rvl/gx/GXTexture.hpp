#ifndef _GXTETURE_
#define _GXTETURE_

#include <types.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/rvl/gx/GXStruct.hpp>

namespace GX {
void InitTexObjLOD(TexObj* obj, TexFilter minFilter, TexFilter magFilter,
    float minLOD, float maxLOD, float lod_bias, bool biasClamp, bool doEdgeLOD, Anisotropy max_aniso); //801707f8
void InitTexObj(TexObj* obj, void* image_ptr, u16 width, u16 height,
    TexFmt format, TexWrapMode wrap_s, TexWrapMode wrap_t, bool mipmap);
void LoadTexObj(const TexObj* obj, TexMapID id); //80170f2c
}//namespace GX
#endif