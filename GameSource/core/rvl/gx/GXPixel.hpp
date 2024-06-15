#ifndef _GXPIXEL_
#define _GXPIXEL_

#include <types.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/rvl/gx/GXStruct.hpp>

namespace GX {
void SetPixelFmt(PixelFmt pix_fmt, ZFmt16 z_fmt); //80172888 Sets pixel format for the framebuffer.
}//namespace GX
#endif