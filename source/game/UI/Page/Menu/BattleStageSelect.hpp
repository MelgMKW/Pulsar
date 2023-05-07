#ifndef _BATTLESTAGESELECT_
#define _BATTLESTAGESELECT_

#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuBattleStage.hpp>

//_sinit_ at 8083d42c
namespace Pages {
class BattleStageSelect: public MenuInteractable { //ID 0x79 
public:
    BattleStageSelect(); //80629954
    ~BattleStageSelect() override; //8083d334 vtable 808d9228
    void OnInit() override; //0x28 8083cc68
    void OnActivate() override; //0x30 8083cd54
    void OnDeactivate() override; //0x34 8083d1f0
    void BeforeEntranceAnimations() override; //0x38 8083cea8
    void BeforeExitAnimations() override; //0x40 8083d194
    void AfterControlUpdate() override; //0x4c 8083cec8
    int GetRuntimeTypeInfo() const override; //0x60 8083d420
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64  8083d154
    int GetActivePlayerBitfield() const override; //0x68 8083d2d0
    int GetPlayerBitfield() const override; //0x6C 8083d2c8
    ManipulatorManager& GetManipulatorManager() override; //0x70 807e1d78
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 8083ccb8
    UIControl* CreateControl(u32 controlId) override; //0x88 8083ccc0
    void SetButtonHandlers(PushButton& button) override; //0x8C 8083d2d8

    void OnButtonClick(PushButton& button, u32 hudSlotId); //8083d11c
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //8083d158
    void OnBackPress(u32 hudSlotId); //8083d15c
    void UpdateBottomText(); //8083cfe4
    void OnTimeout(); //8083d1f4 ends page and loads 0x92 (Stage votes)
    void LoadNextPage(CtrlMenuBattleStageSelectStage* control, PushButton* stageButton, u32 hudSlotId); //8083cfe8
    static Page* GetPageById(PageId id = PAGE_BATTLE_STAGE_SELECT); //8083cb58

    //here the button refers to the back button as the Stage buttons are handled via extern controls
    //onButtonClick    vtable = 0x808bd054 function = 8083d11c
    //onButtonSelect   vtable = 0x808bd054 offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd054 function = 8083d158
    //onBackPress      vtable = 0x808bd048 function = 8083d15c
    //onStartPress     vtable = 0x808bd048 offset   = 0x7c call is virtual

    u32 unknown_0x6C4;
    CtrlMenuBattleStageSelectCup ctrlMenuBattleStageSelectCup; //0x6c8
    CtrlMenuBattleStageSelectStage ctrlMenuBattleStageSelectStage; //0xb54
    bool unknown_0x1a80; //init at 0, set to 1 when a button is pressed
    u8 unknown_0x1a81[0x1a84 - 0x1a81];//0x1a80
}; //total size 0x1a84
size_assert(BattleStageSelect, 0x1a84);
}//namespace Pages
#endif