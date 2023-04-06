#ifndef _CTRLRACETIME_
#define _CTRLRACETIME_
#include <kamek.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>

//_sinit_CtrlRaceTime_cpp; //807f8974
class CtrlRaceTime : public CtrlRaceBase {
public:
    CtrlRaceTime(u8 variantId, u32 type); //807f7bd0 id is just RowCount, 0 = final time, the rest = split, r5 is 4 if final, 5 otherwise
    ~CtrlRaceTime() override; //807f890c vtable 808d4010
    void InitSelf() override; //0x1C 807f7c6c
    void OnUpdate() override; //0x1c 807f7ec0
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //0x20 807f8768
    int GetRuntimeTypeInfo() const override; //0x28 807f8968
    virtual void OnFocus(); //0x50 807f88e8
    virtual void OnDefocus(); //0x54 807f88c0
    virtual int func_0x58(); //807f88b8
    virtual int func_0x5c(); //807f88b0
    u8 GetPlayerId() const; //807f7e80

    Page *GetParentPage() const; //807f8274
    void Load(const char *variant, u8 hudSlotId); //0x2c 807f842c
    void SetTimer(Timer *timer); //807f84c0
    void DisableFlashingAnimation(); //807f8840
    void EnableFlashingAnimation(); //807f8878 if new best time or flap

    static RaceData *GetRacedata(); //807f7eb4
    static bool isBattle(RaceData *racedata); //807f82f4
    static bool isOnlineVS(RaceData *racedata); //807f83a4
    static bool isModeFlag4(RaceData *racedata); //807f83c4
    static void CheckTimer(Timer *timer, u8 *minutes, u8 *seconds, u16 *milliseconds); //807f8320, fills the ptrs if minutes < 99
    static bool IsTimerInvalid(Timer *timer); //807f8360
    static void ResetTimer(Timer *timer, u16 minutes, u8 seconds, u16 milliseconds); //807f8380
    static PageId GetParentPageId(Page *page); //807f826c
    static SectionId GetSectionId(); //807f8298
    static Section *GetCurSection(); //807f8288
    static bool isPaused(Section *curSection); //807f8280
    static void FillTimerGlobal(Timer *timer); //807f82ac global raceinfo timer
    static u8 GetPlayerMaxLap(u8 playerId); //807f7e64
    static bool hasPlayerFinished(u8 playerId); //807f82bc
    static bool isPlayerLast(u8 playerId); //807f83d0
    static void FillLapSplitTimer(u8 playerId, u32 lap, Timer *timer); //807f82dc used for splits
    static void FillFinishTimeTimer(u8 playerId, Timer *timer); //807f83f0
    u32 state; //0 not loaded, 1 loaded, 2 on unload?
    Timer timer; //0x19C
    u8 hudSlotId; //0x1A8
    u8 playerId;  //0x1A9
    u8 unknown_0x1AA[2]; //padding
    u32 idTimes3Plus1; //0x1AC
    u32 frames; //0x1B0 set to the number of active frames of Parent Page OnDeactivate, and then same on OnDeactivate, but never read?
    u8 unknown_0x1B4[0x1B8 - 0x1B4];
    u32 type; //0x1b8
    u8 unknown_0x1BC[0x1C0 - 0x1BC];
    u32 maxLap; //from raceinfoPlayer
}; //0x1C4

size_assert(CtrlRaceTime, 0x1C4);
#endif