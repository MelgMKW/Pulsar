#ifndef _MULTIPLAYER_
#define _MULTIPLAYER_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuMovie.hpp>


//_sinit_ at 8084dcd8
namespace Pages { //MultiPlayerMenu
class MultiPlayer : public MenuInteractable { //ID 0x80
public:
    static const PageId id = PAGE_MULTIPLAYER_MENU;
    MultiPlayer(); //8062b240
    ~MultiPlayer() override; //8084dc4c vtable 808d9d08
    void OnInit() override; //0x28 8084d200
    void OnActivate() override; //0x30 8084d3b0
    void OnDeactivate() override; //0x34 8084dbd4
    void AfterControlUpdate() override; //0x4c 8084d4d8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8084dccc
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64  8084d6fc
    int GetActivePlayerBitfield() const override; //0x68 8084dbe0
    int GetPlayerBitfield() const override; //0x6c 8084dbd8
    ManipulatorManager& GetManipulatorManager() override; //0x70 8084dc44
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 8084d260
    UIControl* CreateControl(u32 controlId) override; //0x88 8084d3a8
    void SetButtonHandlers(PushButton& button) override; //0x8C 8084dbe8

    void OnButtonClick(PushButton& button, u32 hudSlotId); //8084d4dc
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //8084db7c
    void OnBackPress(u32 hudSlotId); //8084db80
    static Page* GetPageById(PageId id = PAGE_MULTIPLAYER_MENU); //8084d0f0
    //onButtonClick    vtable = 0x808bd204 function = 8084d4dc
    //onButtonSelect   vtable = 0x808bd204 offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd204 function = 8084db7c
    //onBackPress      vtable = 0x808bd1f8 function = 8084db80
    //onStartPress     vtable = 0x808bd1f8 offset   = 0x7c call is virtual Handler

}; //total size 0x6c4
size_assert(MultiPlayer, 0x6c4);
}//namespace Pages
#endif