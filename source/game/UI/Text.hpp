#ifndef _TEXT_
#define _TEXT_
#include <kamek.hpp>
#include <core/nw4r/lyt/TextBox.hpp>
#include <game/File/BMG.hpp>
#include <game/Visual/Mii.hpp>
using namespace nw4r;

class CharacterInfo {
    CharacterInfo(); //805cf068
    ~CharacterInfo(); //805cf06c
    u8 unknown[0x18]; //float to int weirdness, changing values changes character size scale etc...
};
class BMGHolder {
public:
    BMGHolder(); //0x805f8b34
    void Load(const char *name); //805f8b90
    void Init(BMGHeader *bmgFile); //805f8c00
    s32 GetMsgId(s32 bmgId) const; //805f8c88
    wchar_t *GetMsgByMsgId(s32 msgId) const; //805f8cf0
    u8 *GetFontType(u32 msgId) const; //805f8d2c
    BMGHeader *bmgFile; //0
    BMGInfo *info; //0x4
    BMGData *data; //0x8 string pool
    u32 *str1Block; //0xc no idea, doesn't seem to exist in mkw
    BMGMessageIds *messageIds; //0x10
}; //Total Size 0x14
size_assert(BMGHolder, 0x14);

class TextInfo {
public:
    TextInfo(); //805cd94c
    u32 intToPass[9]; //0
    u32 bmgToPass[9]; //24
    Mii *miis[9]; //48
    u8 licenseId[9]; //6c
    u8 unknown_0x75[3];
    u32 playerId[9];
    wchar_t *strings[9];
    bool useColoredBorder;
    char unknown_0xC1[3];
}; //total size 0xC4

class TextPaneHandler {
    TextPaneHandler(); //805cda34
    ~TextPaneHandler(); //805cda50
    void Init(lyt::TextBox *pane); //805cdbe4
    void SetMessage(BMGHolder *curFileBmgs, BMGHolder *commonBmgs, u32 bmgId, const TextInfo *pageText = NULL); //805cdd00
    void ResetMessage(); //805cedcc
    void Draw(lyt::DrawInfo *drawInfo); //805cee08
    lyt::TextBox *pane; //0
    CharacterInfo *characterArray; //size max char count
    u32 maxCharacterCount; //very unsure //8
    UnkType *unknown_0xC; //only if 0x10 is true
    u32 isUserInfoBtw1And9; //0x10
    u8 unknown_0x14[0x1C - 0x14];
    class Initializer;
}; //total size 0x1c

class UnkTextPaneClass {
    ~UnkTextPaneClass(); //805cf06c
}; //total size 0x18

class GlobalTextHandler {
    void SetTextHandler(TextPaneHandler *handler); //805cfc24
    void SetCharacter(); //805d00b0
    void Reset(); //805d0674
    TextPaneHandler *curHandler;
    u32 characterCount; //0x4
    u32 unknown_0x8;
    u8 unknown_0xC[0x522c - 0xC];
    u32 characterCount2; //0x5220
    u8 unknown_0x522c[0x522c - 0x5220];
    bool isVisible; //0x522c
    u8 padding[3];
}; //0x5230

class TextMgr {
    static void CreateInstance(); //805cdac0
    static void DestroyInstance(); //805cdb68
    static TextMgr sInstance; //0x809c1be0
    GlobalTextHandler *globalTextHandler;
    int *curSectionDuration;
    MiiGroup *globalMiiGroup;
};


#endif