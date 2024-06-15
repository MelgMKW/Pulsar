#ifndef _FONT_MGR_
#define _FONT_MGR_
#include <kamek.hpp>
#include <core/nw4r/ut/ResFont.hpp>
#include <MarioKartWii/File/BMG.hpp>
#include <MarioKartWii/Mii/MiiGroup.hpp>

using namespace nw4r;

namespace Text {

enum FontIndex {
    TT_KART_FONT_RODAN_NTLG_PRO_B,
    KART_KANJI_FONT,
    TT_KART_EXTENSION_FONT,
    INDICATOR_FONT,
    MARIO_FONT_NUMBER_RED,
    MARIO_FONT_NUMBER_BLUE
};

class FontImage {
    u8 _[0x20];
}; //0x20

struct Texture {
    GX::TexObj* texture; //0 = 0xC

    u16 texLeft; //0x4 = 0x10
    u16 texRight; //0x6 = 0x12
    u16 texTop; //0x8 = 0x14
    u16 texBottom; //0xa = 0x16
}; //0xC

class GameFont : public ut::ResFont {
public:
    GameFont(); //805d0f34 inlined
    ~GameFont() override; //805d0f80 vtable 808b87c0
    void Load(const char* fontName); //805d0ff0 inlined
    void Init(); //805d1214
    void GetTextureByCode(Texture* textureToFill, u16 characterCode) const; //805d1044
    void GetTextureByIdx(Texture* textureToFill, u16 glyphIdx) const; //805d1134
    GX::TexObj* fontTexObjs; //0x1c array of size ut::FontTextureGlyph's imageCount
    u32 imageType; //0x20 0 IA4, 1 RGB5A3
}; //0x24

class FontMgr {
    FontMgr(); //805d130c
    ~FontMgr(); //805d132c
    static FontMgr* sInstance; //809c1bf8
    static FontMgr* CreateInstance(); //805d13c4
    static void DestroyInstance(); //805d1414
    static const char** fontNames; //808b87a8
    void Init(); //805d14a4
    void InitFont(u32 fontIdx); //805d1758 inlined in init 6 times
    GameFont* GetFont(const char* name) const; //805d1804 returns nullptr if not found
    GameFont* fonts[6];
}; //0x18

}//namespace Text
#endif