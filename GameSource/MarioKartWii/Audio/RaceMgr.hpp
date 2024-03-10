#ifndef _RACEAUDIOMGR_
#define _RACEAUDIOMGR_
#include <kamek.hpp>
#include <core/nw4r/ut/List.hpp>
#include <MarioKartWii/Race/racedata.hpp>
#include <MarioKartWii/System/timer.hpp>
#include <MarioKartWii/Audio/Other/AudioValues.hpp>
#include <MarioKartWii/Audio/Actors/KartActor.hpp>
/*
Contributors:
-kHacker35000vr, Melg
*/

namespace Audio {
enum RaceState {
    RACE_STATE_INTRO = 0x2,
    RACE_STATE_BEFORECOUNTDOWN = 0x3,
    RACE_STATE_NORMAL = 0x4,
    RACE_STATE_FAST = 0x5,
    RACE_STATE_FINISHED = 0x7
};

struct CourseIdxToCourseID {
    CourseId courseID;
};

struct CourseIDToMusicID {
    u32 musicID;
};

class RaceMgr {
public:
    static RaceMgr* sInstance; //809c27f8
    static RaceMgr* CreateInstance(); //807104d0
    static void* DestroyInstance(); //80710520

    RaceMgr(); //80710688 also appends the Sound3DListeners (one per local player) to the 3DManager list
    ~RaceMgr(); //807108e8

    void SetRaceState(RaceState raceState); //80711ac4 changes music accordingly etc...
    void SetKartActor(KartActor* sound); //80713754
    void Init(); //80710a00
    void Calc(); //80710ca0
    void UpdateLocalPlayerParams(); //80711514
    void CheckRaceState(); //807125d4 can play final lap jingle, the winning/losing music etc...
    bool IsAPlayerInMega() const; //807117a0
    bool IsAPlayerInStar() const; //8071172c
    bool IsAPlayerSquishedOrSmall() const; //80711668

    void UpdatePlayerMatrix(); //80711198
    void StartRace(); //80711418 called by RSARSounds when trying to play the GO! sound

    EGG::TDisposer<RaceMgr> disposer; //80710340 vtable 808c8fdc
    CourseId courseId;
    u8 unknown_0x14[4];
    KartActor* kartActors[4]; //0x18
    u8 lastUsedKartActorSlot; //0x28
    u8 totalKartActors; //0x29
    u8 unknown_0x2a[0x30 - 0x2a];
    Timer unk_Timer;
    u8 maxLap; //0x3c all of these of the player mostinfront
    u8 lap; //0x3d
    u8 position;
    u8 playerIdFirstLocalPlayer; //0x3f 
    RaceState raceState; //0x40
    GameMode gameMode; //0x44
    GameType gameType; //0x48
    u8 localPlayerCount; //0x4c
    u8 playerCount; //0x4d
    u8 unknown_0x4e[0x54 - 0x4e];
    Track engineVolume;
    u8 unknown_0x70[0x8];
    nw4r::ut::List raceActorsList; //0x78 contains all the LinkedRaceActors
    //in Calc a loop calls their update function
    Mtx34 playerMats[4]; //0x84 used for Sound3DListener's mtx
    Vec3ZeroInit vec3s[4]; //0x144
    u8 unknown_0x174[4];
    static CourseIdxToCourseID trackIdxToCourseID[42];
};//Total Size 0x178
size_assert(RaceMgr, 0x178);
}//namespace Audio

#endif