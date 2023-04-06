#ifndef _CTRLMENUCOURSE_
#define _CTRLMENUCOURSE_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuMovie.hpp>

//_sinit_ at 807e5628
class CourseButton : public CtrlMenuMovieButton {
public:
    CourseButton(); //80628074
    ~CourseButton() override; //80628130 vtable 808d3100 for CtrlMenuMovieHandler

    //virtual ~CourseButton(); //thunk 807e5654 function 80628130 vtable 808d3118 for PushButton
    int GetRuntimeTypeInfo() const override; //0x28 thunk 807e5664 function 807e5604
    const char *GetClassName() const override; //0x2c thunk 807e565c function 807e443c
}; //total size 0x26C
size_assert(CourseButton, 0x26c);

class CtrlMenuCourseSelectCupSub : public LayoutUIControl {
public:
    CtrlMenuCourseSelectCupSub(); //80627f6c
    ~CtrlMenuCourseSelectCupSub() override; //80627fa8 vtable 808d31b8
    void InitSelf() override; //807e47c8
    void OnUpdate() override; //807e4864
    int GetRuntimeTypeInfo() const override; //807e561c
    const char *GetClassName() const override; //807e4410
    virtual void SetRelativePosition(PositionAndScale *parentPosition); //807e4744
    u8 unknown_0x174[0x17c - 0x174];
    Vec3 relativePosition; //0x17C relative to parent
    bool selected; //0x188
    u8 padding[3];
}; //total size 0x18c

class CtrlMenuCourseSelectCup : public LayoutUIControl {
public:
    //ctor inlined
    ~CtrlMenuCourseSelectCup() override; //80628000 vtable 808d3178
    void InitSelf() override; //807e45c0 0x18
    int GetRuntimeTypeInfo() const override; //0x28 807e5610
    const char *GetClassName() const override; //0x2c 807e441c
    void Load(); //807e444c
    CtrlMenuCourseSelectCupSub cupIcons[8]; //0x174 <=> 0x83c cup icons after clicking the cup (above the 4 tracks)
};  //total 0xDD4
size_assert(CtrlMenuCourseSelectCup, 0xdd4);

class CtrlMenuCourseSelectCourse : public LayoutUIControl { //layoutUIControl are coursebutton in the ptmfholder
public:
    static CourseId idxToCourseId[32]; //808a8088
    ~CtrlMenuCourseSelectCourse() override; //80628190 vtable 808d30c0
    void InitSelf() override; //807e5118 0x18
    int GetRuntimeTypeInfo() const override; //0x28 807e55f8
    const char *GetClassName() const override; //0x2c 807e442c
    void OnCourseButtonClick(PushButton *courseButton, u32 hudSlotId); //807e5434
    void OnCourseButtonSelect(PushButton *courseButton, u32 hudSlotId); //807e548c
    void Load(u32 r8, bool inaccessible); //807e4f7c same as pushbutton's load r8
    CourseButton courseButtons[4]; //0x174 <=> 0x1610
    LayoutUIControl control; //0xb24 <=> 0x1FC0 no idea
    PtmfHolder_2A<CtrlMenuCourseSelectCourse, void, PushButton *, u32> onCourseButtonClickHandler;  //0xC98 <=> 0x2134 vtable 808bd090 807e5434
    PtmfHolder_2A<CtrlMenuCourseSelectCourse, void, PushButton *, u32> onCourseButtonSelectkHandler; //0xCAC <=> 0x2148 vtable 808bd090 807e548c
}; //total size 0xCC0
size_assert(CtrlMenuCourseSelectCourse, 0xcc0);

#endif