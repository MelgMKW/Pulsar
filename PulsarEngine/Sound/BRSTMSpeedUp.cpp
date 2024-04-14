#include <kamek.hpp>
#include <MarioKartWii/Kart/KartManager.hpp>
#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <MarioKartWii/Audio/RSARPlayer.hpp>
#include <MarioKartWii/Audio/RaceMgr.hpp>
#include <MarioKartWii/Audio/Actors/KartActor.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceGhostDiffTime.hpp>
#include <Settings/Settings.hpp>


/*Music speedup:
When the player reaches the final lap (if the track has >1 laps) and if the setting is set, the music will
speedup instead of transitioning to the _f file. The jingle will still play.
*/

namespace Pulsar {
namespace Sound {

using namespace nw4r;
static void MusicSpeedup(Audio::RaceRSARPlayer* rsarSoundPlayer, u32 jingle, u8 hudSlotId) {
    //static u8 hudSlotIdFinalLap;

    u8 isSpeedUp = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_RACE, SETTINGRACE_RADIO_SPEEDUP);
    Audio::RaceMgr* raceAudioMgr = Audio::RaceMgr::sInstance;
    const u8 maxLap = raceAudioMgr->maxLap;
    const u8 curLap = raceAudioMgr->lap;
    const RacedataSettings& raceDataSettings = RaceData::sInstance->racesScenario.settings;
    //const u8 idFirstFinalLap = hudSlotIdFinalLap;
    if(maxLap == 1) return;
    if(maxLap == raceDataSettings.lapCount) {

        register Audio::KartActor* kartActor;
        asm(mr kartActor, r29;);
        snd::detail::BasicSound& sound =  kartActor->soundArchivePlayer->soundPlayerArray[0].soundList.GetFront();
        if(isSpeedUp == RACESETTING_SPEEDUP_ENABLED || sound.soundId == SOUND_ID_GALAXY_COLOSSEUM) {
            const RaceInfo* raceInfo = RaceInfo::sInstance;
            const Timer& raceTimer = raceInfo->timerMgr->timers[0];
            const Timer& playerTimer = raceInfo->players[raceDataSettings.hudPlayerIds[hudSlotId]]->lapSplits[maxLap - 2];
            const Timer difference = CtrlRaceGhostDiffTime::SubtractTimers(raceTimer, playerTimer);
            if(difference.minutes < 1 && difference.seconds < 5) {
                sound.ambientParam.pitch += 0.0002f;
            }
            if(maxLap != curLap) rsarSoundPlayer->PlaySound(SOUND_ID_FINAL_LAP, hudSlotId);
        }
        else if((maxLap != curLap) && (raceAudioMgr->raceState == 0x4 || raceAudioMgr->raceState == 0x6)) {
            raceAudioMgr->SetRaceState(Audio::RACE_STATE_FAST);
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