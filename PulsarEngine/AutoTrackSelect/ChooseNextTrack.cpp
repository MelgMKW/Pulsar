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
            /*
            if((oldActions & 0x60) != 0x60) { //not left and right at the same time
                if(oldActions & 0x20) {
                    modHolder->uiinputStates[0].buttonActions |= 0x40;
                    modHolder->uiinputStates[0].buttonActions &= ~0x20;
                }
                else if(oldActions & 0x40) {
                    modHolder->uiinputStates[0].buttonActions |= 0x20;
                    modHolder->uiinputStates[0].buttonActions &= ~0x40;
                }
            }
            */
        }
    }
    ControlButtonInfo::Update(modHolder);
    if(isMirror) {
        //modHolder->uiinputStates[0].buttonActions = oldActions;
        modHolder->uiinputStates[0].stickX = -modHolder->uiinputStates[0].stickX;
    }
}
void BuildChooseNextTrack(Section& section, PageId id) {
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
    isBattle(RaceData::sInstance->racesScenario.settings.gamemode == MODE_PRIVATE_BATTLE),
    curPageIdx(CupsConfig::sInstance->winningCourse / 4)//, lastSentFrames(-1), maxTimeDiff(0), readyWait(0)
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
    CupsConfig::sInstance->ToggleCTs(!CupsConfig::IsRegsSituation());
}

void ChooseNextTrack::OnActivate() {
    this->pageId = PAGE_TT_PAUSE_MENU;
    RaceMenu::OnActivate();
    this->pageId = PAGE_GHOST_RACE_ENDMENU;
    //this->buttons[3].setmsgid(BMG_RANDOM_TRACK);
    this->UpdateButtonInfo(0); //to fix the bad IDs from the array
    this->message->positionAndscale[1].position.y = 180.0f;
    this->countdown.SetInitial(10.0f);
    this->countdown.isActive = true;
    this->countdownControl.AnimateCurrentCountDown();

}

void ChooseNextTrack::OnUpdate() {
    this->countdown.Update();
    this->countdownControl.AnimateCurrentCountDown();
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    if(this->duration == 600) {
        PulsarId lastTrack = cupsConfig->winningCourse;
        if(this->isBattle && lastTrack == N64_SKYSCRAPER) lastTrack = static_cast<PulsarId>(DELFINO_PIER);
        else if(lastTrack % 4 == 3) lastTrack = static_cast<PulsarId>(cupsConfig->GetNextCupId(CupsConfig::ConvertCup_PulsarTrackToCup(lastTrack), 1) * 4);
        else lastTrack = lastTrack + 1U;
        this->buttons[0].buttonId = lastTrack;
        this->OnButtonClick(this->buttons[0], 0);
    }
}

int ChooseNextTrack::getmsgidBMG() const {
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
            this->buttons[i].setmsgid(BMG_BATTLE + curId);
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
            this->buttons[i].buttonId = this->curPageIdx * 4 + i;
            this->buttons[i].setmsgid(UI::GetTrackBMGId(static_cast<PulsarId>(this->buttons[i].buttonId)));
        }
    }
}

void ChooseNextTrack::OnButtonClick(PushButton& button, u32 hudSlotId) {
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    if(button.buttonId == 5) {
        PulsarId next = cupsConfig->RandomizeTrack();
        if(cupsConfig->winningCourse == next) next = cupsConfig->RandomizeTrack();
        cupsConfig->winningCourse = next;
    }
    else cupsConfig->winningCourse = static_cast<PulsarId>(button.buttonId);
    cupsConfig->selectedCourse = cupsConfig->winningCourse;
    this->EndStateAnimated(button.GetAnimationFrameSize(), 0);
    RaceData::sInstance->menusScenario.settings.courseId = cupsConfig->GetCorrectTrackSlot();
    RaceRSARSoundsPlayer* rsarSounds = static_cast<RaceRSARSoundsPlayer*>(RSARSoundsPlayer::sInstance);
    rsarSounds->PlayEndRaceMenuButtonClickSound();
}

void AddArrowsToChooseNext(Pages::RaceMenu& page, u32 controlCount) {
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

PageId CorrectPageAfterResults(PageId id) {
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