#ifndef _CTRLMENUCUP_
#define _CTRLMENUCUP_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuMovie.hpp>
//CtrlMenuCup _sinit_ at 807e63ec 
class CtrlMenuCupSelectCup : public LayoutUIControl {
public:
    //ctor inlined
    ~CtrlMenuCupSelectCup() override; //80627adc vtable 808d3234
    void InitSelf() override; //807e5894 0x18
    int GetRuntimeTypeInfo() const override; //0x28 807e63e0
    const char *GetClassName() const override; //0x2c 807e566c
    void Load(u32 localPlayerBitfield, u32 r8); //807e5688 r8 is pushbutton's load r8
    void OnCupButtonClick(PushButton *button, u32 hudSlotId); //807e5d68
    void OnCupButtonSelect(PushButton *button, u32 hudSlotId); //807e5c58
    static bool IsCupUnlocked(u32 cupIndex); //807e5dc8 in at least one engine/mirror
    PushButton cupButtons[8]; //0x174 = 838 for page ends at 1414 = 1ad8 for page
    PtmfHolder_2A<CtrlMenuCupSelectCup, void, PushButton *, u32> onCupButtonClickHandler; //807e5d68 //0x1414
    PtmfHolder_2A<CtrlMenuCupSelectCup, void, PushButton *, u32> onCupButtonSelectHandler; //807e5c58 //0x1428
    u32 curCupID; //0x143c
    CtrlMenuMovieLayout ctrlMenuMovieLayout; //0x1440 (1b04 for page) ends at 0x15cc (1c90 for page)
}; //total size 0x15cc
size_assert(CtrlMenuCupSelectCup, 0x15cc);

class CtrlMenuCupSelectCourse : public LayoutUIControl {
public:
    static CourseId idxToCourseId[32]; //808a8410
    //ctor inlined
    ~CtrlMenuCupSelectCourse() override; //80627b64 vtable 808d31f8
    void InitSelf() override; //807e60dc 0x18
    void OnUpdate() override; //807e61e0 0x1c
    int GetRuntimeTypeInfo() const override; //0x28 807e63d4
    const char *GetClassName() const override; //0x2c 807e5678
    void Load(); //807e5ecc
    void UpdateTrackList(u32 cupIndex); //807e5ff0
    LayoutUIControl trackNames[4]; //0x174 to 0x744 (23d4 for page)
}; //total size 0x744
size_assert(CtrlMenuCupSelectCourse, 0x744);

#endif