#ifndef _COURSESELECT_
#define _COURSESELECT_

#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/Menu/Menu.hpp>
#include <MarioKartWii/UI/Ctrl/PushButton.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuCourse.hpp>

//_sinit_ at 80840dd8
namespace Pages {
class CourseSelect : public MenuInteractable { //ID 0x6F    
public:
    static const PageId id = PAGE_COURSE_SELECT;
    CourseSelect(); //80627bd8
    ~CourseSelect() override; //80840ce0 vtable 808d9450
    void OnInit() override; //0x28 808402f4
    void OnActivate() override; //0x30 808404a0
    void OnDeactivate() override; //0x34 80840b78
    void BeforeEntranceAnimations() override; //0x38 808405c0
    void BeforeExitAnimations() override; //0x40 80840b1c
    void AfterControlUpdate() override; //0x4c 8084060c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 80840dcc
    void OnExternalButtonSelect(PushButton& button, u32 hudSlotId) override; //0x64  80840aac
    int GetActivePlayerBitfield() const override; //0x68 80840c7c
    int GetPlayerBitfield() const override; //0x6C 80840c74
    ManipulatorManager& GetManipulatorManager() override; //0x70 807e4f74
    UIControl* CreateExternalControl(u32 externControlId) override; //0x84 80840390
    UIControl* CreateControl(u32 controlId) override; //0x88 80840398
    void SetButtonHandlers(PushButton& button) override; //0x8C 80840c84

    void OnButtonClick(PushButton& button, u32 hudSlotId); //80840a44
    void OnButtonDeselect(PushButton& button, u32 hudSlotId); //80840ab0
    void OnBackPress(u32 hudSlotId); //80840ab4
    void UpdateBottomText(CtrlMenuCourseSelectCourse& course, PushButton& button, u32 hudSlotId); //80840728
    void OnTimeout(); //80840ba0 ends page and loads 0x92 (course votes)
    void LoadNextPage(CtrlMenuCourseSelectCourse& control, PushButton& courseButton, u32 hudSlotId); //80840830
    static Page* GetPageById(PageId id = PAGE_COURSE_SELECT); //808401e4
    //here the button refers to the back button as the course buttons are handled via extern controls
    //onButtonClick     vtable = 0x808bd054 function = 80840a44
    //onButtonSelect    vtable = 0x808bd054 offset   = 0x64 call is virtual
    //onButtonDeselect  vtable = 0x808bd054 function = 80840ab0
    //onBackPress       vtable = 0x808bd048 function = 80840ab4
    //onStartPress      vtable = 0x808bd048 offset   = 0x7c call is virtual Handler

    u32 unknown_0x6C4;
    CtrlMenuCourseSelectCup ctrlMenuCourseSelectCup; //0x6c8
    CtrlMenuCourseSelectCourse CtrlMenuCourseSelectCourse; //0x149c
    bool unknown_0x215c; //init at 0, set to 1 when a button is pressed
    u8 unknown_0x215d[0x2160 - 0x215d];
}; //total size 0x2160
size_assert(CourseSelect, 0x2160);
}//namespace Pages
#endif