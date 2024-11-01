#ifndef _SINGLEPLAYER_
#define _SINGLEPLAYER_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuMovie.hpp>


//_sinit_ at 8084fc88
namespace Pages {
class SinglePlayer : public MenuInteractable { //ID 0x69
public:
    static const PageId id = PAGE_SINGLE_PLAYER_MENU;
    SinglePlayer(); //80626698
    ~SinglePlayer() override; //8084fbfc vtable 808d9f00
    void OnInit() override; //0x28 8084ef1c
    void OnActivate() override; //0x30 8084f110
    void OnDeactivate() override; //0x34 8084fb8c
    void AfterControlUpdate() override; //0x4c 8084f294
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8084fc7c
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64  8084f688
    int GetActivePlayerBitfield() const override; //0x68 8084fb98
    int GetPlayerBitfield() const override; //0x6c 8084fb90
    ManipulatorManager& GetManipulatorManager() override; //0x70 8084efbc
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 8084efc4
    UIControl* CreateControl(u32 controlId) override; //0x88 8084f108
    void SetButtonHandlers(PushButton& button) override; //0x8C 8084fba0

    void OnButtonClick(PushButton& button, u32 hudSlotId); //8084f298
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //8084fb34
    void OnBackPress(u32 hudSlotId); //8084fb38
    static Page* GetPageById(PageId id = PAGE_SINGLE_PLAYER_MENU); //8084ee0c
    //onButtonClick    vtable = 0x808bd204 function = 8084f298
    //onButtonSelect   vtable = 0x808bd204 offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd204 function = 8084fb34
    //onBackPress      vtable = 0x808bd1f8 function = 8084fb38
    //onStartPress     vtable = 0x808bd1f8 offset   = 0x7c call is virtual Handler

}; //total size 0x6c4
size_assert(SinglePlayer, 0x6c4);
}//namespace Pages
#endif