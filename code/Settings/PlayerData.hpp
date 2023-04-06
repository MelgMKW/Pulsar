#ifndef _PLAYERDATA_
#define _PLAYERDATA_
#include <kamek.hpp>
#include <File/File.hpp>
#include <Pulsar.hpp>

//Contains all the settings. 
class SettingsHook {
private:
    typedef void (Func)();
    Func *mFunc;
    SettingsHook *mNext;

    static SettingsHook *sHooks;

public:
    SettingsHook(Func *f) {
        mNext = sHooks;
        sHooks = this;
        mFunc = f;
    }

    static void exec() {
        for (SettingsHook *p = sHooks; p; p = p->mNext)
            p->mFunc();
    }
};



class BinaryDummy {
    //empty just exists for future version proofing
};

class Settings {
public:
    class Binary : public BinaryDummy {
    public:
        struct Page {
            u8 radioSetting[6];
            u8 scrollSetting[6];
        };
        Binary() {};
        char magic[4];
        u32 version; //just in case more than 255 versions
        Page pages[3];
    };
    Settings();

    static Settings *GetInstance() { return sInstance; }

    Binary *GetSettings() const { return this->rawBin; }

    void Update();
protected:
    static Settings *sInstance;
    virtual void Init(char *path, const char *curMagic, u32 version) = 0;
    virtual void RequestSave() = 0;

    char filePath[IPCMAXPATH];
    Binary *rawBin;

    //any global var can go here I guess
};


struct TrackTrophy {
    u32 crc32;
    bool hastrophy[4];
};

struct PULTrophies {
    PULTrophies() {
        magic[0] = 'T';
        magic[1] = 'R';
        magic[2] = 'O';
        magic[3] = 'P';
    }
    char magic[4];
    u16 trophyCount[4];
    TrackTrophy trophies[1];
};

class PulsarSettings : public Settings {
public:
    class Binarya : public Settings::Binary {
    public:
        u32 reserved[20];
        u32 trackCount;
        PULTrophies trophiesHolder;
    }__attribute((aligned(0x20)));

    static PulsarSettings *GetInstance() { return (PulsarSettings *)sInstance; }
    PulsarSettings::Binarya *GetSettings() const { return  (PulsarSettings::Binarya *)this->rawBin; } //hides parent
private:
    void Init(char *path, const char *curMagic, u32 curVersion) override;
    void RequestSave() override;
public:
    TrackTrophy *FindTrackTrophy(u32 crc32, TTMode mode);
    void UpdateTrackList(u32 *crc32Array);
    void AddTrophy(u32 crc32, TTMode mode);
    bool HasTrophy(u32 crc32, TTMode mode);
    bool HasTrophy(CourseId id, TTMode mode);
    int GetTrophyCount(TTMode mode) { return this->GetSettings()->trophiesHolder.trophyCount[mode]; }
    static int GetBinSize() { return sizeof(Binarya) + sizeof(TrackTrophy) * (Pulsar::sInstance->GetCtsTrackCount() - 1); }
    static void SaveTask(void *);
    static void Create();
    void Save();
};




enum OPTSettingsPages {
    OPT_MENU_SETTINGS,
    OPT_RACE_SETTINGS,
    OPT_HOST_SETTINGS
};

//MENU SETTINGS
enum OPTRadioMenuSettings {
    OPT_RADIO_FASTMENUS
};

enum OPTRadioMenuFastMenus {
    OPT_RADIO_FASTMENUS_DISABLED = 0x0,
    OPT_RADIO_FASTMENUS_ENABLED = 0x1
};

enum OPTScrollMenuSettings {
    OPT_SCROLL_BOOT
};

enum OPTScrollMenuBoot {
    OPT_SCROLL_BOOT_DISABLED,
    OPT_SCROLL_BOOT_L1,
    OPT_SCROLL_BOOT_L2,
    OPT_SCROLL_BOOT_L3,
    OPT_SCROLL_BOOT_L4
};

//RACE SETTINGS
enum OPTRadioRaceSettings {
    OPT_RADIO_MII,
    OPT_RADIO_SPEEDUP,
    OPT_RADIO_BATTLE,
    OPT_RADIO_BLUES
};

enum OPTRadioRaceMII {
    OPT_RADIO_MII_DISABLED = 0x0,
    OPT_RADIO_MII_ENABLED = 0x1
};

enum OPTRadioRaceSPEEDUP {
    OPT_RADIO_SPEEDUP_DISABLED = 0x0,
    OPT_RADIO_SPEEDUP_ENABLED = 0x1
};

enum OPTRadioRaceBATTLE {
    OPT_RADIO_BATTLE_GLITCH_DISABLED = 0x0,
    OPT_RADIO_BATTLE_GLITCH_ENABLED = 0x1
};

enum OPTRadioRaceBLUES {
    OPT_RADIO_DRAGGABLE_BLUES_DISABLED = 0x0,
    OPT_RADIO_DRAGGABLE_BLUES_ENABLED = 0x1
};

//HOST SETTINGS
enum OPTRadioHostSettings {
    OPT_RADIO_HOSTWINS,
    OPT_RADIO_CC
};

enum OPTRadioHostHostWins {
    OPT_RADIO_HOSTWINS_DISABLED,
    OPT_RADIO_HOSTWINS_ENABLED
};

enum OPTRadioHostCC {
    OPT_RADIO_CC_NORMAL,
    OPT_RADIO_CC_150,
    OPT_RADIO_CC_200
};

enum OPTScrollHostSettings {
    OPT_SCROLL_GP_RACES
};

enum OPTScrollHostGPRACES {
    OPT_SCROLL_GP_RACES_4,
    OPT_SCROLL_GP_RACES_8,
    OPT_SCROLL_GP_RACES_12,
    OPT_SCROLL_GP_RACES_24,
    OPT_SCROLL_GP_RACES_32,
    OPT_SCROLL_GP_RACES_64,
    OPT_SCROLL_GP_RACES_2
};

#endif