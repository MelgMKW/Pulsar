#ifndef _LICENSESETTINGSPAGE_
#define _LICENSESETTINGSPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Other/Message.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>
#include <game/UI/Page/Other/Approve.hpp>

//_sinit_ at 805ee894
class LicenseControl : public LayoutUIControl {
    //no ctor
    ~LicenseControl() override; //805ebf10 vtable 808b992c
    int GetRuntimeTypeInfo() const override; //0x28 805ee678
    const char *GetClassName() const override; //0x2c 805ea818
}; //total size 0x174

class LicenseButton : public PushButton {
    LicenseButton(); //805eaa6c
    ~LicenseButton() override; //805eaaa8 vtable 808b98e0
    int GetRuntimeTypeInfo() const override; //0x28 805ee66c
    const char *GetClassName() const override; //0x2c 805ea824

};

namespace Pages {
class LicenseSelect : public Page { //ID 0x65
    LicenseSelect(); //805ea834
    ~LicenseSelect() override; //805eab00 vtable 808b984c
    PageId GetNextPage() const override; //0x10 805ee658
    void OnInit() override; //0x28 805eabb8 
    void OnActivate() override; //0x30 805eb774
    void AfterControlUpdate() override; //0x4c 805eb79c
    void OnResume() override; //0x54 805eb798
    int GetRuntimeTypeInfo() const override; //0x60 805ee660
    static void SetControlMii(UnkType *unusedArg, LicenseButton *licenseButton, u8 curLicenseId, MiiGroup *miiGroup, u32 index); //805eae94
    void OnLicenseButtonClick(LicenseButton *button, u32 hudSlotId); //805eb7a0
    void OnOptionsButtonClick(PushButton *button, u32 hudSlotId); //805ebb44
    void OnBackButtonClick(CtrlMenuBackButton *button, u32 hudSlotId); //805ebc8c
    void OnBackPress(u32 hudSlotId); //805ebcd0
    void OnNewLicenseApprove(Approve *validatePage, float delay); //805ebce8
    void OnNewLicenseDisapprove(Approve *validatePage, float delay); //805ebcd0

    PtmfHolder_2A<Page, void, LicenseButton *, u32> onLicenseButtonClickHandler; //0x44 805eb7a0
    PtmfHolder_2A<Page, void, PushButton *, u32> onOptionsButtonClickHandler; //0x58 805ebb44
    PtmfHolder_2A<Page, void, CtrlMenuBackButton *, u32> onBackButtonClickHandler; //0x6c 805ebc8c
    PtmfHolder_1A<Page, void, u32> onBackPressHandler; //0x80 805ebcd0
    PtmfHolder_2A<Page, void, Approve *, float> onNewLicenseApprove; //0x94 805ebce8
    PtmfHolder_2A<Page, void, Approve *, float> unknown_0xA8; //0xa8 805ebd44 very similar to above but set next section to 0x46 and not 0x45
    PtmfHolder_2A<Page, void, Approve *, float> onNewLicenseDisapprove; //0xbc 805ebcd0 triggered by page 52
    ControlsManipulatorManager controlManipulatorManager; //0xd0
    CtrlMenuPageTitleText titleText; //0x2f4
    LicenseButton licenseButtons[4]; //0x468
    PushButton optionsButton; //0xdb8
    CtrlMenuBackButton backButton; //0x100c
    MiiGroup miiGroup; //0x1270
    PageId nextPageId;

}; //total size 0x130c
size_assert(LicenseSelect, 0x130c);

class LicenseChangeMii : public Page { //ID 0x66 comes after choose mii
    LicenseChangeMii(); //805ebdac
    ~LicenseChangeMii() override; //805ebf68 vtable 808b97b8
    PageId GetNextPage() const override; //0x10 805ee644
    void OnInit() override; //0x28 805ec008
    void OnActivate() override; //0x30 805ec274
    int GetRuntimeTypeInfo() const override; //0x60 805ee64c
    void OnClick(MessageBox *messageBoxPage); //805ed2d4
    void OnMiiValidate(Approve *validatePage); //85ed450 validate function
    void OnMiiDisapprove(Approve *validatePage); //805ed45c disapprove function
    void OnMessageBoxClick(MessageBox *messageBox); //805ed468
    void UpdateMiiGroup(MiiTexMap *newPotentialMii); //805ecdc8 updates MiiGroup with selected mii in case it is then chosen
    void PrepareMessageBox(); //805ecdd8 updates page 52 with the correct text
    static void SetControlMii(UnkType *unusedArg, LicenseControl *licenseControl, u8 curLicenseId, MiiGroup *miiGroup, u32 index); //805ec4e8
    PtmfHolder_1A<LicenseChangeMii, void, u32> onClick; //0x44 805ed2d4
    PtmfHolder_1A<LicenseChangeMii, void, Approve *> onMiiApprove; //0x58 805ed450
    PtmfHolder_1A<LicenseChangeMii, void, Approve *> onMiiDisapprove; //0x6c 805ed45c
    PtmfHolder_1A<LicenseSettings, void, MessageBox *> onMessageBoxClick; //0x80 805ed468
    PageManipulatorManager pageManipulatorManager; //0x94
    CtrlMenuPageTitleText titleText; //0x1d8
    LicenseControl licenseControl; //0x34c
    MessageWindowControl messageWindowControl; //0x4c0
    MiiGroup miiGroup; //0x634
}; //total size 0x6cc
size_assert(LicenseChangeMii, 0x6cc);

class LicenseSettings : public Page { //ID 0x67
    LicenseSettings(); //805ed4ec 
    ~LicenseSettings() override; //805ed70c vtable 808b973c
    PageId GetNextPage() const override; //0x10 805ee630
    void OnInit() override; //0x28 805ed7e4
    void OnActivate() override; //0x30 805edbf8
    int GetRuntimeTypeInfo() const override; //0x60 805ee638

