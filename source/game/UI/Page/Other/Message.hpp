#ifndef _MESSAGEPAGE_
#define _MESSAGEPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>

//sinit at 805f96d4
namespace Pages {
class Click : public Page { //just a page with one action, clicking
public:
    Click(); //805f8d5c inlined
    ~Click() override; //805f8de0 vtable 808b9d70
    void OnInit() override; //0x28 805f8e48
    void OnActivate() override; //0x30 805f8eb8
    void AfterControlUpdate() override; //805f8edc
    int GetRuntimeTypeInfo() const override; //0x60 805f9698
    virtual void Reset(); //0x64 805f8f40
    virtual void SetMessageWindowText(u32 bmgId, const TextInfo *text = NULL) = 0; //0x68 805f9244
    virtual void SetButtonImage() = 0; //0x6c 805f92d4
    void OnClick(u32 hudSlotId); //805f8f54 ends page and triggers master page onclick ptmf
    static void TriggerPtmf(PtmfHolder_1A<Click, void, u32> *handler, u32 hudSlotId); //805f96a4
    PageManipulatorManager manipulatorManager; //no control but pressing A goes back to prev page
    PtmfHolder_1A<Page, void, Click *> *masterPageOnClickHandler; //0x188
    PtmfHolder_1A<Click, void, u32> onClickHandler;//0x18c 805f8f54 808b9de0 
    u32 hudSlotId; //0x1a0
}; //total size 0x1a4
size_assert(Click, 0x1a4);

class MessageBoxTransparent : public Click { //ID 0x4d used for drift explanation, pressing A goes back to page "under"
public:
    MessageBoxTransparent(); //805f8fac
    ~MessageBoxTransparent() override; //805f9054 vtable 808b9d00
    void OnInit() override; //0x28 805f90e8
    void BeforeEntranceAnimations() override; //0x38 805f924c
    void AfterExitAnimations() override; //0x44 805f9290
    int GetRuntimeTypeInfo() const override; //0x60 805f968c
    void Reset() override; //0x64 805f9224
    void SetMessageWindowText(u32 bmgId, const TextInfo *text = NULL) override; //0x68 805f9244
    void SetButtonImage() override; //0x6c 805f92d4
    u8 unknown_0x1A4;
    u8 padding[3];
    MessageWindowControlScaleFade messageWindow; //0x1a8
    LayoutUIControlScaleFade aButton;
    BlackBackControlForMessage background;
}; //0x604
size_assert(MessageBoxTransparent, 0x604);


class MessageBox : public Click { //ID 0x51, ID 0xc8 and probably others just a message box where pressing A goes to another page
public:
    MessageBox(); //805f931c
    ~MessageBox() override; //805f93dc vtable 808b9c90
    PageId GetNextPage() const override; //0x10 805f9678
    void OnInit() override; //0x28 805f9474
    int GetRuntimeTypeInfo() const override; //0x60 805f9680
    void Reset() override; //0x64 805f95c0
    void SetMessageWindowText(u32 bmgId, const TextInfo *text = NULL) override; //0x68 805f9628 
    void SetButtonImage() override; //0x6c 805f9630
    void SetTitleText(); //805f9620
    void ActivateManipulatorManager(); //805f8eb8 
    void ResetActions();
    u8 unknown_0x1a4; //
    u8 padding[3];
    CtrlMenuPageTitleText titleText; //0x1a8
    MessageWindowControl messageWindow; //0x31c
    LayoutUIControl aButtonImage; //0x490 green animated A for gcn eg
    PageId nextPageId; //0x604
}; //0x608
size_assert(MessageBox, 0x608);
}//namespace Pages


#endif