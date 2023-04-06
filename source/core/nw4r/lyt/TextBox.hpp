#ifndef _NW4R_LYTTEXTBOX_
#define _NW4R_LYTTEXTBOX_
#include <types.hpp>
#include <core/nw4r/lyt.hpp>
#include <core/nw4r/ut/TagProcessorBase.hpp>

namespace nw4r {
namespace lyt {
class TextBox : public Pane {
public:
    TextBox(const res::TextBox *src, const ResBlockSet &resBlockSet); //8007b320
    ~TextBox() override; //8007b610 vtable 80273578
    void *GetRuntimeTypeInfo() const override; //0xc 8007cc10
    void DrawSelf(const DrawInfo &info) override; //0x18 8007b870
    ut::Color GetVtxColor(u64 id) const override; //0x24 8007b7b0
    void SetVtxColor(u64 id, ut::Color color) override; //0x28 8007b7e0
    u8 GetVtxColorElement(u64 id) const override; //0x34 8007b830
    void SetVtxColorElement(u64 id, u8 value) override; //0x38 8007b850
    void LoadMtx(const DrawInfo &info) override; //0x70 8007c6b0
    virtual void AllocStringBuffer(u16 size); //0x74 8007c3a0
    virtual void FreeStringBuffer(); //0x78 8007c470
    virtual u16 SetString(const wchar_t *string, u16 destIndex = 0); //0x7c 8007c4c0
    virtual u16 SetString(const wchar_t *string, u16 destIndex, u16 stringLength); //0x80 8007c5a0
    wchar_t *stringBuf;
    ut::Color colour1, colour2;
    const ut::Font *font;
    float fontSizeX, fontSizeY;
    float lineSpace, charSpace;

    ut::TagProcessorBase<wchar_t> *tagProc; // actually a TagProcessor
    u16 bufferLength;
    u16 stringLength;
    u8 alignment;
    struct {
        u8 isAllocFont : 1;
        u8 hasextAlignment : 2;
    }flags;
}; // Total size 0xf0
}//namespace lyt
}//namespace nw4r
#endif