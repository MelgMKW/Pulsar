#ifndef _NW4R_LYTANIMATION_
#define _NW4R_LYTANIMATION_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/lyt/resources.hpp>
#include <core/nw4r/lyt/ResourceAccessor.hpp>
#include <core/nw4r/lyt/Pane.hpp>

namespace nw4r {
namespace lyt {
class AnimTransform {
public:
    virtual ~AnimTransform(); //80082990 vtable 802737e4
    virtual void SetResource(const res::AnimationBlock *pRes, ResourceAccessor *pResAccessor) = 0;
    virtual void SetResource(const res::AnimationBlock *res, ResourceAccessor *resAccessor, u16 animCount) = 0;
    virtual void Bind(Pane *ane, bool isRecursive, bool disable = false) = 0;
    virtual void Bind(Material *material, bool disable = false) = 0;
    virtual void Animate(u32 index, Pane *ane) = 0;
    virtual void Animate(u32 idx, Material *material) = 0;

    bool IsLoopData() const; //800829e0
    u16 GetFrameSize(); //0x800829d0
    ut::LinkListNode link; //0x4
    const res::AnimationBlock *resource;
    float curFrame; //0x10
};

class AnimTransformBasic : public AnimTransform {
public:
    AnimTransformBasic(); //80082a00
    virtual ~AnimTransformBasic(); //80082a40 vtable 802737c0
    virtual void SetResource(const res::AnimationBlock *pRes, ResourceAccessor *pResAccessor); //80082ad0
    virtual void SetResource(const res::AnimationBlock *res, ResourceAccessor *resAccessor, u16 animCount); //8002af0
    virtual void Bind(Pane *ane, bool isRecursive, bool disable = false); //80082c60
    virtual void Bind(Material *material, bool disable = false); //80082e30
    virtual void Animate(u32 index, Pane *ane); //80082f50
    virtual void Animate(u32 idx, Material *material); //80083130



    u32 unknown_0x14;
    void *unkClass; //size 0x10 80082be8
    u16 animationCount; //from pai1
    u8 unknown_0x1E[2];
}; //total size 0x20

}//namespace lyt
}//namespace nw4r
#endif

