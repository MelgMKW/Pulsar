#include <kamek.hpp>
#include <core/nw4r/snd.hpp>
#include <MarioKartWii/Audio/RaceMgr.hpp>
#include <MarioKartWii/Audio/RSARPlayer.hpp>
#include <MarioKartWii/Audio/Other/AudioStreamsMgr.hpp>
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

static void DisableAndChangeBGMusic(Audio::SinglePlayer& singlePlayer, u32 soundId) {
    const bool isEnabled = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_MUSIC) != MENUSETTING_MUSIC_DISABLE_ALL;
    if(isEnabled) {
        if(soundId == SOUND_ID_WIFI_MUSIC) {
            s32 entryNum = DVDConvertPathToEntryNum(wifiMusicFile);
            if(entryNum >= 0) {
                soundId = SOUND_ID_KC;
                singlePlayer.PrepareSound(soundId, false); //needed so that the streamsMgr has its internal handle set
            }
        }
        else if(soundId == SOUND_ID_OFFLINE_MENUS) {
            s32 entryNum = DVDConvertPathToEntryNum(wifiMusicFile);
            if(entryNum >= 0) {
                soundId = SOUND_ID_KC;
                singlePlayer.PrepareSound(soundId, false); //needed so that the streamsMgr has its internal handle set
            }
        }
        singlePlayer.PlaySound(soundId, 0);
    }
}
kmCall(0x806fa664, DisableAndChangeBGMusic);

static snd::SoundArchive::SoundType PatchPrepareStreamsBG(snd::SoundArchive& archive, u32 soundId) {

    if(soundId == SOUND_ID_KC) {
        const SectionId section = SectionMgr::sInstance->curSection->sectionId;

        u8 type = 0;
        if(section >= SECTION_SINGLE_P_FROM_MENU && section <= SECTION_SINGLE_P_LIST_RACE_GHOST || section == SECTION_LOCAL_MULTIPLAYER) type = 1;
        else if(section >= SECTION_P1_WIFI && section <= SECTION_P2_WIFI_FROOM_COIN_VOTING) type = 2;
        if(type != 0) {
            register Audio::StreamsMgr* streams;
            asm(mr streams, r30;);
            snd::StrmSoundHandle strmHandle(streams->curHandle);
            for(int i = 0; i < 4; ++i) {
                float volume = 0.0f;
                if((type == 2 && (i % 3) != 0) || (type == 1 && i == 0)) volume = 1.0f;
                streams->streamsVolume[i].curValue = volume;
                strmHandle.SetTrackVolume(1 << i, volume);
            }
            return snd::SoundArchive::SOUND_TYPE_INVALID;
        }
    }
    return archive.GetSoundType(soundId);
}
kmCall(0x806fa2fc, PatchPrepareStreamsBG);

static void ToggleMenuMusic() {
    const bool isEnabled = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_MUSIC) != MENUSETTING_MUSIC_DISABLE_ALL;
    Audio::SinglePlayer* singlePlayer = Audio::SinglePlayer::sInstance;
    if(isEnabled) singlePlayer->PlayBGSound(2);
    else singlePlayer->StopSound();
}
Settings::Hook ToggleMenuMusicHook(ToggleMenuMusic);

static float CheckFanfare(const Audio::SinglePlayer& singlePlayer) {
    const bool isEnabled = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_MUSIC) == MENUSETTING_MUSIC_DEFAULT;
    if(isEnabled) return singlePlayer.GetFanfareLength();
    else return -1.0f;
}
kmCall(0x80857860, CheckFanfare);

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
