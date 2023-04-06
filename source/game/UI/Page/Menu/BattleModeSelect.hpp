#ifndef _BATTLEMODESELECT_
#define _BATTLEMODESELECT_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>

//_sinit_ at 8083bb38
namespace Pages {
class BattleModeSelect : public MenuInteractable { //ID 0x75
    BattleModeSelect(); //80628b84
    ~BattleModeSelect() override; //8083baac vtable 808d9008
    void OnInit() override; //8083b1f0 0x28
    void OnActivate() override; //8083b400 0x30
    void OnDeactivate() override; //8083b9f4 0x34
    void AfterControlUpdate() override; //8083b8cc 0x4c
    int GetRuntimeTypeInfo() const override; //8083bb2c 0x60
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //8083b9ac 0x64 
    int GetActivePlayerBitfield() const override; //8083ba48 0x68
    int GetPlayerBitfield() const; //8083ba40 0x6C override;
    ManipulatorManager *GetManipulatorManager() override;; //8083b244 0x70
    UIControl *CreateExternalControl(u32 externControlId) override; //8083b24c 0x84
    UIControl *CreateControl(u32 controlId) override; //8083b3f8 0x88
    void SetButtonHandlers(PushButton *button) override; //8083ba50 0x8C

    void OnButtonClick(PushButton *button, u32 hudSlotId); //8083b8d0
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //8083b9e4
    void OnBackPress(u32 hudSlotId); //8083b9e8
    static Page *GetPageById(PageId id = PAGE_BATTLE_MODE_SELECT); //8085212c

    //onButtonClick    vtable = 0x808bd1a4 function = 8083b8d0
    //onButtonSelect   vtable = 0x808bd1a4 offset = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd1a4 function = 8083b9e4
    //onBackPress      vtable = 0x808bd198 function = 8083b9e8
    //onStartPress     vtable = 0x808bd198 offset = 0x7c call is virtual


}; //total size 0x6c4
size_assert(BattleModeSelect, 0x6c4);
}//namespace Pages

#endif