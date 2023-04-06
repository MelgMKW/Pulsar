#ifndef _SINGLEPLAYER_
#define _SINGLEPLAYER_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuMovie.hpp>


//_sinit_ at 8084fc88
namespace Pages {
class SinglePlayer : public MenuInteractable { //ID 0x69
public:
    SinglePlayer(); //80626698
    ~SinglePlayer() override; //8084fbfc vtable 808d9f00
    void OnInit() override; //8084ef1c 0x28
    void OnActivate() override; //8084f110 0x30
    void OnDeactivate() override; //8084fb8c 0x34
    void AfterControlUpdate() override; //8084f294 0x4c
    int GetRuntimeTypeInfo() const override; //8084fc7c 0x60
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //8084f688 0x64 
    int GetActivePlayerBitfield() const override; //8084fb98 0x68
    int GetPlayerBitfield() const override; //8084fb90 0x6c
    ManipulatorManager *GetManipulatorManager() override;; //8084efbc 0x70
    UIControl *CreateExternalControl(u32 externControlId) override; //8084efc4 0x84
    UIControl *CreateControl(u32 controlId) override; //8084f108 0x88
    void SetButtonHandlers(PushButton *button) override; //8084fba0 0x8C

    void OnButtonClick(PushButton *button, u32 hudSlotId); //8084f298
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //8084fb34
    void OnBackPress(u32 hudSlotId); //8084fb38
    static Page *GetPageById(PageId id = PAGE_SINGLE_PLAYER_MENU); //8084ee0c
    //onButtonClick    vtable = 0x808bd204 function = 8084f298
    //onButtonSelect   vtable = 0x808bd204 offset = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd204 function = 8084fb34
    //onBackPress      vtable = 0x808bd1f8 function = 8084fb38
    //onStartPress     vtable = 0x808bd1f8 offset = 0x7c call is virtual Handler

}; //total size 0x6c4
size_assert(SinglePlayer, 0x6c4);
}//namespace Pages
#endif