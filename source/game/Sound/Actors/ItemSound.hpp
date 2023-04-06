#ifndef _ITEMSOUND_
#define _ITEMSOUND_
#include <kamek.hpp>
#include <game/Sound/Actors/RaceActor.hpp>

using namespace nw4r;

class ItemSound : public AudioActor<2>, public LinkedRaceActor {
public:
    ItemSound(); //807040dc

    //AUDIOACTOR
    //SoundActor vtable 808c8928
    ~ItemSound() override; //80706f3c

    //AudioActor vtable 808c84a0 at 0x54
    //~ItemSound thunk 80707094
    void detail_UpdateAmbientArg(void *arg, const snd::detail::BasicSound *sound) override; //thunk 8070708c func 80705728

    //LinkedRaceActor vtable 808c89a4 at 0x8c
    void Link(void *pointer, u16 objectId) override; //0x8 thunk 8070712c func 807042c0
    void Unlink() override; //0xc thunk 80707124 func 807042c8
    void Update() override; //0x10 thunk 8070711c func 807042d0
    Vec3 &GetPosition() const override; //0x14 thunk 80707114 func 807056f4
    void Reset() override; //0x18 thunk 8070710c func 807056b4
    void UpdateUserParam(u8 param) override; //0x1c thunk 80707104 func 807056fc
    void UpdateUserParam2(u8 param) override; //0x20 thunk 807070fc func 80705710
    void DisableConditional() override; //0x24 thunk 807070f4 func 807042ec if conditions are met
    void UpdateUserParam3() override; //0x28 thunk 807070ec func 80704324
    AudioHandle *StartSoundLimited(u32 soundId, float localVar) override; //0x30 thunk 807070e4 func 80704364 checks for conditions before thunk starting 
    AudioHandle *HoldSoundLimited(u32 soundId) override; //0x34 thunk 807070dc func 807046a0
    void StopAllSound(int fadeOutFrames) override; //0x38 thunk 807070d4 func 80705468
    AudioHandle *StartNewSoundLimited(u32 soundId, float volume) override; //0x3c thunk 807070cc func 80704998 if an handle is already set, does not start the sound 
    bool StartSound(u32 soundId, AudioHandle *handle) override; //0x4c thunk 807070bc func 807054cc
    bool StartSound(u32 soundId, AudioHandle *handle, const snd::SoundStartable::StartInfo *startInfo) override; //0x50 thunk 807070c4 func 80705540
    bool HoldSound(u32 soundId, AudioHandle *handle) override; //0x54 thunk 807070ac func 807055c0
    bool HoldSound(u32 soundId, AudioHandle *handle, const snd::SoundStartable::StartInfo *startInfo) override; //0x58 thunk 807070b4 func 80705634
    void SetupBRASD(snd::detail::AnimSoundFile *rawBRASD) override; //0x5c thunk 807070a4 func 80704f7c
    void UpdateBRASDFrame(float frame) override; //0x60 thunk 8070709c func 80704f80

};  // Total size 0xac
size_assert(ItemSound, 0xac);



class GessoSound : public AudioActor<1>, public LinkedRaceActor {
public:
    GessoSound(); //80704bd4

    //AUDIOACTOR
    //SoundActor vtable 808c81c8
    ~GessoSound() override; //80706fc8

    //AudioActor vtable 808c81e4 at 0x54
    //~GessoSound thunk 80707154 func 80706fc8
    void detail_UpdateAmbientArg(void *arg, const snd::detail::BasicSound *sound) override; //thunk 8070714c func 80705404

    //LinkedRaceActor vtable 808c8244 at 0x88
    void Link(void *pointer, u16 objectId) override; //0x8 thunk 807071e4 func 80704d78
    void Update() override; //0x10 thunk 807071dc func 80704d80
    Vec3 &GetPosition() const override; //0x14 thunk 807071d4 func 80705394
    void Reset() override; //0x18 thunk 807071cc func 80705354
    void UpdateUserParam(u8 param) override; //0x1c thunk 807071c4 func 8070539c
    void UpdateUserParam2(u8 param) override; //0x20 thunk 807071bc func 807053b0
    void DisableConditional() override; //0x24 thunk 807071b4 func 807053c8 if conditions are met
    void UpdateUserParam3() override; //0x28 thunk 807071ac func 807053e4
    AudioHandle *StartSoundLimited(u32 soundId, float localVar) override; //0x30 thunk 807071a4 func 80704d98 checks for conditions before thunk starting 
    AudioHandle *HoldSoundLimited(u32 soundId) override; //0x34 thunk 8070719c func 80705040
    void StopAllSound(int fadeOutFrames) override; //0x38 thunk 80707194 func 80705158
    AudioHandle *StartNewSoundLimited(u32 soundId, float volume) override; //0x3c thunk 8070718c func 80704f84 if an handle is already set, does not start the sound 
    bool StartSound(u32 soundId, AudioHandle *handle) override; //0x4c thunk 8070717c func 8070516c
    bool StartSound(u32 soundId, AudioHandle *handle, const snd::SoundStartable::StartInfo *startInfo) override; //0x50 thunk 80707184 func 807051e0
    bool HoldSound(u32 soundId, AudioHandle *handle) override; //0x54 thunk 8070716c func 80705260
    bool HoldSound(u32 soundId, AudioHandle *handle, const snd::SoundStartable::StartInfo *startInfo) override; //0x58 thunk 80707174 func 807052d4
    void SetupBRASD(snd::detail::AnimSoundFile *rawBRASD) override; //0x5c thunk 80707164 func 80704f74
    void UpdateBRASDFrame(float frame) override; //0x60 thunk 8070715c func 80704f78

};  // Total size 0xa8
size_assert(GessoSound, 0xa8);
#endif