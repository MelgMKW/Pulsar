#include <kamek.hpp>
#include <core/nw4r/snd.hpp>
#include <MarioKartWii/Audio/RaceMgr.hpp>
#include <MarioKartWii/Audio/RSARPlayer.hpp>
#include <Sound/MiscSound.hpp>
#include <Settings/Settings.hpp>

namespace Pulsar {
namespace Sound {
using namespace nw4r;

//RaceAudioMgr SetRaceState patch that skips the entire func, effectively disabling the mgr
static void DisableRaceMusic(Audio::SinglePlayer& singlePlayer, u32 soundId, s16 delay) {
    const bool isEnabled = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_MUSIC) == MENUSETTING_MUSIC_DEFAULT;
    if(isEnabled) singlePlayer.PlaySound(soundId, delay);
}
kmCall(0x80711fcc, DisableRaceMusic); //RaceMgr::SetRaceState
kmCall(0x80711df4, DisableRaceMusic); //RaceMgr::SetRaceState
kmCall(0x80712198, DisableRaceMusic); //RaceMgr::SetRaceState
kmCall(0x80711074, DisableRaceMusic); //RaceMgr::SetRaceState
kmCall(0x8064a398, DisableRaceMusic); //wifi waiting, hook at Page::LiveViewWaiting
kmCall(0x8064a340, DisableRaceMusic); //wifi waiting

static void PreventPrepareRaceMusic(u32 unused, Audio::Handle* handle, u32 soundId) {
    const bool isEnabled = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_MUSIC) == MENUSETTING_MUSIC_DEFAULT;
    if(isEnabled) Audio::Manager::sInstance->PrepareSound(handle, soundId);
}
kmCall(0x806f8eb4, PreventPrepareRaceMusic);

static void DisableMenuMusic(Audio::SinglePlayer& singlePlayer, u32 soundId, s16 delay) {
    const bool isEnabled = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_MUSIC) != MENUSETTING_MUSIC_DISABLE_ALL;
    if(isEnabled) singlePlayer.PlaySound(soundId, delay);
}
kmCall(0x806fa64c, DisableMenuMusic);
kmCall(0x806fa664, DisableMenuMusic);

static void ToggleMenuMusic() {
    const bool isEnabled = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_MUSIC) != MENUSETTING_MUSIC_DISABLE_ALL;
    Audio::SinglePlayer* singlePlayer = Audio::SinglePlayer::sInstance;
    if(isEnabled) singlePlayer->PlayBGSound(2);
    else singlePlayer->StopSound();
}
Settings::Hook ToggleMenuMusicHook(ToggleMenuMusic);


snd::SoundStartable::StartResult PlayExtBRSEQ(snd::SoundStartable& startable, Audio::Handle& handle, const char* fileName, const char* labelName, bool hold) {
    snd::SoundStartable::StartInfo startInfo;
    startInfo.seqSoundInfo.startLocationLabel = labelName;
    startInfo.enableFlag |= snd::SoundStartable::StartInfo::ENABLE_SEQ_SOUND_INFO;

    void* file = ArchiveRoot::sInstance->GetFile(ARCHIVE_HOLDER_COMMON, fileName);
    if(file != nullptr) {
        startInfo.seqSoundInfo.seqDataAddress = file;
        if(hold) return startable.detail_HoldSound(&handle, SOUND_ID_MINITURBO, &startInfo);
        else return startable.detail_StartSound(&handle, SOUND_ID_MINITURBO, &startInfo);
    }
    return snd::SoundStartable::START_ERR_USER;
}

//disable TF music delay
kmWrite16(0x80711FE8, 0x00004800);
kmWrite16(0x80712024, 0x00004800);
kmWrite16(0x8071207C, 0x00004800);
kmWrite16(0x807120B8, 0x00004800);

//disable tf music reset
kmWrite32(0x80719920, 0x48000010);

//disable THP and demo by blring SinglePlayer::CalcTitlePageNext
kmWrite32(0x806fa738, 0x4e800020);
}//namespace Audio
}//namespace Pulsar
