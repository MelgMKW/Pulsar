#include <kamek.hpp>
#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <MarioKartWii/Kart/KartManager.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>
#include <PulsarSystem.hpp>
#include <Info.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <Settings/Settings.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <SlotExpansion/CupsConfig.hpp>

namespace OptPack{
namespace Race{

static void UpdateTimer(){
    if (!Pulsar::CupsConfig::IsRegsSituation() && !IsBattle() && Pulsar::Info::IsFeather()) {
        for (int i = 0; i < GetLocalPlayerCount(); i++)
        {
            RaceData* raceData = RaceData::sInstance;
            RaceInfo* raceInfo = RaceInfo::sInstance;
            u32 playerId = raceData->GetPlayerIdOfLocalPlayer(i);
            Kart::Player *player = Kart::Manager::sInstance->GetKartPlayer(playerId);
            float currentRaceCompletion = raceInfo->players[playerId]->raceCompletion;
            RaceStage stage = raceInfo->stage;
            if(raceData->menusScenario.settings.gamemode != MODE_TIME_TRIAL){
                // if the race has not started, we do not want the timer to be changed from -1 (globally)
                if (stage >= RACESTAGE_RACE){
                    if (currentRaceCompletion <= Pulsar::System::sInstance->lastRaceCompletion[playerId]){
                        // if the race is over, we do not want them to be respawned (on per player basis)
                        if ((raceInfo->players[playerId]->stateFlags & 0x2) == 0x2){
                            Pulsar::System::sInstance->noRaceProgressionTimer[playerId] = -1;
                        }
                        // if someone has fallen off, we want their timer reset
                        else if((player->link.pointers->kartStatus->bitfield0 & 0x10) == 0x10 && Pulsar::System::sInstance->noRaceProgressionTimer[playerId] != -1){
                            Pulsar::System::sInstance->noRaceProgressionTimer[i] = 720;
                        }
                        // if someone is getting combo'd we don't want them to respawn, hence the damage check
                        else if (Pulsar::System::sInstance->noRaceProgressionTimer[playerId] > 0
                        && Pulsar::System::sInstance->noRaceProgressionTimer[playerId] != -1
                        && (player->link.pointers->kartStatus->bitfield1 & 0x1) != 0x1
                        ){
                            --Pulsar::System::sInstance->noRaceProgressionTimer[playerId];
                        }
                        else if (Pulsar::System::sInstance->noRaceProgressionTimer[playerId] == 0){
                            player->link.pointers->kartCollision->ActivateOob(1, 0, 0, 0);
                            --Pulsar::System::sInstance->noRaceProgressionTimer[playerId];
                        }
                    }
                    else{
                        Pulsar::System::sInstance->noRaceProgressionTimer[playerId] = 600;
                    }
                    Pulsar::System::sInstance->lastRaceCompletion[playerId] = currentRaceCompletion;  
                }
            }
        }
    }
}
static RaceFrameHook UpdateRaceProgTimerHook(UpdateTimer);

static void ResetTimer(){
    if (!Pulsar::CupsConfig::IsRegsSituation() && Pulsar::Info::IsFeather()){
        for (int i = 0; i < 4; i++)Pulsar::System::sInstance->noRaceProgressionTimer[i] = -1;
    }
}
static RaceLoadHook ResetRaceProgTimerHook(ResetTimer);

} // namespace Race
} // namespace OptPack