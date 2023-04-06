#include <Pulsar.hpp>
#include <AutoTrackSelect/ChooseNextTrack.hpp>
#include <SlotExpansion/UI/ExpansionUIMisc.hpp>
#include <UI/BMG.hpp>


namespace PulsarUI {
void BuildChooseNextTrack(Section *section, PageId id) {
    section->CreateAndInitPage(id);
    ChooseNextTrack *choose = new(ChooseNextTrack);
    section->Set(choose, PAGE_GHOST_RACE_ENDMENU);
    choose->Init(PAGE_GHOST_RACE_ENDMENU);
}
kmCall(0x8062f020, BuildChooseNextTrack);


ChooseNextTrack::ChooseNextTrack() {
    controlBMGId = BMG_CHOOSE_NEXT;
    nextPage = PAGE_ONLINERACE_ENDWAIT;
    onRightArrowSelectHandler.subject = this;
    onRightArrowSelectHandler.ptmf = &ChooseNextTrack::OnRightArrowSelect;
    onLeftArrowSelectHandler.subject = this;
    onLeftArrowSelectHandler.ptmf = &ChooseNextTrack::OnLeftArrowSelect;
    onButtonClickHandler.ptmf = static_cast<void (Pages::RaceMenu:: *)(PushButton *, u32)>(&ChooseNextTrack::OnButtonClick);
    curPageIdx = Pulsar::sInstance->winningCourse / 4;
}

void ChooseNextTrack::OnActivate() {
    RaceMenu::OnActivate();
    this->UpdateButtonInfo(0); //to fix the bad IDs from the array
}

void ChooseNextTrack::OnUpdate() {
    Pulsar *pulsar = Pulsar::sInstance;
    if (this->duration > 600) {
        this->buttons[0].buttonId = pulsar->winningCourse + 1;
        this->OnButtonClick(&this->buttons[0], 0);
    }
}

int ChooseNextTrack::GetMessageBMG() const {
    return this->controlBMGId;
}
u32 ChooseNextTrack::GetButtonCount() const {
    return 4;
}
const u32 *ChooseNextTrack::GetVariantsIdxArray() const {
    static const u32 array[4] = { 0, 1, 2 ,4 }; //can't use 3 because 808da7a8 of variant names
    return array;
}

bool ChooseNextTrack::IsPausePage() const {
    return false;
}
const char *ChooseNextTrack::GetButtonsBRCTRName() const {
    return "ChooseNext";
}

void ChooseNextTrack::OnRightArrowSelect(SheetSelectControl::SheetSelectButton *button, u32 hudSlotId) {
    this->UpdateButtonInfo(1);
}
void ChooseNextTrack::OnLeftArrowSelect(SheetSelectControl::SheetSelectButton *button, u32 hudSlotId) {
    this->UpdateButtonInfo(-1);
}
void ChooseNextTrack::UpdateButtonInfo(s32 direction) {
    Pulsar *pulsar = Pulsar::sInstance;
    int ret = pulsar->GetNextCupId(this->curPageIdx, direction);
    u32 count = pulsar->ctsCupCount;
    if (pulsar->hasOddCups && ret == count - 1) {
        if (direction == -1) ret = count - 2;
        else ret = 0;
    }
    this->curPageIdx = ret;
    for (int i = 0; i < 4; i++) {
        PushButton *button = &this->buttons[i];
        button->buttonId = this->curPageIdx * 4 + i;
        button->SetMsgId(PulsarUI::GetTrackBMG((CourseId)button->buttonId));
    }
}

void ChooseNextTrack::OnButtonClick(PushButton *button, u32 hudSlotId) {
    Pulsar *pulsar = Pulsar::sInstance;
    pulsar->SaveSelectedCourse(button);
    this->EndStateAnimated(button->GetAnimationFrameSize(), 0);
    RaceRSARSoundsPlayer *rsarSounds = (RaceRSARSoundsPlayer *)RSARSoundsPlayer::sInstance;
    rsarSounds->PlayEndRaceMenuButtonClickSound();

    //this->ChangeSectionBySceneChange(SECTION_P1_WIFI_FROOM_VS_VOTING, 0, button->GetAnimationFrameSize());

}

void AddArrowsToChooseNext(Pages::RaceMenu *page, u32 controlCount) {
    bool isChooseNext = false;
    if (SectionMgr::sInstance->curSection->sectionId == SECTION_P1_WIFI_FRIEND_VS && page->pageId == PAGE_GHOST_RACE_ENDMENU) {
        controlCount += 1;
        isChooseNext = true;
    }
    page->InitControlGroup(controlCount);
    if (isChooseNext) {
        ChooseNextTrack *choose = (ChooseNextTrack *)page;
        choose->AddControl(controlCount - 1, &choose->arrows, 0);
        choose->arrows.SetRightArrowHandler((PtmfHolder_2A<Page, void, SheetSelectControl *, u32>*) & choose->onRightArrowSelectHandler);
        choose->arrows.SetLeftArrowHandler((PtmfHolder_2A<Page, void, SheetSelectControl *, u32>*) & choose->onLeftArrowSelectHandler);
        choose->arrows.Load("button", "RaceArrowRight", "ButtonArrowRight",
            "RaceArrowLeft", "ButtonArrowLeft", 1, 0, false);
    }
}
kmCall(0x80858ebc, AddArrowsToChooseNext);

PageId CorrectPageAfterResults(PageId id) {
    RKNetController *controller = RKNetController::sInstance;
    RKNetControllerSub *sub = &controller->subs[controller->currentSub];
    u8 hostAid = sub->hostAid;
    u8 localAid = sub->localAid;
    SectionMgr98 *mgr98 = SectionMgr::sInstance->sectionMgr98;
    if (Pulsar::sInstance->hasHAW && hostAid == localAid && mgr98->currentRaceNumber != mgr98->vsRaceCount) id = PAGE_GHOST_RACE_ENDMENU;
    return id;
}
kmBranch(0x80646754, CorrectPageAfterResults);
}//namespace PulsarUI