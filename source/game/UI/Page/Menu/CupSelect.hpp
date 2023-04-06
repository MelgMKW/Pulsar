#ifndef _CUPSELECT_
#define _CUPSELECT_
#include <kamek.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuCup.hpp>



//_sinit_ at 80842340
namespace Pages {
class CupSelect : public MenuInteractable { //ID 0x6e
public:
    static CourseId idxToCourseId[32]; //808ad320
    static const char cupTPLs[0x8][0x10]; //808AF8E0
    CupSelect(); //80627684
    ~CupSelect() override; //80842240 vtable 808d94e8
    void OnInit() override; //80840efc 0x28
    void OnActivate() override; //80841110 0x30
    void OnDeactivate() override; //80841ff8 0x34
    void BeforeEntranceAnimations() override; //80842020 0x38
    void BeforeExitAnimations() override; //8084207c 0x40
    void AfterControlUpdate() override; //808414b8 0x4c
    void OnResume() override; //80841de4 0x54
    int GetRuntimeTypeInfo() const override; //80842334 0x60
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //80841b4c 0x64 
    int GetActivePlayerBitfield() const override; //808421dc 0x68
    int GetPlayerBitfield() const; //808421d4 0x6C override;
    ManipulatorManager *GetManipulatorManager() override;; //808414b0 0x70
    UIControl *CreateExternalControl(u32 externControlId) override; //80841000 0x84
    UIControl *CreateControl(u32 controlId) override; //80841008 0x88
    void SetButtonHandlers(PushButton *button) override; //808421e4 8083716C 0x8C

    void UpdateText(CtrlMenuCupSelectCup *cups); //80841614 updates tracklist and bottomtext if grandprix (with trophy and rank)
    void LoadNextPage(CtrlMenuCupSelectCup *ctrlMenuCupSelectCup, PushButton *cupButton, u32 hudSlotId); //80841744
    void OnTimeout(); //808420d8 ends page and loads 0x92 (course votes)
    void OnButtonClick(PushButton *button, u32 hudSlotId); //808418e8 refers to back button
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //80841b50
    void OnBackPress(u32 hudSlotId); //80841b54
    static Page *GetPageById(PageId id = PAGE_CUP_SELECT); //80840dec only ever used with id = cup select so it's here

    //for back button
    //onButtonClick    vtable = 0x808bd06c function = 808418e8
    //onButtonSelect   vtable = 0x808bd06c offset = 0x64 call is virtual
    //onButtonDeselect vtable = 0x808bd06c function = 80841b50
    //onBackPress      vtable = 0x808bd060 function = 80841b54
    //onStartPress     vtable = 0x808bd060 offset = 0x7c call is virtual

    CtrlMenuCupSelectCup ctrlMenuCupSelectCup; //0x6c4
    CtrlMenuCupSelectCourse ctrlMenuCupSelectCourse; //0x1c90
    u32 clickedCupId; //0x23d4
    u32 unknown_0x23D8;
    float float_0x23dc;
}; //total size 0x23e0
size_assert(CupSelect, 0x23e0);
}//namespace Pages
#endif