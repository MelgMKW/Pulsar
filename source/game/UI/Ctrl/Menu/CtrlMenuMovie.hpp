#ifndef _CTRLMENUMOVIEBUTTON_
#define _CTRLMENUMOVIEBUTTON_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/PushButton.hpp>

class Page;
class MovieScale {
    MovieScale(); //807e84a8
    Vec2 scale;
}; //0x8

//_sinit_ at 807e917c
class CtrlMenuMovieHandler {
public:
    //no ctor
    virtual ~CtrlMenuMovieHandler(); //80627a40 vable 808D3608 
    virtual void Toggle(bool hide); //807e8138
    virtual int GetMovieCount() const = 0;
    virtual char **GetPaneNames() const = 0;
    static bool IsMirror(); //807e8188
    nw4r::lyt::Pane **panes; //0x4
    Page *parentPage; //0x8
    bool isHidden; //0xC
    u8 padding[3];
    u32 delay; //0x10 in frames, until it appears
    MovieScale *scales; //0x14 size movie count
}; //total size 0x18
size_assert(CtrlMenuMovieHandler, 0x18);


class CtrlMenuMovieLayout : public CtrlMenuMovieHandler, public LayoutUIControl {
    //no ctor
    ~CtrlMenuMovieLayout() override; //80627a80 808d34b0 for thp part
    int GetMovieCount() const override; //807e8e04
    char **GetPaneNames() const override; //807e82dc
    //virtual ~CtrlMenuMovieLayout(); //thunk 807e91fc function 80627a80 vtable 808d34c8
    void InitSelf() override; //0x18 thunk 807e91f4 function 807e8e0c
    void OnUpdate() override; //0x1c thunk 807e91ec function 807e8ff8
    int GetRuntimeTypeInfo() const override; //0x28 thunk 807e920c function 80
    const char *GetClassName() const override; //0x2c thunk 807e9204 function 807e8c4c
    void OnDeactivate(); //807e8c5c
}; //total size 0x18C
size_assert(CtrlMenuMovieLayout, 0x18c);


class CtrlMenuMovieButton : public CtrlMenuMovieHandler, public PushButton {
public:
    CtrlMenuMovieButton() {};
    ~CtrlMenuMovieButton() override; //806280d4 vtable 808d3590 for Movie
    int GetMovieCount() const override; //807e2520
    char **GetPaneNames() const override; //807e82d0
    //virtual ~CtrlMenuMovieButton(); //807e91a4 vtable 808d35a8 for PushButton
    void InitSelf() override; //0x18 thunk 807e2574 function 807e8698
    void OnUpdate() override; //0x1c thunk 807e256c function 807e84ac
    int GetRuntimeTypeInfo() const override; //0x28 thunk 807e91b4 function 807e9170
    const char *GetClassName() const override; //0x2c thunk 807e91ac function 807e82f4
    void OnDeactivate() override; //0x3c thunk 807e257c function 807e8300

}; //total size 0x26C
size_assert(CtrlMenuMovieButton, 0x26c);

class CtrlMenuSingleTopMovieButton : public CtrlMenuMovieHandler, public PushButton {
    ~CtrlMenuSingleTopMovieButton() override; //807e9114 vtable 808d3518 for thp
    int GetMovieCount() const override; //807e8954
    char **GetPaneNames() const override; //807e82e8
    //virtual ~CtrlMenuSingleTopMovieButton(); thunk 807e91d4 func 807e9114 vtable 808d3530 for pushbutton
    void InitSelf() override; //0x18 thunk 807e91c4 function 807e895c
    void OnUpdate() override; //0x1c thunk 807e91bc function 807e8b48
    int GetRuntimeTypeInfo() const override; //0x28 thunk 807e91e4 function 807e9108
    const char *GetClassName() const override; //0x2c thunk 807e91dc function 807e879c
    void OnDeactivate() override; //0x3c thunk 807e91cc function 807e87ac
}; //total size 0x26c
size_assert(CtrlMenuSingleTopMovieButton, 0x26c);

#endif