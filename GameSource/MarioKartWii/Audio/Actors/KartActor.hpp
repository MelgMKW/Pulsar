#ifndef _KARTACTOR_
#define _KARTACTOR_
#include <kamek.hpp>
#include <MarioKartWii/Audio/Actors/RaceActor.hpp>
#include <MarioKartWii/Audio/Other/AudioValues.hpp>


using namespace nw4r;
namespace Kart {
class Player;
}

class Object;

namespace Audio {
class EngineMgr;
class KartActor : public SimpleRaceActor { //LinkedRaceActor: 0xb2 is KCLVariant (when needed), 0xb3 is hudSlotId
public:
    static Vec3 DefaultVelocity; //809c2858 0.0f x3
    KartActor(); //8070722c

    //AUDIOACTOR
    //SoundActor vtable 808c8928
    ~KartActor() override; //807073ec
    StartResult SetupSound(snd::SoundHandle* handle, u32 soundId, const StartInfo* startInfo, void* setupArg) override; //8070803c
    //Actor vtable 808c8944 at 0x54
    //~Actor thunk 8070ca1c func 807073ec
    void detail_UpdateAmbientArg(void* arg, const snd::detail::BasicSound* sound) override; //thunk 807025c8 func 80701794

    //LinkedRaceActor vtable 808c89a4 at 0x94 
    void Link(void* pointer, u16 objectId) override; //thunk 8070ca84 func 80707534
    void Unlink() override; //thunk 8070ca7c func 80707648
    void Update() override; //thunk 8070ca74 func 807076d0
    void DisableConditional() override; //thunk 8070ca6c func 807074d0 when race has ended?
    void UpdateUserParam3() override; //thunk 8070ca64 func 80707514
    Handle* StartSoundLimited(u32 soundId, float localVar) override; //thunk 8070ca5c func 807082d8 checks if player is ghosts amongst others
    Handle* HoldSoundLimited(u32 soundId) override; //thunk 8070ca54 func 80708040
    void StopAllSound(int fadeOutFrames) override; //thunk 8070ca4c func 80707f7c
    Handle* StartNewSoundLimited(u32 soundId, float volume) override; //thunk 8070ca44 func 80709980
    bool StartSound(u32 soundId, Handle* handle) override; //thunk 8070ca3c func 807092b4
    bool HoldSound(u32 soundId, Handle* handle) override; //thunk 8070ca34 func 80709338

    virtual u32 GetRoadSoundId() const; //8070bb6c "0x12c" for stuff like mud that triggers even when driving normally
    virtual u32 GetBrakingSoundId() const; //8070bcbc "0x130"
    virtual u32 GetDriftAndSSMTRoadSoundId() const; //8070b8f0 "0x134" RR is the prime example of this
    virtual u32 GetLandingSoundId() const; //8070ba40 "0x138"

    void SetActorType(ActorType type); //807074b0
    static void OutputSoundToWiimotes(Handle* handle, u32 outputLineBitfield); //80708b20 inlined
    void ApplyKCLSoundTrigger(u8 soundTriggerVariant); //80708b44
    void PlayBoostSound(); //80708bac ramps do not count
    void PlayRampSound(); //80708d48
    void PlayCannonSound(); //80709150
    void PlayHornSound(const KartActor& other); //807091ac
    void PlayMTSounds(); //807093c4
    void PlayRoadSound(); //80709610
    void OnObjectNormalCollision(Object* object); //80709b08
    void OnObjectWallCollision(Object* object); //80709ca4
    //Massive switch that has multiple roles
    //Plays the collision sound itself
    //Plays the object's collided sound (for most, ID 0x229 which is some kind of bam sound)
    //Plays the characterSound
    void PlayObjectCollisionSounds(Object* object, u32 objectId, bool isInvincible, bool isInvincible2); //80709df8 isInvincible = star, etc..
    void PlayWallCollisionSound(); //8070afcc all but bushes
    void PlayBushCollisionSound(); //8070b09c
    void UpdateLapSounds(); //8070b250, can play sounds by itself based on certain conditions like lap transitions
    void UpdateKCLValues(); //8070b490
    void SetRoadState(u32 state); //8070b8dc
    void SetNonLocalVolumeAndPriority(); //8070be0c alters volume (and priority) if non-local
    void PlayOtherKartCollisionSound(); //8070c8e4
    void PlayEngineSound(u32 engineSoundId, float pitch, float volume); //8070c564
    void SetPitch(float pitch); //8070c758 set pitch will actually be 1-(0.4 * pitch); most notably used when the bullet starts to run out

    bool isChargingSSMT; //0xb4
    u8 padding[3];
    EngineMgr* engineMgr; //some sort of kart engine manager
    Handle handles[4]; //0xbc c4 seems to be the one used most of the times? cur handle?
    u8 unknown_0xCc[0xDb - 0xCc]; //0xd6 weird s16 cumulative speed
    u8 currentLap; //0xdb
    Kart::Player* kartPlayer; //0xdc
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
    u32 outputLineFlag; //0xf4 and of 1 << (hudslotIds + 1)
    u32 roadSate; //0xf8 0 = normal, 1 = on water, 2/3 = on silent road
};  // Total size 0xfc
size_assert(KartActor, 0xfc);

class EngineMgr {
public:

    void Init(KartActor* kartActor); //806fae60
    void Update(); //806fafb4
    void CalcSoundId(); //806fb2fc
    void CalcPitch(); //806fb640
    void CalcAccelerating(float curSpeed); //806fb444 both directions
    void CalcBraking(float curSpeed); //806fb558
    KartId kartId;
    u32 engineState; //1 braking, 2 accelerating both forwards and backwards, 3 nothing

    float baseAccelerationRPM; //0x8 engine RPM based on kart and CC
    float baseDeccelerationRPM; //0xc engine RPM same
    float baseBrakingPitch; //0x10 depends on kart
    float baseEnginePitch; //0x14
    float soundIncreasePerSpeedPercent; //0x18
    float unknown_0x1c[2];
    float curPitch; //0x24
    float unknown_0x28[2];

    PitchModuler moduler; //0x30

    float baseSpeed; //0x40
    u32 curSoundId; //0x44
    float curVolume; //0x48
    bool isAccelerating;
    u8 padding[3];
    KartActor* kartActor; //0x50
    Kart::Player* kartPlayer; //0x54

}; //0x58
}//namespace Audio


#endif