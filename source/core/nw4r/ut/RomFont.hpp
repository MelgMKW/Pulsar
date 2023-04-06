#ifndef _NW4R_UT_ROMFONT_
#define _NW4R_UT_ROMFONT_
#include <types.hpp>
#include <core/nw4r/ut/Font.hpp>
#include <core/rvl/os/font.hpp>

namespace nw4r {
namespace ut {

class RomFont : public Font {
public:
    RomFont(); //800b1a20
    ~RomFont() override; //800b1a80 vtable 80274dac
    int GetWidth() const override; //0xc 800b1ae0
    int GetHeight() const override; //0x10 800b1af0
    int GetAscent() const override; //0x14 800b1b50
    int GetDescent() const override; //0x18 800b1b60
    int GetBaselinePos() const override; //0x1c 800b1b70
    int GetCellHeight() const override; //0x20 800b1b80
    int GetCellWidth() const override; //0x24 800b1b90
    int GetMaxCharWidth() const override; //0x28 800b1ba0
    Type GetType() const override; //0x2c 800b1bb0
    GXTexFmt GetTextureFormat() const override; //0x30 800b1bc0
    int GetLineFeed() const override; //0x34 800b1bd0
    const CharWidths GetDefaultCharWidths() const override; //0x38 800b1be0
    void SetDefaultCharWidths(const CharWidths &widths) override; //0x3c 800b11c00
    bool SetAlternateChar(u16 code) override; //0x40 800b11c20
    void SetLineFeed(int linefeed) override; //0x44 800b11cb0
    int GetCharWidth(u16 code) const override; //0x48 800b11cc0
    const CharWidths GetCharWidths(u16 code) const override; //0x4c 800b1d50
    void GetGlyph(Glyph *glyphPtr, u16 code) const override; //0x50 800b1da0
    bool HasGlyph(u16 c) const override; //0x54 800b1ea0
    FontEncoding GetEncoding() const override; //0x58 800b1f66

    OSFontHeader *fontHeader; //0x10
    CharWidths defaultWidths;  //0x14
    u16 altChar; //0x18
}; //0x1c


}//namespace ut
}//namespace nw4r
#endif