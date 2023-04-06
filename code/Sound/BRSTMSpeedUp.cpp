#include <kamek.hpp>
#include <game/Race/Kart/KartHolder.hpp>
#include <game/Sound/RSARSounds.hpp>
#include <game/Sound/RaceAudioManager.hpp>
#include <game/Sound/Actors/KartSound.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceGhostDiffTime.hpp>
#include <Settings/PlayerData.hpp>


/*Music speedup:
When the player reaches the final lap (if the track has >1 laps) and if the setting is set, the music will
speedup instead of transitioning to the _f file. The jingle will still play.
*/
void MusicSpeedup(RaceRSARSoundsPlayer *rsarSoundPlayer, u32 jingle, u32 r5) {
    static u8 hudSlotIdFinalLap;
    RaceAudioMgr *audio = RaceAudioMgr::sInstance;
    u8 maxLap = audio->maxLap;
    u8 curLap = audio->lap;
    u8 idFirstFinalLap = hudSlotIdFinalLap;
    if (maxLap == 1) return;
    if (maxLap == RaceData::sInstance->racesScenario.settings.lapCount) {
        if (PulsarSettings::GetInstance()->GetSettings()->pages[OPT_RACE_SETTINGS].radioSetting[OPT_RADIO_SPEEDUP] == OPT_RADIO_SPEEDUP_ENABLED) {
            RaceInfo *raceInfo = RaceInfo::sInstance;
            Timer *raceTimer = &raceInfo->timerManager->timers[0];
            Timer *playerTimer = &raceInfo->players[idFirstFinalLap]->lapSplits[maxLap - 2];
            Timer difference;
            CtrlRaceGhostDiffTime::SubtractTimers(difference, raceTimer, playerTimer);
            if (difference.minutes < 1 && difference.seconds < 5) {
                KartHolder::sInstance->GetKart(hudSlotIdFinalLap)->pointers.kartSound->soundArchivePlayer->soundPlayerArray
                    ->soundList.GetFirst()->ambientParam.pitch += 0.0002f;
            }
            if (maxLap != curLap) rsarSoundPlayer->PlaySound(0x74, r5);
        }
        else if ((maxLap != curLap) && (audio->raceState == 0x4 || audio->raceState == 0x6)) audio->ChangeMusic(RACE_STATE_FAST);
    }
    else if (maxLap != curLap) {
        rsarSoundPlayer->PlaySound(jingle, r5);
        hudSlotIdFinalLap = audio->playerIdFirstLocalPlayer;
    }
    return;
}
kmCall(0x8070b2f8, MusicSpeedup);
kmWrite32(0x8070b2c0, 0x60000000);
kmWrite32(0x8070b2d4, 0x60000000);