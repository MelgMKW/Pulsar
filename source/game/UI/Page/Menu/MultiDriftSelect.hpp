#ifndef _MULTIDRIFTSELECT_
#define _MULTIDRIFTSELECT_

#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Page/Menu/MultiKartSelect.hpp>
#include <game/UI/Ctrl/CountDown.hpp>

/*
Contributors:
-Melg
*/

//_sinit_ at 8084ba10
namespace Pages {
class MultiDriftSelect : public MenuInteractable { //ID 0x82
public:
    MultiDriftSelect(); //8062b8bc
    ~MultiDriftSelect() override; //8084b984 vtable 808d9bc8
    void OnInit() override; //0x28 8084aac4
    void OnActivate() override; //0x30 8084b280
    void AfterControlUpdate() override; //0x4c 8084b388
    void OnResume() override; //0x54 8084b8c4
    int GetRuntimeTypeInfo() const override; //0x60 8084ba04
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //0x64 8084b7ec
    int GetActivePlayerBitfield() const override; //0x68 8084af84
    int GetPlayerBitfield() const override; //0x6C 8084af8c
    ManipulatorManager *GetManipulatorManager() override; //0x70 8084af7c
    void OnControlsInitialized() override; //0x80 8084aff0
    UIControl *CreateExternalControl(u32 externControlId) override; //0x84 8084aff4
    UIControl *CreateControl(u32 controlId) override; //0x88 8084b150
    void SetButtonHandlers(PushButton *button) override; //0x8c 8084af94


    void OnButtonClick(PushButton *button, u32 hudSlotId); //8084b500
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //8084b7f0
    void OnBackPress(u32 hudSlotId); //8084b7f4


    static Page *GetPageById(PageId id = PAGE_MULTIPLAYER_DRIFT_SELECT); //8084ba24

    //onButtonClick function = 8084b500 (onClick)
    //onButtonSelect offset = 0x64 call is virtual (onSelect)
    //onButtonDeselect function = 8084b7f0 (onDeSelect, just a blr)
    //onBackPress function = 8084b7f4 (onBackPress)
    //onStartPress offset = 0x7c call is virtual Handler (onStartPress?)

    CountDown *timer;
    MultiKartBox *boundingBoxes; //0x6c8
    u32 unknown_0x6cc;

};
size_assert(MultiDriftSelect, 0x6d0);
}//namespace Pages
/* controlGroup:
index 0 = CharaName (MachineSelectName.brctr)
Index 1 = LayoutUIControl (MachineSelectNULL6 variant MachineSelectNULL) which contains 6 controls MachineSelectNULLX
Index 2 = LayoutUIControl (MachineSelectNULL6 variant MachineSelectNULL) which contains 6 controls MachineSelectNULLX each containing 2 controls MachineSelect2_X
*/

#endif