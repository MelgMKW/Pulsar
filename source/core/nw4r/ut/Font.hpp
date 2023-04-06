#ifndef _NW4R_UT_FONT_
#define _NW4R_UT_FONT_
#include <types.hpp>
#include <core/nw4r/ut/CharStrmReader.hpp>
#include <core/rvl/gx/GXEnum.hpp>

namespace nw4r {
namespace ut {
enum FontEncoding {
    FONT_ENCODING_UTF8,  //UTF-8
    FONT_ENCODING_UTF16, //UTF-16
    FONT_ENCODING_SJIS,  //ShiftJIS
    FONT_ENCODING_CP1252 //CP1252
};

struct CharWidths {
    s8 leftWith; //width of space to the left of glyph
    u8 glyphWidth;
    s8 charWidth; //total char width = left + glyph + right
};

struct Glyph {
    const void *texture;
    CharWidths  widths;
    u8  height;
    GXTexFmt exFormat;
    u16 texWidth;
    u16 texHeight;
    u16 cellX;
    u16 cellY;
};

class Font {
public:
    enum Type {
        TYPE_NULL,
        TYPE_ROM,
        TYPE_RESOURCE,
        TYPE_PAIR
    };

    virtual ~Font(); //8007c670 vtable 80274e08
    virtual int GetWidth() const = 0; //0xc
    virtual int GetHeight() const = 0; //0x10
    virtual int GetAscent() const = 0; //0x14
    virtual int GetDescent() const = 0; //0x18
    virtual int GetBaselinePos() const = 0; //0x1c
    virtual int GetCellHeight() const = 0; //0x20
    virtual int GetCellWidth() const = 0; //0x24
    virtual int GetMaxCharWidth() const = 0; //0x28
    virtual Type GetType() const = 0; //0x2c
    virtual GXTexFmt GetTextureFormat() const = 0; //0x30
    virtual int GetLineFeed() const = 0; //0x34
    virtual const CharWidths GetDefaultCharWidths() const = 0; //0x38
    virtual void SetDefaultCharWidths(const CharWidths &widths) = 0; //0x3c
    virtual bool SetAlternateChar(u16 code) = 0; //0x40
    virtual void SetLineFeed(int linefeed) = 0; //0x44
    virtual int GetCharWidth(u16 code) const = 0; //0x48
    virtual const CharWidths GetCharWidths(u16 code) const = 0; //0x4c
    virtual void GetGlyph(Glyph *glyphPtr, u16 code) const = 0; //0x50
    virtual bool HasGlyph(u16 c) const = 0; //0x54
    virtual FontEncoding GetEncoding() const = 0; //0x58

    void InitReaderFunc(FontEncoding encoding); //800b1970
    CharStrmReader::ReadNextCharFunc readerFunc; //ptmf
}; //0x10

}//namespace ut
}//namespace nw4r
#endif