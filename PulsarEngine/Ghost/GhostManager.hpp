
#ifndef _PUL_GHOSTMANAGER__
#define _PUL_GHOSTMANAGER__
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Other/GhostManager.hpp>
#include <MarioKartWii/UI/Page/Other/TTSplits.hpp>
#include <PulsarSystem.hpp>
#include <Ghost/PULLeaderboard.hpp>

namespace Pulsar {
namespace UI {
class ExpGhostSelect;
void BeforeEntranceAnimations(Pages::TTSplits* page);
}
namespace Ghosts {

//Implements MultiGhost and handles leaderboards/expert
class  Mgr {
public:
    enum CBTiming {
        IS_LOADING_LEADERBOARDS,
        IS_SETTING_RACE,
        IS_SAVING_GHOST
    };
    typedef void(*RKGCallback)(const RKG& decompressed, CBTiming timing, int index);

    static const Mgr* GetInstance() { return sInstance; }
    static Mgr* CreateInstance();
    static void DestroyInstance();
    static void SetCb(RKGCallback userCb) { cb = userCb; }
    const Leaderboard& GetLeaderboard() const { return this->leaderboard; }
    const GhostData& GetGhostData(u32 idx) const { return this->files[idx]; }
    u32 GetSelGhostIdx(u32 idx) const { return this->selGhostsIndex[idx]; }

    bool HasExpert() const { return this->expertGhost.isActive; }
    const PulsarId GetPulsarId() const { return this->pulsarId; }
    const Timer& GetExpert() const { return this->expertGhost; }
    u32 GetFavGhostFileIndex(TTMode mode) const { return this->favGhostFileIndex[mode]; }
    void ToggleGhostSaving(bool savingIsEnabled) {
        areGhostsSaving = savingIsEnabled;
    }
    static void InsertCustomGroupToList(GhostList* list, CourseId id);
    static void LoadCorrectMainGhost(Pages::GhostManager& ghostManager, u8 r4);
    static void ExtendSetupGhostRace(Pages::GhostManager& ghostManager, bool isStaffGhost, bool replaceGhostMiiByPlayer, bool disablePlayerMii);
    static void ExtendSetupGhostReplay(Pages::GhostManager& ghostManager, bool isStaffGhosts);

    static inline u32 GetRKGcrc32(const RKG& rkg) {
        u32 crc32;
        if (rkg.header.compressed) crc32 = *(u32*)((u32)&rkg + reinterpret_cast<const CompressedRKG*>(&rkg)->dataLength + 0x8C);
        else crc32 = rkg.uncompressedCRC32;
        return crc32;
    }
    static inline u32 GetCompressedRKGLength(const CompressedRKG& rkg) {
        return rkg.dataLength + sizeof(RKGHeader) + 0x4 + 0x4;
    }
    static inline u32 GetRKGLength(const RKG& rkg) {
        if (rkg.header.compressed) return GetCompressedRKGLength(reinterpret_cast<const CompressedRKG&>(rkg));
        else return sizeof(RKG);
    }
    static const char* GetGhostFileName(u32 fileIndex) {
        if (fileIndex == expertFileIdx) return "?";
        else return IO::sInstance->GetFileName(fileIndex);
    }
    //u32 GetGhostIndex(const GhostListEntry& entry) const;
    bool LoadGhost(RKG& dest, u32 index) const;


private:
    Mgr() : pulsarId(PULSARID_NONE), files(nullptr), areGhostsSaving(true) {
        Racedata* racedata = Racedata::sInstance;
        for (int i = 0; i < 4; ++i) racedata->ghosts[i].ClearBuffer();
    }
    ~Mgr() {
        delete[] this->files; //in case Reset wasn't called before
    }
    static Mgr* sInstance;
    void Init(PulsarId id);
    void Reset();
    void SaveLeaderboard();
    bool SaveGhost(const RKSYS::LicenseLdbEntry& entry, u32 ldbPosition, bool isFlap);
    bool EnableGhost(const GhostListEntry& entry, bool isMain);
    void DisableGhost(const GhostListEntry& entry);
    void LoadAllGhosts(u32 maxGhosts, bool isGhostRace);
    void CreateGhost(RKSYS::LicenseLdbEntry* entry, u32 position);
    void SetFavGhost(const GhostListEntry& entry, TTMode mode, bool add) { this->leaderboard.SetFavGhost(entry.padding[0], mode, add); }
    static void CreateAndSaveFiles(Mgr* self);
    static char folderPath[IOS::ipcMaxPath];
    static RKGCallback cb; //int = ghost index


    GhostData* files;
    PulsarId pulsarId;
    Timer expertGhost; //0x8
    u32 rkgCount; //0x14
    u32 mainGhostIndex; //0x18 from the watch replay;
    u32 selGhostsIndex[3]; //0x1c
    u32 lastUsedSlot; //0x28
    u32 favGhostFileIndex[2]; //0x34 for saving and loading
    bool areGhostsSaving; //0x3C

    s32 expertEntryNum; //0x40
    u32 padding[0xf]; //0x44
    RKG rkg; //0x80 aligned for file operations
    Leaderboard leaderboard; //aligned for file operations
    RKSYS::LicenseLdbEntry entry;

    static const u32 expertFileIdx = 39;
    friend class UI::ExpGhostSelect; //UI backend
    friend class Leaderboard;
    friend void UI::BeforeEntranceAnimations(Pages::TTSplits* page); //not formally part of ExpGhostSelect but calls "SaveGhost"
};


}//namespace Ghosts
}//namespace Pulsar

#endif