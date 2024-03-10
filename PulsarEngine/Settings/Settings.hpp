#ifndef _SETTINGS_
#define _SETTINGS_
#include <kamek.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <PulsarSystem.hpp>
#include <Settings/UI/SettingsPanel.hpp>
#include <MarioKartWii/UI/Page/Menu/SinglePlayer.hpp>

namespace Pulsar {
namespace UI { class SettingsPanel; }
namespace Settings {

//Contains all the settings. 
enum Type {
    SETTINGSTYPE_MENU,
    SETTINGSTYPE_RACE,
    SETTINGSTYPE_HOST
};

enum SectionIndexes {
    SECTION_PAGES,
    SECTION_MISC,
    SECTION_TROPHIES,
    SECTION_GP
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
}; //0x8


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
    static const u32 version = 1;
    static const u32 index = SECTION_PAGES;
    Pulsar::SectionHeader header;
    u32 pageCount;
    Page pages[1];
};

struct MiscParams {
    static const u32 miscMagic = 'MISC';
    static const u32 version = 1;
    static const u32 index = SECTION_MISC;
    Pulsar::SectionHeader header;
    u32 reserved[20]; //0xc
    PulsarCupId lastSelectedCup; //0x5c
    u32 trackCount; //0x60
};

struct TrophiesHolder {
    static const u32 tropMagic = 'TROP';
    static const u32 version = 1;
    static const u32 index = SECTION_TROPHIES;
    Pulsar::SectionHeader header;
    u16 trophyCount[4];
    TrackTrophy trophies[1];
};

struct GPCupStatus {
    u8 gpCCStatus[4]; //one per CC
};
struct GPSection {
    static const u32 gpMagic = 'GP\0\0';
    static const u32 version = 1;
    static const u32 index = SECTION_GP;
    enum Status {
        GOLD_TROPHY = 0,
        SILVER_TROPHY = 1,
        BRONZE_TROPHY = 2,
        NO_TROPHY = 3,

        //2 bits for trophy
        //4 bits for rank, 0 to 7
        //3 2 1 a b c d e

    };
    Pulsar::SectionHeader header;
    GPCupStatus gpStatus[1]; //one per cup
};

struct BinaryHeader {
    u32 magic;
    u32 version;
    u32 fileSize;
    u32 sectionCount;
    u32 offsets[1]; //0x10
    //u32 offsetToPages;
    //u32 offsetToMisc;
    //u32 offsetToTrophies;
    //u32 offsetToGP;
};

struct BinaryHeaderV1 {
    u32 magic;
    u32 version;
    u32 fileSize;
    u32 offsetToPages;
    u32 offsetToMisc;
    u32 offsetToTrophies;
    u32 offsetToGP;
};

class alignas(0x20) Binary {
    static const u32 binMagic = 'PULP';
    static const u32 sectionCount = 4;
    static const u32 curVersion = 3;

    Binary(u32 curVersion, u32 pageCount, u32 trackCount) {
        const u32 cupCount = trackCount / 4;
        header.magic = binMagic;
        header.version = curVersion;
        header.offsets[PagesHolder::index]    = sizeof(BinaryHeader) + sizeof(u32) * (sectionCount - 1);
        header.offsets[MiscParams::index]     = header.offsets[PagesHolder::index] + sizeof(PagesHolder) + sizeof(Page) * (pageCount - 1);
        header.offsets[TrophiesHolder::index] = header.offsets[MiscParams::index] + sizeof(MiscParams);
        header.offsets[GPSection::index]      = header.offsets[TrophiesHolder::index] + sizeof(TrophiesHolder) + sizeof(TrackTrophy) * (trackCount - 1);
        header.fileSize = header.offsets[GPSection::index] + sizeof(GPSection) + sizeof(GPCupStatus) * (cupCount - 1);
        header.sectionCount = sectionCount;

        PagesHolder& pages = this->GetSection<PagesHolder>();
        pages.header.magic = PagesHolder::pageMagic;
        pages.header.version = PagesHolder::version;
        pages.header.size = sizeof(PagesHolder) + sizeof(Page) * (pageCount - 1);
        pages.pageCount = pageCount;

        MiscParams& params = this->GetSection<MiscParams>();
        params.header.magic = MiscParams::miscMagic;
        params.header.version = MiscParams::version;
        params.header.size = sizeof(MiscParams);
        params.trackCount = trackCount;
        params.lastSelectedCup = PULSARCUPID_NONE;

        TrophiesHolder& trophies = this->GetSection<TrophiesHolder>();
        trophies.header.magic = TrophiesHolder::tropMagic;
        trophies.header.version = TrophiesHolder::version;
        trophies.header.size = sizeof(TrophiesHolder) + sizeof(TrackTrophy) * (trackCount - 1);

        GPSection& gp = this->GetSection<GPSection>();
        gp.header.magic = GPSection::gpMagic;
        gp.header.version = GPSection::version;

        gp.header.size = sizeof(GPSection) + sizeof(GPCupStatus) * (cupCount - 1);
        memset(&gp.gpStatus[0], 0xFF, sizeof(GPCupStatus) * cupCount);
    }

