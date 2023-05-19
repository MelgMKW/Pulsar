#include <kamek.hpp>
#include <game/Race/Kart/KartHolder.hpp>
#include <game/Race/RaceInfo/RaceInfo.hpp>
#include <game/Sound/RSARSounds.hpp>
#include <game/Sound/RaceAudioMgr.hpp>
#include <game/Sound/Actors/KartSound.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceGhostDiffTime.hpp>
#include <Settings/Settings.hpp>


/*Music speedup:
When the player reaches the final lap (if the track has >1 laps) and if the setting is set, the music will
speedup instead of transitioning to the _f file. The jingle will still play.
*/

namespace Pulsar {
namespace Audio {

void MusicSpeedup(RaceRSARSoundsPlayer* rsarSoundPlayer, u32 jingle, u32 r5) {
    static u8 hudSlotIdFinalLap;
    RaceAudioMgr* audio = RaceAudioMgr::sInstance;
    const u8 maxLap = audio->maxLap;
    const u8 curLap = audio->lap;
    const u8 idFirstFinalLap = hudSlotIdFinalLap;
    if(maxLap == 1) return;
    if(maxLap == RaceData::sInstance->racesScenario.settings.lapCount) {
        if(Settings::GetSettingValue(SETTINGSTYPE_RACE, SETTINGRACE_RADIO_SPEEDUP) == RACESETTING_SPEEDUP_ENABLED) {
            const RaceInfo* raceInfo = RaceInfo::sInstance;
            const Timer& raceTimer = raceInfo->timerMgr->timers[0];
            const Timer& playerTimer = raceInfo->players[idFirstFinalLap]->lapSplits[maxLap - 2];
            const Timer difference = CtrlRaceGhostDiffTime::SubtractTimers(raceTimer, playerTimer);
            if(difference.minutes < 1 && difference.seconds < 5) {
                KartHolder::sInstance->GetKart(hudSlotIdFinalLap)->pointers.kartSound->soundArchivePlayer->soundPlayerArray
                    ->soundList.GetFirst()->ambientParam.pitch += 0.0002f;
            }
            if(maxLap != curLap) rsarSoundPlayer->PlaySound(0x74, r5);
        }
        else if((maxLap != curLap) && (audio->raceState == 0x4 || audio->raceState == 0x6)) audio->ChangeMusic(RACE_STATE_FAST);
    }
    else if(maxLap != curLap) {
        rsarSoundPlayer->PlaySound(jingle, r5);
        hudSlotIdFinalLap = audio->playerIdFirstLocalPlayer;
    }
    return;
}
kmCall(0x8070b2f8, MusicSpeedup);
kmWrite32(0x8070b2c0, 0x60000000);
kmWrite32(0x8070b2d4, 0x60000000);

}//namespace Audio
}//namespace Pulsar