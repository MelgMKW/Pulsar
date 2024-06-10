#ifndef _TEXT_
#define _TEXT_
#include <kamek.hpp>
#include <core/nw4r/lyt/TextBox.hpp>
#include <MarioKartWii/UI/Text/Glyph.hpp>
#include <MarioKartWii/File/BMG.hpp>
#include <MarioKartWii/UI/Text/FontMgr.hpp>
#include <MarioKartWii/Mii/MiiGroup.hpp>

using namespace nw4r;

namespace Text {

class Info {
public:
    Info(); //805cd94c
    u32 intToPass[9]; //0
    u32 bmgToPass[9]; //24
    Mii* miis[9]; //48
    u8 licenseId[9]; //6c
    u8 unknown_0x75[3];
    u32 playerId[9]; //0x78
    wchar_t* strings[9]; //0x9c
    bool useColoredBorder; //0xc0
    char unknown_0xC1[3];
}; //total size 0xC4

class PaneHandler {
public:
    PaneHandler(); //805cda34
    ~PaneHandler(); //805cda50
    void Init(lyt::TextBox* pane); //805cdbe4
    void SetMessage(const BMGHolder& curFileBmgs, const BMGHolder& commonBmgs, u32 bmgId, const Info* text = nullptr); //805cdd00
    void ResetMessage(); //805cedcc
    void Draw(const lyt::DrawInfo& drawInfo); //805cee08
    static bool GetBMGInfo(const BMGHolder& curFileBmgs, const BMGHolder& commonBmgs, u32 bmgId,
        wchar_t* msgDest, Text::FontIndex* fontIdx); //805cef10


    lyt::TextBox* pane; //0
    GlyphParams* glyphArray; //0x4 size max glyph count
    u32 stringBufferLength; //8 maxCharCount
    GlyphUnicodeExternal* extraUnicodeGlyphs; //0xc only exists if 0x10 > 0, array size 0x10
    u32 extraUnicodeCharCount; //0x10 essentially userInfo 3x's x digit, the 3 probably specifies that unicode char work with this pane
    u32 curGlyphCount; //0x14
    u32 curExternalUnicodeGlyphCount; //0x18
    class Initializer;
}; //total size 0x1c

class MessageParams {
    u8 _[4]; //0x5060
    u32 glyphCount; //0x5064
    float unknownglobal58MinusMaxTopPos; //0x5068
    float totalMsgSpace; //0x506c
    float unknownGlobal0x50; //0x5070
    float maxTopPos;
    float maxBottomPos; //0x5078
}; //0x1c

class GlobalHandler { //accessed at 809c1be0
    struct FontParams {
        GameFont* font; //0 set to kanjiFont by SetTextHandler, but then set to the actual font used by the bmg
        float fontWidthRatio; //0x4 paneWidth / fontWidth
        float fontHeightRatio; //0x8 paneHeight 51 / fontHeight 51
        float fontTopMostPos; //0xc heightRatio * ascent 40
        float fontBottomMostPos; //0x10 heightRatio * descent
    };
    GlobalHandler(); //805cfbd8
    ~GlobalHandler(); //805cfbe4

    void SetPaneHandler(PaneHandler* handler); //805cfc24
    void SetPaneHandlerAndPane(PaneHandler* handler, lyt::TextBox* pane); //805d0e08 uses the specified pane and not the pane handler's
    void SetCharacter(u16 characterCode); //805d00b0
    void Calc(); //805d0674 calculates the coordinates of all the glyph params
    void CalcMessageParams(); //805d0cd4
    void SetExternalUnicodeChar(GlyphUnicodeExternal::Code* codes, u32 charCount); //805d0324

    GlyphParams* GetGlyphParamsAndIncrement(); //805d0d98
    GlyphUnicodeExternal* GetUnicodeGlyphParamsAndIncrement(); //805d0dd0

    PaneHandler* curHandler;
    u32 setUpGlyphCount; //0x4
    u32 externalUnicodeGlyphCount; //0x8 as in not part of a BMG but added because of an escape sequence (eg A button that depends on the controller)

    FontParams mainFont; //0xC
    FontParams extensionFont; //0x20
    FontParams indicatorFont; //34

    float paneLineSpace; //0x48
    float paneCharSpace; //0x4c
    float unknown_0x50;
    float totalMsgSpace; //0x54
    float totalMsgHeight; //0x58 as a negative value

    u8 unknown_0x5c[4];

    GlyphHolder subs[0x200]; //0x60
    MessageParams messageParams; //0x5060
    u32 glyphCount2; //0x5220 max 200
    u32 glyphCount3; //0x5224 max 200
    u32 usedMessageParams; //0x5228
    bool isSetUp; //0x522c
    u8 padding[3];
}; //0x5230

class Mgr {
    static void CreateInstance(); //805cdac0
    static void DestroyInstance(); //805cdb68
    static Mgr mInstance; //809c1be0
    GlobalHandler* globalTextHandler;
    int* curSectionDuration; //809c1be4
    MiiGroup* globalMiiGroup; //809c1be8
};
}//namespace Text

#endif