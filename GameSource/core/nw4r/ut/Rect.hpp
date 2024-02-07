#ifndef _NW4R_UTRECT_
#define _NW4R_UTRECT_
#include <types.hpp>
namespace nw4r {
namespace ut {
struct Rect {
    float left;
    float top;
    float right;
    float bottom;
};
size_assert(Rect, 0x10);
}//namespace ut
}//namespace nw4r
#endif