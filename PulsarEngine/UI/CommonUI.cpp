#include <kamek.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>
#include <MarioKartWii/UI/Page/Other/TTSplits.hpp>
#include <MarioKartWii/UI/Page/Menu/MultiDriftSelect.hpp>
#include <MarioKartWii/UI/Page/Other/VR.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <PulsarSystem.hpp>
#include <Gamemodes/OnlineTT/OnlineTT.hpp>
#include <Gamemodes/KO/KOMgr.hpp>
#include <Gamemodes/KO/KORaceEndPage.hpp>
#include <Network/PulSELECT.hpp>
#include <Network/PacketExpansion.hpp>
#include <AutoTrackSelect/ChooseNextTrack.hpp>

namespace Pulsar {
//For hooks which are shared by different things
namespace UI {

PageId TTSplitsGetNextPage(const Pages::TTSplits& splits) {
    const bool isOTT = System::sInstance->IsContext(PULSAR_MODE_OTT);

    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(isOTT || sectionId == SECTION_GP) return PAGE_GPVS_LEADERBOARD_UPDATE;
    else if(sectionId == SECTION_TT || sectionId == SECTION_GHOST_RACE_1 || sectionId == SECTION_GHOST_RACE_2) return PAGE_TT_LEADERBOARDS;
    else if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) return PAGE_GHOST_REPLAY_PAUSE_MENU; //Enhanced Replay
    return PAGE_NONE;
}
kmBranch(0x808561dc, TTSplitsGetNextPage);

void LoadCorrectPageAfterMultiDrift(Pages::MultiDriftSelect* page, u32 animDirection, float animLength) {
    page->EndStateAnimated(animLength, animDirection);
    System* system = System::sInstance;
    SectionMgr* sectionMgr = SectionMgr::sInstance;
    if(system->ottVoteState == OTT::COMBO_SELECTION) {
        system->ottVoteState = OTT::COMBO_SELECTED;
        Network::ExpSELECTHandler& handler = Network::ExpSELECTHandler::Get();
        for(int i = 0; i < 2; ++i) {
            handler.toSendPacket.playersData[i].character = sectionMgr->sectionParams->characters[i];
            handler.toSendPacket.playersData[i].kart = sectionMgr->sectionParams->karts[i];
        }
        handler.toSendPacket.allowChangeComboStatus = Network::SELECT_COMBO_SELECTED;
    }
    else if(sectionMgr->curSection->Get<Pages::VR>() != nullptr) {
        page->nextPageId = IsBattle() ? PAGE_BATTLE_CUP_SELECT : PAGE_CUP_SELECT;
    }
}
kmCall(0x8084b68c, LoadCorrectPageAfterMultiDrift);

//if more custom racemenus added in pulsar, make the func virtual
void RaceMenuExtraControls(Pages::RaceMenu& page, u32 gameControlCount) {

    const SectionId curSectionId = SectionMgr::sInstance->curSection->sectionId;
    if(curSectionId >= SECTION_P1_WIFI_FRIEND_VS || curSectionId >= SECTION_P2_WIFI_FRIEND_COIN) {
        if(page.pageId == ChooseNextTrack::fakeId) return static_cast<ChooseNextTrack&>(page).InitExtraControls(gameControlCount);
        else if(page.pageId == KO::RaceEndPage::fakeId) return static_cast<KO::RaceEndPage&>(page).InitExtraControls(gameControlCount);
    }
    page.InitControlGroup(gameControlCount);
}
kmCall(0x80858ebc, RaceMenuExtraControls);
}//namespace UI

}//namespace Pulsar