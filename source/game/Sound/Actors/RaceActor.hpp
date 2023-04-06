#ifndef _RACEACTOR_
#define _RACEACTOR_
#include <core/nw4r/ut/List.hpp>
#include <core/nw4r/snd/AnimSound.hpp>
#include <core/nw4r/snd/AnimSoundFile.hpp>
#include <game/Sound/AudioManager.hpp>
#include <kamek.hpp>


using namespace nw4r;

template <int handleNum>
class AudioActor : public EGG::Audio3DActor { //value for <4>||<2>||<1>
public:
    //ctor always inlined
    //Sound3DActor vtable 808c7fa0||808c86c8||808c8408
    ~AudioActor() override; //807005b8||807041c4||80704c7c
    //Audio3DActor vtable 808c7fbc||808c86e4||808c8424 at 0x54
    //~AudioActor thunk 80702578 func 807005b8||thunk 80707054 func 807041c4||thunk 80707134 func 80704c7c
    using snd::Sound3DActor::detail_UpdateAmbientArg; //thunk 80702570 func 8009c600
    virtual void SetPosition(const Vec3 &position); //0x14 80700814||807042e8||80704d94
    //these check if any of the handles are set
    virtual AudioHandle *TryStartSound(u32 soundId); //0x18 807017f8||80706364||8070578c
    virtual AudioHandle *TryStopAndStartSound(u32 soundId, u32 handleIdToStop); //0x1c 807019d0||8070653c||80705964 stops handleToStop sound and starts a new one
    virtual AudioHandle *TryStartSound(u32 soundId) const; //0x20 80701884||807063f0||80705818
    virtual AudioHandle *TryStopAndStartSound(u32 soundId, u32 handleIdToStop) const; //0x24 80701a64||807065d0||807059f8
    virtual AudioHandle *TryStartSound(const char *soundName); //0x28 80701910||8070647c||807058a4
    virtual AudioHandle *TryStopAndStartSound(const char *soundName); //0x2c 80701af8||80706664||80705a8c stops current sound and starts a new one
    virtual AudioHandle *TryHoldSound(u32 soundId); //0x30 80701bb4||80706720||80705b48
    virtual AudioHandle *TryHoldSound(u32 soundId, u32 handleId); //0x34 80701ea0||80706a0c||80705e34
    virtual AudioHandle *TryHoldSound(u32 soundId) const; //0x38 80701fc9c||80706808||80705c30
    virtual AudioHandle *TryHoldSound(u32 soundId, u32 handleId) const; //0x3c 80701f08||80706a74||80705e9c
    virtual AudioHandle *TryHoldSound(const char *soundName); //0x40 80701d84||807068f0||80705d18
    virtual AudioHandle *TryHoldSound(const char *soundName, u32 handleId); //0x44 80701f70||80706adc||80705f04
    virtual AudioHandle *TryPrepareSound(u32 soundId); //0x48 80702014||80706b80||80705fa8
    virtual AudioHandle *TryStopAndPrepareSound(u32 soundId, u32 handleIdToStop); //0x4c 807021ec||80706d58||80706180
    virtual AudioHandle *TryPrepareSound(u32 soundId) const; //0x50 807020a0||80706c0c||80706034
    virtual AudioHandle *TryStopAndPrepareSound(u32 soundId, u32 handleIdToStop) const; //0x54 80702280||80706dec||80706214
    virtual AudioHandle *TryPrepareSound(const char *soundName); //0x58 8070212c||80706c98||807060c0
    virtual AudioHandle *TryStopAndPrepareSound(const char *soundName, u32 handleIdTopStop); //0x5c 80702314||80706e80||807062a8
    AudioHandle handles[handleNum]; //0x80
    u32 handleCount; //0x90 unsure
}; //0x94||0x8C||0x88

class LinkedRaceActor { //actors managed by RaceAudioManager //nw4r has a similar "LinkedObject" so names copied
    static u16 actorCount; //809c26a0
    LinkedRaceActor(); //80702678
    ~LinkedRaceActor(); //807026cc
    virtual void Link(void *pointer, u16 objectId); //0x8 80702714 vtable 808c8020 appends to the list
    virtual void Unlink(); //0xc 807027d0
    virtual void Update() = 0; //0x10
    virtual Vec3 &GetPosition() const = 0; //0x14
    virtual void Reset(); //0x18 8070296c
    virtual void UpdateUserParam(u8 param) = 0; //0x1c
    virtual void UpdateUserParam2(u8 param) = 0; //0x20
    virtual void DisableConditional() = 0; //0x24 if conditions are met
    virtual void UpdateUserParam3() = 0; //0x28
    virtual void SetSoundParams(snd::Sound3DParam *param, snd::detail::BasicSound *sound); //0x2c 807029e0 sets basicSound and if inherited, Sound3dParam
    virtual AudioHandle *StartSoundLimited(u32 soundId, float localVar) = 0; //0x30 checks for conditions before starting
    virtual AudioHandle *HoldSoundLimited(u32 soundId) = 0;  //0x34
    virtual void StopAllSound(int fadeOutFrames) = 0; //0x38
    virtual AudioHandle *StartNewSoundLimited(u32 soundId, float volume) = 0; //0x3c no overlap; if an handle is already set, does not start the sound
    virtual bool StartSound(u32 soundId); //40 807013a0 
    virtual bool HoldSound(u32 soundId); //44 80701398 returns false as this has no AudioHandle natively
    virtual void StopSound(int fadeOutFrames); //0x48 80701394 just a blr as this has no AudioHandle natively
    virtual bool StartSound(u32 soundId, AudioHandle *handle) = 0; //0x4c
    virtual bool StartSound(u32 soundId, AudioHandle *handle, const snd::SoundStartable::StartInfo *startInfo) = 0; //0x50
    virtual bool HoldSound(u32 soundId, AudioHandle *handle) = 0; //0x54
    virtual bool HoldSound(u32 soundId, AudioHandle *handle, const snd::SoundStartable::StartInfo *startInfo) = 0; //0x58
    virtual void SetupBRASD(snd::detail::AnimSoundFile *rawBRASD) = 0; //0x5c
    virtual void UpdateBRASDFrame(float frame) = 0; //0x60

