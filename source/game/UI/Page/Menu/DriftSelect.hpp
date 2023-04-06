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
class DriftSelect : public MenuInteractable { //ID 0x6D
public:
    DriftSelect(); //806273cc
    ~DriftSelect() override; //8084E7BC vtable 808d9db0
    void OnInit() override; //8084ddfc 0x28 might be for 6c
    void OnActivate() override; //8084e13c 0x30 calls the thp
    void OnDeactivate() override; //8084e704 0x34 calls the thp
    void AfterControlUpdate() override; //8084e25c 0x4c
    int GetRuntimeTypeInfo() const override; //8084e83c 0x60 returns 809C45e8
    void OnExternalButtonSelect(PushButton *button, u32 r5) override; //8084e6bc
    int GetActivePlayerBitfield() const override; //8084e758 returns 0x6bc
    int GetPlayerBitfield() const override; //8084e750
    ManipulatorManager *GetManipulatorManager() override;; //8084dee0
    UIControl *CreateExternalControl(u32 id) override; //0x84 8084dee8
    UIControl *CreateControl(u32 id) override; //0x88 TO BE DEFINED 8084e134 2 buttons
    void SetButtonHandlers(PushButton *pushButton) override; //8084e760 0x8C

    void OnButtonClick(PushButton *button, u32 hudSlotId); //8084e388
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //8084e6f4
    void OnBackPress(u32 hudSlotId); //8084e6f8
    static Page *GetPageById(PageId id = PAGE_DRIFT_SELECT); //8084dcec

    //onDriftButtonClick vtable = 0x808bd15c function = 8084e388
    //onDriftButtonSelect vtable = 0x808bd15c offset = 0x64 call is virtual
    //onDriftButtonDeselect vtable = 0x808bd15c function = 8084e6f4
    //onBackPress vtable = 0x808BD1150 function = 8084e6f8
    //on StartPres svtable = 0x808bd150 offset = 0x7c call is virtual Handler
    CountDown *timer; //0x6C4
    SectionId sectionId;
}; //Total Size 0x6CC
size_assert(DriftSelect, 0x6CC);
}//namespace Pages
#endif