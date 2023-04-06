
#ifndef _SIP_MULTIGHOSTMGR_
#define _SIP_MULTIGHOSTMGR_
#include <kamek.hpp>
#include <game/UI/Page/Other/GhostManager.hpp>
#include <Pulsar.hpp>
#include <Settings/PlayerData.hpp>
#include <File/File.hpp>
#include <File/Folder.hpp>
#include <Ghost/PULLeaderboard.hpp>

//Implements MultiGhost and handles leaderboards/expert
class PULLeaderboard;
class MultiGhostMgr {
public:
    MultiGhostMgr();
    ~MultiGhostMgr();
    static MultiGhostMgr *GetInstance() { return sInstance; }
    static MultiGhostMgr *CreateInstance();
    static void DestroyInstance();
    PULLeaderboard *GetLeaderboard() { return &this->leaderboard; }
    const GhostData *GetGhostData(u32 idx) const { return &this->files[idx]; }
    const CourseId GetCourseId() const { return this->courseId; }
    const Timer &GetExpert() const { return this->expertGhost; }
    void Init(CourseId id);
    void Reset();
    bool EnableGhost(GhostListEntry *entry, bool isMain);
    void DisableGhost(GhostListEntry *entry);
    bool LoadGhost(RKG *dest, u32 index);
    void LoadAllGhost(RKG *buffer, u32 maxGhosts, bool isGhostRace);
    void CreateGhost(TimeEntry *entry, u32 position);
    //void CopyRKGAndInitParams(RKG *src, u8 id, bool isGhostRace) const;
    static void CreateAndSaveFiles(void *holder);
private:
    static MultiGhostMgr *sInstance;
    GhostData *files;
    CourseId courseId;
    Timer expertGhost;
    u32 rkgCount;
    u32 padding[20];

public:
    RKG rkg __attribute((aligned(0x20))); //aligned for file operations
    PULLeaderboard leaderboard __attribute((aligned(0x20))); //aligned for file operations
    TimeEntry entry;
    u32 mainGhostIndex; //from the watch replay;
    u32 selGhostsIndex[3];
    u32 lastUsedSlot;
    static char folderPath[IPCMAXPATH];

};

#endif