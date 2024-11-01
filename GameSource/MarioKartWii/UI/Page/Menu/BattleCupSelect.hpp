#ifndef _BATTLECUPSELECT_
#define _BATTLECUPSELECT_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuBattleCup.hpp>

//_sinit_ at 8083a0c0
namespace Pages {
class BattleCupSelect : public MenuInteractable { //ID 0x78
    static const PageId id = PAGE_BATTLE_CUP_SELECT; //ID 0x78
    BattleCupSelect(); //8062949c
    ~BattleCupSelect() override; //80839fc0 vtable 808d8ea8
    void OnInit() override; //0x28 80838f70
    void OnActivate() override; //0x30 80839084
    void OnDeactivate() override; //0x34 80839d94
    void BeforeEntranceAnimations() override; //0x38 80839d98
    void BeforeExitAnimations() override; //0x40 80839df4
    void AfterControlUpdate() override; //0x4c 808393f4
    void OnResume() override; //0x54 80839b7c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8083a0b4
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64  80839904
    int GetActivePlayerBitfield() const override; //0x68 80839f54
    int GetPlayerBitfield() const override; //80839f4c0x6C
    ManipulatorManager& GetManipulatorManager() override; //0x70 80839fb8
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 80838fe8
    UIControl* CreateControl(u32 controlId) override; //0x88 80838ff0
    void SetButtonHandlers(PushButton& button) override; //0x8C 80839f5c
    void OnTimeout(); //0x92 (course votes) 80839e50 ends page and loads
    void UpdateText(); //80839550 updates tracklist
    void LoadNextPage(CtrlMenuBattleCupSelectCup& ctrlMenuBattleCupSelectCup, PushButton& cupButton, u32 hudSlotId); //8083955c
    void OnButtonClick(PushButton& button, u32 hudSlotId); //80839694
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //80839908
    void OnBackPress(u32 hudSlotId); //8083990c
    static Page* GetPageById(PageId id = PAGE_BATTLE_CUP_SELECT); //80838e60 only ever used with id = battlecupselect so it's here

    //for back button
    //onButtonClick    vtable = 0x808bd03c function = 80839694
    //onButtonSelect   vtable = 0x808bd03c offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd03c function = 80839908
    //onBackPress      vtable = 0x808bd030 function = 8083990c
    //onStartPress     vtable = 0x808bd030 offset   = 0x7c call is virtual

    CtrlMenuBattleCupSelectCup ctrlMenuBattleCupSelectCup; //0x6c4
    CtrlMenuBattleCupSelectStage ctrlMenuBattleCupSelectStage; //0xe98 to 0x1750
    u32 curCupId; //0x1750
    u32 unknown_0x1754;
    float float_0x1758;
}; //0x175c
}//namespace Pages
size_assert(BattleCupSelectPage, 0x175c);
#endif