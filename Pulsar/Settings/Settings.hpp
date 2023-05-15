#ifndef _SETTINGS_
#define _SETTINGS_
#include <kamek.hpp>
#include <IO/File.hpp>
#include <SlotExpansion/CupsDef.hpp>
#include <PulsarSystem.hpp>



namespace Pulsar {
//Contains all the settings. 
enum SettingsType {
    SETTINGSTYPE_MENU,
    SETTINGSTYPE_RACE,
    SETTINGSTYPE_HOST
};

class SettingsHook : public DoFuncsHook {
    static DoFuncsHook* settingsHooks;
public:
    SettingsHook(Func& f) : DoFuncsHook(f, &settingsHooks) {}
    static void exec() { DoFuncsHook::exec(settingsHooks); }
};

struct TrackTrophy {
    u32 crc32;
    bool hastrophy[4];
};
struct Trophies {
    Trophies() : magic(tropMagic) {}
    u32 magic;
    u16 trophyCount[4];
    TrackTrophy trophies[1];
    static const u32 tropMagic = 'TROP';
};
namespace UI { class SettingsPanel; }

class Settings {
protected: //so that it can be inherited from
    class alignas(0x20) Binary {
        struct Page {
            union {
                struct {
                    u8 radioSetting[6];
                    u8 scrollSetting[6];
                };
                u8 settings[12];
            };
        };
        Binary(u32 curVersion) : magic(binMagic), version(curVersion) {}
        u32 magic;
        u32 version; //just in case more than 255 versions
        Page pages[3];
        u32 reserved[20];
        u32 trackCount;
        Trophies trophiesHolder;
        friend class Settings;
    };
    friend class System;
    friend class UI::SettingsPanel;

    static const u32 curVersion = 1;
    static const u32 binMagic = 'PULP';
    static Settings* sInstance;
    static void SaveTask(void*);
    virtual void Init(const u16* totalTrophyCount, const char* path);
    virtual int GetSettingsBinSize() const {
        return sizeof(Binary) - sizeof(TrackTrophy) + sizeof(TrackTrophy) * CupsDef::sInstance->GetEffectiveTrackCount();
    }
    char filePath[IOS::ipcMaxPath];
    Binary* rawBin;
private:
    u16 totalTrophyCount[4];
    TrackTrophy* FindTrackTrophy(u32 crc32, TTMode mode) const;
    void UpdateTrackList();
    void SetSettingValue(SettingsType type, u32 setting, u8 value);

public:
    Settings() : rawBin(nullptr) {}
    static Settings* GetInstance() { return sInstance; }
    void Update() {
        SettingsHook::exec();
        System::sInstance->taskThread->Request(&Settings::SaveTask, nullptr, 0);
    }
    void Save();

    void AddTrophy(u32 crc32, TTMode mode);
    bool HasTrophy(u32 crc32, TTMode mode) const;
    bool HasTrophy(PulsarId id, TTMode mode) const;
    u16 GetTotalTrophyCount(TTMode mode) const { return totalTrophyCount[mode]; }
    int GetTrophyCount(TTMode mode) const { return this->rawBin->trophiesHolder.trophyCount[mode]; }

    static u8 GetSettingValue(SettingsType type, u32 setting);
    static void Create();

};
}

//SETTINGS ENUM, for the page, DO NOT FORGET THE +6 for scrollers (see menu settings for example)
//Use these 3 for "u32 setting" in GetSettingValue, the return will be the value of the other enums
enum MenuSettings {
    SETTINGMENU_RADIO_FASTMENUS = 0,

    SETTINGMENU_SCROLL_BOOT = 0 + 6
};

enum RaceSettings {
    SETTINGRACE_RADIO_MII,
    SETTINGRACE_RADIO_SPEEDUP,
    SETTINGRACE_RADIO_BATTLE,
    SETTINGRACE_RADIO_BLUES
};

enum HostSettings {
    SETTINGHOST_RADIO_HOSTWINS = 0,
    SETTINGHOST_RADIO_CC = 1,

    SETTINGHOST_SCROLL_GP_RACES = 0 + 6
};

//INDIVIDUAL SETTINGS
enum MenuSettingFastMenus {
    MENUSETTING_FASTMENUS_DISABLED = 0x0,
    MENUSETTING_FASTMENUS_ENABLED = 0x1
};

enum MenuSettingBoot {
    MENUSETTING_BOOT_DISABLED,
    MENUSETTING_BOOT_L1,
    MENUSETTING_BOOT_L2,
    MENUSETTING_BOOT_L3,
    MENUSETTING_BOOT_L4
};

//RACE SETTINGS
enum RaceSettingMII {
    RACESETTING_MII_DISABLED = 0x0,
    RACESETTING_MII_ENABLED = 0x1
};

enum RaceSettingSPEEDUP {
    RACESETTING_SPEEDUP_DISABLED = 0x0,
    RACESETTING_SPEEDUP_ENABLED = 0x1
};

enum RaceSettingBATTLE {
    RACESETTING_BATTLE_GLITCH_DISABLED = 0x0,
    RACESETTING_BATTLE_GLITCH_ENABLED = 0x1
};

enum RaceSettingBLUES {
    RACESETTING_DRAGGABLE_BLUES_DISABLED = 0x0,
    RACESETTING_DRAGGABLE_BLUES_ENABLED = 0x1
};

//HOST SETTINGS
enum HostSettingHAW {
    HOSTSETTING_HOSTWINS_DISABLED,
    HOSTSETTING_HOSTWINS_ENABLED
};

enum HostSettingHostCC {
    HOSTSETTING_CC_NORMAL,
    HOSTSETTING_CC_150,
    HOSTSETTING_CC_100,
    HOSTSETTING_CC_MIRROR
};

enum HostSettingGPRACES {
    HOSTSETTING_GP_RACES_4,
    HOSTSETTING_GP_RACES_8,
    HOSTSETTING_GP_RACES_12,
    HOSTSETTING_GP_RACES_24,
    HOSTSETTING_GP_RACES_32,
    HOSTSETTING_GP_RACES_64,
    HOSTSETTING_GP_RACES_2,
    //space for a 7th setting is available
};

#endif