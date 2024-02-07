#ifndef _NW4R_LYTDRAWINFO_
#define _NW4R_LYTDRAWINFO_
#include <types.hpp>
#include <core/nw4r/ut/Rect.hpp>
#include <core/rvl/mtx/mtx.hpp>

namespace nw4r {
namespace lyt {
class DrawInfo {
public:
    DrawInfo(); //80082620
    virtual ~DrawInfo();  //800826a0 vtable 802737b0
    Mtx matrix;
    ut::Rect rect;
    Vec2 scale;
    float alpha;
    struct {
        u8 mulViewDraw : 1;
        u8 influencedAlpha : 1;
        u8 locationAdjust : 1;
        u8 invisiblePaneCalculateMtx : 1;
    }flag; //0x50
}; // Total size 0x54
size_assert(DrawInfo, 0x54);
}//namespace lyt
}//namespace nw4r

#endif

