#ifndef _GPCLASSSELECTPAGE_
#define _GPCLASSSELECTPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>

//_sinit_ at 808401d0
namespace Pages {
class GPClassSelect : public MenuInteractable { //ID 0x6a
    GPClassSelect(); //80626950
    ~GPClassSelect() override; //80840138 vtable 808d9398
    void OnInit() override; //8083f4a8 0x28
    void OnActivate() override; //8083f838 0x30
    void OnDeactivate() override; //8083fbc4
    void AfterControlUpdate() override; //8083f914
    int GetRuntimeTypeInfo() const override; //808401c4 0x60
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //8083fb2c 0x64 
    int GetActivePlayerBitfield() const override; //808400d4 0x68
    int GetPlayerBitfield() const; //808400cc 0x6C override;
    ManipulatorManager *GetManipulatorManager() override;; //8083f578 0x70
    void OnStartPress(u32 hudSlotId) override; //8083fbc8 0x7C
    UIControl *CreateExternalControl(u32 externControlId) override; //8083f580 0x84
    UIControl *CreateControl(u32 controlId) override; //8083f7b0 0x88
    void SetButtonHandlers(PushButton *button) override; //808400dc 0x8C

    void OnButtonClick(PushButton *button, u32 hudSlotId); //8083f988
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //8083fbb4
    void OnBackPress(u32 hudSlotId); //8083fbb8

    static Page *GetPageById(PageId id = PAGE_GP_CLASS_SELECT);

    //onButtonClick    vtable = 0x808bd1ec function = 8083f988
    //onButtonSelect   vtable = 0x808bd1ec offset = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd1ec function = 8083fbb4
    //onBackPress      vtable = 0x808bd1e0 function = 8083fbb8
    //onStartPress     vtable = 0x808bd1e0 offset = 0x7c call is virtual

    bool isLimitedKarts; //0x6c4 when you press start, the bool flips
    u8 padding[3];
    LayoutUIControl switchImage; //0x6c8
}; //total size 0x83c
size_assert(GPClassSelect, 0x83c);
}//namespace Pages
#endif