    Binary(const Binary& old) { //V2 -> V3

        const BinaryHeaderV1& oldHeader = reinterpret_cast<const BinaryHeaderV1&>(old.header);
        const PagesHolder& oldPages = *reinterpret_cast<const PagesHolder*>(ut::AddU32ToPtr(&old, oldHeader.offsetToPages)); //
        const MiscParams& oldParams = *reinterpret_cast<const MiscParams*>(ut::AddU32ToPtr(&old, oldHeader.offsetToMisc));
        //const TrophiesHolder& oldTrophies = old.GetSection<TrophiesHolder>();

        u32 pageCount = oldPages.pageCount;
        u32 trackCount = oldParams.trackCount;

        new(this) Binary(curVersion, pageCount, trackCount);

        PagesHolder& pages = this->GetSection<PagesHolder>();
        MiscParams& params = this->GetSection<MiscParams>();
        TrophiesHolder& trophies = this->GetSection<TrophiesHolder>();

        memcpy(&pages, &oldPages, pages.header.size + params.header.size + trophies.header.size);
        GPSection& gp = this->GetSection<GPSection>();
        const u32 cupCount = trackCount / 4;
        memset(&gp.gpStatus[0], 0xFF, sizeof(GPCupStatus) * cupCount);
    }

    template<typename T>
    inline T& GetSection() {
        return *reinterpret_cast<T*>(ut::AddU32ToPtr(this, this->header.offsets[T::index]));
    }
    template<typename T>
    inline const T& GetSection() const {
        return *reinterpret_cast<const T*>(ut::AddU32ToPtr(this, this->header.offsets[T::index]));
    }
    template <class T>
    bool CheckSection(const T& t) { if(t.header.magic != T::magic) return false; return true; }

    BinaryHeader header;
    PagesHolder pages;
    //MiscParams misc;
    //TrophiesHolder trophies;
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
private:

    friend class System;
    friend class UI::SettingsPanel;


    static Mgr* sInstance;
    static void SaveTask(void*);
    void Init(u32 pageCount, const u16* totalTrophyCount, const char* path);
    int GetSettingsBinSize() const;
    char filePath[IOS::ipcMaxPath];
    Binary* rawBin;


    TrackTrophy* FindTrackTrophy(u32 crc32, TTMode mode) const;
    void UpdateTrackList();
    void SetSettingValue(Type type, u32 setting, u8 value);
    void AdjustTrackCount(u32 newTrackCount);
    Binary* UpdateVersion(const Binary* old);

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
    void SetLastSelectedCup(PulsarCupId id) { this->rawBin->GetSection<MiscParams>().lastSelectedCup = id; }

    void AddTrophy(u32 crc32, TTMode mode);
    bool HasTrophy(u32 crc32, TTMode mode) const;
    bool HasTrophy(PulsarId id, TTMode mode) const;
    u16 GetTotalTrophyCount(TTMode mode) const { return totalTrophyCount[mode]; }
    int GetTrophyCount(TTMode mode) const { return this->rawBin->GetSection<TrophiesHolder>().trophyCount[mode]; }
    PulsarCupId GetSavedSelectedCup() const { return this->rawBin->GetSection<MiscParams>().lastSelectedCup; }

    //GP
    static u8 GetGPStatus(u32 idx, u32 cc) {
        Mgr* mgr = Mgr::sInstance;
        GPSection& gp = mgr->rawBin->GetSection<GPSection>();
        return gp.gpStatus[idx].gpCCStatus[cc];
    }
    static GPRank ComputeRankFromStatus(u8 gpStatus) {
        return static_cast<GPRank>(gpStatus >> 2);
    }
    static u32 ComputeTrophyFromStatus(u8 gpStatus) {
        return gpStatus & 0b11;
    }
    static void SetGPStatus(u32 idx, u32 cc, u32 trophy, GPRank rank) {
        Mgr* mgr = Mgr::sInstance;
        GPSection& gp = mgr->rawBin->GetSection<GPSection>();
        u8 newStatus = trophy | (rank << 2);

        const u8 oldStatus = gp.gpStatus[idx].gpCCStatus[cc];
        bool isNew = false;
        if(oldStatus == 0xFF) isNew = true;
        else {
            const GPRank oldRank = ComputeRankFromStatus(oldStatus);
            const u32 oldTrophy = ComputeTrophyFromStatus(oldStatus);

            if(trophy < oldTrophy) isNew = true;
            else if(trophy == oldTrophy && rank < oldRank) isNew = true;
        }
        if(isNew) {
            gp.gpStatus[idx].gpCCStatus[cc] = newStatus;
            mgr->RequestSave();
        }
    }

    static u8 GetSettingValue(Type type, u32 setting);
    static void Create();

private:
    u16 totalTrophyCount[4];
    u32 pageCount;

};
}//namespace Settings
}//namespace Pulsar

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

#endif