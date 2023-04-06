#ifndef _ACTIONLESSPAGE_
#define _ACTIONLESSPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>

//_sinit_ at 80602ef4
namespace Pages {

class ActionLess : public Page {
    ActionLess(); //805bab40 inlined
    ~ActionLess() override; //805bab84 vtable 808b7480
    void OnInit() override; //0x28 805babec
    void OnActivate() override; //0x30 805bac40  
    void AfterControlUpdate() override; //0x4c 805bac4c, ends the page
    int GetRuntimeTypeInfo() const override; //0x60 805bb28c
    ManipulatorManager manipulatorManager;
    u8 unknown_0x54[4]; //0x54
}; //0x58

class AutoEnding : public ActionLess { //ID 0x4F but also ID 0x50 and ID 0xc7
    AutoEnding(); //805bae98
    ~AutoEnding() override; //805baf68 vtable 808b73a8
    void OnInit() override; //0x28 805bb024
    int GetRuntimeTypeInfo() const override; //0x60 805bb26c
    virtual void ResetText(); //0x64 805bb1c0
    virtual void SetMessageWindowText(u32 bmgId, const TextInfo *text); //0x68 805bb218
    CtrlMenuPageTitleText titleText; //0x58 to 0x1CC
    BusySymbol busySymbol; //0x1CC to 0x340
    MessageWindowControl *messageWindow; //type SimpleMessageWindowControl if 0x50
    u32 unknown_0x344; //set to -1 by OnInit
}; //total size 0x348
size_assert(AutoEnding, 0x348);
}//namespace pages

#endif