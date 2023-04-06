#ifndef _KARTSOUND_
#define _KARTSOUND_
#include <kamek.hpp>
#include <game/Sound/Actors/RaceActor.hpp>

using namespace nw4r;
class Kart;
class KartSound : public SimpleRaceAudioActor {
public:
    static Vec3 DefaultVelocity; //809c2858 0.0f x3
    KartSound(); //8070722c

    //AUDIOACTOR
    //SoundActor vtable 808c8928
    ~KartSound() override; //807073ec
    StartResult SetupSound(snd::SoundHandle *handle, u32 soundId, const StartInfo *startInfo, void *setupArg) override; //8070803c
    //AudioActor vtable 808c8944 at 0x54
    //~AudioActor thunk 8070ca1c func 807073ec
    void detail_UpdateAmbientArg(void *arg, const snd::detail::BasicSound *sound) override; //thunk 807025c8 func 80701794

    //LinkedRaceActor vtable 808c89a4 at 0x94 
    void Link(void *pointer, u16 objectId) override; //thunk 8070ca84 func 80707534
    void Unlink() override; //thunk 8070ca7c func 80707648
    void Update() override; //thunk 8070ca74 func 807076d0
    void DisableConditional() override; //thunk 8070ca6c func 807074d0 when race has ended?
    void UpdateUserParam3() override; //thunk 8070ca64 func 80707514
    AudioHandle *StartSoundLimited(u32 soundId, float localVar) override; //thunk 8070ca5c func 807082d8 checks if player is ghosts amongst others
    AudioHandle *HoldSoundLimited(u32 soundId) override; //thunk 8070ca54 func 80708040
    void StopAllSound(int fadeOutFrames) override; //thunk 8070ca4c func 80707f7c
    AudioHandle *StartNewSoundLimited(u32 soundId, float volume) override; //thunk 8070ca44 func 80709980
    bool StartSound(u32 soundId, AudioHandle *handle) override; //thunk 8070ca3c func 807092b4
    bool HoldSound(u32 soundId, AudioHandle *handle) override; //thunk 8070ca34 func 80709338

    void SetLinked_0xC(u32 r4); //807074b0
    int GetRoadSound() const; //8070b8f0 actually virtual, but missing the middle class 
    void UpdateLapSounds(); //8070b250, can play sounds by itself based on certain conditions like lap transitions
    void UpdateMTSounds(); //807093c4

    bool isChargingSSMT; //0xb4
    u8 padding[3];
    UnkType *unkClass_0xb8; //some sort of kart engine manager
    AudioHandle handles[4]; //0xbc c4 seems to be the one used most of the times? cur handle?
    u8 unknown_0xCc[0xDb - 0xCc]; //0xd6 weird s16 cumulative speed
    u8 currentLap; //0xdb
    Kart *kart; //0xdc
    bool isLocal; //0xe0
    bool isGhost; //0xe1
    u8 wheelCount; //0xe2
    u8 unknown_0xe3;
    u32 team; //0xe4
    bool isColliding; //0xe8 bitfield 0 any wheel collision from status
    u8 driftState; //0xe9 from kartMovement
    u8 unknown_0xea[2];
    float speedNorm; //0xec
    u16 kclFlag; //0xf0
    u16 variant; //0xf2
    u8 unknown_0xF4[0xfc - 0xf4];
};  // Total size 0xfc
size_assert(KartSound, 0xfc);
#endif