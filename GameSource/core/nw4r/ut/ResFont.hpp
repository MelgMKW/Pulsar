#ifndef _NW4R_UT_RESFONT_
#define _NW4R_UT_RESFONT_
#include <types.hpp>
#include <core/nw4r/ut/Font.hpp>
#include <core/nw4r/ut/BinaryFileFormat.hpp>

namespace nw4r {
namespace ut {
namespace detail {
class ResFontBase : public Font {
public:
    ResFontBase(); //800b1f90
    ~ResFontBase() override; //800b1ff0 vtable 80274e74
    int GetWidth() const override; //0xc 800b2040
    int GetHeight() const override; //0x10 800b2050
    int GetAscent() const override; //0x14 800b2060
    int GetDescent() const override; //0x18 800b2070
    int GetBaselinePos() const override; //0x1c 800b2090
    int GetCellHeight() const override; //0x20 800b20b0
    int GetCellWidth() const override; //0x24 800b20c0
    int GetMaxCharWidth() const override; //0x28 800b20d0
    Type GetType() const override; //0x2c 800b20e0
    GX::TexFmt GetTextureFormat() const override; //0x30 800b20f0
    int GetLineFeed() const override; //0x34 800b2100
    const CharWidths GetDefaultCharWidths() const override; //0x38 800b2110
    void SetDefaultCharWidths(const CharWidths& widths) override; //0x3c 800b2130
    bool SetAlternateChar(u16 code) override; //0x40 800b2150
    void SetLineFeed(int linefeed) override; //0x44 800b2210
    int GetCharWidth(u16 code) const override; //0x48 800b2220
    const CharWidths GetCharWidths(u16 code) const override; //0x4c 800b2270
    void GetGlyph(Glyph* glyphPtr, u16 code) const override; //0x50 800b2390
    bool HasGlyph(u16 c) const override; //0x54 800b2460
    FontEncoding GetEncoding() const override; //0x58 800b2520

    void* resource; //0x10
    FontInformation* fontInfo; //0x14
    mutable u16 lastCharCode; //0x18
    mutable u16 lastGlyphIndex; //0x1a
}; //0x1c
}//namespace detail
class ResFont : public detail::ResFontBase {
public:
    ResFont(); //800b2830
    ~ResFont() override; //800b2870 vtable 80274ed0
    void SetResource(void* rawBRFNT); //800b28d0 
    static FontInformation* Rebuild(BinaryFileHeader* brfnt);  //800b2a20 brfnt file header
};

}//namespace ut
}//namespace nw4r
#endif