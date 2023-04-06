#ifndef _NW4R_LYTTYPES_
#define _NW4R_LYTTYPES_
#include <types.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace lyt {
namespace detail {
typedef s16 ResS16;
typedef u16 ResU16;
typedef s32 ResS32;
typedef u32 ResU32;
}
struct TexSRT {
    math::VEC2 translate;
    float rotate;
    math::VEC2 scale;
};

struct AlphaCompare {
    u8 compare;
    u8 operation;
    u8 ref0;
    u8 ref1;
};

struct ChanCtrl {
    u8 matSrcColor;
    u8 matSrcAlpha;
    u8 reserve1;
    u8 reserve2;
};
struct IndirectStage {
    u8 texCoordGen;
    u8 texMap;
    u8 scaleS;
    u8 scaleT;
};
template<typename T>
const T *ConvertOffsToPtr(const void *baseAddress, unsigned int offset); //80080130 for res::TexMap


class AnimTransform;

class AnimationLink {
public:
    ut::LinkListNode link;
    AnimTransform *animTrans;
    u16 idx;
    bool disable;
};

}//namespace lyt
}//namespace nw4r
#endif