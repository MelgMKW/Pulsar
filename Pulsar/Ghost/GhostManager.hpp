
#ifndef _PUL_GHOSTMANAGER__
#define _PUL_GHOSTMANAGER__
#include <kamek.hpp>
#include <game/UI/Page/Other/GhostManager.hpp>
#include <game/UI/Page/Other/TTSplits.hpp>
#include <PulsarSystem.hpp>
#include <Settings/Settings.hpp>
#include <IO/File.hpp>
#include <IO/Folder.hpp>
#include <Ghost/PULLeaderboard.hpp>


namespace Pulsar {
namespace UI {
class ExpGhostSelect;
void BeforeEntranceAnimations(Pages::TTSplits* page);
}
namespace Ghosts {

//Implements MultiGhost and handles leaderboards/expert
class Manager {
public:
    static const Manager* GetInstance() { return sInstance; }
    static Manager* CreateInstance();
    static void DestroyInstance();
    const Leaderboard& GetLeaderboard() const { return this->leaderboard; }
    const GhostData& GetGhostData(u32 idx) const { return this->files[idx]; }
    const PulsarId GetPulsarId() const { return this->pulsarId; }
    const Timer& GetExpert() const { return this->expertGhost; }
    void ToggleGhostSaving(bool savingIsEnabled){
        areGhostsSaving = savingIsEnabled;
    }
    static void InsertCustomGroupToList(GhostList* list, CourseId id);
    static void LoadCorrectMainGhost(Pages::GhostManager& ghostManager, u8 r4);
    static void ExtendSetupGhostRace(Pages::GhostManager& ghostManager, bool isStaffGhost, bool replaceGhostMiiByPlayer, bool disablePlayerMii);
    static void ExtendSetupGhostReplay(Pages::GhostManager& ghostManager, bool isStaffGhosts);

    static inline u32 GetRKGcrc32(const RKG& rkg) {
        u32 crc32;
        if(rkg.header.compressed) crc32 = *(u32*)((u32)&rkg + reinterpret_cast<const CompressedRKG*>(&rkg)->dataLength + 0x8C);
        else crc32 = rkg.uncompressedCRC32;
        return crc32;
    }
    static inline u32 GetRKGLength(const RKG& rkg) {
        u32 length = sizeof(RKG);
        if(rkg.header.compressed) length = reinterpret_cast<const CompressedRKG*>(&rkg)->dataLength + sizeof(RKGHeader) + 0x4 + 0x4;
        return length;
    }
private: 
    Manager() : pulsarId(PULSARID_NONE), files(nullptr), areGhostsSaving(true) {
        RaceData *racedata = RaceData::sInstance;
        for(int i = 0; i<4; ++i) racedata->ghosts[i].ClearBuffer();
    }
    ~Manager();
    static Manager* sInstance;
    void Init(PulsarId id);
    void Reset();
    bool SaveGhost(const TimeEntry& entry, u32 ldbPosition, bool isFlap);
    bool EnableGhost(const GhostListEntry& entry, bool isMain);
    void DisableGhost(const GhostListEntry& entry);
    bool LoadGhost(RKG& dest, u32 index);
    void LoadAllGhosts(u32 maxGhosts, bool isGhostRace);
    void CreateGhost(TimeEntry* entry, u32 position);
    static void CreateAndSaveFiles(Manager* manager);
    static char folderPath[IOS::ipcMaxPath];


    GhostData* files;
    PulsarId pulsarId;
    Timer expertGhost;
    u32 rkgCount;
    u32 mainGhostIndex; //from the watch replay;
    u32 selGhostsIndex[3];
    u32 lastUsedSlot;
    bool areGhostsSaving;
    u32 padding[20];
    alignas(0x20) RKG rkg; //aligned for file operations
    alignas(0x20) Leaderboard leaderboard; //aligned for file operations

public:
    TimeEntry entry;
    
    friend class UI::ExpGhostSelect; //UI backend
    friend class Leaderboard;
    friend void UI::BeforeEntranceAnimations(Pages::TTSplits* page); //not formally part of ExpGhostSelect but calls "SaveGhost"
};


}//namespace Ghosts
}//namespace Pulsar

#endif