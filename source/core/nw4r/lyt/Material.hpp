#ifndef _NW4R_LYTMATERIAL_
#define _NW4R_LYTMATERIAL_
#include <types.hpp>
#include <core/nw4r/lyt/resources.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/ut/Color.hpp>
#include <core/rvl/gx/GX.hpp>
#include <core/nw4r/lyt/common.hpp>
#include <core/nw4r/lyt/TexMap.hpp>
#include <core/nw4r/lyt/lytTypes.hpp>

namespace nw4r {
namespace lyt {
class AnimTransform;
class AnimResource;
namespace detail {
struct BitGXNums {
    u32                 texMap : 4;
    u32                 texSRT : 4;
    u32                 texCoordGen : 4;
    u32                 indSRT : 2;
    u32                 indStage : 3;
    u32                 tevSwap : 1;
    u32                 tevStage : 5;
    u32                 chanCtrl : 1;
    u32                 matCol : 1;
    u32                 alpComp : 1;
    u32                 blendMode : 1;
};
}

class Material {
public:
    Material(const res::Material *source, const ResBlockSet &resBlockSet); //8007f660
    virtual ~Material(); //800801b0 vtable 80273780
    virtual bool SetupGX(bool modVtxColor, u8 alpha); //80081210
    virtual void BindAnimation(AnimTransform *animTransform); //800820b0
    virtual void UnbindAnimation(AnimTransform *animTransform); //800820d0
    virtual void UnbindAllAnimation(); //800820e0
    virtual void Animate(); //80082100
    virtual AnimationLink *FindAnimationLink(AnimTransform *animTransform); //800821c0
    virtual AnimationLink *FindAnimationLink(const AnimResource &animResource); //800821d0
    virtual void SetAnimationEnable(AnimTransform *animTransform, bool enable); //800821e0
    virtual void SetAnimationEnable(const AnimResource &animResource, bool enable); //80082230
    TexMap *GetTexMapAry(); //80080990
    ut::LinkList<AnimationLink, offsetof(AnimationLink, link)> animLinkList; //0x4
    GXColorS10 tevColours[3]; //0x10
    ut::Color tevKColours[4]; //0x28
    detail::BitGXNums GXMemCap;
    detail::BitGXNums GXMemNum;
    void *GPMem; //0x40 starts with tex map array
    char name[0x15]; //0x44
    bool isUserAllocated; //0x59
    u8 padding[3];
}; // total size 0x5C
}//namespace lyt
}//namespace nw4r
#endif