#include <MarioKartWii/UI/Page/Other/ActionLess.hpp>
#include <PulsarSystem.hpp>
#include <UI/UI.hpp>
#include <Settings/Settings.hpp>
#include <AutoTrackSelect/AutoVote.hpp>
#include <SlotExpansion/Network/PulSELECT.hpp>

namespace Pulsar {
namespace UI {
//If ever there is a need for more custom sections, CustomSectionBuilder should be easy to make
static void BuildCustomSection(Section& section, SectionId id) {
    if(id < SECTION_P1_WIFI_FROOM_VS_VOTING || id > SECTION_P2_WIFI_FROOM_COIN_VOTING
        || !Info::IsHAW(false)) section.CreateSectionPages(id);
    else {
        section.CreateAndInitPage(PAGE_AUTO_ENDING2);
        section.CreateAndInitPage(PAGE_MESSAGEBOX);
        AutoVote* autoVote = new(AutoVote);
        section.Set(autoVote, PAGE_COUNTDOWN);
        autoVote->Init(PAGE_COUNTDOWN);
    }
}
kmCall(0x80622088, BuildCustomSection);

static void AddCustomLayers(Section& section, SectionId id) {
    if(id < SECTION_P1_WIFI_FROOM_VS_VOTING || id > SECTION_P2_WIFI_FROOM_COIN_VOTING
        || !Info::IsHAW(false)) section.AddInitialLayers(id);
    else section.AddPageLayer(PAGE_COUNTDOWN);
}
kmCall(0x8062213c, AddCustomLayers);

void AutoVote::OnActivate() {
    Pages::AutoEnding* msg = SectionMgr::sInstance->curSection->Get<Pages::AutoEnding>(PAGE_AUTO_ENDING2);
    msg->SetMessageWindowText(BMG_READY_TO_RACE, nullptr);
    this->AddPageLayer(PAGE_AUTO_ENDING2, 0);
}

void AutoVote::BeforeControlUpdate() {}
void AutoVote::OnResume() {}

void AutoVote::OnInit() {
    this->timerControl.isHidden = true;
    CountDownTimer::OnInit();
}

void AutoVote::OnDispose() {
    RKNet::SELECTHandler::DestroyInstance();
}

void AutoVote::OnUpdate() {
    Network::CustomSELECTHandler* select = reinterpret_cast<Network::CustomSELECTHandler*>(RKNet::SELECTHandler::sInstance);
    CupsConfig* cupsConfig = CupsConfig::sInstance;

    const SectionMgr* sectionMgr = SectionMgr::sInstance;
    if(status == 6) {
        Pages::MessageBox* messageBox = sectionMgr->curSection->Get<Pages::MessageBox>();
        messageBox->Reset();
        messageBox->SetMessageWindowText(0xfb2);
        const PtmfHolder_1A<Page, void, Pages::Click&>& onMessageClickPtmf = this->onDisconnectHandler;
        messageBox->masterPageOnClickHandler = &onMessageClickPtmf;
        this->AddPageLayer(PAGE_MESSAGEBOX, 0);
        this->status = COUNTDOWN_STATUS_DISCONNECT_MSG;
    }
    if(reinterpret_cast<RKNet::SELECTHandler*>(select)->IsPrepared() && status == 2) {
        const RKNet::Controller* controller = RKNet::Controller::sInstance;
        const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
        const u8 hostAid = sub.hostAid;
        const u8 localAid = sub.localAid;
        PulsarId vote;
        if(hostAid == localAid) {
            vote = cupsConfig->winningCourse;
            select->toSendPacket.pulWinningCourse = vote;
            select->toSendPacket.winningVoterAid = hostAid;
        }
        else {
            const PulsarId hostVote = static_cast<PulsarId>(select->receivedPackets[hostAid].pulSELPlayerData[0].pulCourseVote);
            if(hostVote != 0x43) {
                vote = hostVote;
                cupsConfig->winningCourse = hostVote;
                select->toSendPacket.pulWinningCourse = vote;
                select->toSendPacket.winningVoterAid = hostAid;
                select->toSendPacket.phase = 2;
            }
            else vote = PULSARID_FIRSTREG;
        }
        const SectionParams* params = sectionMgr->sectionParams;
        for(int i = 0; i < params->localPlayerCount; ++i) {
            const PlayerCombo& combo = params->combos[i];
            reinterpret_cast<RKNet::SELECTHandler*>(select)->SetPlayerData(combo.selCharacter, combo.selKart,
                static_cast<CourseId>(vote), i, combo.starRank);
        }
        bool isReady = true;
        if(sub.connectionCount == 1 || this->duration > 5000) {
            isReady = false;
            this->status = COUNTDOWN_STATUS_DISCONNECTED; //6
        }
        else if(hostAid == localAid) {
            for(int i = 0; i < sub.connectionCount; ++i) {
                if(i != hostAid) {
                    if(select->receivedPackets[i].phase != 2) {
                        //check winning course
                        isReady = false;
                    }
                }
            }
            select->toSendPacket.phase = 2;
        }
        else if(select->receivedPackets[hostAid].phase != 2) isReady = false;
        if(isReady) ++readyDuration;
        if(readyDuration > 180) {
            reinterpret_cast<RKNet::SELECTHandler*>(select)->AllocatePlayerIdsToAids();
            this->status = COUNTDOWN_STATUS_VOTES_PAGE;
            ArchiveRoot::sInstance->RequestLoadCourseAsync(static_cast<CourseId>(cupsConfig->winningCourse));
            this->SetModeTypes();
            this->PrepareRace();
            this->UpdateFriendParams();
            this->ChangeSectionBySceneChange(static_cast<SectionId>(sectionMgr->curSection->sectionId + 0x10), 0, 0.0f);
        }
    }
}

}//namespace UI
}//namespace Pulsar