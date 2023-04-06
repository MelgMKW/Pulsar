#ifndef _MIISELECTPAGE_
#define _MIISELECTPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/SheetSelect.hpp>
#include <game/UI/Ctrl/TabControl.hpp>


//_sinit_ at 80849570
class MiiName : public LayoutUIControl {
public:
    ~MiiName() override; //80626640 vtable 808d9a58
    void InitSelf() override; //0x18 80849284
    int GetRuntimeTypeInfo() const override; //0x28 80849504
    const char *GetClassName() const override; //0x2c 80847e34
}; //0x174

namespace Pages {
class MiiSelect : public MenuInteractable { //ID 0x60
    MiiSelect(); //8062635c
    ~MiiSelect() override; //80849450 vtable 808d99c0
    void OnInit() override; //80847e40 0x28
    void OnActivate() override; //80848568 0x30
    void OnDeactivate() override; //80848bd4 0x34
    void AfterControlUpdate() override; //808487e8 0x4c
    int GetRuntimeTypeInfo() const override; //808494f8 0x60
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //80848ae8 0x64 
    int GetActivePlayerBitfield() const override; //808481cc 0x68
    int GetPlayerBitfield() const override; //80849448 0x6C;
    ManipulatorManager *GetManipulatorManager() override;; //80848044 0x70
    UIControl *CreateExternalControl(u32 externControlId) override; //8084804c 0x84
    UIControl *CreateControl(u32 controlId) override; //80848230 0x88
    void SetButtonHandlers(PushButton *button) override; //808481d4 0x8C

    void OnButtonClick(PushButton *button, u32 hudSlotId); //808487ec
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //80848b58
    void OnBackPress(u32 hudSlotId); //80848b60
    void OnRightArrowPress(SheetSelectControl *control, u32 hudSlotId); //80848be8
    void OnLeftArrowPress(SheetSelectControl *control, u32 hudSlotId); //80848d40
    void OnTabButtonClick(TabControl *control, u32 hudSlotId, u32 optionId); //80848e44
    static Page *GetPageById(PageId id = PAGE_MII_SELECT); //80849594
    static void TriggerTabPtmf(PtmfHolder_3A<TabControl *, void, u32, u32, u32> *handler, TabControl *, u32, u32); //80849510
    static void TriggerSheetPtmf(PtmfHolder_2A<SheetSelectControl *, void, u32, u32> *handler, SheetSelectControl *, u32); //80849540

    void SetMiiIcons(u8 firstMiiIdx); //80848f94
    int GetCurTabMiiCount() const; //80849234 depends on current tab category
    //onButtonClick    function = 808487ec
    //onButtonSelect   offset = 0x64 call is virtual
    //onButtonDeselect function = 80848b58
    //onBackPress      function = 80848b60
    //onStartPress     offset = 0x7c call is virtual

    SheetSelectControl sheetSelectControl; //0x6c4
    TabControl tabControl; //0xbfc
    PtmfHolder_2A<MiiSelect, void, SheetSelectControl *, u32> *onRightArrowPressHandler;  //80848be8 0xd88
    PtmfHolder_2A<MiiSelect, void, SheetSelectControl *, u32> *onLeftArrowPressHandler;  //80848d40 0xd8c
    PtmfHolder_3A<MiiSelect, void, TabControl *, u32, u32> *onTabButtonClick;  //80848e44 0xd90
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