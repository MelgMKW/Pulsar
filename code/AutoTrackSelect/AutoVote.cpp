#include <Pulsar.hpp>
#include <Settings/PlayerData.hpp>
#include <AutoTrackSelect/AutoVote.hpp>
#include <SlotExpansion/Network/PulSELECT.hpp>
namespace PulsarUI {


//If ever there is a need for more custom sections, CustomSectionBuilder should be easy to make
void BuildCustomSection(Section *section, SectionId id) {
    //u32 raceCount = SectionMgr::sInstance->sectionMgr98->currentRaceNumber; 
    if (id != SECTION_P1_WIFI_FROOM_VS_VOTING || !Pulsar::sInstance->hasHAW) section->CreateSectionPages(id);
    else {
        section->CreateAndInitPage(PAGE_ACTION_LESS);
        section->CreateAndInitPage(PAGE_MESSAGEBOX);
        AutoVote *autoVote = new(AutoVote);
        section->Set(autoVote, PAGE_COUNTDOWN);
        autoVote->Init(PAGE_COUNTDOWN);
    }
}
kmCall(0x80622088, BuildCustomSection);

void AddCustomLayers(Section *section, SectionId id) {
    //u32 raceCount = SectionMgr::sInstance->sectionMgr98->currentRaceNumber;
    if (id != SECTION_P1_WIFI_FROOM_VS_VOTING || !Pulsar::sInstance->hasHAW) section->AddInitialLayers(id);
    else section->AddPageLayer(PAGE_COUNTDOWN);
}
kmCall(0x8062213c, AddCustomLayers);

void AutoVote::OnActivate() {}
void AutoVote::BeforeControlUpdate() {}
void AutoVote::OnResume() {}


void AutoVote::OnInit() {
    this->timerControl.isHidden = true;
    CountDownTimer::OnInit();
}

void AutoVote::OnDispose() {
    RKNetSELECTHandler::DestroyStaticInstance();
}

void AutoVote::OnUpdate() {
    PulsarSELECT::Handler *select = (PulsarSELECT::Handler *)RKNetSELECTHandler::sInstance;
    Pulsar *pulsar = Pulsar::sInstance;
    SectionMgr *sectionMgr = SectionMgr::sInstance;
    if (status == 6) {
        Pages::MessageBox *messageBox = sectionMgr->curSection->Get<Pages::MessageBox>(PAGE_MESSAGEBOX);
        messageBox->Reset();
        messageBox->SetMessageWindowText(0xfb2);
        messageBox->masterPageOnClickHandler = (PtmfHolder_1A<Page, void, Pages::Click *> *) & this->onDisconnectHandler;
        this->AddPageLayer(PAGE_MESSAGEBOX, 0);
        this->status = COUNTDOWN_STATUS_DISCONNECT_MSG;
    }
    if (((RKNetSELECTHandler *)select)->IsPrepared() && status == 2) {
        RKNetController *controller = RKNetController::sInstance;
        RKNetControllerSub *sub = &controller->subs[controller->currentSub];
        u8 hostAid = sub->hostAid;
        u8 localAid = sub->localAid;
        CourseId vote;
        if (hostAid == localAid) {
            vote = (CourseId)(pulsar->winningCourse + SELECTTRACKOFFSET);
            select->toSendPacket.pulWinningCourse = vote;
            select->toSendPacket.winningVoterAid = hostAid;
        }
        else {
            CourseId hostVote = (CourseId)select->receivedPackets[hostAid].pulSELPlayerData[0].pulCourseVote;
            if (hostVote != 0x43) {
                vote = hostVote;
                pulsar->winningCourse = hostVote;
                select->toSendPacket.pulWinningCourse = hostVote;
                select->toSendPacket.winningVoterAid = hostAid;
                select->toSendPacket.phase = 2;
            }
            else vote = LUIGI_CIRCUIT;
        }
        SectionMgr98 *mgr98 = sectionMgr->sectionMgr98;
        for (int i = 0; i < mgr98->localPlayerCount; i++) {
            PlayerCombo *combo = &mgr98->combos[i];
            ((RKNetSELECTHandler *)select)->SetPlayerData(combo->selCharacter, combo->selKart, vote, i, combo->starRank);
        }
        bool isReady = true;
        if (sub->connectionCount == 1 || this->duration > 720) {
            isReady = false;
            this->status = COUNTDOWN_STATUS_DISCONNECTED; //6
        }
        else if (hostAid == localAid) {
            u8 phase = 2;
            for (int i = 0; i < sub->connectionCount; i++) {
                if (i != hostAid) {
                    if (select->receivedPackets[i].phase != 2) {
                        isReady = false;
                        phase = select->toSendPacket.phase;
                    }
                }
            }
            select->toSendPacket.phase = 2;
        }
        else if (select->receivedPackets[hostAid].phase != 2) isReady = false;
        if (isReady) {
            ((RKNetSELECTHandler *)select)->AllocatePlayerIdsToAids();
            this->status = COUNTDOWN_STATUS_VOTES_PAGE;
            ArchiveRoot::sInstance->RequestLoadCourseAsync(pulsar->winningCourse);
            this->SetModeTypes();
            this->PrepareRace();
            this->UpdateFriendParams();
            this->ChangeSectionBySceneChange(SECTION_P1_WIFI_FRIEND_VS, 0, 0.0f);
        }
    }
}

}//namespace PulsarUI