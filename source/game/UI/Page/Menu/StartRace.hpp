#ifndef _STARTGAMEOKPAGE_
#define _STARTGAMEOKPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuText.hpp>

//_sinit_ at 80842a64
namespace Pages {
class StartRace : public MenuInteractable { //ID 0x4B //tied to one OK button "Start?"
    static const PageId id = PAGE_START_RACE;
    StartRace(); //80625a7c
    ~StartRace() override; //808429d8 vtable 808d9580
    void OnInit() override; //0x28 80842464
    void OnActivate() override; //0x30 808428a0
    void AfterControlUpdate() override; //0x4c 80842914
    int GetRuntimeTypeInfo() const override; //0x60 80842a58
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64  808429a4
    int GetActivePlayerBitfield() const override; //0x68 808425e0
    int GetPlayerBitfield() const override; //0x6C 808429c8
    ManipulatorManager& GetManipulatorManager() override; //0x70 808429d0
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 8084247c
    UIControl* CreateControl(u32 controlId) override; //0x88 80842644
    void SetButtonHandlers(PushButton& button) override; //0x8C 808425e8
    void OnButtonClick(PushButton& button, u32 hudSlotId); //80842948 refers to back button
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //808429a8
    void OnBackPress(u32 hudSlotId); //808429ac
    static Page* GetPageById(PageId id = PAGE_START_RACE); //80842354
    //onButtonClick    vtable = 0x808bd30c function = 80842948
    //onButtonSelect   vtable = 0x808bd30c offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd30c function = 808429a8
    //onBackPress      vtable = 0x808bd300 function = 808429ac
    //onStartPress     vtable = 0x808bd300 offset   = 0x7c call is virtual

    bool hasButtonBeenPressed; //0x6c4 used to select which sound to play 
    u8 padding[3];
    CtrlMenuObiTop ctrlMenuObiTop; //0x6c8

}; //total size 0x6cc
size_assert(StartRace, 0x6cc);
}//namespace Pages


#endif