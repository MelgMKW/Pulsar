#include <kamek.hpp>
#include <game/Kart/KartManager.hpp>
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

void MusicSpeedup(RaceRSARSoundsPlayer* rsarSoundPlayer, u32 jingle, u8 hudSlotId) {
    //static u8 hudSlotIdFinalLap;

    u8 isSpeedUp = Settings::GetSettingValue(SETTINGSTYPE_RACE, SETTINGRACE_RADIO_SPEEDUP);
    RaceAudioMgr* raceAudioMgr = RaceAudioMgr::sInstance;
    const u8 maxLap = raceAudioMgr->maxLap;
    const u8 curLap = raceAudioMgr->lap;
    //const u8 idFirstFinalLap = hudSlotIdFinalLap;
    if(maxLap == 1) return;
    if(maxLap == RaceData::sInstance->racesScenario.settings.lapCount) {
        if(isSpeedUp == RACESETTING_SPEEDUP_ENABLED) {
            const RaceInfo* raceInfo = RaceInfo::sInstance;
            const Timer& raceTimer = raceInfo->timerMgr->timers[0];
            const Timer& playerTimer = raceInfo->players[hudSlotId]->lapSplits[maxLap - 2];
            const Timer difference = CtrlRaceGhostDiffTime::SubtractTimers(raceTimer, playerTimer);
            if(difference.minutes < 1 && difference.seconds < 5) {
                register KartSound* kartSound;
                asm(mr kartSound, r29;);
                kartSound->soundArchivePlayer->soundPlayerArray[0].soundList.GetFront().ambientParam.pitch += 0.0002f;
            }
            if(maxLap != curLap) rsarSoundPlayer->PlaySound(SOUND_ID_FINAL_LAP, hudSlotId);
        }
        else if((maxLap != curLap) && (raceAudioMgr->raceState == 0x4 || raceAudioMgr->raceState == 0x6)) {
            raceAudioMgr->SetRaceState(RACE_STATE_FAST);
        }
    }
    else if(maxLap != curLap) {
        rsarSoundPlayer->PlaySound(SOUND_ID_NORMAL_LAP, hudSlotId);
        //hudSlotIdFinalLap = raceAudioMgr->playerIdFirstLocalPlayer;
    }
    return;
}
kmCall(0x8070b2f8, MusicSpeedup);
kmWrite32(0x8070b2c0, 0x60000000);
kmWrite32(0x8070b2d4, 0x60000000);

}//namespace Audio
}//namespace Pulsar