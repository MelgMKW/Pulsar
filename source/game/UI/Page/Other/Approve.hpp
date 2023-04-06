#ifndef _APROVEPAGE_
#define _APROVEPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>

//_sinit_ at 805c23d0
namespace Pages {
class Approve : public Page {//ID 0x52
    //generic text box to validate a choice, essentially a message box page with a OK button
    //OnClick and the 2 back functions trigger a ptmf that is set by another page
    Approve(); //805c1cc0
    ~Approve() override; //805c1e18 vtable 808b7c48
    PageId GetNextPage() const override; //0x10 805c235c
    void OnInit() override; //0x28 805c1eb8
    void OnActivate() override; //0x30 805c208c
    void OnDeactivate() override; //0x34 805c2118
    void BeforeEntranceAnimations() override; //0x38 805c2324
    int GetRuntimeTypeInfo() const override; //0x60 805c2364
    virtual void Reset(); //sets texts to empty bmgs
    void OnClick(PushButton *button, u32 hudSlotId); //805c21c0
    void OnBackButtonClick(CtrlMenuBackButton *button, u32 hudSlotId); //805c223c
    void OnBackPress(u32 hudSlotId); //805c22b8
    void SetTitleMessage(u32 bmgId, const TextInfo *info); //805c21a8
    void SetMessageWindowMessage(u32 bmgId, const TextInfo *info); //805c21b0
    void SetApproveButtonMessage(u32 bmgId, const TextInfo *info); //805c21b8
    static void TriggerApprovePtmf(PtmfHolder_2A<Page, void, Approve *, float> *handler, Approve *button, u32 hudSlotId);
    static void TriggerDisapprovePtmf(PtmfHolder_2A<Page, void, Approve *, float> *handler, Approve *button, u32 hudSlotId);
    CtrlMenuPageTitleText titleText; //0x44
    PushButton approveButton; //0x1b8
    CtrlMenuBackButton backButton; //0x40c
    MessageWindowControl messageWindow; //0x670
    PtmfHolder_2A<Page, void, PushButton *, u32> onClickHandler; //0x7e4 805c21c0
    PtmfHolder_2A<Page, void, CtrlMenuBackButton *, u32> onBackButtonClickHandler; //0x7f8 805c223c
    PtmfHolder_1A<Page, void, u32> onBackPressHandler; //0x80C 805c22b8
    PtmfHolder_2A<Page, void, Approve *, float> *onApproveHandler;   //0x820 page refers to another page here, this is triggered OnButtonClick
    PtmfHolder_2A<Page, void, Approve *, float> *onDisapproveHandler; //0x824 same but for back functions, float = delay
    ControlsManipulatorManager manipulatorManager; //0x828
    u32 activePlayersBitfield; //0xa4c
    u32 unknown_0xa50; //some kind of state
    PageId nextPageId; //0xa54
}; //total size 0xa58
size_assert(Approve, 0xa58);
}//namespace Pages
#endif