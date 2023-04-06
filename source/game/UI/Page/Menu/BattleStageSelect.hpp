#ifndef _BATTLESTAGESELECT_
#define _BATTLESTAGESELECT_

#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuBattleStage.hpp>

//_sinit_ at 8083d42c
namespace Pages {
class BattleStageSelect : public MenuInteractable { //ID 0x79 
public:
    BattleStageSelect(); //80629954
    ~BattleStageSelect() override; //8083d334 vtable 808d9228
    void OnInit() override; //8083cc68 0x28
    void OnActivate() override; //8083cd54 0x30
    void OnDeactivate() override; //8083d1f0 0x34
    void BeforeEntranceAnimations() override; //8083cea8 0x38
    void BeforeExitAnimations() override; //8083d194 0x40
    void AfterControlUpdate() override; //8083cec8 0x4c
    int GetRuntimeTypeInfo() const override; //8083d420 0x60
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //8083d154 0x64 
    int GetActivePlayerBitfield() const override; //8083d2d0 0x68
    int GetPlayerBitfield() const; //8083d2c8 0x6C override;
    ManipulatorManager *GetManipulatorManager() override;; //807e1d78 0x70
    UIControl *CreateExternalControl(u32 externControlId) override; //8083ccb8 0x84
    UIControl *CreateControl(u32 controlId) override; //8083ccc0 0x88
    void SetButtonHandlers(PushButton *button) override; //8083d2d8 0x8C

    void OnButtonClick(PushButton *button, u32 hudSlotId); //8083d11c
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //8083d158
    void OnBackPress(u32 hudSlotId); //8083d15c
    void UpdateBottomText(); //8083cfe4
    void OnTimeout(); //8083d1f4 ends page and loads 0x92 (Stage votes)
    void LoadNextPage(CtrlMenuBattleStageSelectStage *control, PushButton *stageButton, u32 hudSlotId); //8083cfe8
    static Page *GetPageById(PageId id = PAGE_BATTLE_STAGE_SELECT); //8083cb58

    //here the button refers to the back button as the Stage buttons are handled via extern controls
    //onButtonClick 0x658 vtable 808bd054 8083d11c
    //onButtonSelect 0x66C vtable 808bd054 virtual 0x64
    //onButtonDeselect 0x680 vtable 808bd054 8083d158
    //onBackPress  0x694 vtable 808bd048 8083d15c
    //onStartPress 0x6A8 vtable 808bd048 virtual off 0x7C

    u32 unknown_0x6C4;
    CtrlMenuBattleStageSelectCup ctrlMenuBattleStageSelectCup; //0x6c8
    CtrlMenuBattleStageSelectStage ctrlMenuBattleStageSelectStage; //0xb54
    bool unknown_0x1a80; //init at 0, set to 1 when a button is pressed
    u8 unknown_0x1a81[0x1a84 - 0x1a81];//0x1a80
}; //total size 0x1a84
size_assert(BattleStageSelect, 0x1a84);
}//namespace Pages
#endif