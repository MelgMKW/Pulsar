#ifndef _UNLOCKPAGE_
#define _UNLOCKPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>

namespace Pages {

//_sinit_ at 808551ec
class Unlock : public MenuInteractable { //ID 0xCD
public:
    static const PageId id = PAGE_UNLOCK;
    Unlock(); //8062be24
    ~Unlock() override; //80855130 vtable 808da4d0
    void OnInit() override; //0x28 80853e18
    void OnActivate() override; //0x30 80854104
    void AfterControlUpdate() override; //0x4c 80854320
    int GetRuntimeTypeInfo() const override; //0x60 808551e0
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64 80854748
    int GetActivePlayerBitfield() const override; //0x68 808550c4
    int GetPlayerBitfield() const override; //0x6C 808550bc
    ManipulatorManager& GetManipulatorManager() override; //0x70 80855128
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 80853e30
    UIControl* CreateControl(u32 controlId) override; //0x88 80853ec0
    void SetButtonHandlers(PushButton& button) override; //0x8C 808550cc

    void OnButtonClick(PushButton& button, u32 hudSlotId); //8085447c
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //8085474c
    void OnBackPress(u32 hudSlotId); //80854750
    void SetTitleBMG(u32 unlockIdx); //80854754
    void PrepareControls(u32 unlockIdx); //80854810
    void SetMessageWindowMessage(CharacterId character, KartId kart); //80854e00 ids set to -1 if the other is unlocked
    void SetModels(CharacterId character, KartId kart); //80854b40 same as above

    static Page* GetPageById(PageId id = PAGE_UNLOCK); //80853cb8
    //onButtonClick     vtable = 0x808bcff4 function = 8085447c
    //onButtonSelect    vtable = 0x808bcff4 offset   = 0x64
    //onButtonDeselect  vtable = 0x808bcff4 function = 8085474c
    //onBackPress       vtable = 0x808bcfe8 function = 80854750
    //onStartPress      vtable = 0x808bcfe8 offset   = 0x7c

    MessageWindowControl messageWindowControl; //0x6c4
    DriverModelControl driverModelControl; //0x838
    VehicleModelControl vehicleModelControl; //0x9c0
    u8 unknown_0xb44[8]; //0xb44
    LayoutUIControl cupIcon; //0xb4c
};//total size 0xcc0
size_assert(Unlock, 0xcc0);


}//namespace Pages
#endif