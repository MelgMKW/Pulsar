#ifndef _NW4R_LYTPANE_
#define _NW4R_LYTPANE_
#include <types.hpp>
#include <core/nw4r/lyt/resources.hpp>
#include <core/nw4r/lyt/DrawInfo.hpp>
#include <core/nw4r/lyt/lytTypes.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/ut/List.hpp>
#include <core/nw4r/ut/Color.hpp>
#include <core/nw4r/ut/Rect.hpp>

namespace nw4r {
namespace lyt {
class AnimTransform;
class AnimResource;
class Material;
class DrawInfo;

namespace detail {
class PaneBase {
public:
    virtual ~PaneBase();
    ut::LinkListNode link;
};
}//namespace detail

class Pane : public detail::PaneBase {
public:
    //Pane(nw4r::lyt::res::Pane const *); // todo: this struct
    Pane(res::Pane *src); //80078980
    ~Pane() override; //80078ac0 vtable 80273438
    virtual void *GetRuntimeTypeInfo() const; //0xc 800798f0
    virtual void CalculateMtx(const DrawInfo &info); //0x10 80078ef0
    virtual void Draw(const DrawInfo &info); //0x14 800791f0
    virtual void DrawSelf(const DrawInfo &info); //0x18 80079280
    virtual void Animate(u64 option); //0x1c 80079290
    virtual void AnimateSelf(u64 option); //0x20 80079320
    virtual ut::Color GetVtxColor(u64 id) const; //0x24 80078ce0
    virtual void SetVtxColor(u64 id, ut::Color color); //0x28 80078cf0
    virtual u8 GetColorElement(u64 id) const; //0x2c 80078d00
    virtual void SetColorElement(u64 id, u8 value); //0x30 80078d30
    virtual u8 GetVtxColorElement(u64 id) const; //0x34 80078d60
    virtual void SetVtxColorElement(u64 id, u8 value); //0x38 8008d70
    virtual Pane *FindPaneByName(const char *name, bool recursive); //0x3c 80078d80
    virtual Material *FindMaterialByName(const char *name, bool recursive); //0x40 80078e30
    virtual void BindAnimation(AnimTransform *anim, bool unk1, bool unk2); //0x44 800793e0
    virtual void UnbindAnimation(AnimTransform *anim, bool unk); //0x48 80079400
    virtual void UnbindAllAnimation(bool unk); //0x4c 80079490
    virtual void UnbindAnimationSelf(AnimTransform *anim); //0x50 800794b0
    virtual AnimationLink *FindAnimationLinkSelf(AnimTransform *anim); //0x54 80079550
    virtual AnimationLink *FindAnimationLinkSelf(const AnimResource &anim); //0x58 80079560
    virtual void SetAnimationEnable(AnimTransform *anim, bool unk1, bool unk2); //0x5c 80079570
    virtual void SetAnimationEnable(const AnimResource &anim, bool unk1, bool unk2); //0x60 80079670
    virtual u64 GetMaterialNum() const; //0x64 800798a0
    virtual Material *GetMaterial() const; //0x68  800798c0
    virtual Material *GetMaterial(u64 id) const; //0x6c 800798d0
    virtual void LoadMtx(const DrawInfo &info); //0x70 80079770

    void AppendChild(Pane *child); //80078c00
    void AddAnimationLink(AnimationLink *animationLink); //80079510
    const ut::Rect GetPaneRect(const DrawInfo &info) const; //80078c50
    Vec2 GetVtxPos() const;
    u16 GetExtUserDataNum() const; // 802AC5A0

    Pane *parent; //0xC
    ut::LinkList<Pane, offsetof(detail::PaneBase, link)> childList; //0x10
    ut::LinkList<AnimationLink, offsetof(AnimationLink, link)> animLinkList; //0x1c

    Material *material; //0x28

    math::VEC3 trans; //0x2c
    math::VEC3 rotate; //0x38
    Vec2 scale; //0x44
    Vec2 size; //0x4c

    Mtx calcMtx; //0x54
    Mtx effectiveMtx; //0x84

    u32 unknown_0xB4;  //0xb4

    u8 alpha; //0xb8
    u8 effectiveAlpha;
    u8 origin;
    u8 flag; //0xbb

    char name[0x11];
    char userdata[9];

    bool isUserAllocated;
    u8 _D7;
}; // Total size 0xd8




}//namespace lyt
}//namespace nw4r

#endif