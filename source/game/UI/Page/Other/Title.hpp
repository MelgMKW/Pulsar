#ifndef _TITLEPAGE_
#define _TITLEPAGE_
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuPressStart.hpp>

//_sinit_ at 8063c3b8
class TitleImage : public LayoutUIControl {
    TitleImage(); //8063a598 inlined
    ~TitleImage() override; //8063a5d4 vtable 808bef0c
    void InitSelf() override; //0x18 8063a6cc
    int GetRuntimeTypeInfo() const override; //0x28 8063c3ac
    const char *GetClassName() const override; //0x2c 8063a58c
    void Load(); //8063a62c
    void ChangeImage(bool isMirrorUnlocked, u32 tplID); //8063a8d4 0 1 2 3 4 5 for mario1, mario2, peach, luiji, koopa, mario_luiji
}; //0x174
size_assert(TitleImage, 0x174);

class TitleMovieControl : public LayoutUIControl {
    TitleMovieControl(); //8063b804 inlined
    ~TitleMovieControl() override; //8063b840 vtable 808bee08
    void InitSelf() override; //0x18 8063b938
    void OnUpdate() override; //0x1c 8063b970
    int GetRuntimeTypeInfo() const override; //0x28 8063c380
    const char *GetClassName() const override; //0x2c 8063b7f4
    void Load(); //8063b898
}; //0x174
size_assert(TitleMovieControl, 0x174);

namespace Pages {
class Title : public Page { //ID 0x57
    Title(); //8063aa08
    ~Title() override; //8063aae4 vtable 808beea8
    PageId GetNextPage() const override; //0x10 8063c398
    void OnInit() override; //0x28 8063ab6c
    void OnDispose() override; //0x2c 8063ad60 just a blr 
    void OnActivate() override; //0x30 8063ad64   
    void BeforeEntranceAnimations() override; //0x38 8063ade4
    void AfterEntranceAnimations() override; //0x3c 8063ae94
    void BeforeExitAnimations() override; //0x40 8063aee0
    void AfterExitAnimations() override; //0x44 8063af90
    void AfterControlUpdate() override; //0x4c 8063afc8
    void OnResume() override; //0x54 8063b124
    int GetRuntimeTypeInfo() const override; //0x60 8063c3a0
    ManipulatorManager manipulatorManager; //0x44
    CtrlMenuPressStart pressStart; //0x54
    TitleImage titleImage; //0x1c8
    bool hasController; //0x33c
    u8 padding[3];
    PageId nextPageId;
    u32 initialPageDuration; //0x344 just a copy of 0x20 OnDeactivate?
    bool isMirrorUnlocked;
    u8 padding2[3];
    u32 tplID; //randomized tpl to show 0 1 2 3 4 5 for mario1, mario2, peach, luiji, koopa, mario_luiji
}; //0x350
size_assert(Title, 0x350);

class BlurryTitle : public Page { //ID 0x58 behind main menu
    BlurryTitle(); //8063b514
    ~BlurryTitle() override; //8063b560 vtable 808bee44
    void OnInit() override; //0x28 8062d5d4
    void OnActivate() override; //0x30 8063b698
    void BeforeEntranceAnimations() override; //0x38 8063b7f0
    int GetRuntimeTypeInfo() const override; //0x60 8063c38c
    LayoutUIControl blurryTitleImage; //0x44
    ManipulatorManager manipulatorManager; //0x1b8
}; //total size 0x1c8
size_assert(BlurryTitle, 0x1c8);

class TitleMovie : public Page { //ID 0x59
    TitleMovie(); //8063bb08
    ~TitleMovie() override; //8063bb6c vtable 808beda4
    void OnInit() override; //0x28 8063bbe4
    void OnActivate() override; //0x30 8063bcf8
    void OnDeactivate() override; //0x34 8063be88
    void AfterExitAnimations() override; //0x44 8063be44
    void BeforeControlUpdate() override; //0x48 8063be9c
    void AfterControlUpdate() override; //0x4c 8063bfcc
    int GetRuntimeTypeInfo() const override; //8063c374
    TitleMovieControl movie;
    ManipulatorManager manipulatorManager; //0x1b8
    u32 movieDuration; //0x20
    bool isEnding;
    u8 padding[3];
}; //0x1d0
size_assert(TitleMovie, 0x1d0);

class BlinkingPressA : public Page { //ID the blinking "press A" on demo
    BlinkingPressA(); //8063c0ac
    ~BlinkingPressA() override; //8063c110 vtable 808bed40
    void OnInit() override; //0x28 8063c188
    void OnActivate() override; //0x30 8063c210
    void OnDeactivate() override; //0x34 8063c268
    void AfterControlUpdate() override; //0x4c 8063c27c
    int GetRuntimeTypeInfo() const override; //8063c368
    ManipulatorManager manipulatorManager; //0x44
    bool hasController; //0x54
    u8 padding[3];
    CtrlMenuPressStart pressA; //0x58

}; //0x1cc 
size_assert(BlinkingPressA, 0x1cc);
}//namespace Pages
#endif

