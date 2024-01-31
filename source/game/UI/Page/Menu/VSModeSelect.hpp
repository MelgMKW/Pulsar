#ifndef _VSTEAMSELECTPAGE_
#define _VSTEAMSELECTPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>

//_sinit_ at 80852c6c
namespace Pages {
class VSModeSelect : public MenuInteractable { //ID 0x72
    static const PageId id = PAGE_VS_MODE_SELECT;
    VSModeSelect(); //80628210
    ~VSModeSelect() override; //80852be0 vtable 808da238
    void OnInit() override; //0x28 8085223c
    void OnActivate() override; //0x30 80852450
    void OnDeactivate() override; //80852b28
    void AfterControlUpdate() override; //0x4c 808529fc
    int GetRuntimeTypeInfo() const override; //0x60 80852c60
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64  80852ae0
    int GetActivePlayerBitfield() const override; //0x68 80852b7c
    int GetPlayerBitfield() const override; //0x6C 80852b74
    ManipulatorManager& GetManipulatorManager() override; //0x70 80852290
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 80852298
    UIControl* CreateControl(u32 controlId) override; //0x88 80852448
    void SetButtonHandlers(PushButton& button) override; //0x8C 80852b84

    void OnButtonClick(PushButton& button, u32 hudSlotId); //80852a00
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //80852b18
    void OnBackPress(u32 hudSlotId); //80852b1c
    static Page* GetPageById(PageId id = PAGE_VS_MODE_SELECT); //8085212c

    //onButtonClick    vtable = 0x808bd1a4 function = 80852a00
    //onButtonSelect   vtable = 0x808bd1a4 offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd1a4 function = 80852b18
    //onBackPress      vtable = 0x808bd198 function = 80852b1c
    //onStartPress     vtable = 0x808bd198 offset   = 0x7c call is virtual

}; //0x6c4
size_assert(VSModeSelect, 0x6c4);
}//namespace Pages
#endif