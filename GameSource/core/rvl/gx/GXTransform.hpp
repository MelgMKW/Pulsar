#ifndef _GXTRANSFORM_
#define _GXTRANSFORM_

#include <types.hpp>
#include <core/rvl/mtx/mtx.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <core/rvl/gx/GXEnum.hpp>
namespace GX {
void SetProjection(const float mtx[4][4], ProjectionType type); //8017301c
void SetProjectionv(const float* ptr); //80173080
void GetProjectionv(float* p); //801730cc
void SetViewport(float xOrigin, float yOrigin, float width, float height, float near, float far); //801733b4
void SetScissor(u32 left, u32 top, u32 width, u32 height); //80173430
}//namespace GX

#endif