    PtmfHolder_2A<LicenseSettings, void, PushButton *, u32> onRecordsButtonClick; //0x44 805edc50 vt 808b97ac
    PtmfHolder_2A<LicenseSettings, void, PushButton *, u32> onChangeMiiButtonClick; //0x58 805edc94 vt 808b97ac
    PtmfHolder_2A<LicenseSettings, void, PushButton *, u32> onEraseLicenseButtonClick; //0x6C 805edcd8 vt 808b97ac
    PtmfHolder_2A<LicenseSettings, void, CtrlMenuBackButton *, u32> onBackButtonClick; //0x80 805edd1c
    PtmfHolder_2A<LicenseSettings, void, PushButton *, u32> onSelectButton; //0x94 805edd68
    PtmfHolder_1A<LicenseSettings, void, u32> onBackPress; //0xa8 805eddd4
    ControlsManipulatorManager controlsManipulatorManager; //0xbc
    CtrlMenuPageTitleText titleText;    //0x2e0
    LicenseControl licenseControl; //0x454
    PushButton recordsButton; //0x5c8
    PushButton changeMiiButton; //0x81c
    PushButton eraseLicenseButton; //0xa70
    CtrlMenuBackButton backButton;  //0xcc4
    CtrlMenuInstructionText bottomText; //0xf28
    MiiGroup miiGroup; //0x109c
    PageId nextPageId; //0x1134
}; //total size 0x1138
size_assert(LicenseSettings, 0x1138);

class LicenseErase : public Page { //ID 0x68
    LicenseErase(); //805eddf4
    ~LicenseErase() override; //805edf84 vtable 808b96b4
    PageId GetNextPage() const override; //0x10 805ee41c returns -1 
    void OnInit() override; //0x28 805ee030
    void OnActivate() override; //0x30 805ee238 just a blr   
    void OnResume() override; //0x54 805ee244
    int GetRuntimeTypeInfo() const override; //0x60 805ee624
    PtmfHolder_2A<LicenseSettings, void, PushButton *, u32> onYesButtonClick; //0x44 805ee434 vt 808b9730
    PtmfHolder_2A<LicenseSettings, void, PushButton *, u32> onNoButtonClick; //0x58 805ee578
    PtmfHolder_1A<LicenseSettings, void, u32> onBackPress; //0x6c 805ee5cc
    PtmfHolder_1A<LicenseSettings, void, Page *> onErasedLicense; //0x80 805ee5dc, page 0x51 is r4
    ControlsManipulatorManager controlsManipulatorManager; //0x94
    CtrlMenuPageTitleText titleText; //0x2b8
    MessageWindowControl messageWindow; //0x42c
    PushButton yesButton; //0x5a0
    PushButton noButton; //0x7f4
    CtrlMenuBackButton backButton; //0xa48
}; //0xcac
size_assert(LicenseErase, 0xcac);
}//namespace Pages
#endif