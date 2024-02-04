#ifndef _SETTINGS_
#define _SETTINGS_
#include <kamek.hpp>
#include <SlotExpansion/CupsDef.hpp>
#include <PulsarSystem.hpp>
#include <Settings/UI/SettingsPanel.hpp>


namespace Pulsar {
namespace UI { class SettingsPanel; }
namespace Settings {

//Contains all the settings. 
enum Type {
    SETTINGSTYPE_MENU,
    SETTINGSTYPE_RACE,
    SETTINGSTYPE_HOST
};

class Hook : public DoFuncsHook {
    static DoFuncsHook* settingsHooks;
public:
    Hook(Func& f) : DoFuncsHook(f, &settingsHooks) {}
    static void exec() { DoFuncsHook::exec(settingsHooks); }
};

struct TrackTrophy {
    u32 crc32;
    bool hastrophy[4];
};


struct Page {
    union {
        struct {
            u8 radioSetting[6];
            u8 scrollSetting[6];
        };
        u8 settings[12];
    };
};

struct PagesHolder {
    static const u32 pageMagic = 'PAGE';
    Pulsar::SectionHeader header;
    u32 pageCount;
    Page pages[1];
};

struct MiscParams {
    static const u32 miscMagic = 'MISC';
    Pulsar::SectionHeader header;
    u32 reserved[20];
    PulsarCupId lastSelectedCup;
    u32 trackCount;
};

struct TrophiesHolder {
    static const u32 tropMagic = 'TROP';
    Pulsar::SectionHeader header;
    u16 trophyCount[4];
    TrackTrophy trophies[1];
};

struct BinaryHeader {
    u32 magic;
    u32 version;
    u32 fileSize;
    u32 offsetToPages;
    u32 offsetToMisc;
    u32 offsetToTrophies;
};

class alignas(0x20) Binary {
    static const u32 binMagic = 'PULP';

    Binary(u32 curVersion, u32 pageCount) {
        u32 trackCount = CupsDef::sInstance->GetEffectiveTrackCount();

        header.magic = binMagic;
        header.version = curVersion;
        header.offsetToPages = offsetof(Binary, pages);
        header.offsetToMisc = header.offsetToPages + sizeof(PagesHolder) + sizeof(Page) * (pageCount - 1);
        header.offsetToTrophies = header.offsetToMisc + sizeof(MiscParams);
        header.fileSize = header.offsetToTrophies + sizeof(TrophiesHolder) + sizeof(TrackTrophy) * (trackCount - 1);

        PagesHolder& pages = this->GetSection<PagesHolder, &BinaryHeader::offsetToPages>();
        pages.header.magic = PagesHolder::pageMagic;
        pages.pageCount = pageCount;
        MiscParams& params = this->GetSection<MiscParams, &BinaryHeader::offsetToMisc>();
        params.header.magic = MiscParams::miscMagic;
        params.trackCount = trackCount;
        params.lastSelectedCup = PULSARCUPID_NONE;
        this->GetSection<TrophiesHolder, &BinaryHeader::offsetToTrophies>().header.magic = TrophiesHolder::tropMagic;

    }

    template<typename T, u32 BinaryHeader::* offset>
    inline T& GetSection() {
        return *reinterpret_cast<T*>(ut::AddU32ToPtr(this, this->header.*offset));
    }
    template <class T>
    bool CheckSection(const T& t) { if(t.header.magic != T::magic) return false; return true; }

    BinaryHeader header;
    PagesHolder pages;
    MiscParams misc;
    TrophiesHolder trophies;
    friend class Mgr;
};

/*
template<>
inline PagesHolder& Binary::GetSection<PagesHolder>() {
    return *reinterpret_cast<PagesHolder*>(ut::AddU32ToPtr(this, this->header.offsetToPages));
}

template<>
inline MiscParams& Binary::GetSection<MiscParams>() {
    return *reinterpret_cast<MiscParams*>(ut::AddU32ToPtr(this, this->header.offsetToMisc));
}

template<>
inline TrophiesHolder& Binary::GetSection<TrophiesHolder>() {
    return *reinterpret_cast<TrophiesHolder*>(ut::AddU32ToPtr(this, this->header.offsetToTrophies));
}
*/




class Mgr {
protected:

    friend class System;
    friend class UI::SettingsPanel;
    static const u32 curVersion = 2;

    static Mgr* sInstance;
    static void SaveTask(void*);
    virtual void Init(u32 pageCount, const u16* totalTrophyCount, const char* path);
    virtual int GetSettingsBinSize(u32 pageCount) const;
    char filePath[IOS::ipcMaxPath];
    Binary* rawBin;
private:
    u16 totalTrophyCount[4];
    TrackTrophy* FindTrackTrophy(u32 crc32, TTMode mode) const;
    void UpdateTrackList();
    void SetSettingValue(Type type, u32 setting, u8 value);
    void AdjustTrackCount(u32 newTrackCount);

public:
    Mgr() : rawBin(nullptr) {}
    static Mgr* GetInstance() { return sInstance; }
    void Update() {
        Hook::exec();
        this->RequestSave();
    }
    void RequestSave() {
        System::sInstance->taskThread->Request(&Mgr::SaveTask, nullptr, 0);
    }
    void Save();
    void SetLastSelectedCup(PulsarCupId id) { this->rawBin->GetSection<MiscParams, &BinaryHeader::offsetToMisc>().lastSelectedCup = id; }

    void AddTrophy(u32 crc32, TTMode mode);
    bool HasTrophy(u32 crc32, TTMode mode) const;
    bool HasTrophy(PulsarId id, TTMode mode) const;
    u16 GetTotalTrophyCount(TTMode mode) const { return totalTrophyCount[mode]; }
    int GetTrophyCount(TTMode mode) const { return this->rawBin->GetSection<TrophiesHolder, &BinaryHeader::offsetToTrophies>().trophyCount[mode]; }

    static u8 GetSettingValue(Type type, u32 setting);
    static void Create();

};
}//namespace Settings
}//namespace Pulsar

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