#ifndef _CHARACTERSELECT_
#define _CHARACTERSELECT_

#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/CountDown.hpp>
#include <game/UI/Ctrl/ModelControl.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuCharacterSelect.hpp>
/*
Contributors:
-kHacker35000vr, Melg
*/

//_sinit_ for both classes below at
class CharaName :public LayoutUIControl {
public:
    CharaName(); //8083d840
    ~CharaName() override; //0x8062912c vtable 808d9358
    void InitSelf() override; //0x18 8083f09c
    int GetRuntimeTypeInfo() const override; //0x28 8083f368
    const char *GetClassName() const override; //0x2c 8083d440
    u32 unknown_0x178;
}; //total size 0x178
size_assert(CharaName, 0x178);

namespace Pages {
class CharacterSelect : public MenuInteractable { //ID 0x6B
public:
    CharacterSelect(); //80626c10
    ~CharacterSelect() override; //8083f2cc vtable 808d92c0 
    void OnInit() override; //8083d55c
    void OnDispose() override; //8083ef3c
    void OnActivate() override; //8083da78
    void BeforeEntranceAnimations() override; //8083ef4c
    void BeforeExitAnimations() override; //8083eff4
    void AfterControlUpdate() override; //8083ddbc
    void OnResume() override; //8083eebc
    int GetRuntimeTypeInfo() const override; //8083f35c
    void OnExternalButtonSelect(PushButton *button, u32 r5) override; //8083e8d8
    int GetActivePlayerBitfield() const override; //8083f268 returns 0x6bc
    int GetPlayerBitfield() const override; //8083f260
    ManipulatorManager *GetManipulatorManager() override;; //8083ddb4
    UIControl *CreateExternalControl(u32 id) override; //0x84 8083d87c
    UIControl *CreateControl(u32 id) override; //0x88 8083d884
    void SetButtonHandlers(PushButton *pushButton) override; //8083f270 0x8C
    void OnButtonDriverClick(CtrlMenuCharacterSelect::ButtonDriver *button, u32 buttonId, u8 hudSlotId); //8083dfa8
    void OnButtonDriverSelect(CtrlMenuCharacterSelect::ButtonDriver *button, u32 buttonId, u8 hudSlotId); //8083e5f4
    void OnButtonClick(PushButton *button, u32 hudSlotId); //8083e928 refers to back button
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //8083e924
    void OnBackPress(u32 hudSlotId); //8083e928
    static void func_8083ec28(); //some weird random stuff that stores different characters in racedata scenario 1
    static void func_8083ee1c(); //same, but without the random
    static Page *GetPageById(PageId id = PAGE_CHARACTER_SELECT); //80840dec only ever used with id = char select so it's here

    //here the button refers to the backbutton since the char buttons are handled via external controls
    //onButtonClick    vtable = 0x808bd1d4 function = 8083e740
    //onButtonSelect   vtable = 0x808bd1d4 offset = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd1d4 function = 8083E924
    //onBackPress vtable = 0x808BD1C8 function = 8083E928 (onBackPress)
    //onStartPress     vtable = 0x808bd1c8 offset = 0x7c call is virtual Handler

    CtrlMenuCharacterSelect ctrlMenuCharSelect; //0x6C4
    Mii *localPlayerMiis;
    u8 unknwon_0x8F8[0x904 - 0x8f8];
    u32 localPlayerBitfield; //0x904
    u32 unknwon_0x908;
    CountDown *timer; //0x90c
    CharaName *names;
    DriverModelControl *models;

}; //Total Size 0x918
size_assert(CharacterSelect, 0x918);
}//namespace Pages
//807e2fcc select initial character

extern CharacterId buttonIdToCharacterId[24];

//808a7de0 buttonsId to characterId
#endif