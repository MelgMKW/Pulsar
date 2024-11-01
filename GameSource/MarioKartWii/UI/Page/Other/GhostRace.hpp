#ifndef _GHOSTRACEPAGE_
#define _GHOSTRACEPAGE_
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/Other/Message.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuText.hpp>
#include <MarioKartWii/UI/Ctrl/MessageWindowControl.hpp>
#include <MarioKartWii/UI/Ctrl/GhostInfoControl.hpp>
#include <MarioKartWii/File/RKG.hpp>

//_sinit_ at 805e0c18
namespace Pages {
class GhostRaceExplanation : public Page { //ID 0x9f
public:
    static const PageId id = PAGE_GHOST_RACE_EXPLANATION;
    GhostRaceExplanation(); //805de9f0
    ~GhostRaceExplanation() override; //805deb08 vtable 808b91a0
    int IsHomeMenuWorking() const; //0x14 805deeac
    void OnInit() override; //0x28 805deba8
    void OnActivate() override; //0x30 805ded24
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805e0b1c
    void OnButtonClick(PushButton& button, u32 hudSlotId); //805deefc
    void OnBackPress(u32 hudSlotId); //805def88
    PtmfHolder_2A<GhostRaceExplanation, void, PushButton&, u32> onButtonClickHandler; //0x44 805deefc vtable 808b9210
    PtmfHolder_1A<GhostRaceExplanation, void, u32> onBackPressHandler; //0x58 805def88 vtable 808b9204
    ControlsManipulatorManager manipulatorManager; //0x6c
    CtrlMenuPageTitleText titleText; //0x290
    MessageWindowControl messageWindow; //0x404
    PushButton nextButton; //0x578
    CtrlMenuBackButton backButton; //0x7cc
}; //0xa30
size_assert(GhostRaceExplanation, 0xa30);


class GhostRaceMgr : public Page { //ID 0xa0
public:
    static const PageId id = PAGE_GHOST_RACE_MGR;
    GhostRaceMgr(); //805defd4
    ~GhostRaceMgr() override; //805df058 vtable 808b9130
    PageId GetNextPage() const override; //805e0b08
    void OnInit() override; //0x28 805df0c0
    void OnActivate() override; //0x30 805df1d0
    void BeforeEntranceAnimations() override; //0x38 805df2f0
    void BeforeExitAnimations() override; //0x40 805df2f4
    void AfterControlUpdate() override; //0x4c 805df2f8
    void OnResume() override; //0x54 805df540
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805e0b10

    //only called if RKSYS DLd ghost request failed; also displays errors if one occurs
    void DownloadGhost(); //805df978 
    void PrepareRace(); //805e0344
    void OnErrorBoxClick(MessageBox& msgBoxPage); //805e053c

    PtmfHolder_1A<GhostRaceMgr, void, MessageBox&> onErrorBoxClickHandler;//0x44 805e053c vtable 808b9194 
    ManipulatorManager manipulatorManager; //0x58
    u8 unknown_0x68[4];
    bool hasRKG; //0x6c
    u8 padding2[3];
    RKG rkg; //0x70
    PageId nextPage; //0x2870
}; //0x2874
size_assert(GhostRaceMgr, 0x2874);

class GhostRaceInfo : public Page { //ID 0xA1
public:
    static const PageId id = PAGE_GHOST_RACE_INFO;
    GhostRaceInfo(); //805e0584
    ~GhostRaceInfo() override; //805e069c vtable 808b90b4
    void OnInit() override; //0x28 805e073c
    void OnActivate() override; //0x30 805e08b4
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805e0afc
    void OnButtonClick(PushButton& button, u32 hudSlotId); //805e0918
    void OnBackPress(u32 hudSlotId); //805e0a44
    void UpdateGhostInfo(const RKG& rkg); //805e08c0
    PtmfHolder_2A<GhostRaceInfo, void, PushButton&, u32> onButtonClickHandler; //0x44 805e0918 vtable 808b3124
    PtmfHolder_1A<GhostRaceInfo, void, u32> onBackPressHandler; //0x58 805e0a44 vtable 808b9118
    ControlsManipulatorManager manipulatorManager; //0x6c
    CtrlMenuPageTitleText titleText; //0x290
    GhostInfoControl ghostInfoControl; //0x404
    PushButton challengexButton; //0x650
    CtrlMenuBackButton backButton; //0x8a4
    u32 actionTaken; //0xb08 0 = challenge, 1 back
}; //0xb0c
size_assert(GhostRaceInfo, 0xb0c);
}//namespace Pages
#endif

