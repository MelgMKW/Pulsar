#ifndef _BATTLEMODESELECT_
#define _BATTLEMODESELECT_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>

//_sinit_ at 8083bb38
namespace Pages {
class BattleModeSelect : public MenuInteractable { //ID 0x75
    static const PageId id = PAGE_BATTLE_MODE_SELECT;
    BattleModeSelect(); //80628b84
    ~BattleModeSelect() override; //8083baac vtable 808d9008
    void OnInit() override; //0x28 8083b1f0
    void OnActivate() override; //0x30 8083b400
    void OnDeactivate() override; //0x34 8083b9f4
    void AfterControlUpdate() override; //0x4c 8083b8cc
    int GetRuntimeTypeInfo() const override; //0x60 8083bb2c
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64 8083b9ac
    int GetActivePlayerBitfield() const override; //0x68 8083ba48
    int GetPlayerBitfield() const override; //0x6C 8083ba40
    ManipulatorManager& GetManipulatorManager() override; //0x70 8083b244
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 8083b24c
    UIControl* CreateControl(u32 controlId) override; //0x88 8083b3f8
    void SetButtonHandlers(PushButton& button) override; //0x8C 8083ba50

    void OnButtonClick(PushButton& button, u32 hudSlotId); //8083b8d0
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //8083b9e4
    void OnBackPress(u32 hudSlotId); //8083b9e8
    static Page* GetPageById(PageId id = PAGE_BATTLE_MODE_SELECT); //8085212c

    //onButtonClick    vtable = 0x808bd1a4 function = 8083b8d0
    //onButtonSelect   vtable = 0x808bd1a4 offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd1a4 function = 8083b9e4
    //onBackPress      vtable = 0x808bd198 function = 8083b9e8
    //onStartPress     vtable = 0x808bd198 offset   = 0x7c call is virtual


}; //total size 0x6c4
size_assert(BattleModeSelect, 0x6c4);
}//namespace Pages

#endif