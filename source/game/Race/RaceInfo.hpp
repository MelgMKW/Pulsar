/*
Raceinfo is a class that stores various information about the race and players, as well as handling some RNG

Contributors:
  Seeky (main documentation)
  _tZ (RaceinfoPlayer attributes)
  Kevin (various attributes)
  Leseratte (race finish time attributes)
  stebler (intro timer attribute)
  Melg (battle score attribute)
*/
#ifndef _RACEINFO_
#define _RACEINFO_
#include <kamek.hpp>
#include <game/System/Timer.hpp>
#include <game/Input/InputData.hpp>
#include <game/System/Random.hpp>

class GmDataAbstract {
public:
    virtual int UpdateLocalPlayers(); //8053fb98
    virtual int HandlePositionTracking(); //8053f4a0
    class RaceInfo *raceinfo;
}; //Total size 0x8

class GmDataOnlineVsPlayer {
public:
    GmDataOnlineVsPlayer(); //80532488
    Timer raceFinishTime;
    u8 unknown_0xc[0x14 - 0xc];
}; //Total size 0x14

class GmDataOnlineVs : public GmDataAbstract {
public: //vtable override 808b3928
    //unknown virtual function 1
    int UpdateLocalPlayers() override; //8053fb98
    //unknown virtual function 3
    int HandlePositionTracking() override; //8053f4a0
    //unknown virtual functions 5-9
    //constructor was inlined
    GmDataOnlineVsPlayer players[12];
    u8 sendRH2[0x28]; //0x28 bytes
    u8 unknown_0x120[0x174 - 0x120];
}; //Total size 0x174

class TimerManager {
public:
    //ctor inlined
    virtual ~TimerManager(); //805376e0 vtable 808b34b0
    virtual int Reset(); //80535864
    virtual int Update(); //80535904
    Timer timers[3];
    Random random;
    u8 unknown_0x40[0x50 - 0x40];
}; //Total size 0x50

class RaceinfoRandom : public Random {
public:
    RaceinfoRandom(s32 r4); //80555514
}; //Total size 0x18

class RaceinfoPlayer {
public:
    RaceinfoPlayer(u8 id, u8 lapCount); //80533ed8
    virtual ~RaceinfoPlayer(); //80532f48 vtable 808b34a4
    u8 UpdateGpRankScore(); //805368f8
    void FillTimerWithSplits(u8 lap, Timer *timer); //8053572c
    u8 unknown_0x4[0x8 - 0x4];
    u8 id;
    u8 unknown_0x9; //might be padding
    u16 checkpoint;
    float raceCompletion; //fraction of way through a lap (ex. 1.0 is the start of lap 1, 2.5 is half way through lap 2)
    float raceCompletionMax;
    float firstKcpLapCompletion;
    float nextCheckpointLapCompletion;
    float nextCheckpointLapCompletionMax;
    u8 position;
    u8 respawn;
    u16 battleScore;
    u16 currentLap;
    u8 maxLap;
    u8 currentKCP;
    u8 maxKCP;
    u8 unknown_0x29[0x2c - 0x29];
    u32 frameCounter;
    u32 framesInFirst;
    u8 unknown_0x34[0x38 - 0x34];
    u32 stateFlags; //bit flags:
    /*
      64 is coming last animation?
      32 is finishing the race?
      16 is a dc?
      4 is driving wrong way
      2 is end of race camera
      1 is in race?
    */
    Timer *lapSplits; //array of lapCount length
    Timer *raceFinishTime; //0x40
    u8 unknown_0x44[0x48 - 0x44];
    ControllerHolder *controllerHolder; //see inputdata.h
    u8 unknown_0x4c[0x54 - 0x4c];
}; //Total size 0x54

class RaceInfo {
public:
    static RaceInfo *sInstance; //809bd730
    static RaceInfo *GetStaticInstance(); //80532084
    static void GestroyStaticInstance(); //805320d4
    static RaceinfoRandom *GetRandom(); //807bd718
    RaceInfo(); //805327a0
    void *SetupGamemodeData(u32 mode); //80532188
    bool IsAtLeastStage(u32 stage);

    virtual ~RaceInfo(); //80532e3c vtable 808b3350
    RaceinfoRandom *random1;
    RaceinfoRandom *random2;
    RaceinfoPlayer **players; //pointer to an array of pointers, length is player count
    void *gamemodeData; //different class for each gamemode
    TimerManager *timerManager;
    u8 *playerIdInEachPosition; //pointer to an array of player ids, 0 is the id in 1st, 1 is 2nd...
    u8 unknown_0x1c[2];
    s16 introTimer;
    u32 timer;
    u8 unknown_0x24[0x28 - 0x24];
    u32 stage; //0: intro camera, 1: countdown, 2: race
    u8 unknown_0x2c;
    bool isSpectating; //0x2d
    bool canCountdownStart; //instantly true offline, needs syncing online
    bool cutSectionMode; //true for modes 11 & 12
    u8 unknown_0x30[0x3c - 0x30];
    void *kmg;
    u8 unknown_0x40[0x4c - 0x40];
}; //Total size 0x4c
#endif