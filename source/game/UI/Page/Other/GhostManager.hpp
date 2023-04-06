#ifndef _GHOSTMANAGER_
#define _GHOSTMANAGER_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/System/Ghost.hpp>


/*
Contributors:
-stebler, Melg
*/

enum GhostManagerPageState {
    IDLE,
    SAVED_GHOST_RACE_FROM_MENU = 0x3,
    SAVED_GHOST_REPLAY = 0x6,
    STAFF_GHOST_RACE_FROM_MENU = 0x9,
    STAFF_GHOST_REPLAY = 0xc
};

class GhostManager;
struct GhostListEntry {

    const GhostData *data; //0x0
    u32 ghostGroupId; //0x4
    u32 index; //0x8 ghost group ghostdata array index
    bool isNew; //0xC
    u8 unknown_0xD[3];
}; //total size 0x10

class GhostList {
public:
    GhostList(); //805e208c
    ~GhostList(); //805e209c
    void FillWithAllGhosts(); //805e20dc
    void FillWithAllDLdGhosts(); //805e2198
    void Init(CourseId id); //0x805e2200
    void Reset(); //805e22c8 inlined sets count to 0

    void FillFromGroup(u32 ghostGroupId, GhostGroup *group, CourseId course, bool *isNew); //805e22d4 isNew only passed for downloaded ghosts
    void Sort(); //805e241c inlined
    static int CompareEntries(GhostListEntry *entry, GhostListEntry *entry2); //805e2430 returns distance between the 2?
    void EraseEntry(u32 entryIndex); //805e2610 erases it from the license too
    GhostData *GetGhostData(u32 entryIndex); //805e2500
    bool CheckIsNew(u32 entryIndex); //805e2528
    bool AreAllGhostsNew(); //805e2554
    void InitSectionMgr98Params(s32 entryIndex); //805e2588
    GhostListEntry entries[38];
    u32 count; //0x260
    GhostManager *ghostManagerPage; //0x264
}; //total size 0x268

//_sinit_ at 805e272c
namespace Pages {
class GhostManager : public Page { //ID 0xA7
public:
    GhostManager(); //805e0c38 vtable 0x808b9258
    ~GhostManager() override; //0x805e0cb8
    void OnInit() override; //805e0d84
    void OnActivate() override; //805e0ffc
    void OnDeactivate() override; //805e1100
    void BeforeEntranceAnimations() override; //805e10f8
    void BeforeExitAnimations() override; //805e10fc
    void AfterControlUpdate() override; //805e1104
    void OnSectionChange() override; //805e1108
    int GetRuntimeTypeInfo() const override; //805e2720

    void UpdateState(); //805e1214
    void RequestAllGhosts(); //805e11b0 appears to be unused
    bool AreStaffGhostsLoading(); //805e15c4, delays call to setup until this returns false
    GhostData *GetGhostData(GhostType type, u32 licenseId, CourseId id); //805e163c
    void RequestGhost(bool checkRKGValidity); //0x805e1998
    void SetupGhostRace(bool isStaffGhost, bool replaceGhostMiiByPlayer, bool disablePlayerMii);
    void SetupGhostReplay(bool isStaffGhosts); //805e1d5c
    void LoadGhost(u32 r4);
    void UpdateStateToReplay();
    ManipulatorManager manager; //0x44
    GhostGroup *savedGhostGroups[4]; //0x54
    GhostGroup *downloadedGhostsGroup; //0x64
    GhostGroup *easyStaffGhostsGroup; //0x68
    GhostGroup *expertStaffGhostsGroup; //0x6C
    GhostGroup *unknown_group; //0x70
    bool isNew[0x20]; //for each track 
    GhostManagerPageState state; //0x94
    u32 unknown_0x98;
    GhostManagerPageState nextState; //0x9C
    GhostList list; //0xA0
    RKG *rkgPointer; //0x20 aligned
    RKG rkgBuffer;
};//total size 0x2b0c
size_assert(GhostManager, 0x2B0C);
}
extern "C" {
    CourseId GetCourseIdBySlot(u32 slot); //just the nbr of the track
    void LoadStaffGhost(u32 ghostType, u32 courseId, RKG *rkgBuffer);
    int CourseIdToGhostIndex(CourseId id);
}//namespace Pages
#endif