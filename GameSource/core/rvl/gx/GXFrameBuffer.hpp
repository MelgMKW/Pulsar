#ifndef _GXFRAMEBUFFER_
#define _GXFRAMEBUFFER_

#include <types.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/rvl/gx/GXStruct.hpp>

namespace GX {
void SetCopyClear(Color clear_clr, u32 clear_z); //8016f9c8 Sets the color and z values for clearing framebuffer during copy.
}//namespace GX
#endif