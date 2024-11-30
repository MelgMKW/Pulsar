#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceWifi.hpp>
#include <MarioKartWii/UI/Page/Other/Title.hpp>
#include <MarioKartWii/UI/Page/Other/Message.hpp>
#include <MarioKartWii/RKSYS/RKSYSMgr.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <PulsarSystem.hpp>
#include <AutoTrackSelect/ChooseNextTrack.hpp>
#include <Gamemodes/KO/KOMgr.hpp>
#include <Gamemodes/KO/KORaceEndPage.hpp>
#include <Debug/Debug.hpp>
#include <UI/UI.hpp>



namespace Pulsar {

namespace UI {
//No ghost saving on RKSYS
kmWrite32(0x8054913C, 0x60000000);
kmWrite32(0x80855f48, 0x48000148);

//BMG size patch (Diamond)
kmWrite32(0x8007B37C, 0x38000128);

static PageId AfterWifiResults(PageId id) {
    const SectionMgr* sectionMgr = SectionMgr::sInstance;
    const System* system = System::sInstance;

    if (system->IsContext(PULSAR_MODE_KO)) id = system->koMgr->KickPlayersOut(id); //return KO::RaceEndPage with the choice to spectate if the local players are out 
    if (id != static_cast<PageId>(KO::RaceEndPage::id) && system->IsContext(PULSAR_HAW)) {
        ChooseNextTrack* chooseNext = ExpSection::GetSection()->GetPulPage<ChooseNextTrack>();
        if (chooseNext != nullptr) id = chooseNext->GetPageAfterWifiResults(id);
    }
    return id;
}
kmBranch(0x80646754, AfterWifiResults);


//Credit to Kazuki for making the original ASM code, and Brawlbox for porting it to C++
static void LaunchRiivolutionButton(SectionMgr* sectionMgr) {
    const SectionId id = sectionMgr->nextSectionId;
    if (id == SECTION_CHANNEL_FROM_MENU || id == SECTION_CHANNEL_FROM_CHECK_RANKINGS || id == SECTION_CHANNEL_FROM_DOWNLOADS) Debug::LaunchSoftware();
    else sectionMgr->LoadSection();
}
kmCall(0x80553a60, LaunchRiivolutionButton);

//Top left message when a race is about to start in a froom
static void FixStartMessageFroom(CtrlRaceWifiStartMessage* startMsg, u32 bmgId, Text::Info* info) {
    const SectionMgr* sectionMgr = SectionMgr::sInstance;
    const SectionId id = sectionMgr->curSection->sectionId;
    if (id == SECTION_P1_WIFI_FRIEND_VS || id == SECTION_P1_WIFI_FRIEND_TEAMVS
        || id == SECTION_P2_WIFI_FRIEND_VS || id == SECTION_P2_WIFI_FRIEND_TEAMVS) {
        const System* system = System::sInstance;
        const u32 raceNumber = sectionMgr->sectionParams->onlineParams.currentRaceNumber + 1;
        bmgId = BMG_GP_RACE;
        if (system->IsContext(PULSAR_MODE_KO)) {
            const KO::Mgr* koMgr = system->koMgr;
            const u32 playerCount = system->nonTTGhostPlayersCount;
            u32 koCount = 0;
            if (playerCount == 2) koCount = 1;
            else if (raceNumber % koMgr->racesPerKO == 0) {
                const u32 koPerRace = koMgr->koPerRace;
                if (playerCount - koPerRace > 1) koCount = koPerRace; //eliminating the setting's amount of players, does not lead in a potential final
                else koCount = playerCount - (1 + koMgr->alwaysFinal); //check if the setting is on, if it is, leave 2 players, otherwise, leave 1 player/the ko count is the complement
            }
            bmgId = BMG_KO_ELIM_START_NONE + koCount;
        }
        info->intToPass[0] = raceNumber;
        info->intToPass[1] = system->netMgr.racesPerGP + 1;
    }
    startMsg->SetMessage(bmgId, info);
}
kmCall(0x807f8b7c, FixStartMessageFroom);

static void DisplayDate(CtrlMenuPressStart* start) {
    start->Load();
    start->SetMessage(BMG_DATE);
}
kmCall(0x8063ac58, DisplayDate);

static void CustomRoomDenyText(Pages::MessageBoxTransparent* msgBox, u32 bmgId, const Text::Info* info) {
    if (Pulsar::System::sInstance->netMgr.denyType == Network::DENY_TYPE_BAD_PACK) bmgId = BMG_ROOM_DENY;
    msgBox->SetMessageWindowText(bmgId, info);
}
kmCall(0x805dd90c, CustomRoomDenyText);

SectionParams& FavouriteCombo(SectionParams& params) {
    const RKSYS::Mgr* rksysMgr = RKSYS::Mgr::sInstance;
    s32 curLicense = rksysMgr->curLicenseId;
    if (curLicense >= 0) {
        const RKSYS::LicenseMgr& license = rksysMgr->licenses[curLicense];
        CharacterId favChar = license.GetFavouriteCharacter();
        KartId favKart = license.GetFavouriteKart();

        const s32 charWeight = GetCharacterWeightClass(favChar);
        const s32 kartWeight = GetKartWeightClass(favKart);
        if (kartWeight != -1) {
            if (charWeight == -1 || charWeight != kartWeight) {
                switch (kartWeight) {
                case 0:
                    favChar = BABY_DAISY;
                    break;
                case 1:
                    favChar = DAISY;
                    break;
                case 2:
                    favChar = FUNKY_KONG;
                }
            }
            params.characters[0] = favChar;
            params.karts[0] = favKart;
            params.combos[0].selCharacter = favChar;
            params.combos[0].selKart = favKart;
        }
    }

    return params;
}
kmBranch(0x805e4228, FavouriteCombo);

u8 ModifyCheckRankings() {
    register Pages::RaceMenu* ttEnd;
    asm(mr ttEnd, r28;);
    register float animLength;
    asm(fmr animLength, f31;);
    ttEnd->ChangeSectionBySceneChange(SECTION_P1_WIFI, 0, animLength);
    return 0;
    //ttEnd->EndStateAnimated(0, animLength);

}
kmCall(0x8085b4bc, ModifyCheckRankings);
kmPatchExitPoint(ModifyCheckRankings, 0x8085bbe0);


}//namespace UI
}//namespace Pulsar