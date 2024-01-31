#ifndef _CUPSELECT_
#define _CUPSELECT_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuCup.hpp>



//_sinit_ at 80842340
namespace Pages {
class CupSelect : public MenuInteractable { //ID 0x6e
public:
    static const PageId id = PAGE_CUP_SELECT;
    static CourseId idxToCourseId[32]; //808ad320
    static const char cupTPLs[0x8][0x10]; //808AF8E0
    CupSelect(); //80627684
    ~CupSelect() override; //80842240 vtable 808d94e8
    void OnInit() override; //0x28 80840efc
    void OnActivate() override; //0x30 80841110
    void OnDeactivate() override; //0x34 80841ff8
    void BeforeEntranceAnimations() override; //0x38 80842020
    void BeforeExitAnimations() override; //0x40 8084207c
    void AfterControlUpdate() override; //0x4c 808414b8
    void OnResume() override; //0x54 80841de4
    int GetRuntimeTypeInfo() const override; //0x60 80842334
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64  80841b4c
    int GetActivePlayerBitfield() const override; //0x68 808421dc
    int GetPlayerBitfield() const override; //0x6C 808421d4
    ManipulatorManager& GetManipulatorManager() override; //0x70 808414b0
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 80841000
    UIControl* CreateControl(u32 controlId) override; //0x88 80841008
    void SetButtonHandlers(PushButton& button) override; //0x8C 808421e4 8083716C

    void UpdateText(CtrlMenuCupSelectCup& cups); //80841614 updates tracklist and bottomtext if grandprix (with trophy and rank)
    void LoadNextPage(CtrlMenuCupSelectCup& ctrlMenuCupSelectCup, PushButton& cupButton, u32 hudSlotId); //80841744
    void OnTimeout(); //0x92 (course votes) 808420d8 ends page and loads
    void OnButtonClick(PushButton& button, u32 hudSlotId); //808418e8 refers to back button
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //80841b50
    void OnBackPress(u32 hudSlotId); //80841b54
    static Page* GetPageById(PageId id = PAGE_CUP_SELECT); //80840dec only ever used with id = cup select so it's here

    //for back button
    //onButtonClick    vtable = 0x808bd06c function = 808418e8
    //onButtonSelect   vtable = 0x808bd06c offset   = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd06c function = 80841b50
    //onBackPress      vtable = 0x808bd060 function = 80841b54
    //onStartPress     vtable = 0x808bd060 offset   = 0x7c call is virtual

    CtrlMenuCupSelectCup ctrlMenuCupSelectCup; //0x6c4
    CtrlMenuCupSelectCourse ctrlMenuCupSelectCourse; //0x1c90
    u32 clickedCupId; //0x23d4
    u32 unknown_0x23D8;
    float float_0x23dc;
}; //total size 0x23e0
size_assert(CupSelect, 0x23e0);
}//namespace Pages
#endif