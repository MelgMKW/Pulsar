#ifndef _ADDMKCHANNELPAGE_
#define _ADDMKCHANNELPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>

//_sinit_ at 805bf3b4
namespace Pages {
class MKChannelExplanation : public Page { //ID 0xca
    MKChannelExplanation(); //805bee4c
    ~MKChannelExplanation() override; //805bef64 vtable 808b7818
    PageId GetNextPage() const override; //0x10 805bf1ac
    void OnInit() override; //0x28 805bf004 
    void OnActivate() override; //0x30 805bf1a0
    int GetRuntimeTypeInfo() const override; //0x60 805bf2dc
    void OnButtonClick(CtrlMenuBackButton *button, u32 hudSlotId); //805bf1e4
    void OnBackPress(u32 hudSlotId); //805bf290
    static void TriggerButtonPtmf(PtmfHolder_2A<AddMKChannel, void, PushButton *, u32> *, u32); //805bf2f4
    static void TriggerBackPtmf(PtmfHolder_1A<AddMKChannel, void, u32> *, u32); //805bf354
    PtmfHolder_2A<AddMKChannel, void, PushButton *, u32> onbuttonClickHandler; //0x44 805bf1e4
    PtmfHolder_1A<AddMKChannel, void, u32> onBackPressHandler; //0x58 805bf290
    ControlsManipulatorManager manipulatorManager; //0x6c
    CtrlMenuPageTitleText titleText; //0x290
    MessageWindowControl messageWindow; //0x404
    PushButton nextButton; //0x578
    CtrlMenuBackButton backButton; //0x7cc
}; //total size 0xa30
size_assert(MKChannelExplanation, 0xa30);

class AddMKChannel : public Page { //ID 0xcb
    AddMKChannel(); //805be66c

    ~AddMKChannel() override; //805be84c vtable 808b7894
    PageId GetNextPage() const override; //0x10 805beb34
    void OnInit() override; //0x28 805be8f8
    void OnDispose() override; //0x2c 805beb28
    void OnActivate() override; //0x30 805beb2c
    void OnDeactivate() override; //0x34 805beb30
    int GetRuntimeTypeInfo() const override; //0x60 805bf2e8

    void OnAddButtonClick(PushButton *button, u32 hudSlotId); //805beb4c
    void OnCancelButtonClick(PushButton *button, u32 hudSlotId); //805bed74
    void OnBackButtonClick(CtrlMenuBackButton *button, u32 hudSlotId); //805bee00
    void OnBackPress(u32 hudSlotId); //805bee3c

    static void TriggerButtonPtmf(PtmfHolder_2A<AddMKChannel, void, PushButton *, u32> *, u32); //805bf324
    static void TriggerBackPtmf(PtmfHolder_1A<AddMKChannel, void, u32> *, u32); //805bf384

    PtmfHolder_2A<AddMKChannel, void, PushButton *, u32> onAddButtonHandler; //0x44 805beb4c
    PtmfHolder_2A<AddMKChannel, void, PushButton *, u32> onCancelButtonClickHandler; //0x58 805bed74
    PtmfHolder_2A<AddMKChannel, void, CtrlMenuBackButton *, u32> onBackButtonClickHandler; //0x6c 805bee00
    PtmfHolder_1A<AddMKChannel, void, u32> onBackPressHandler; //0x80 805bee3c
    ControlsManipulatorManager manipulatorManager; //0x94
    CtrlMenuPageTitleText titleText; //0x2b8
    MessageWindowControl messageWindow; //0x42c
    PushButton addButton; //0x5a0
    PushButton cancelButton; //0x7f4
    CtrlMenuBackButton backButton; //0xa48
}; //total size 0xcac
size_assert(AddMKChannel, 0xCAC);
}//namespace Pages
#endif