    bool CannotPlaySounds(); //807028e4 if it returns 1, the actor is forbidden from playing sounds
    Vec3 *GetKartPosition() const; //807029cc only call if the subject is Kart
    Vec3 *GetObjectPosition() const; //807029d4 called by RaceAudioActor update, so that HAS to be overridden

    //+0x20 to get "final" classes offsets
    void *pointer; //Kart, ItemObj etc.. depends on the child class
    u16 objectId; //0x8 item, kart, etc.. depends on the child class
    bool isUnlinked; //0xa to prevent double removes
    bool isLinked; //0xb to prevent double appends
    u32 unknown_0xC;
    u16 actorIdx; //0x10 count
    u8 padding[2];
    ut::Link actorLink; //0x14
    bool unknown_0x1C;
    bool isDisabled; //0x1D bad name but when true, resets actor velocity; holding at true resets every frame so essentially disables the actor
    u8 unknown_0x1e;
    u8 id; //hudslotid, item id, depends on actor
}; //0x20

class RaceAudioActor : public AudioActor<4>, public LinkedRaceActor {
    //no ctor
    //AUDIOACTOR
    //Sound3DActor vtable 808c7d60
    ~RaceAudioActor() override; //807009bc
    StartResult SetupSound(snd::SoundHandle *handle, u32 soundId, const StartInfo *startInfo, void *setupArg) override; //80700818

    //AudioActor vtable 808c7d7c at 0x54
    //~AudioActor thunk 80702588 func 807009bc
    void detail_UpdateAmbientArg(void *arg, const snd::detail::BasicSound *sound) override; //thunk 807025c8 func 80701794

    //LinkedRaceActor vtable 808c7ddc at 0x94 
    void Update() override; //thunk 80702670 func 807007cc
    Vec3 &GetPosition() const override; //thunk 80702668 func 80701760
    void Reset() override; //thunk 80702660 func 8058bde0
    void UpdateUserParam(u8 param) override; //thunk 80702658 func 80701768
    void UpdateUserParam2(u8 param) override; //thunk 80702650 func 8070177c
    void DisableConditional() override; //thunk 80702648 func 80700b80
    void UpdateUserParam3() override; //thunk 80702640 func 80700bbc

    AudioHandle *StartSoundLimited(u32 soundId, float localVar) override; //thunk 80702638 func 80700d4c
    AudioHandle *HoldSoundLimited(u32 soundId) override; //thunk 80702630 func 807014e8
    void StopAllSound(int fadeOutFrames) override; //thunk 80702628 func 807016fc
    AudioHandle *StartNewSoundLimited(u32 soundId, float volume) override; //thunk 80702620 func 807013a8
    bool StartSound(u32 soundId, AudioHandle *handle) override; //thunk 807025f8 func 80701154
    bool StartSound(u32 soundId, AudioHandle *handle, const StartInfo *startInfo) override; //thunk 80702600 func 807011e0
    bool HoldSound(u32 soundId, AudioHandle *handle) override; //thunk 807025e8 func 80701274
    bool HoldSound(u32 soundId, AudioHandle *handle, const StartInfo *startInfo) override; //thunk 807025f0 func 80701300
    void SetupBRASD(snd::detail::AnimSoundFile *rawBRASD) override; //thunk 807025e0 func 80700728
    void UpdateBRASDFrame(float frame) override; //thunk 807025d8 func 80700754

}; //0xb4

class SimpleRaceAudioActor : public RaceAudioActor { //for actors without BRASD support
    //no ctor
    //AUDIOACTOR
    //Sound3DActor vtable 808C8A68
    ~SimpleRaceAudioActor() override; //80707360

    //AudioActor vtable 808c8a84 at 0x54
    //~AudioActor thunk 8070ca14 func 80707360

    //LinkedRaceActor vtable 808C8AE4 at 0x94 
    void Update() override = 0;
    void SetupBRASD(snd::detail::AnimSoundFile *rawBRASD) override; //thunk 8070ca2c func 8070ca08 just a blr as no brasd
    void UpdateBRASDFrame(float frame) override; //thunk 8070ca24 func 8070ca0c just a blr

}; //0xb4


class AnimAudio : public snd::detail::AnimSoundImpl { //BRASD for example penguins
    snd::detail::AnimEventPlayer players[2];
}; //0x40

class RaceAnimAudioActor : public RaceAudioActor {
    RaceAnimAudioActor(); //80701018
    //AUDIOACTOR
    //SoundActor vtable 808c7b00
    ~RaceAnimAudioActor() override; //80702498
    //AudioActor vtable 808c7b1c
    //~AudioActor thunk 807025d0 func

    //LinkedRaceActor vtable 808c7b7c at 0x94 
    bool StartSound(u32 soundId) override; //thunk 80702618 func 80701140
    bool HoldSound(u32 soundId) override; //thunk 80702610 func 80701260
    void StopSound(int fadeOutFrames) override; //thunk 80702608 func 80701380
    AnimAudio animAudio; //0xb4
    snd::detail::AnimSoundFile *rawBRASD; //0xf4
    AudioHandle handle; //0xf8
}; //0xfc

#endif