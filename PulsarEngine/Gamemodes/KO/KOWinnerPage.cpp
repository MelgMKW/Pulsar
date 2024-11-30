#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/UI/Page/Other/WWRaceSupporting.hpp>
#include <Gamemodes/KO/KOWinnerPage.hpp>
#include <Gamemodes/KO/KOMgr.hpp>
#include <Network/PacketExpansion.hpp>


namespace Pulsar {
namespace KO {

WinnerPage::WinnerPage() {
    status = WAITING_STATS;
    timeRecvStats = 0;
    onClickHandler.subject = this;
    onClickHandler.ptmf = &WinnerPage::HandleClick;
}

void WinnerPage::OnInit() {
    this->InitControlGroup(6);
    for(int i = 0; i < 3; ++i) {
        LayoutUIControl& stats = this->stats[i];
        this->AddControl(i, stats, 0);
        ControlLoader loader(&stats);
        char variant[0x50];
        snprintf(variant, 0x50, "Stats_%d", i);
        loader.Load(UI::raceFolder, "ko_stats", variant, nullptr);
        stats.isHidden = true;
    }


    this->AddControl(3, this->miiAndName, 0);
    ControlLoader loaderMii(&this->miiAndName);
    loaderMii.Load(UI::raceFolder, "ko_winner", "ko_winner", 0);
    this->miiAndName.isHidden = true;


    this->AddControl(4, this->titleText, 0);
    ControlLoader loader(&this->titleText);
    loader.Load(UI::raceFolder, "ko_title", "ko_title", nullptr);
    this->titleText.isHidden = true;

    this->AddControl(5, this->msgWindow, 0);
    this->msgWindow.Load(UI::controlFolder, Pages::WWRaceEndWait::msgWindowBRCTR, Pages::WWRaceEndWait::msgWindowBRCTR);
    this->msgWindow.SetMessage(UI::BMG_PLEASE_WAIT_A_MOMENT);

    this->manipulator.Init(1, false);
    this->SetManipulatorManager(manipulator);

}

void WinnerPage::OnDeactivate() {
    Mgr* mgr = System::sInstance->koMgr;
    SectionId id = mgr->GetSectionAfterKO(SECTION_P1_WIFI_FROM_FROOM_RACE);
    this->ChangeSectionBySceneChange(id, 0, 0.0f);
}

void WinnerPage::DisplayWinner() {
    this->manipulator.SetGlobalHandler(FORWARD_PRESS, this->onClickHandler, false);
    this->manipulator.activeLocalPlayerBitfield = 1;
    this->msgWindow.isHidden = true;
    const Mgr* mgr = System::sInstance->koMgr;
    MiiGroup& playerMiis = SectionMgr::sInstance->sectionParams->playerMiis;
    this->miiAndName.SetMiiPane("chara", playerMiis, mgr->winnerPlayerId, 5);
    this->miiAndName.isHidden = false;
    Text::Info info;
    info.miis[0] = playerMiis.GetMii(mgr->winnerPlayerId);
    this->titleText.SetMessage(UI::BMG_KO_WINNER, &info);
    this->titleText.isHidden = false;
    this->PlaySound(SOUND_ID_NEW_RECORD, -1);
}

void WinnerPage::AfterControlUpdate() {
    if(this->status == WAITING_STATS) {
        const Mgr* mgr = System::sInstance->koMgr;
        RKNet::Controller* controller = RKNet::Controller::sInstance;
        const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
        const u8 winnerAid = controller->aidsBelongingToPlayerIds[mgr->winnerPlayerId];
        const Mgr::Stats::Final* finalStats;
        if(sub.localAid == winnerAid) finalStats = &mgr->stats[0].final;
        else {
            const Network::PulRH1* dest = controller->GetReceivedPacketHolder<Network::PulRH1>(winnerAid)->packet;
            finalStats = reinterpret_cast<const Mgr::Stats::Final*>(&dest->timeInDanger);
        }
        if(finalStats->finalPercentageSum != 0) {
            this->status = HAS_STATS;
            this->timeRecvStats = this->duration;

            for(int i = 0; i < 3; ++i) {
                this->stats[i].isHidden = false;
                this->stats[i].SetTextBoxMessage("menu_text", UI::BMG_KO_AVERAGE_PERCENT_TITLE + i);
            }
            Text::Info info;
            info.intToPass[0] = finalStats->finalPercentageSum / (SectionMgr::sInstance->sectionParams->onlineParams.currentRaceNumber + 1);
            this->stats[0].SetTextBoxMessage("score", UI::BMG_PERCENT_RACE, &info);

            u16 framesDanger = finalStats->timeInDanger;
            u32 minutes = framesDanger / 3600;
            u32 remainingFrames = framesDanger - minutes * 3600;
            u32 seconds = remainingFrames / 60;
            remainingFrames = remainingFrames - seconds * 60;
            u32 milliseconds = remainingFrames * 1000 / 60;
            info.intToPass[0] = minutes;
            info.intToPass[1] = seconds;
            info.intToPass[2] = milliseconds;
            this->stats[1].SetTextBoxMessage("score", UI::BMG_DISPLAY_TIME, &info);
            info.intToPass[0] = finalStats->almostKOdCounter;
            this->stats[2].SetTextBoxMessage("score", UI::BMG_NUMBER_RACE, &info);

            this->DisplayWinner();
        }

    }

    const u32 duration = this->duration;
    if(status == HAS_STATS && duration - timeRecvStats == 600) {
        this->EndStateAnimated(0, 0.0f);
    }
    else if(status == WAITING_STATS) {
        if(duration == 600) {
            status = NO_STATS_TIME_ELAPSED;
            this->DisplayWinner();
        }
    }
    else if(status == NO_STATS_TIME_ELAPSED) {
        if(duration == 900) this->EndStateAnimated(0, 0.0f);
    }
}


void WinnerPage::HandleClick(u32 hudSlotId) {
    this->EndStateAnimated(0, 0.0f);
}

static PageId LoadCorrectPageAfterOnlineLdb(PageId ret) {
    const System* system = System::sInstance;
    if(system->IsContext(PULSAR_MODE_KO) && system->koMgr->winnerPlayerId != 0xFF) ret = static_cast<PageId>(WinnerPage::id);
    return ret;
}
kmBranch(0x8085cc70, LoadCorrectPageAfterOnlineLdb);

}//namespace KO
}//namespace Pulsar
