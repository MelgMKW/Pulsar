#ifndef _PULSAR_
#define _PULSAR_
#include <kamek.hpp>
#include <core/rvl/ipc/ipc.hpp>
#include <game/System/Identifiers.hpp>
#include <game/System/random.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/Race/RaceData.hpp>

enum TTMode {
    TTMODE_150,
    TTMODE_200,
    TTMODE_150_FEATHER,
    TTMODE_200_FEATHER,
};

class Pulsar {
private:
    static const u32 RegsCRC32[32];
    enum GhostMode {
        GHOSTS_DISABLED,
        GHOSTS_150ONLY,
        GHOSTS_150FEATHER,
        GHOSTS_150200,
        GHOSTS_ALL,
    };
#pragma pack(push, 1)
    struct BinaryHeader {
        u32 magic;
        u32 version;
        u32 length; //without the header
    };

    struct Info {
        u8 regsMode;
        bool hasTTTrophies;
        bool forcedHostAlwaysWins;
        bool has200cc;
        bool hasUMTs;
        bool hasFeather;
        bool hasMegaTC;
        bool reserved[3];
        u32 prob100cc;
        u32 prob150cc;
        u32 wiimmfiRegion;
        u32 trackBlocking;
        char modFolderName[IPCMAXFILENAME + 1]; //lengths to specify
    };

    struct InfoHolder {
        BinaryHeader header; //MAGIC PULS
        Info info;
    };
    struct Track {
        u8 slot;
        u8 musicSlot;
        u32 crc32;
    };

    struct Cup {
        u32 idx;
        Track tracks[4];
    };

    struct CupsHolder {
        BinaryHeader header;
        u32 ctsCupCount;
        u16 trophyCount[4];
        Cup cups[1]; //CUPS
    };
    struct Binary {
        InfoHolder infoHolder;
        CupsHolder cupsHolder;
        //BMGHeader *rawBmg;
    };


#pragma pack(pop)

public:
    static Pulsar *sInstance;
    static void GetStaticInstance();
    Pulsar(Binary *binary, EGG::ExpHeap *heap);

    //System functions
    static int GetClassSize(Binary *bin) {
        u32 count = bin->cupsHolder.ctsCupCount;
        return sizeof(Pulsar) + (count + (count & 1) - 1) * sizeof(Cup);
    }
    static void InitIO();
    static s32 Open(const char *path, IOS::Mode mode);
    static void ChangeImage(LayoutUIControl *control, const char *paneName, const char *tplName);
    const char *GetModFolder() const { return userInfo.modFolderName; }

    //Cup Functions
    int GetTotalCupCount() const { return ctsCupCount + HasRegs() * 8; }
    int GetCtsTrackCount() const { return ctsCupCount * 4; }
    int GetTotalTrackCount() const { return GetTotalCupCount() * 4; }
    u16 GetTotalTrophyCount(TTMode mode) const { return trophyCount[mode]; }

    //Ghosts
    int GetCRC32(CourseId id) const;
    void GetTrackGhostFolder(char *dest, CourseId pulsarId) const;

    //Slot Getters
    CourseId GetCorrectTrackSlot() const;
    int GetCorrectMusicSlot() const;

    //Reg Check
    static bool IsReg(u32 pulsarId) { return pulsarId < 0x100; }
    static bool IsRegCup(u32 cupId) { return cupId < 8; }

    //Conversions
    static u32 ConvertCup_PulsarIdToRealId(u32 pulsarCupId) {
        if (IsRegCup(pulsarCupId)) {
            if ((pulsarCupId & 1) == 0) return pulsarCupId / 2;
            else return (pulsarCupId + 7) / 2;
        }
        else return pulsarCupId - 0x40;
    }
    static u32 ConvertCup_PulsarIdToIdx(u32 pulsarCupId) {
        if (!IsRegCup(pulsarCupId)) pulsarCupId -= 0x38;
        return pulsarCupId;
    }
    u32 ConvertCup_IdxToPulsarId(u32 cupIdx) const {
        if (!IsRegCup(cupIdx)) return cupIdx + 0x38;
        else return cupIdx;
    }
    static CourseId ConvertTrack_PulsarIdToRealId(u32 pulsarId) {
        if (IsReg(pulsarId)) {
            if (pulsarId < 32) return (CourseId)idToCourseId[pulsarId];
            else return (CourseId)pulsarId; //battle
        }
        else return (CourseId)(pulsarId - 0x100);
    }

    //User Options Getters
    bool HasRegs() const { return userInfo.regsMode > 0; }
    bool HasTrophies() const { return userInfo.hasTTTrophies; }
    bool Has200cc() const { return userInfo.has200cc; }
    bool HasUMTs() const { return userInfo.hasUMTs; }
    bool HasFeather() const { return true /*userInfo.hasFeather*/; }
    bool HasMegaTC() const { return userInfo.hasMegaTC; }
    u32 GetWiimmfiRegion() const { return userInfo.wiimmfiRegion; }
    u32 GetTrackBlocking() const { return userInfo.trackBlocking; }

    //Context checking
    bool CheckHAWConditions() const;
    bool Is200cc() const { return RaceData::sInstance->racesScenario.settings.engineClass == CC_100 && Has200cc(); }

    //Slot Expansion
    void SaveSelectedCourse(PushButton *courseButton);
    u32 GetNextCupId(u32 cupId, s32 direction) const;
    CourseId RandomizeTrack(Random *random) const;

    //Constants
    EGG::ExpHeap *heap;
    EGG::TaskThread *taskThread;
    u32 ctsCupCount;
    bool hasOddCups;

    //Variables
    CourseId winningCourse;
    CourseId selectedCourse;
    u32 lastSelectedCup;
    u32 lastSelectedButtonIdx;
    bool hasHAW;
    TTMode ttMode;
    u8 curArrayIdx;
    u32 *lastTracks;

    //Custom BMGS
    BMGHolder customBmgs;
private:
    //Data
    BMGHeader *rawBmg;
    Info userInfo;
    u16 trophyCount[4];
    Cup cups[1];

public:
    //string pool
    static const u8 idToCourseId[42];
    static const char pulsarString[8];
    static const char UIAssets[15];
    static const char CommonAssets[18];
    static const char breff[25];
    static const char breft[26];
    static const char controlFolder[8];
    static const char buttonFolder[7];
    static const char raceFolder[11];
    static const char bgFolder[3];
    static const char *ttModeFolders[4];
};

#endif