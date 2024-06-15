/*
Raceinfo is a class that stores various information about the race and players, as well as handling some RNG

Contributors:
  Seeky (main documentation)
  _tZ (RaceInfoPlayer attributes)
  Kevin (various attributes)
  Leseratte (race finish time attributes)
  stebler (intro timer attribute)
  Melg (battle score attribute)
*/

#ifndef _RACEINFO_
#define _RACEINFO_
#include <kamek.hpp>
#include <MarioKartWii/File/KMG.hpp>
#include <MarioKartWii/System/Timer.hpp>
#include <MarioKartWii/System/ElineManager.hpp>
#include <MarioKartWii/System/Random.hpp>
#include <MarioKartWii/Input/ControllerHolder.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/Race/RaceInfo/GameModeData.hpp>

enum RaceStage {
    RACESTAGE_INTRO,
    RACESTAGE_COUNTDOWN,
    RACESTAGE_RACE
};

class KMGHolder {
public:
    static u16 ConvertStageIdToIdx; //80538344 block plaza -> idx 0 etc...
    virtual ~KMGHolder(); //805371a8 vtable 808b34d8
    void SetKMG(KMG* rawKMG); //8053831c
    KMG* rawKMG;
}; //0x8

class RaceTimerMgrBase {
public:
    virtual ~RaceTimerMgrBase(); //80532de0 vtable 808b34c4
    virtual void Reset(); //80532d44
    virtual void Update(); //805336a0
    Timer timers[3];
    Random random;
};

class RaceTimerMgr : public RaceTimerMgrBase {
public:
    ~RaceTimerMgr() override; //805376e0 vtable 808b34b0
    void Reset() override; //80535864
    void Update() override; //80535904
    u8 unknown_0x40[0x50 - 0x40];
}; //Total size 0x50

class RaceInfoPlayer {
public:
    RaceInfoPlayer(u8 id, u8 lapCount); //80533ed8
    virtual ~RaceInfoPlayer(); //80532f48 vtable 808b34a4
    u8 UpdateGPHiddenScore(); //805368f8
    void FillTimerWithSplits(u8 lap, Timer* timer); //8053572c
    void UpdateRealLocal(); //805342e8 inlined
    void EndLap(); //805349b8
    void EndRace(const Timer& finishTime, bool hasNoCameras, u32 r6); //805347f4
    void Vanish(); //80534c78 for example when a ghost ends its race
    void Disconnect(); //80534cbc sets state to |0x10
    void UpdateCheckPoint(u16 cpId, bool isDrivingBackwards, float completion);
    void CopyCPUInputs(const Input::State& cpuState); //80535718

    u8 unknown_0x4[0x8 - 0x4];
    u8 id; //0x8
    u8 unknown_0x9; //might be padding
    u16 checkpoint; //0xa
    float raceCompletion; //0xc fraction of way through a lap (ex. 1.0 is the start of lap 1, 2.5 is half way through lap 2)
    float raceCompletionMax; //0x10
    float firstKcpLapCompletion; //0x14
    float nextCheckpointLapCompletion; //0x18
    float nextCheckpointLapCompletionMax; //0x1c
    u8 position; //0x20
    u8 respawn; //0x21
    u16 battleScore; //0x22
    u16 currentLap; //0x24
    u8 maxLap; //0x26
    u8 currentKCP;
    u8 maxKCP; //0x28
    u8 unknown_0x29[0x2c - 0x29];
    u32 frameCounter; //0x2c
    u32 framesInFirst; //0x30
    u8 unknown_0x34[0x38 - 0x34];
    u32 stateFlags; //0x38 bit flags:
    /*
      0x40 is coming last animation?
      0x20 is finishing the race?
      0x10 is a dc?
      0x4 is driving wrong way
      0x2 is end of race camera
      0x1 is in race?
    */
    Timer* lapSplits; //0x3c array of lapCount length
    Timer* raceFinishTime; //0x40
    u32 status; //0x44
    Input::RealControllerHolder* realControllerHolder; //0x48
    u8 unknown_0x4c[0x54 - 0x4c];
}; //Total size 0x54
size_assert(RaceInfoPlayer, 0x54);

class RaceInfo {
public:
    static RaceInfo* sInstance; //809bd730
    static RaceInfo* CreateInstance(); //80532084
    static void DestroyInstance(); //805320d4

    RaceInfo(); //805327a0
    virtual ~RaceInfo(); //80532e3c vtable 808b3350
    GMData* CreateGMData(GameMode gamemode); //80532188
    void Init(); //80532f88
    void Update(); //805331b4
    u8 GetLapCount(); //805336a4
    void SetPlayerDisconnected(u8 playerId); //80533d84 used if a player is disconnected
    bool IsAtLeastStage(RaceStage stage); //80536230
    bool CanRaceEnd(); //80536208
    const KMP::Holder<JGPT>* GetJGPTHolder(u8 playerId); //8053621c just wraps around GMData's virtual func
    const KMP::Holder<KTPT>* GetKTPTHolder(u8 playerId); //805365c8
    void GetInitialPhysicsValues(Vec3* position, Vec3* angles, u8 playerId); //805362dc
    s8 GetStartENPT(u8 playerId); //80536828 from ENPH 0
    KRT** GetRawKRT(); //805368c4 from GPDataGP else returns 0
    int GetBattleDuration(); //805326ec
    void ComputeDelfinoPierTideState(); //805330c0 inlined
    void CloneTimer(Timer* dest); //80535ca0
    void EndPlayerRace(u8 playerId); //80533c6c

    Random* random;
    Random* onlineAndTTRandom;
    RaceInfoPlayer** players; //pointer to an array of pointers, length is player count
    GMData* gamemodeData; //0x10
    RaceTimerMgr* timerMgr; //0x14
    u8* playerIdInEachPosition; //0x18 pointer to an array of player ids, 0 is the id in 1st, 1 is 2nd...
    u8 unknown_0x1c[2];
    s16 introTimer;
    u32 raceFrames; //0x20
    u8 randomUsedForBattleStartPoints; //0x24
    u8 randomUnknown_0x25;
    u8 padding[2]; //0x26
    RaceStage stage; //0x28
    u8 unknown_0x2c; //0x2c
    bool isSpectating; //0x2d
    bool canCountdownStart; //instantly true offline, needs syncing online
    bool cutSectionMode; //true for modes 11 & 12
    u8 unknown_0x30[0x3c - 0x30];
    KMGHolder* kmg; //0x3c
    ElineManager* elineManager; //0x40
    float unknown_0x44;
    bool isDelfinoPierTideLow; //0x48 unsure
    u8 unknown_0x49[3];
}; //Total size 0x4c
size_assert(RaceInfo, 0x4c);


#endif