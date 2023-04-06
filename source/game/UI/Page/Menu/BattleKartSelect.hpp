#ifndef _BATTLEKARTSELECT_
#define _BATTLEKARTSELECT_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Page/Menu/CharacterSelect.hpp>
#include <game/UI/Page/Menu/KartSelect.hpp>
#include <game/UI/Ctrl/ModelControl.hpp>

//_sinit_ at 8083b0cc
namespace Pages {
class BattleKartSelect : public MenuInteractable { //ID 0x76
public:
    BattleKartSelect(); //80628e3c 
    ~BattleKartSelect() override; //8083b014 vtable 0x808D8F40
    void OnInit() override; //8083a1e4
    void OnActivate() override; //8083a458
    void BeforeEntranceAnimations() override; //8083af3c
    void BeforeExitAnimations() override; //8083af9c
    void AfterControlUpdate() override; //8083a78c
    int GetRuntimeTypeInfo() const override; //8083b0c0
    void OnExternalButtonSelect(PushButton *button, u32 r5) override; //8083aaa4
    int GetActivePlayerBitfield() const override; //8083b004 returns 0x6bc
    int GetPlayerBitfield() const override; //8083affc
    ManipulatorManager *GetManipulatorManager() override;; //8083b00c
    UIControl *CreateExternalControl(u32 id) override; //0x84 8083a1f8
    UIControl *CreateControl(u32 id) override; //0x88 8083a33c
    void SetButtonHandlers(PushButton *pushButton) override; //8083a2e0 0x8C
    void OnButtonClick(PushButton *button, u32 hudSlotId); //8083a918 refers to back button
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //8083ab78
    void OnBackPress(u32 hudSlotId); //8083ab80
    static void func_8083ac54(); //some weird random stuff that stores different karts in racedata scenario1, akin to char select
    static void func_8083ad54(); //same, but without the random
    static Page *GetPageById(PageId id = PAGE_BATTLE_KART_SELECT); //8083a0d4
    //onButtonClick    vtable = 0x808bd114 function = 8083A918
    //onButtonSelect   vtable = 0x808bd114 offset = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd114 function = 8083AB78
    //onBackPress      vtable = 0x808BD108 function = 8083AB80
    //onStartPress     vtable = 0x808BD108 offset = 0x7c call is virtual Handler

    u32 unknwown_0x6C4; //init at -1
    CountDown *timer;
    u32 unknown_0x6CC;
    VehicleModelControl vehicleModel; //0x6D0
    CharaName name; //0x854
    CtrlMenuMachineGraph ctrlMenuMachineGraph;
}; // Total Size 0xb50
size_assert(BattleKartSelect, 0xB50);
}//namespace Pages
#endif