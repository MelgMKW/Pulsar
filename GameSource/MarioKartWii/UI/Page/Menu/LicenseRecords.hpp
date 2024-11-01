#ifndef _LICENSERECORDSPAGE_
#define _LICENSERECORDSPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>

//_sinit_ at 8085ffc0
namespace Pages {

class LicenseRecords : public MenuInteractable { //ID 0xCE ID 0xD0 ID 0xD1 ID 0xD2
    static const PageId id = PAGE_OVERALL_RECORDS;
    LicenseRecords(); //8062c0f4
    ~LicenseRecords() override; //8085ff34 vtable 808daeb0
    void OnInit() override; //0x28 8085f1bc
    void OnActivate() override; //0x30 8085f470
    void AfterControlUpdate() override; //0x4c 8085f4dc
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8085ffb4
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64 8085f5bc
    int GetActivePlayerBitfield() const override; //0x68 8085fec8
    int GetPlayerBitfield() const override; //0x6C 8085fec0
    ManipulatorManager& GetManipulatorManager() override; //0x70 8085ff2c
    UIControl* CreateExternalControl(u32 externControlId); //0x84 8085f264
    UIControl* CreateControl(u32 controlId) override; //0x88 8085f310
    void SetButtonHandlers(PushButton& button) override; //0x8C 8085fed0

    static Page* GetPageById(PageId id = PAGE_OVERALL_RECORDS); //8085f0ac
}; //0x6c4
size_assert(LicenseRecords, 0x6c4);
}//namespace Pages
#endif