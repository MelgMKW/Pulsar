#include <MarioKartWii/Race/Racedata.hpp>
#include <MarioKartWii/Audio/RSARPlayer.hpp>
#include <PulsarSystem.hpp>
#include <Network/PacketExpansion.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <SlotExpansion/UI/ExpansionUIMisc.hpp>
#include <AutoTrackSelect/ChooseNextTrack.hpp>

namespace Pulsar {
namespace UI {

void RaceControlButtonInfo::Update(const Input::ControllerHolder* controllerHolder) {
    Input::ControllerHolder* modHolder = const_cast<Input::ControllerHolder*>(controllerHolder);
    bool isMirror = false;
    //u16 oldActions;
    if (modHolder != nullptr) {
        //oldActions = modHolder->uiinputStates[0].buttonActions;
        isMirror = Racedata::sInstance->racesScenario.settings.modeFlags & 1;
        if (isMirror) {
            modHolder->uiinputStates[0].stickX = -modHolder->uiinputStates[0].stickX;
        }
    }
    ControlButtonInfo::Update(modHolder);
    if (isMirror) {
        //modHolder->uiinputStates[0].buttonActions = oldActions;
        modHolder->uiinputStates[0].stickX = -modHolder->uiinputStates[0].stickX;
    }
}
/*
static void BuildChooseNextTrack(Section& section, PageId id) {
    section.CreateAndInitPage(id);
    if(Info::IsHAW(false)) {
        ChooseNextTrack* choose = new(ChooseNextTrack);
        section.Set(choose, ChooseNextTrack::fakeId);
        choose->Init(ChooseNextTrack::fakeId);
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
*/

ChooseNextTrack::ChooseNextTrack() :
    isBattle(Racedata::sInstance->racesScenario.settings.gamemode == MODE_PRIVATE_BATTLE)
{
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
    this->isHost = sub.hostAid == sub.localAid;
    this->status = STATUS_NOTRACK;
    //if(this->isHost) this->status = STATUS_NOTRACK;
    //else this->status = STATUS_TRACK_SELECTED; //non-hosts never send a track

    messageBMGId = BMG_CHOOSE_NEXT;
    nextPage = PAGE_WWRACEEND_WAIT;
    onRightArrowSelectHandler.subject = this;
    onRightArrowSelectHandler.ptmf = &ChooseNextTrack::OnRightArrowSelect;
    onLeftArrowSelectHandler.subject = this;
    onLeftArrowSelectHandler.ptmf = &ChooseNextTrack::OnLeftArrowSelect;
    onButtonClickHandler.ptmf = &ChooseNextTrack::OnButtonClick;
    for (int i = 0; i < 6; ++i) new (&this->manipulatorManager.holders[0].info) RaceControlButtonInfo;
    for (int i = 0; i < 12; ++i) hasReceivedHostTrack[i] = false;
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    PulsarId lastTrack = cupsConfig->GetWinning();
    if (!this->isBattle && cupsConfig->IsAlphabetical() && lastTrack >= PULSARID_FIRSTCT) lastTrack = static_cast<PulsarId>(cupsConfig->GetInvertedArray()[lastTrack - PULSARID_FIRSTCT] + PULSARID_FIRSTCT);
    curPageIdx = CupsConfig::ConvertCup_PulsarTrackToCup(lastTrack);
    cupsConfig->ToggleCTs(System::sInstance->IsContext(PULSAR_CT));

}

void ChooseNextTrack::OnActivate() {
    this->pageId = PAGE_TT_PAUSE_MENU;
    RaceMenu::OnActivate();
    this->pageId = ChooseNextTrack::fakeId;
    //this->buttons[3].SetMessage(BMG_RANDOM_TRACK);
    this->UpdateButtonInfo(0); //to fix the bad IDs from the array
    this->message->positionAndscale[1].position.y = 180.0f;
    this->countdown.SetInitial(static_cast<float>(System::sInstance->GetInfo().GetChooseNextTrackTimer()));
    this->countdown.isActive = true;
    this->countdownControl.AnimateCurrentCountDown();
}

void ChooseNextTrack::OnUpdate() {
    this->countdown.Update();
    this->countdownControl.AnimateCurrentCountDown();
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    if (this->duration == System::sInstance->GetInfo().GetChooseNextTrackTimer() * 60) {
        PulsarId lastTrack = cupsConfig->GetWinning();
        if (this->isBattle && lastTrack == N64_SKYSCRAPER) lastTrack = static_cast<PulsarId>(DELFINO_PIER);
        else {
            const bool isAlphabetical = cupsConfig->IsAlphabetical();

            if (isAlphabetical && lastTrack >= PULSARID_FIRSTCT) lastTrack = static_cast<PulsarId>(cupsConfig->GetInvertedArray()[lastTrack - PULSARID_FIRSTCT] + PULSARID_FIRSTCT);
            u32 rowIdx = lastTrack % 4;
            PulsarCupId cupId = CupsConfig::ConvertCup_PulsarTrackToCup(lastTrack);
            if (rowIdx == 3) {
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
    return this->messageBMGId;
}
u32 ChooseNextTrack::GetButtonCount() const {
    return this->isBattle ? 4 : maxButtonCount;
}
const u32* ChooseNextTrack::GetVariantsIdxArray() const {
    static const u32 array[maxButtonCount] ={ 0,1,2,4,5 }; //can't use 3 because 808da7a8 of variant names
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

    if (this->isBattle) {
        this->curPageIdx = (this->curPageIdx + direction + 3) % 3;
        bool isHidden = false;
        if (this->curPageIdx == 2) isHidden = true;
        this->buttons[2].isHidden = isHidden;
        this->buttons[2].manipulator.inaccessible = isHidden;
        this->buttons[3].isHidden = isHidden;
        this->buttons[3].manipulator.inaccessible = isHidden;

        for (int i = 0; i < 4; ++i) {
            u32 curId = this->curPageIdx * 4 + i;
            this->buttons[i].buttonId = curId + 0x20;
            this->buttons[i].SetMessage(BMG_BATTLE + curId);
        }
    }
    else {
        const CupsConfig* cupsConfig = CupsConfig::sInstance;
        int ret = cupsConfig->GetNextCupId(static_cast<PulsarCupId>(this->curPageIdx), direction);
        const u32 count = cupsConfig->GetCtsTrackCount() / 4;
        if (cupsConfig->HasOddCups() && ret == count - 1) {
            if (direction == -1) ret = count - 2;
            else ret = 0;
        }
        this->curPageIdx = ret;
        for (int i = 0; i < 4; ++i) {
            this->buttons[i].buttonId = cupsConfig->ConvertTrack_PulsarCupToTrack(static_cast<PulsarCupId>(this->curPageIdx), i);
            this->buttons[i].SetMessage(UI::GetTrackBMGId(static_cast<PulsarId>(this->buttons[i].buttonId), true));
        }
    }
    this->buttons[4].buttonId = -1;
}

void ChooseNextTrack::OnButtonClick(PushButton& button, u32 hudSlotId) {
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    PulsarId next;
    if (button.buttonId == -1) {
        next = cupsConfig->RandomizeTrack();
        if (cupsConfig->GetWinning() == next) next = cupsConfig->RandomizeTrack();
    }
    else next = static_cast<PulsarId>(button.buttonId);
    cupsConfig->SetWinning(next);
    cupsConfig->SetSelected(next);
    this->status = STATUS_TRACK;
    this->EndStateAnimated(0, button.GetAnimationFrameSize());
    Racedata::sInstance->menusScenario.settings.courseId = cupsConfig->GetCorrectTrackSlot();
    Audio::RaceRSARPlayer* rsarPlayer = static_cast<Audio::RaceRSARPlayer*>(Audio::RSARPlayer::sInstance);
    rsarPlayer->PlayEndRaceMenuButtonClickSound();
}

static void AddArrowsToChooseNext(Pages::RaceMenu& page, u32 controlCount) {
    bool isChooseNext = false;
    const SectionId curSectionId = SectionMgr::sInstance->curSection->sectionId;
    if ((curSectionId >= SECTION_P1_WIFI_FRIEND_VS || curSectionId >= SECTION_P2_WIFI_FRIEND_COIN)
        && page.pageId == ChooseNextTrack::fakeId) {
        controlCount += 2;
        isChooseNext = true;
    }
    page.InitControlGroup(controlCount);
    if (isChooseNext) {
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

void ChooseNextTrack::UpdateRH1() {
    RKNet::Controller* controller = RKNet::Controller::sInstance;
    RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
    for (int aid = 0; aid < 12; ++aid) {
        if ((1 << aid & sub.availableAids) == 0) continue;
        if (aid == sub.localAid) continue;
        for (int i = 0; i < 2; ++i) {
            RKNet::PacketHolder<Network::PulRH1>* holder = controller->splitToSendRACEPackets[i][aid]->GetPacketHolder<Network::PulRH1>();
            /*
            this shouldn't be needed because the "ExportRH1ToPulRH1" always does it
            const u32 curSize = holder->packetSize;/
            u32 addedSize = 0;
            if(curSize == sizeof(RKNet::RACEHEADER1Packet)) addedSize = sizeof(Network::PulRH1) - sizeof(RKNet::RACEHEADER1Packet);
            else if(holder->packetSize == 0) addedSize = sizeof(Network::PulRH1);
            holder->packetSize += addedSize;
            */
            Network::PulRH1* sendPacket = holder->packet;
            sendPacket->chooseNextStatus = this->status;
            const CupsConfig* cupsConfig = CupsConfig::sInstance;
            sendPacket->nextTrack = cupsConfig->GetWinning();
            sendPacket->variantIdx = cupsConfig->GetCurVariantIdx();
            sendPacket->hasTrack = true;
        }
    }
}

SectionId ChooseNextTrack::ProcessHAW(SectionId defaultId) {

    SectionId ret = defaultId;
    const SectionMgr* sectionMgr = SectionMgr::sInstance;

    //Process Received Packets:
    RKNet::Controller* controller = RKNet::Controller::sInstance;
    RKNet::ControllerSub& sub = controller->subs[controller->currentSub];

    bool hasReceivedEveryone = true;
    bool isEveryoneWaiting = true;
    bool isEveryoneInRace = true;

    for (int aid = 0; aid < 12; ++aid) {
        if ((1 << aid & sub.availableAids) == 0) continue;
        if (aid == sub.localAid) continue;
        const u32 lastBufferUsed = controller->lastReceivedBufferUsed[aid][RKNet::PACKET_RACEHEADER1];
        const RKNet::PacketHolder<Network::PulRH1>* holder = controller->splitReceivedRACEPackets[lastBufferUsed][aid]->GetPacketHolder<Network::PulRH1>();

        if (holder->packetSize == sizeof(Network::PulRH1)) {
            const Network::PulRH1* rh1 = holder->packet;
            if (aid == sub.hostAid) {
                if (rh1->chooseNextStatus == STATUS_TRACK) {
                    this->status = STATUS_TRACK;
                    CupsConfig* cupsConfig = CupsConfig::sInstance;
                    cupsConfig->SetWinning(static_cast<PulsarId>(rh1->nextTrack), rh1->variantIdx);
                    //cupsConfig->selectedCourse = cupsConfig->winningCourse;
                    Racedata::sInstance->menusScenario.settings.courseId = cupsConfig->GetCorrectTrackSlot();
                }
                else if (rh1->chooseNextStatus == STATUS_HOST_START) {
                    this->status = STATUS_RH1_READY;
                }
            }

            if (this->isHost) {
                if (rh1->chooseNextStatus < STATUS_TRACK) hasReceivedEveryone = false;
                else if (rh1->timer != 0) isEveryoneInRace = false;
            }
        }
    }

    if (this->isHost) {
        if (hasReceivedEveryone && this->status == STATUS_TRACK) {
            this->status = STATUS_HOST_START;
        }
        if (isEveryoneInRace && this->status == STATUS_HOST_START) {
            this->status = STATUS_RH1_READY;
        }
    }
    if (this->status == STATUS_RH1_READY) ret = sectionMgr->curSection->sectionId;
    else {
        ret = SECTION_NONE;
        this->UpdateRH1();
    }
    return ret;
}

PageId ChooseNextTrack::GetPageAfterWifiResults(PageId defaultId) const {
    PageId ret = defaultId;
    if (this->isHost) {
        const SectionParams* params = SectionMgr::sInstance->sectionParams;
        if (this->isBattle && params->redWins < 2 && params->blueWins < 2
            || !this->isBattle && params->onlineParams.currentRaceNumber != System::sInstance->netMgr.racesPerGP) ret = static_cast<PageId>(ChooseNextTrack::id);
    }
    return ret;
}

}//namespace UI
}//namespace Pulsar