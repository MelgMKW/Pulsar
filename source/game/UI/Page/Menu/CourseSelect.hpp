#ifndef _COURSESELECT_
#define _COURSESELECT_

#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuCourse.hpp>

//_sinit_ at 80840dd8
namespace Pages {
class CourseSelect : public MenuInteractable { //ID 0x6F    
public:
    CourseSelect(); //80627bd8
    ~CourseSelect() override; //80840ce0 vtable 808d9450
    void OnInit() override; //808402f4 0x28
    void OnActivate() override; //808404a0 0x30
    void OnDeactivate() override; //80840b78 0x34
    void BeforeEntranceAnimations() override; //808405c0 0x38
    void BeforeExitAnimations() override; //80840b1c 0x40
    void AfterControlUpdate() override; //8084060c 0x4c
    int GetRuntimeTypeInfo() const override; //80840dcc 0x60
    void OnExternalButtonSelect(PushButton *button, u32 hudSlotId) override; //80840aac 0x64 
    int GetActivePlayerBitfield() const override; //80840c7c 0x68
    int GetPlayerBitfield() const; //80840c74 0x6C override;
    ManipulatorManager *GetManipulatorManager() override;; //807e4f74 0x70
    UIControl *CreateExternalControl(u32 externControlId) override; //80840390 0x84
    UIControl *CreateControl(u32 controlId) override; //80840398 0x88
    void SetButtonHandlers(PushButton *button) override; //80840c84 0x8C

    void OnButtonClick(PushButton *button, u32 hudSlotId); //80840a44
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //80840ab0
    void OnBackPress(u32 hudSlotId); //80840ab4
    void UpdateBottomText(CtrlMenuCourseSelectCourse *course, PushButton *button, u32 hudSlotId); //80840728
    void OnTimeout(); //80840ba0 ends page and loads 0x92 (course votes)
    void LoadNextPage(CtrlMenuCourseSelectCourse *control, PushButton *courseButton, u32 hudSlotId); //80840830
    static Page *GetPageById(PageId id = PAGE_COURSE_SELECT); //808401e4
    //here the button refers to the back button as the course buttons are handled via extern controls
    //onButtonClick 0x658 vtable 808bd054 80840a44
    //onButtonSelect 0x66C vtable 808bd054 virtual 0x64
    //onButtonDeselect 0x680 vtable 808bd054 80840ab0
    //onBackPress  0x694 vtable 808bd048 80840ab4
    //onStartPress 0x6A8 vtable 808bd048 virtual off 0x7C

    u32 unknown_0x6C4;
    CtrlMenuCourseSelectCup ctrlMenuCourseSelectCup; //0x6c8
    CtrlMenuCourseSelectCourse CtrlMenuCourseSelectCourse; //0x149c
    bool unknown_0x215c; //init at 0, set to 1 when a button is pressed
    u8 unknown_0x215d[0x2160 - 0x215d];
}; //total size 0x2160
size_assert(CourseSelect, 0x2160);
}//namespace Pages
#endif