#ifndef _AMBIENCE_
#define _AMBIENCE_
#include <kamek.hpp>
#include <MarioKartWii/Sound/Other/AudioValues.hpp>


class Ambience {
    Ambience(); //806fd624
    ~Ambience(); //806fd6b0
    void Update(); //806fd818
    bool IsPlayingSoundId(u32 soundId) const; //806fd73c
    void PlayAmbience(u8 hudSlotId, u32 soundId); //806fd770 inlined
    void ResetVolume(u8 hudSlotId); //806fd7d4 sets it to 1.0f if it is currently <= 0
    void SetVolume(u8 hudSlotId, u32 stepCount, float volume); //806fd800
    AudioHandle handle;
    SoundTrack volumes[4]; //0x4 one per hudSlotId
}; //0x74

class RaceAmbienceMgr {
public:
    static RaceAmbienceMgr* sInstance; //809c2338
    static RaceAmbienceMgr* CreateInstance(); //806fb8b8
    static void DestroyInstance(); //806fb964
    RaceAmbienceMgr(); //806fbab0
    ~RaceAmbienceMgr(); //806fbb70
    void Init(CourseId courseId); //806fbc90 
    void StopGlobalSound(); //806fbcc4 irrespective of its id
    void StopGlobalSoundFadeOut(); //806fbe14 20 frames of fadeOut
    void Update(); //806fbcdc
    //sets the volume of the Ambience who is tied to the sound id (if it exists)
    void SetAmbienceVolume(u32 soundId, u32 stepCount, u8 hudSlotId, float volume); //806fcefc 
    void PlayAmbience(u32 soundId, u8 hudSlotId); //806fcda8
    bool PlayGlobalSound(u32 soundId); //806fcba0
    void StopGlobalSound(u32 soundId, int fadeOutFrames); //806fcd74 only stops it if it matches soundId
    void SetAllAmbiencesVolume(u8 hudSlotId, u32 stepCount, float volume); //806fcfa0
    void UpdateAmbiences(); //806fd03c inlined

    //Is called during the intro once and then every time the camera switches
    //For example on LC, helicopter->crowd->louder crowd->stop
    void PlayIntroAmbience(); //806fbe30 

    void UpdateVeniceAndRingMissionAmbiences(); //806fd0ac

    static u8 playerCount; //809c2349
    EGG::TDisposer<RaceAmbienceMgr> disposer; //806fb720 vtable 808c79e4
    CourseId courseId; //0x10
    u8 introStep; //increments by 1 everytime playintro is called
    AudioHandle globalSounds; //0x18 shocks, POW, BOMBS, blue shells etc...
    Ambience susb[3]; //0x1c up to 3, for example MG has 2 (the wind and the cave)

    AudioHandle handle2; //0x178
    float unknown_0x17c;
    u32 unknown_0x180[2];
    u8 unknown_0x188[4];//0x188
    AudioHandle handle3; //0x18c

}; //0x190


#endif