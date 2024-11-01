#ifndef _MIISELECTPAGE_
#define _MIISELECTPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>
#include <MarioKartWii/UI/Ctrl/UIControl.hpp>
#include <MarioKartWii/UI/Ctrl/SheetSelect.hpp>
#include <MarioKartWii/UI/Ctrl/TabControl.hpp>


//_sinit_ at 80849570
class MiiName : public LayoutUIControl {
public:
    ~MiiName() override; //80626640 vtable 808d9a58
    void InitSelf() override; //0x18 80849284
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 80849504
    const char* GetClassName() const override; //0x2c 80847e34
}; //0x174

namespace Pages {
class MiiSelect : public MenuInteractable { //ID 0x60
    static const PageId id = PAGE_MII_SELECT;
    MiiSelect(); //8062635c
    ~MiiSelect() override; //80849450 vtable 808d99c0
    void OnInit() override; //0x28 80847e40
    void OnActivate() override; //0x30 80848568
    void OnDeactivate() override; //0x34 80848bd4
    void AfterControlUpdate() override; //0x4c 808487e8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 808494f8
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64  80848ae8
    int GetActivePlayerBitfield() const override; //0x68 808481cc
    int GetPlayerBitfield() const override; //0x6C 80849448
    ManipulatorManager& GetManipulatorManager() override; //0x70 80848044
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 8084804c
    UIControl* CreateControl(u32 controlId) override; //0x88 80848230
    void SetButtonHandlers(PushButton& button) override; //0x8C 808481d4

    void OnButtonClick(PushButton& button, u32 hudSlotId); //808487ec
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //80848b58
    void OnBackPress(u32 hudSlotId); //80848b60
    void OnRightArrowPress(SheetSelectControl& control, u32 hudSlotId); //80848be8
    void OnLeftArrowPress(SheetSelectControl& control, u32 hudSlotId); //80848d40
    void OnTabButtonClick(TabControl& control, u32 hudSlotId, u32 optionId); //80848e44
    static Page* GetPageById(PageId id = PAGE_MII_SELECT); //80847d24
    static void TriggerTabPtmf(PtmfHolder_3A<TabControl&, void, u32, u32, u32>* handler, TabControl*, u32, u32); //80849510
    static void TriggerSheetPtmf(PtmfHolder_2A<SheetSelectControl&, void, u32, u32>* handler, SheetSelectControl*, u32); //80849540

    void SetMiiIcons(u8 firstMiiIdx); //80848f94
    int GetCurTabMiiCount() const; //80849234 depends on current tab category
    //onButtonClick    vtable = 0x808bd06c function = 808487ec
    //onButtonSelect   vtable = 0x808bd06c offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd06c function = 80848b58
    //onBackPress      vtable = 0x808bd060 function = 80848b60
    //onStartPress     vtable = 0x808bd060 offset   = 0x7c call is virtual

    SheetSelectControl sheetSelectControl; //0x6c4
    TabControl tabControl; //0xbfc
    PtmfHolder_2A<MiiSelect, void, SheetSelectControl&, u32>* onRightArrowPressHandler;  //0xd88 80848be8
    PtmfHolder_2A<MiiSelect, void, SheetSelectControl&, u32>* onLeftArrowPressHandler;  //0xd8c 80848d40
    PtmfHolder_3A<MiiSelect, void, TabControl&, u32, u32>* onTabButtonClick;  //0xd90 80848e44
    u32 clickedButtonId; //0xD94
    u32 firstMiiIdx; //0xd98, +10 per page since 10 miis per page
    u32 tabId; //0xD9C 0 for wii console, 1 for guest
    u32 activeHudSlotId; //0xda0 80847e6c
    u32 localPlayerCount; //0xDA4
    MiiName miiName; //0xDA8
    u32 unknown_0xF1C;
}; //0xf20
size_assert(MiiSelect, 0xf20);
}//namespace Pages

#endif