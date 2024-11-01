#ifndef _NW4R_UTCOLOR_
#define _NW4R_UTCOLOR_
#include <types.hpp>
#include <core/rvl/gx/GXStruct.hpp>
namespace nw4r {
namespace ut {
struct Color : public GX::Color {
    Color(u32 color) { operator=(color); }
    Color() { operator=(0xFFFFFFFF); }
    Color(const GX::Color& color) { operator=(color); }
    Color(int r, int g, int b, int a) { this->r = (u8)r, this->g = (u8)g, this->b = (u8)b, this->a = (u8)a; }
    Color& operator=(u32 color) {
        *(u32*)(this) = color;
        return *this;
    }
    operator GX::ColorS10() const {
        GX::ColorS10 color10 = { this->r, this->g, this->b, this->a };
        return color10;
    }
    u32& ToU32ref() {
        return *reinterpret_cast<u32*>(this);
    }
    const u32& ToU32ref() const {
        return *reinterpret_cast<const u32*>(this);
    }

    operator u32() const {
        return ToU32ref();
    }

    //bool operator ==(const Color& rhs) const { return u32(this) == u32(rhs); }


}; // Total size 0x4
size_assert(Color, 0x4);
}//namespace ut
}//namespace nw4r
#endif
