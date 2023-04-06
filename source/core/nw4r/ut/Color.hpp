#ifndef _NW4R_UTCOLOR_
#define _NW4R_UTCOLOR_
#include <types.hpp>
#include <core/rvl/gx/GXStruct.hpp>
namespace nw4r {
namespace ut {
struct Color : public GXColor {
    Color(u32 color) { operator=(color); }
    Color() { operator=(0xFFFFFFFF); }
    Color(const GXColor &color) { operator=(color); }
    Color(int r, int g, int b, int a) { this->r = (u8)r, this->g = (u8)g, this->b = (u8)b, this->a = (u8)a; }
    Color &operator=(u32 color) {
        *(u32 *)(this) = color;
        return *this;
    }
}; // Total size 0x4
size_assert(Color, 0x4);
}//namespace ut
}//namespace nw4r
#endif
