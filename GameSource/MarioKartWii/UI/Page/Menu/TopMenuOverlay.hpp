#ifndef _TOPMENUOVERLAYPAGE_
#define _TOPMENUOVERLAYPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>

//_sinit_ at 8084edf8
namespace Pages {
class TopMenuOverlay : public Menu { //ID 0x5e simply a MenuPage in its simplest form with no actions etc...
    static const PageId id = PAGE_TOP_MENU_OVERLAY;
    TopMenuOverlay(); //806261e8
    ~TopMenuOverlay() override; //8084ed6c vtable 808d9e48
    int GetRuntimeTypeInfo() const override; //0x60 8084edec
    int GetActivePlayerBitfield() const override; //0x68 8084ed5c
    int GetPlayerBitfield() const override; //0x6C 8084ed54
    ManipulatorManager& GetManipulatorManager() override; //0x70 8084ed64
    UIControl* CreateControl(u32 controlId) override; //0x88 MenuObiTop etc... 8084e96c
    virtual int vf_0x98(); //8084ed4c
    u8 unknown_0x430[4];
    ManipulatorManager manipulatorManager; //0x434
    u8 unknown_0x444[8];
    static Page* GetPageById(PageId id = PAGE_TOP_MENU_OVERLAY); //8084e85c
}; //total size 0x44c
size_assert(TopMenuOverlay, 0x44c);
}//namespace Pages

#endif