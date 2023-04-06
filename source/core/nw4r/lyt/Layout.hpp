#ifndef _NW4R_LYTLAYOUT_
#define _NW4R_LYTLAYOUT_
#include <types.hpp>
#include <core/nw4r/lyt.hpp>
#include <core/nw4r/ut/TagProcessorBase.hpp>

namespace nw4r {
namespace lyt {
class Layout {
public:
    Layout(); //0x8007a000
    virtual ~Layout(); //8007a040 vtable 802734c0
    virtual bool Build(const void *lytResBuffer, ResourceAccessor *resAcc); //8007a170
    virtual AnimTransform *CreateAnimTransform(); //8007a4c0
    virtual AnimTransform *CreateAnimTransform(const void *animResBuffer, ResourceAccessor *resAcc); //8007a540
    virtual AnimTransform *CreateAnimTransform(const AnimResource &animRes, ResourceAccessor *resAcc); //8007a5a0
    virtual void BindAnimation(AnimTransform *animTransform); //8007a630
    virtual void UnbindAnimation(AnimTransform *animTransform); //8007a660
    virtual void UnbindAllAnimation(); //8007a690
    virtual bool BindAnimationAuto(const AnimResource &res, ResourceAccessor *resAcc); //8007a6b0
    virtual void SetAnimationEnable(AnimTransform *anim, bool enable); //8007a940
    virtual void CalculateMtx(const DrawInfo &info); //8007a970
    virtual void Draw(const DrawInfo &info); //8007a990
    virtual void Animate(u64 option = 0); //8007a9b0
    virtual void SetTagProcessor(nw4r::ut::TagProcessorBase<wchar_t> *tagProc); //8007a9d0
    static Pane *BuildPaneObj(s32 type, const void *data, const ResBlockSet &resBlockSet); //8007ab90
    ut::LinkList<AnimTransform, offsetof(AnimTransform, link)> animList; //0xc
    Pane *rootPane; //0x10
    GroupContainer *groupContainer; //0x14
    float width; //0x18
    float height; //0x1c 
}; // Total size 0x20
}//namespace lyt
}//namespace nw4r
#endif