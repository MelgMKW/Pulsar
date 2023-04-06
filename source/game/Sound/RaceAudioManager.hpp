#ifndef _MUSICHANDLER_
#define _MUSICHANDLER_
#include <kamek.hpp>
#include <core/nw4r/ut/List.hpp>
#include <game/Race/racedata.hpp>
#include <game/System/timer.hpp>
#include <game/Sound/Actors/KartSound.hpp>
/*
Contributors:
-kHacker35000vr, Melg
*/

enum RaceState {
    RACE_STATE_INTRO = 0x2,
    RACE_STATE_BEFORECOUNTDOWN = 0x3,
    RACE_STATE_NORMAL = 0x4,
    RACE_STATE_FAST = 0x5,
    RACE_STATE_FINISHED = 0x7
};

struct CourseNbrToCourseID {
    CourseId courseID;
};

struct CourseIDToMusicID {
    u32 musicID;
};

class RaceAudioMgr {
public:
    static RaceAudioMgr *sInstance; //0x809c27f8
    static RaceAudioMgr *GetStaticInstance(); //807104d0
    static void *DestroyStaticInstance(); //80710520
    static u32 GetCourseSoundId(); //807101f4
    static u32 trackToMusicIDTable[42]; //808a1d80 battle
    RaceAudioMgr(); //0x80710688
    ~RaceAudioMgr(); //807108e8
    void ChangeMusic(RaceState raceState);
    void SetKartSound(KartSound *sound); //80713754
    void Init(); //80710a00
    void Calc(); //80710ca0
    void UpdateLocalPlayerParams(); //80711514
    void CheckRaceState(); //807125d4 can play final lap jingle, the winning/losing music etc...
    EGG::TDisposer<RaceAudioMgr> disposer; //80710340 vtable 0x808c8fdc
    CourseId courseId;
    u8 unknown_0x14[4];
    KartSound *kartSounds[4]; //0x18
    u8 lastUsedKartSoundSlot;
    u8 totalKartSounds;
    u8 unknown_0x28[0x30 - 0x2a];
    Timer unk_Timer;
    u8 maxLap; //0x3c all of these of the player mostinfront
    u8 lap; //0x3d
    u8 position;
    u8 playerIdFirstLocalPlayer; //0x3f 
    u32 raceState;
    GameMode gameMode;
    GameType gameType;
    u8 localPlayerCount;
    u8 playerCount;
    u8 unknown_0x4e[0x54 - 0x4e];
    SoundTrack engineVolume;
    u8 unknown_0x70[0x8];
    nw4r::ut::List actorsList; //0x78 contains all the classes that can generate sound; KartSound, an ItemSound class, an EffectSound etc..., 
    //in Calc a loop calls their update function
    Mtx34 playerMats[4]; //0x84 not completely sure
    Vec3ZeroInit vec3s[4]; //0x144
    u8 unknown_0x174[4];
};//Total Size 0x178
size_assert(RaceAudioMgr, 0x178);
extern CourseNbrToCourseID trackNbrToCourseID[42];

#endif