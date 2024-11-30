#include <MarioKartWii/RKNet/SELECT.hpp>
#include <MarioKartWii/RKNet/ITEM.hpp>
#include <MarioKartWii/3D/Camera/CameraMgr.hpp>

#include <MarioKartWii/UI/Page/Other/SELECTStageMgr.hpp>
#include <MarioKartWii/UI/Page/Other/VR.hpp>
#include <MarioKartWii/UI/Page/Other/Votes.hpp>
#include <MarioKartWii/UI/Page/Leaderboard/GPVSLeaderboardTotal.hpp>
#include <MarioKartWii/UI/Page/Other/WifiVSResults.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceRankNum.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceItemWindow.hpp>
#include <MarioKartWii/Race/Raceinfo/Raceinfo.hpp>
#include <MarioKartWii/Kart/KartManager.hpp>
#include <Network/PacketExpansion.hpp>
#include <Gamemodes/KO/KOMgr.hpp>
#include <Gamemodes/KO/KORaceEndPage.hpp>
#include <Gamemodes/KO/KOWinnerPage.hpp>

namespace Pulsar {
namespace KO {

//Replicate SetModeTypes here: CC not needed, 
void HAWChangeData() {
    const System* system = System::sInstance;
    RKNet::Controller* controller = RKNet::Controller::sInstance;
    RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
    const u8 localAid = sub.localAid;
    if(system->IsContext(PULSAR_MODE_KO)) {
        u8 oldAidsBelonging[12];
        u8 oldPlayerIds[12][2];
        //u8 oldPlayerIds[12];
        //memset(oldPlayerIds, 0xFF, sizeof(u8) * 12);

        Mgr* mgr = system->koMgr;
        mgr->PatchAids(sub);
        int inCounter = 0;
        int koCounter = 0;
        for(int i = 0; i < 12; ++i) {
            oldAidsBelonging[i] = controller->aidsBelongingToPlayerIds[i];
            controller->aidsBelongingToPlayerIds[i] = 0xff;
        }
        for(int aid = 0; aid < 12; ++aid) {
            if((1 << aid & sub.availableAids) != 0)
            {
                controller->aidsBelongingToPlayerIds[inCounter] = aid;
                ++inCounter;
                const u8 hudCount = aid == sub.localAid ? sub.localPlayerCount : sub.connectionUserDatas[aid].playersAtConsole;
                if(hudCount == 2) {
                    controller->aidsBelongingToPlayerIds[inCounter] = aid;
                    ++inCounter;
                }
            }
        }
        for(int playerId = 0; playerId < 12; ++playerId) {
            u8 aid = oldAidsBelonging[playerId];
            u8 hudSlotId = 0;
            if(playerId != 0 && oldAidsBelonging[playerId - 1] == aid) hudSlotId = 1;
            oldPlayerIds[aid][hudSlotId] = playerId;
        }



        Racedata* racedata = Racedata::sInstance;
        SectionMgr* sectionMgr = SectionMgr::sInstance;
        SectionParams* params = sectionMgr->sectionParams;
        //Swap guest and main if needed
        if(sub.localPlayerCount == 2 && !mgr->IsKOdAid(localAid, 0) && !mgr->GetIsSwapped()) mgr->SwapControllersAndUI();

        //update racedataPlayers and miis
        for(int playerId = 0; playerId < 12; ++playerId) {

            RacedataPlayer& player = racedata->menusScenario.players[playerId];
            const u8 aid = controller->aidsBelongingToPlayerIds[playerId];

            if(aid >= 12) {
                player.playerType = PLAYER_NONE;
                params->onlineParams.regionId[playerId] = 0xF;
                //params->playerMiis.DeleteMii(playerId);
            }
            else {
                u8 hudSlotId = 0;
                if(playerId != 0 && controller->aidsBelongingToPlayerIds[playerId - 1] == aid) hudSlotId = 1;
                const u8 oldPlayerId = oldPlayerIds[aid][hudSlotId];
                const RacedataPlayer& prev = racedata->menusScenario.players[oldPlayerId];
                memcpy(&player, &prev, sizeof(RacedataPlayer));
                if(aid == localAid) player.playerType = PLAYER_REAL_LOCAL;
                else player.playerType = PLAYER_REAL_ONLINE;
                MiiGroup& playerMiis = params->playerMiis;
                playerMiis.mii[playerId] = playerMiis.mii[oldPlayerId];
                for(int i = 0; i < 7; ++i) {
                    MiiTexObj* tex = playerMiis.texObj[i];
                    if(tex != nullptr) memcpy(&tex[playerId], &tex[oldPlayerId], sizeof(MiiTexObj));
                }
                //params->playerMiis.AddMii(playerId, &player.mii);
            }
        }
        const SectionId next = sectionMgr->nextSectionId;
        if(sub.localPlayerCount == 1 && (next == SECTION_P2_WIFI_FRIEND_VS || next == SECTION_P2_WIFI_FRIEND_VS)) {
            sectionMgr->nextSectionId = static_cast<SectionId>(next - 4);
        }

        if(mgr->isSpectating) racedata->menusScenario.settings.gametype = GAMETYPE_ONLINE_SPECTATOR;

    }
}
}//namespace KO
}//namespace Pulsar