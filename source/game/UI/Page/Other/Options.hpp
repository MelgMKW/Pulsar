#ifndef _OPTIONS_
#define _OPTIONS_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>

/*
Contributors:
-Melg
*/
//_sinit_ at 80601284
namespace Pages {
class Options : public Page { //ID 0xC0
public:
    Options(); //805fd518
    ~Options() override; //805fd638 vtable 808ba3ec
    PageId GetNextPage() const override; //80601060
    void OnInit() override; //805fd6e4
    void OnDispose() override; //805fd8e4
    void OnActivate() override; //805fd8e8
    int GetRuntimeTypeInfo() const override; //80601068 returns809c1ce8

    void OnButtonClick(PushButton *pushButton, u32 hudSlotId); //805fd90c
    void OnBackPress(u32 hudSlotId); //805fda80
    static void TriggerPtmf(PtmfHolder_2A<Options, void, PushButton *, u32> *handler, PushButton *button, u32 hudSlotId); //80601134
    static void TriggerBackPtmf(PtmfHolder_1A<Options, void, u32> *handler, u32 hudSlotId); //80601254
    PtmfHolder_2A<Options, void, PushButton *, u32> onButtonClickHandler; //0x44 vtable 808ba45c 805fd90c
    PtmfHolder_1A<Options, void, u32> onBackPressHandler; //0x58 vtable 808ba450 805fda80
    ControlsManipulatorManager manipulatorManager; //0x6C
    CtrlMenuPageTitleText titleText; //0x290
    PushButton gcnRumble; //0x404
    PushButton nintendoWiFi; //0x658
    PushButton AddMarioKartChannel; //0x8ac
    CtrlMenuBackButton backButton; //0xb00 ends at d64
    PageId nextPageId; //when you press a button


}; //total size 0xd68
size_assert(Options, 0xD68);

class WiFiOptions : public Page { //ID 0xC1
    WiFiOptions(); //805fdaa8
    ~WiFiOptions() override; //805fdbd8 vtable 808ba370
    PageId GetNextPage() const override; //0x10 8060104c
    void OnInit() override; //0x28 805fdc9c
    void OnActivate() override; //0x30 805fdf34
    int GetRuntimeTypeInfo() const override; //0x60 80601054
    void OnButtonClick(PushButton *pushButton, u32 hudSlotId); //805fdf58
    void OnBackPress(u32 hudSlotId); //805fe110
    static void TriggerPtmf(PtmfHolder_2A<WiFiOptions, void, PushButton *, u32> *handler, PushButton *button, u32 hudSlotId); //80601104
    static void TriggerBackPtmf(PtmfHolder_1A<WiFiOptions, void, u32> *handler, u32 hudSlotId); //80601224
    PtmfHolder_2A<WiFiOptions, void, PushButton *, u32> onButtonClickHandler; //0x44 805fdf58 808ba3e0
    PtmfHolder_1A<WiFiOptions, void, u32> onBackPressHandler; //0x58 805fe110 808ba3d4
    ControlsManipulatorManager manipulatorManager; //0x6C
    CtrlMenuPageTitleText titleText; //0x290
    PushButton regionSetting; //0x404
    PushButton flagAndRegion; //0x658
    PushButton messageService; //0xb00
    PushButton dataSharing; //0x8ac
    PushButton miiDisplay; //0xd54
    CtrlMenuBackButton backButton; //0xfa8 to 120C
    PageId nextPageId;
};
size_assert(WiFiOptions, 0x1210);

class OptionExplanation : public Page {//ID 0xc2 a message box with explanations about the upcoming OptionBox, and a next button
    OptionExplanation(); //805fe128
    ~OptionExplanation() override; //805fe240 vtable 808ba2f4
    void OnInit() override; //0x28 805fe2e0
    void OnActivate() override; //0x30 805fe460
    int GetRuntimeTypeInfo() const override; //0x60 80601040
    void OnButtonClick(PushButton *pushButton, u32 hudSlotId); //805fe48c
    void OnBackPress(u32 hudSlotId); //805fe57c
    static void TriggerPtmf(PtmfHolder_2A<OptionExplanation, void, PushButton *, u32> *handler, PushButton *button, u32 hudSlotId); //806010d4
    static void TriggerPtmf(PtmfHolder_1A<OptionExplanation, void, u32> *handler, u32 hudSlotId); //806011f4
    PtmfHolder_2A<OptionExplanation, void, PushButton *, u32> onButtonClickHandler; //0x44 805fe48c 808ba364
    PtmfHolder_1A<OptionExplanation, void, u32> onBackPressHandler; //0x58 805fe57c 808ba358
    ControlsManipulatorManager manipulatorManager; //0x6C
    CtrlMenuPageTitleText titleText; //0x290
    MessageWindowControl messageWindow; //0x404
    PushButton nextButton; //0x578
    CtrlMenuBackButton backButton; //0x7cc
    PageId nextPageId; //a30, if set to 0, chains into itself
};
size_assert(OptionExplanation, 0xa34);

class OptionChoice : public Page { //ID 0xc3 (2used buttons) and ID 0xc4(3 buttons), a message box with yes/no buttons
    // "master" page inits and sets the controls to the correct values
    OptionChoice(); //805fe5f8
    ~OptionChoice() override; //805fe728 vtable 808ba278
    void OnInit() override; //0x28 805fe7d4
    void OnActivate() override; //0x30 805fea58
    void OnResume() override; //0x54 805fea88
    int GetRuntimeTypeInfo() const override; //0x60 80601034
    void OnButtonClick(PushButton *pushButton, u32 hudSlotId); //805febe4
    void OnBackPress(u32 hudSlotId); //805fed8c
    void SetTitleText(u32 bmgId); //805feb60 inlined
    void SetMessageWindowText(u32 bmgId); //805feb6c inlined
    void SetButtonText(u32 buttonId, u32 bmgId, u32 ed8); //805feb78 inlined
    void SetInitialButton(u8 buttonId); //805febdc
    static void TriggerPtmf(PtmfHolder_2A<OptionChoice, void, PushButton *, u32> *handler, PushButton *button, u32 hudSlotId); //806010a4
    static void TriggerBackPtmf(PtmfHolder_1A<OptionChoice, void, u32> *handler, u32 hudSlotId); //806011c4
    PtmfHolder_2A<OptionChoice, void, PushButton *, u32> onButtonClickHandler; //0x44 805febe4 808ba2e8
    PtmfHolder_1A<OptionChoice, void, u32> onBackPressHandler; //0x58 805fed8c 808ba2dc
    ControlsManipulatorManager manipulatorManager; //0x6C
    CtrlMenuPageTitleText titleText; //0x290
    MessageWindowControl messageWindow; //0x404
    PushButton buttons[3]; //0x578
    CtrlMenuBackButton backButton; //c74 to ed8
    u32 confirmationWindowBmgId[3]; //0xed8 tied to which button is pressed
    u32 usedButtons; //0xee4
    u32 choiceChosen;
    u8 initialButton; //0xeec based on rksys setting, mostly
    u8 padding[3];
};
size_assert(OptionChoice, 0xef0);

class RegionOptions : public Page {//ID 0xc5
    RegionOptions(); //805feda4
    ~RegionOptions() override; //805feefc vtable 808ba1fc
    PageId GetNextPage() const override; //0x10 805ff134
    void OnInit() override; //0x28 805fef9c
    void OnActivate() override; //0x30 805ff128
    int GetRuntimeTypeInfo() const override; //0x60 80601028
    void OnButtonClick(PushButton *pushButton, u32 hudSlotId); //805ff194
    void OnBackButtonClick(CtrlMenuBackButton *backButton, u32 hudSlotId); //805ff1e0
    void OnBackPress(u32 hudSlotId); //805ff2a0
    static void TriggerPtmf(PtmfHolder_2A<OptionChoice, void, PushButton *, u32> *handler, PushButton *button, u32 hudSlotId); //80601074
    static void TriggerBackPtmf(PtmfHolder_1A<OptionChoice, void, u32> *handler, u32 hudSlotId); //80601194
    PtmfHolder_2A<OptionChoice, void, PushButton *, u32> onButtonClickHandler; //0x44 805ff194 808ba26c
    PtmfHolder_2A<OptionChoice, void, CtrlMenuBackButton *, u32> onBackButtonClickHandler; //0x58 805ff1e0 808ba26c
    PtmfHolder_1A<OptionChoice, void, u32> onBackPressHandler; //0x6c 805ff2a0 808ba260
    ControlsManipulatorManager manipulatorManager; //0x80
    CtrlMenuPageTitleText titleText; //0x2A4
    MessageWindowControl messageWindow; //418
    PushButton yesButton; //0x58c
    CtrlMenuBackButton backButton; //0x7e0
}; //0xa44
size_assert(RegionOptions, 0xa44);

class MasterOptions : public Page { //ID 0xc6 chooses which option to load depending on the section and which button was pressed in the generic box pages
    //0xc2 = choice, 0xc3 and c4 = choice, 0xc7 = waiting, 0xc8 = choice saved
    MasterOptions(); //805ff328
    ~MasterOptions() override; //805ff3a4 vtable 808ba180
    PageId GetNextPage() const override; //0x10 80601014
    void OnInit() override; //0x28 805FF40C
    void OnActivate() override; //0x30 805fF478
    void BeforeEntranceAnimations() override; //0x38 805ff4d8
    void BeforeExitAnimations() override; //0x40 805ff4dc
    void AfterControlUpdate() override; //0x4c 805ff4e0
    void OnResume() override; //0x54 805ff6c4 sets the option in rksys too
    int GetRuntimeTypeInfo() const override; //0x60 8060101c
    void SetNextPageType(u32 r4); //806000c4 inlined at 805fe070, no idea what r4 is
    void LoadOptionChoice(u32 r4); //806003e0 called by OnDeactivate r4 is add page layer r5, called if type = 0
    void LoadOptionFirstExplanation(u32 r4); //80600128 same, called if type >= 1
    void LoadOptionNextExplanation(u32 r4); //806002e4 inlined
    void LoadOptionChoiceSaved(); //806009fc loads message box page 0xc8
    void LoadOptionWaitingNetwork(); //8060079c inlined loads waiting page 0xC7
    void LoadOptionWaiting(); //806008cc, inlined
    void LoadOptionChoiceSavedNetwork(); //806009fc to get error code
    static void TriggerPtmf(PtmfHolder_1A<MasterOptions, void, u32> *handler, u32 hudSlotId); //80601164
    PtmfHolder_1A<MasterOptions, void, u32> onClickHandler; //0x44 80600F88 back press and ChoiceSaved boxes
    ManipulatorManager manipulatorManager; //0x58
    u32 nextPageType; //0x68 0 = choice box, >= 1 explanation box
    u32 unknown_0x6C; //0x6C
    PageId nextPageId; //0x70
    u32 choiceChosen; //0x74 used to set the correct text
};
size_assert(MasterOptions, 0x78);
}//namespace Pages

#endif