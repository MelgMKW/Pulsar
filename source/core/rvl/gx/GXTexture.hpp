#ifndef _GXTETURE_
#define _GXTETURE_

#include <types.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/rvl/gx/GXStruct.hpp>

extern "C" {
    void GXInitTexObjLOD(GXTexObj *obj, GXTexFilter minFilter, GXTexFilter magFilter,
        float minLOD, float maxLOD, float lod_bias, bool biasClamp, bool doEdgeLOD, GXAnisotropy max_aniso); //801707f8
}
#endif