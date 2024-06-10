#ifndef _GLYPH_
#define _GLYPH_
#include <kamek.hpp>
#include <core/nw4r/lyt/TextBox.hpp>
#include <MarioKartWii/File/BMG.hpp>
#include <MarioKartWii/UI/Text/FontMgr.hpp>
#include <MarioKartWii/Mii/MiiGroup.hpp>

using namespace nw4r;

namespace Text {

class GlyphParams {
public:

    GlyphParams(); //805cf068
    ~GlyphParams(); //805cf06c
    void SetCharacter(u16 characterCode, const GameFont& font, u16 _0x5c); //805cf0ac inlined

    u16 top;
    u16 bottom; //0x2
    u16 left; //0x4
    u16 right; //0x6

    u16 imageType; //0x8 0 IA4, 1 RGB5A3
    u16 _0x5cGlobalTexHandler; //0xa

    Texture texture; //0xC
}; //0x18

class GlyphUnicodeExternal : public GlyphParams { //supports up to 4 unicode codes
public:
    struct Code {
        u16 unicode;
        u16 duration;
    };
    GlyphUnicodeExternal(); //805cf110
    ~GlyphUnicodeExternal(); //805cf114
    void SetCharacter(const Code* codes, u32 count, const GameFont& font, u32 x5cGlobalHandler); //805cf154
    int CalcCharIdxToUse(u16 time) const; //805cf1fc uses duration and time to check which unicode should be displayed (returns the idx)
    Texture otherGlyphs[3];
    u16 duration[4]; //0x3C of each character, this creates the shrinking A button "animation"
}; //0x44


class GlyphDrawer {
public:
    GlyphDrawer(lyt::TextBox* pane); //805cf264
    ~GlyphDrawer(); //805cf27c
    void Init(); //805cf2bc
    void Draw(const GlyphParams& params); //805cf598
    void DrawExternalUnicode(const GlyphUnicodeExternal& externalUnicodes); //805cf680
    void SetupGXColors(u16 imageType, u16 r5); //805cf7e4

    lyt::TextBox* pane;
    u32 imageType;
    u32 r5;
    GX::TexObj* texture; //0xC
}; //0x10

struct GlyphHolder {
    u8 unknown[4];
    float width; //0x4
    float unknownGlobalText0x50; //0x8
    u16 characterCode; //0xC
    u8 padding[2];
    GlyphParams* params; //0x10
    GameFont* font; //0x14
    float fontWidthRatio; //0x18 paneWidth / fontWidth
    float fontHeightRatio; //0x1c paneHeight 51 / fontHeight 51
    float fontTopMostPos; //0x20 heightRatio * ascent 40
    float fontBottomMostPos; //0x24 heightRatio * descent
}; //0x28
}//namespace Text

#endif