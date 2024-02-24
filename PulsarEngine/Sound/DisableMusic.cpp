#include <kamek.hpp>
#include <MarioKartWii/Sound/Other/AudioValues.hpp>
#include <Settings/Settings.hpp>
#include <Settings/UI/SettingsPanel.hpp>


namespace OptPack {
namespace Audio {
void SetMusicState(){
        SoundPlayersVolumeMgr::sInstance->volumes[0].curValue = 1;
        if (Pulsar::Settings::Mgr::GetSettingValue(Pulsar::Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_DISABLEMUSIC)){
            SoundPlayersVolumeMgr::sInstance->volumes[0].curValue = 0;
        }
    }
    kmBranch(0x80710ba8, SetMusicState);//menu music
    kmBranch(0x80715c38, SetMusicState);//menu music
    kmBranch(0x80715e60, SetMusicState); //ingame music
    kmBranch(0x8070f598, SetMusicState); //wifi-music
    Pulsar::Settings::Hook PatchMusicInstantly(SetMusicState);
} // namespace Audio
} // namespace OptPack