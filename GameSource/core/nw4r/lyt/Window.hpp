#ifndef _NW4R_LYTWINDOW_
#define _NW4R_LYTWINDOW_
#include <types.hpp>
#include <core/nw4r/lyt/Pane.hpp>
#include <core/nw4r/lyt/Common.hpp>
#include <core/nw4r/lyt/TexMap.hpp>

namespace nw4r {
namespace lyt {

struct WindowFrameSize {
    float l;
    float r;
    float t;
    float b;
};
struct InflationLRTB {
    float l;
    float r;
    float t;
    float b;
};
class Window : public Pane {
public:
    struct Content {
        ut::Color vtxColors[4];
        detail::TexCoordAry texCoordAry; //0x10
    }; //0x18

    struct Frame {
        u8 textureFlip;
        Material* material;
    };
    Window(const res::TextBox* src, const ResBlockSet& resBlockSet); //8007cc30
    ~Window() override; //0x8 8007cec0 vtable 8027363c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0xc 8007f2f0
    void DrawSelf(const DrawInfo& info) override; //0x18 8007d1b0
    virtual void AnimateSelf(u64 option); //0x20 8007d2f0
    ut::Color GetVtxColor(u64 id) const override; //0x24 8007d110
    void SetVtxColor(u64 id, ut::Color color) override; //0x28 8007d140
    u8 GetVtxColorElement(u64 id) const override; //0x34 8007d170
    void SetVtxColorElement(u64 id, u8 value) override; //0x38 8007d190
    Material* FindMaterialByName(const char* name, bool recursive) override; //0x40 8007d010
    void UnbindAnimationSelf(AnimTransform* anim) override; //0x50 8007d380
    virtual u64 GetMaterialNum() const override; //0x64 8007f1a0
    virtual Material* GetMaterial(u64 id) const override; //0x6c 8007f1b0
    virtual Material* GetContentMaterial() const; //0x74 8007f210
    virtual Material* GetFrameMaterial(u32 frameIdx) const; //0x78 8007f1e0
    virtual void DrawContent(const math::VEC2& basePt, const WindowFrameSize& frameSize, u8 alpha); //0x7c 8007d410
    virtual void DrawFrame(const math::VEC2& basePt, const Frame& frame, const WindowFrameSize& frameSize, u8 alpha); //0x80 8007d520
    virtual void DrawFrame4(const math::VEC2& basePt, const Frame* frames, const WindowFrameSize& frameSize, u8 alpha); //0x84 8007db00
    virtual void DrawFrame8(const math::VEC2& basePt, const Frame* frames, const WindowFrameSize& frameSize, u8 alpha); //0x88 8007e250

    const WindowFrameSize GetFrameSize(u8 frameIdx, const Frame* frames);

    InflationLRTB contentInflation; //0xd8
    Content content; //0xe8
    Frame* frames; //0x100
    u8 frameCount; //0x104
    u8 padding2[3];
}; // Total size 0x108

}//namespace lyt
}//namespace nw4r
#endif