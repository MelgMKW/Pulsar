#ifndef _SETTINGS_PARAMS_
#define _SETTINGS_PARAMS_
#include <kamek.hpp>
#include <PulsarSystem.hpp>
#include <Config.hpp>

namespace Pulsar {
namespace UI { class SettingsPanel; }
namespace Settings {

class Params {
public:
    static const int pulsarPageCount = 5;
    static const int userPageCount = 0;
    static const int pageCount = pulsarPageCount + userPageCount;

    static const int maxRadioCount = 6; //per page, due to space
    static const int maxScrollerCount = 5; //per page, due to space

    //Pulsar and User
    static u8 radioCount[pageCount];
    static u8 scrollerCount[pageCount];
    static u8 buttonsPerPagePerRow[pageCount][maxRadioCount];
    static u8 optionsPerPagePerScroller[pageCount][maxScrollerCount];

};

//Contains all the settings. 
enum Type {
    SETTINGSTYPE_MENU,
    SETTINGSTYPE_RACE,
    SETTINGSTYPE_HOST,
    SETTINGSTYPE_OTT,
    SETTINGSTYPE_KO,
};

//If you want to add settings to your packs, they go in this enum, and GetUserSettingValue should be used to obtain the value of a given setting
enum UserType {

};

}//namespace Settings

//SETTINGS ENUM, for the page, DO NOT FORGET THE +6 for scrollers (see menu settings for example)
//Use these 3 for "u32 setting" in GetSettingValue, the return will be the value of the other enums
enum MenuSettings {
    SETTINGMENU_RADIO_FASTMENUS = 0,
    SETTINGMENU_RADIO_LAYOUT = 1,
    SETTINGMENU_RADIO_MUSIC = 2,
    SETTINGMENU_SCROLL_BOOT = 0 + 6
};

enum RaceSettings {
    SETTINGRACE_RADIO_MII,
    SETTINGRACE_RADIO_SPEEDUP,
    SETTINGRACE_RADIO_BATTLE,
    SETTINGRACE_RADIO_BLUES,
    SETTINGRACE_RADIO_SOM,

    SETTINGRACE_SCROLL_SOM = 0 + 6
};

enum HostSettings {
    SETTINGHOST_RADIO_HOSTWINS = 0,
    SETTINGHOST_RADIO_CC = 1,
    SETTINGHOST_ALLOW_MIIHEADS = 2,

    SETTINGHOST_SCROLL_GP_RACES = 0 + 6
};

enum OTTSettings {
    SETTINGOTT_ONLINE = 0,
    SETTINGOTT_OFFLINE = 1,
    SETTINGOTT_ALLOWCHANGECOMBO = 2,
    SETTINGOTT_ALLOWUMTS = 3,
    SETTINGOTT_MUTEPTANDPLAYERS = 4,
};

enum KOSettings {
    SETTINGKO_ENABLED = 0,
    SETTINGKO_FINAL = 1,
    SETTINGKO_KOPERRACE = 0 + 6,
    SETTINGKO_RACESPERKO = 1 + 6,

};

//MENU SETTINGS
enum MenuSettingFastMenus {
    MENUSETTING_FASTMENUS_DISABLED = 0x0,
    MENUSETTING_FASTMENUS_ENABLED = 0x1
};

enum MenuSettingLayout {
    MENUSETTING_LAYOUT_DEFAULT = 0x0,
    MENUSETTING_LAYOUT_ALPHABETICAL = 0x1
};

enum MenuSettingMusic {
    MENUSETTING_MUSIC_DEFAULT = 0x0,
    MENUSETTING_MUSIC_DISABLE_ALL = 0x1,
    MENUSETTING_MUSIC_DISABLE_RACE = 0x2
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

enum RaceSettingSOM {
    RACESETTING_SOM_LEFT = 0x0,
    RACESETTING_SOM_RIGHT = 0x1,
    RACESETTING_SOM_DISABLED = 0x2
};

enum RaceSettingSOMDigits {
    HOSTSETTING_SOM_DIGITS_0,
    HOSTSETTING_SOM_DIGITS_1,
    HOSTSETTING_SOM_DIGITS_2,
    HOSTSETTING_SOM_DIGITS_3,
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

enum HostSettingMiiHeads {
    HOSTSETTING_ALLOW_MIIHEADS_ENABLED,
    HOSTSETTING_ALLOW_MIIHEADS_DISABLED
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

//OTTSETTINGS
enum OTTSettingOnline {
    OTTSETTING_ONLINE_DISABLED,
    OTTSETTING_ONLINE_NORMAL,
    OTTSETTING_ONLINE_FEATHER,
};

enum OTTSettingOffline {
    OTTSETTING_OFFLINE_DISABLED,
    OTTSETTING_OFFLINE_NORMAL,
    OTTSETTING_OFFLINE_FEATHER,
};

enum OTTSettingCombo {
    OTTSETTING_COMBO_DISABLED,
    OTTSETTING_COMBO_ENABLED
};

enum OTTSettingUMTs {
    OTTSETTING_UMTS_DISABLED,
    OTTSETTING_UMTS_ENABLED
};

//KOSETTINGS
enum KOSettingEnabled {
    KOSETTING_DISABLED,
    KOSETTING_ENABLED,
};
enum KOSettingFINAL {
    KOSETTING_FINAL_DISABLED,
    KOSETTING_FINAL_ALWAYS,
};
enum KOSettingKOPerRace {
    KOSETTING_KOPERRACE_1,
    KOSETTING_KOPERRACE_2,
    KOSETTING_KOPERRACE_3,
    KOSETTING_KOPERRACE_4
};

enum KOSettingRacesPerKO {
    KOSETTING_RACESPERKO_1,
    KOSETTING_RACESPERKO_2,
    KOSETTING_RACESPERKO_3,
    KOSETTING_RACESPERKO_4
};
//KOSETTINGS

}//namespace Pulsar



#endif