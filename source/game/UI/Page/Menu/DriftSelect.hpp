#ifndef _DRIFTSELECT_
#define _DRIFTSELECT_

#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/CountDown.hpp>

/*
Contributors:
-Melg
*/

//_sinit_ at 8084e848
namespace Pages {
class DriftSelect: public MenuInteractable { //ID 0x6D
public:
    DriftSelect(); //806273cc
    ~DriftSelect() override; //8084E7BC vtable 808d9db0
    void OnInit() override; //0x28 8084ddfc
    void OnActivate() override; //0x30 8084e13c
    void OnDeactivate() override; //0x34 8084e704
    void AfterControlUpdate() override; //0x4c 8084e25c
    int GetRuntimeTypeInfo() const override; //0x60 8084e83c
    void OnExternalButtonSelect(PushButton& button, u32 r5) override; //0x64 8084e6bc
    int GetActivePlayerBitfield() const override; //0x68 8084e758
    int GetPlayerBitfield() const override; //0x6c 8084e750
    ManipulatorManager& GetManipulatorManager() override; //0x70 8084dee0
    UIControl* CreateExternalControl(u32 id) override; //0x84 8084dee8
    UIControl* CreateControl(u32 id) override; //0x88 8084e134
    void SetButtonHandlers(PushButton& pushButton) override; //0x8C 8084e760

    void OnButtonClick(PushButton& button, u32 hudSlotId); //8084e388
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //8084e6f4
    void OnBackPress(u32 hudSlotId); //8084e6f8
    static Page* GetPageById(PageId id = PAGE_DRIFT_SELECT); //8084dcec

    //onButtonClick    vtable = 0x808bd15c function = 8084e388
    //onButtonSelect   vtable = 0x808bd15c offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd15c function = 8084e6f4
    //onBackPress      vtable = 0x808bd150 function = 8084e6f8
    //onStartPress     vtable = 0x808bd150 offset   = 0x7c call is virtual

    CountDown* timer; //0x6C4
    SectionId sectionId;
}; //Total Size 0x6CC
size_assert(DriftSelect, 0x6CC);
}//namespace Pages
#endif