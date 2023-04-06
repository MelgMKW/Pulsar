#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#ifndef _MAINMENU_
#define _MAINMENU_
namespace Pages {
class MainMenu : public MenuInteractable { //ID 0x5a
    MainMenu(); //80625da0
    ~MainMenu() override; //80851c94 vtable 808da0a0 
    void OnInit() override; //0x28 808503dc
    void OnActivate() override; //0x30 80850db0
    void OnDeactivate() override; //0x34 80851b88
    void AfterControlUpdate() override; //0x4C 80851108
    int GetRuntimeTypeInfo() const override; //0x60 80851d2c
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //0x64 8085151c 
    int GetActivePlayerBitfield() const override; //0x68 80851c8c
    int GetPlayerBitfield() const override; //0x6C 80851c84
    ManipulatorManager *GetManipulatorManager() override;; //0x70 808504dc
    UIControl *CreateExternalControl(u32 externControlId) override; //0x84 808504e4
    UIControl *CreateControl(u32 controlId) override; //0x88 80850580
    void SetButtonHandlers(PushButton *button) override; //0x8C 80850d54
    void ResetSectionMgr98AndRaceDataScenario1(u8 localPlayerCount); //player count = 1 except for 2P/3P/4P buttons
    void ShowMessageBox(); //80851b8c "Unable to connect to nintendo wi-fi", no idea how to trigger, inlined
    void OnButtonClick(PushButton *button, u32 hudSlotId); //8085110c
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //808515a0
    void OnBackPress(u32 hudSlotId); //808516ac
    static Page *GetPageById(PageId id = PAGE_MAIN_MENU); //808502cc
    //onButtonClick    vtable = 0x808bd2f4 function = 8085110c
    //onButtonSelect   vtable = 0x808bd2f4 offset = 0x64
    //onButtonDeselect vtable = 0x808bd2f4 function = 808515a0
    //onBackPress vtable = 0x808BD2e8 function =808516ac (onBackPress)
    //onStartPress     vtable = 0x808bd2e8 offset = 0x7c
    LayoutUIControl buttonTitles[4]; //0x6c4 the blue thing englobing buttons
    PushButton *topMenuSingle; //0xc94 pushbutton part of ctrlmenumoviebutton
    PushButton *topMenuMulti2P; //0xc98 same
    PushButton *topMenuMulti3P; //0xC9C same
    PushButton *topMenuMulti4P; //0xCA0 same
    PushButton *topMenuWifi1P; //0xCA4
    PushButton *topMenuWifi2P; //0xCA8
    PushButton *topMenuChannel; //0xCAC 
    PushButton *fileAdminCopy; //0xcb0
    PushButton *fileAdmin; //license settings most likely
}; //total size 0cb8
size_assert(MainMenu, 0xcb8);
}//namespace Pages
#endif