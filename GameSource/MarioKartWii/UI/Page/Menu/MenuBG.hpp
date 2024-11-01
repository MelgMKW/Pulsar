#ifndef _MENUBGPAGE_
#define _MENUBGPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>

namespace Pages {

//_sinit_ at 80838e4c
class MenuBG : public Menu { //ID 0x5B, also ID 0x5D just a layoutUIControl which is the usual moving horizontal lines BG
    //0x5B = MenuBG.brctr
    //0x5D = OptionBG.brctr

    static const PageId id = PAGE_MENU_BG;
    MenuBG(); //80626078
    ~MenuBG() override; //80838dc0 vtable 808d8e10

    void BeforeEntranceAnimations() override; //0x38 80838dbc
    void AfterControlUpdate() override; //0x4c 80838da0
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80838e40
    int GetActivePlayerBitfield() const override; //0x68 80838dac
    int GetPlayerBitfield() const override; //0x6C; 80838da4
    ManipulatorManager& GetManipulatorManager() override; //0x70 80838db4
    UIControl* CreateControl(u32 controlId) override; //0x88 80838c3c

    static Page* GetPageById(PageId id = PAGE_MENU_BG); //80838b2c

    ManipulatorManager manipulatorManager; //0x430
}; //total size 0x440
size_assert(MenuBG, 0x440);

}//namespace Pages
#endif