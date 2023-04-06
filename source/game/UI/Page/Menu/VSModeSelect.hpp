#ifndef _VSTEAMSELECTPAGE_
#define _VSTEAMSELECTPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>

//_sinit_ at 80852c6c
namespace Pages {
class VSModeSelect : public MenuInteractable { //ID 0x72
    VSModeSelect(); //80628210
    ~VSModeSelect() override; //80852be0 vtable 808da238
    void OnInit() override; //8085223c 0x28
    void OnActivate() override; //80852450 0x30
    void OnDeactivate() override; //80852b28
    void AfterControlUpdate() override; //808529fc 0x4c
    int GetRuntimeTypeInfo() const override; //80852c60 0x60
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //80852ae0 0x64 
    int GetActivePlayerBitfield() const override; //80852b7c 0x68
    int GetPlayerBitfield() const; //80852b74 0x6C override;
    ManipulatorManager *GetManipulatorManager() override;; //80852290 0x70
    UIControl *CreateExternalControl(u32 externControlId) override; //80852298 0x84
    UIControl *CreateControl(u32 controlId) override; //80852448 0x88
    void SetButtonHandlers(PushButton *button) override; //80852b84 0x8C

    void OnButtonClick(PushButton *button, u32 hudSlotId); //80852a00
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //80852b18
    void OnBackPress(u32 hudSlotId); //80852b1c
    static Page *GetPageById(PageId id = PAGE_VS_MODE_SELECT); //8085212c

    //onButtonClick    vtable = 0x808bd1a4 function = 80852a00
    //onButtonSelect   vtable = 0x808bd1a4 offset = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd1a4 function = 80852b18
    //onBackPress      vtable = 0x808bd198 function = 80852b1c
    //onStartPress     vtable = 0x808bd198 offset = 0x7c call is virtual

}; //0x6c4
size_assert(VSModeSelect, 0x6c4);
}//namespace Pages
#endif