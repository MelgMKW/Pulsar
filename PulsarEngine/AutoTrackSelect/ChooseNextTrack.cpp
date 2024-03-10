#include <MarioKartWii/Race/RaceData.hpp>
#include <AutoTrackSelect/ChooseNextTrack.hpp>
#include <SlotExpansion/UI/ExpansionUIMisc.hpp>
#include <UI/UI.hpp>
#include <PulsarSystem.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>


namespace Pulsar {

namespace UI {

void RaceControlButtonInfo::Update(const Input::ControllerHolder* controllerHolder) {
    Input::ControllerHolder* modHolder = const_cast<Input::ControllerHolder*>(controllerHolder);
    bool isMirror = false;
    //u16 oldActions;
    if(modHolder != nullptr) {
        //oldActions = modHolder->uiinputStates[0].buttonActions;
        isMirror = RaceData::sInstance->racesScenario.settings.modeFlags & 1;
        if(isMirror) {
            modHolder->uiinputStates[0].stickX = -modHolder->uiinputStates[0].stickX;
        }
    }
    ControlButtonInfo::Update(modHolder);
    if(isMirror) {
        //modHolder->uiinputStates[0].buttonActions = oldActions;
        modHolder->uiinputStates[0].stickX = -modHolder->uiinputStates[0].stickX;
    }
}
static void BuildChooseNextTrack(Section& section, PageId id) {
    section.CreateAndInitPage(id);
    if(Info::IsHAW(false)) {
        ChooseNextTrack* choose = new(ChooseNextTrack);
        section.Set(choose, PAGE_GHOST_RACE_ENDMENU);
        choose->Init(PAGE_GHOST_RACE_ENDMENU);
    }
}
kmCall(0x8062f020, BuildChooseNextTrack); //0x70
kmCall(0x8062f08c, BuildChooseNextTrack); //0x71
kmCall(0x8062f0f8, BuildChooseNextTrack); //0x72
kmCall(0x8062f164, BuildChooseNextTrack); //0x73
kmCall(0x8062f1d0, BuildChooseNextTrack); //0x74
kmCall(0x8062f23c, BuildChooseNextTrack); //0x75
kmCall(0x8062f2a8, BuildChooseNextTrack); //0x76
kmCall(0x8062f314, BuildChooseNextTrack); //0x77

ChooseNextTrack::ChooseNextTrack() :
    isBattle(RaceData::sInstance->racesScenario.settings.gamemode == MODE_PRIVATE_BATTLE)
{
    if(RKNet::Controller::sInstance->subs[RKNet::Controller::sInstance->currentSub].hostAid
        == RKNet::Controller::sInstance->subs[RKNet::Controller::sInstance->currentSub].localAid) {
        status = STATUS_HOST;
    }
    else status = STATUS_NOTRACK;

    controlBMGId = BMG_CHOOSE_NEXT;
    nextPage = PAGE_WWRACEEND_WAIT;
    onRightArrowSelectHandler.subject = this;
    onRightArrowSelectHandler.ptmf = &ChooseNextTrack::OnRightArrowSelect;
    onLeftArrowSelectHandler.subject = this;
    onLeftArrowSelectHandler.ptmf = &ChooseNextTrack::OnLeftArrowSelect;
    onButtonClickHandler.ptmf = &ChooseNextTrack::OnButtonClick;
    for(int i = 0; i < 6; ++i) new (&this->manipulatorManager.holders[0].info) RaceControlButtonInfo;
    for(int i = 0; i < 12; ++i) hasReceivedHostTrack[i] = false;
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    PulsarId lastTrack = cupsConfig->winningCourse;
    if(!this->isBattle && cupsConfig->IsAlphabetical() && lastTrack >= PULSARID_FIRSTCT) lastTrack = static_cast<PulsarId>(cupsConfig->GetInvertedArray()[lastTrack - PULSARID_FIRSTCT] + PULSARID_FIRSTCT);
    curPageIdx = CupsConfig::ConvertCup_PulsarTrackToCup(lastTrack);
    cupsConfig->ToggleCTs(!CupsConfig::IsRegsSituation());

}

void ChooseNextTrack::OnActivate() {
    this->pageId = PAGE_TT_PAUSE_MENU;
    RaceMenu::OnActivate();
    this->pageId = PAGE_GHOST_RACE_ENDMENU;
    //this->buttons[3].SetMessage(BMG_RANDOM_TRACK);
    this->UpdateButtonInfo(0); //to fix the bad IDs from the array
    this->message->positionAndscale[1].position.y = 180.0f;
    this->countdown.SetInitial(static_cast<float>(Info::GetChooseNextTrackTimer()));
    this->countdown.isActive = true;
    this->countdownControl.AnimateCurrentCountDown();
}

void ChooseNextTrack::OnUpdate() {
    this->countdown.Update();
    this->countdownControl.AnimateCurrentCountDown();
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    if(this->duration == Info::GetChooseNextTrackTimer() * 60) {
        PulsarId lastTrack = cupsConfig->winningCourse;
        if(this->isBattle && lastTrack == N64_SKYSCRAPER) lastTrack = static_cast<PulsarId>(DELFINO_PIER);
        else {
            const bool isAlphabetical = cupsConfig->IsAlphabetical();

            if(isAlphabetical && lastTrack >= PULSARID_FIRSTCT) lastTrack = static_cast<PulsarId>(cupsConfig->GetInvertedArray()[lastTrack - PULSARID_FIRSTCT] + PULSARID_FIRSTCT);
            u32 rowIdx = lastTrack % 4;
            PulsarCupId cupId = CupsConfig::ConvertCup_PulsarTrackToCup(lastTrack);
            if(rowIdx == 3) {
                cupId = cupsConfig->GetNextCupId(cupId, 1);
                rowIdx = -1;
            }
            lastTrack = cupsConfig->ConvertTrack_PulsarCupToTrack(cupId, rowIdx + 1);
        }
        this->buttons[0].buttonId = lastTrack;
        this->OnButtonClick(this->buttons[0], 0);
    }
}


int ChooseNextTrack::GetMessageBMG() const {
    return this->controlBMGId;
}
u32 ChooseNextTrack::GetButtonCount() const {
    return this->isBattle ? 4 : 5;
}
const u32* ChooseNextTrack::GetVariantsIdxArray() const {
    static const u32 array[5] ={ 0,1,2,4,5 }; //can't use 3 because 808da7a8 of variant names
    return array;
}

bool ChooseNextTrack::IsPausePage() const {
    return false;
}
const char* ChooseNextTrack::GetButtonsBRCTRName() const {
    return "ChooseNext";
}

void ChooseNextTrack::OnRightArrowSelect(SheetSelectControl& control, u32 hudSlotId) {
    this->UpdateButtonInfo(1);
}
void ChooseNextTrack::OnLeftArrowSelect(SheetSelectControl& control, u32 hudSlotId) {
    this->UpdateButtonInfo(-1);
}
void ChooseNextTrack::UpdateButtonInfo(s32 direction) {

    if(this->isBattle) {
        this->curPageIdx = (this->curPageIdx + direction + 3) % 3;
        bool isHidden = false;
        if(this->curPageIdx == 2) isHidden = true;
        this->buttons[2].isHidden = isHidden;
        this->buttons[2].manipulator.inaccessible = isHidden;
        this->buttons[3].isHidden = isHidden;
        this->buttons[3].manipulator.inaccessible = isHidden;

        for(int i = 0; i < 4; ++i) {
            u32 curId = this->curPageIdx * 4 + i;
            this->buttons[i].buttonId = curId + 0x20;
            this->buttons[i].SetMessage(BMG_BATTLE + curId);
        }
    }
    else {
        const CupsConfig* cupsConfig = CupsConfig::sInstance;
        int ret = cupsConfig->GetNextCupId(static_cast<PulsarCupId>(this->curPageIdx), direction);
        const u32 count = cupsConfig->GetCtsTrackCount() / 4;
        if(cupsConfig->HasOddCups() && ret == count - 1) {
            if(direction == -1) ret = count - 2;
            else ret = 0;
        }
        this->curPageIdx = ret;
        for(int i = 0; i < 4; ++i) {
            this->buttons[i].buttonId = cupsConfig->ConvertTrack_PulsarCupToTrack(static_cast<PulsarCupId>(this->curPageIdx), i);
            this->buttons[i].SetMessage(UI::GetTrackBMGId(static_cast<PulsarId>(this->buttons[i].buttonId)));
        }
    }
    this->buttons[4].buttonId = -1;
}

void ChooseNextTrack::OnButtonClick(PushButton& button, u32 hudSlotId) {
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    if(button.buttonId == -1) {
        PulsarId next = cupsConfig->RandomizeTrack();
        if(cupsConfig->winningCourse == next) next = cupsConfig->RandomizeTrack();
        cupsConfig->winningCourse = next;
    }
    else cupsConfig->winningCourse = static_cast<PulsarId>(button.buttonId);
    cupsConfig->selectedCourse = cupsConfig->winningCourse;
    this->EndStateAnimated(button.GetAnimationFrameSize(), 0);
    RaceData::sInstance->menusScenario.settings.courseId = cupsConfig->GetCorrectTrackSlot();
    Audio::RaceRSARPlayer* rsarPlayer = static_cast<Audio::RaceRSARPlayer*>(Audio::RSARPlayer::sInstance);
    rsarPlayer->PlayEndRaceMenuButtonClickSound();
}

static void AddArrowsToChooseNext(Pages::RaceMenu& page, u32 controlCount) {
    bool isChooseNext = false;
    const SectionId curSectionId = SectionMgr::sInstance->curSection->sectionId;
    if((curSectionId >= SECTION_P1_WIFI_FRIEND_VS || curSectionId >= SECTION_P2_WIFI_FRIEND_COIN)
        && page.pageId == PAGE_GHOST_RACE_ENDMENU) {
        controlCount += 2;
        isChooseNext = true;
    }
    page.InitControlGroup(controlCount);
    if(isChooseNext) {
        ChooseNextTrack& choose = static_cast<ChooseNextTrack&>(page);
        choose.AddControl(controlCount - 2, choose.arrows, 0);
        choose.arrows.SetRightArrowHandler(choose.onRightArrowSelectHandler);
        choose.arrows.SetLeftArrowHandler(choose.onLeftArrowSelectHandler);
        choose.arrows.Load("button", "RaceArrowRight", "ButtonArrowRight",
            "RaceArrowLeft", "ButtonArrowLeft", 1, 0, false);

        choose.AddControl(controlCount - 1, choose.countdownControl, 0);
        choose.countdownControl.Load(choose.countdown);
    }
}
kmCall(0x80858ebc, AddArrowsToChooseNext);

static PageId CorrectPageAfterResults(PageId id) {
    const SectionMgr* sectionMgr = SectionMgr::sInstance;
    if(Info::IsHAW(false)) {
        const ChooseNextTrack* page = sectionMgr->curSection->Get<ChooseNextTrack>(PAGE_GHOST_RACE_ENDMENU);
        if(page != nullptr && page->IsHost()) {
            const SectionParams* params = sectionMgr->sectionParams;
            if(page->isBattle && params->redWins < 2 && params->blueWins < 2
                || !page->isBattle && params->currentRaceNumber != System::sInstance->racesPerGP) id = PAGE_GHOST_RACE_ENDMENU;
        }
    }

    return id;
}
kmBranch(0x80646754, CorrectPageAfterResults);
}//namespace UI
}//namespace Pulsar