#ifndef _ONLINERACESUPPORTINGPAGES_
#define _ONLINERACESUPPORTINGPAGES_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>

//_sinit_ at 8064fba8
namespace Pages {
class RaceEndWait : public Page { //ID 0x48 "Please wait a moment" at the end of online races
public:
    RaceEndWait(); //8064f168
    ~RaceEndWait() override; //8064f1b4 vtable 808c0200
    void OnInit() override; //0x28 8064f228
    void OnActivate() override; //0x30 8064f320
    void AfterControlUpdate() override; //0x4c 8064f374 very interesting, sets next section
    int GetRuntimeTypeInfo() const override; //0x60 8064faf4
    ManipulatorManager manipulatorManager; //0x44
    SimpleMessageWindowControl msgWindow; //0x54
    u32 state; //0x1c8 0 nothing, 1 isDisplayingText? unsure
}; //total size 0x1cc
size_assert(RaceEndWait, 0x1cc);

class DisableHomeButton : public Page { //ID 0x94 used in online races
public:
    DisableHomeButton(); //8064f9d8
    ~DisableHomeButton() override; //8064fa1c vtable 808c019c
    int IsHomeMenuWorking() override; //0x14 8064fae0 returns 3
    void OnInit() override; //0x28 8064fa84
    int GetRuntimeTypeInfo() const override; //0x60 8064fae8
    ManipulatorManager manipulatorManager; //0x44
}; //total size 0x54
size_assert(DisableHomeButton, 0x54);

}//namespace Pages
#endif