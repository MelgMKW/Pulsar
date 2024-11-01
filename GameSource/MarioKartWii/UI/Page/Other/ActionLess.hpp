#ifndef _ACTIONLESSPAGE_
#define _ACTIONLESSPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuText.hpp>
#include <MarioKartWii/UI/Ctrl/MessageWindowControl.hpp>

//_sinit_ at 805bb294
namespace Pages {

class ActionLess : public Page { //has to be ended by another Page
    ActionLess(); //805bab40 inlined
    ~ActionLess() override; //805bab84 vtable 808b7480
    void OnInit() override; //0x28 805babec
    void OnActivate() override; //0x30 805bac40  
    void AfterControlUpdate() override; //0x4c 805bac4c, ends the page
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805bb28c
    virtual void ResetText() = 0; //0x64
    virtual void SetMessageWindowText(u32 bmgId, const Text::Info* text = nullptr) = 0; //0x68
    void RequestEnd(bool canEnd); //805bac84
    ManipulatorManager manipulatorManager;
    bool canEnd; //0x54
    u8 padding[3];
}; //0x58

class AutoEndingTransparent : public ActionLess { //ID 0x4C on top of another page https://imgur.com/Z3zJZLd
public:
    static const PageId id = PAGE_AUTO_ENDING_TRANSPARENT;
    AutoEndingTransparent(); //805bac90
    ~AutoEndingTransparent() override; //805bacf8
    void OnInit() override; //0x28 805bad8c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805bb280
    void ResetText() override; //0x64 805bae80
    void SetMessageWindowText(u32 bmgId, const Text::Info* text = nullptr) override; //0x68 805bae90
    BusySymbol busySymbol; //0x58
    MessageWindowControlScaleFade messageWindow; //type SimpleMessageWindowControl if 0x50
    BlackBackControlForMessage bg; //0x340
};

class AutoEnding : public ActionLess { //ID 0x4F but also ID 0x50 and ID 0xc7 used for msg that have a spinner "waiting for"
public:
    static const PageId id = PAGE_AUTO_ENDING;
    AutoEnding(); //805bae98
    ~AutoEnding() override; //805baf68 vtable 808b73a8
    void OnInit() override; //0x28 805bb024
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805bb26c
    void ResetText() override; //0x64 805bb1c0
    void SetMessageWindowText(u32 bmgId, const Text::Info* text = nullptr) override; //0x68 805bb218
    void SetTitleText(u32 bmgId, const Text::Info* text = nullptr); //805bb210
    CtrlMenuPageTitleText titleText; //0x58 to 0x1CC
    BusySymbol busySymbol; //0x1CC to 0x340
    MessageWindowControl* messageWindow; //type SimpleMessageWindowControl if 0x50
    u32 unknown_0x344; //set to -1 by OnInit
}; //total size 0x348
size_assert(AutoEnding, 0x348);



}//namespace pages

#endif