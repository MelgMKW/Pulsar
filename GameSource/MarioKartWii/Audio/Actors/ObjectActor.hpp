#ifndef _OBJECTACTOR_
#define _OBJECTACTOR_
#include <kamek.hpp>
#include <MarioKartWii/Audio/Actors/RaceActor.hpp>

namespace Audio {
using namespace nw4r;
//ObjFlow has 3 sound values, not sure what they do hence the names
class ObjectActor : public SimpleRaceActor { //type 1 
    ObjectActor(); //8070ca8c

    //AUDIOACTOR
    //SoundActor vtable 808c8b88
    ~ObjectActor() override; //8070cb78
    StartResult SetupSound(snd::SoundHandle* handle, u32 soundId, const StartInfo* startInfo, void* setupArg) override; //8070e674

    //Actor vtable 808c8ba4 at 0x54
    //~Actor thunk 8070e770 func 8070cb78

    //LinkedRaceActor vtable 808c8c04 at 0x94 
    void Link(void* pointer, u16 objectId) override; //0x8 thunk 8070e7b0 func 8070cd38
    void Unlink() override; //0xc thunk 8070e7a8 func 8070cd30
    void Update() override; //0x10 thunk 8070e7a0 func 8070cc08
    void DisableConditional() override; //0x24 thunk 8070e798 func 8070e188
    void UpdateUserParam3() override; //0x28 thunk 8070e790 func 8070e5f0
    Handle* StartSoundLimited(u32 soundId, float localVar) override; //0x30 thunk 8070e788 func 8070ce00
    Handle* HoldSoundLimited(u32 soundId) override;  //0x34 thunk 8070e780 func 8070d978
    Handle* StartNewSoundLimited(u32 soundId, float volume) override; //0x3c thunk 8070e778 func 8070dc8c

    u32 unknown_0xb4;
}; //0xb8


class ObjectActorAnim : public RaceAnimActor { //type 3 presumably if the object supports BRASDs
    ObjectActorAnim(); //807029f0

    //AUDIOACTOR
    //SoundActor vtable 808c8088
    ~ObjectActorAnim() override; //80703fb0
    StartResult SetupSound(snd::SoundHandle* handle, u32 soundId, const StartInfo* startInfo, void* setupArg) override; //80703ac8
    //Actor vtable 808c8944 at 0x54
    //~Actor thunk 8070408c func 80703fb0

    //LinkedRaceActor vtable 808c8104 at 0x94 
    void Link(void* pointer, u16 objectId) override; //0x8 thunk 807040d4 func 80702a84
    void Unlink() override; //0xc thunk 807040cc func 80702af4
    void Update() override; //0x10 thunk 807040c4 func 80702afc
    void DisableConditional() override; //0x24 thunk 807040bc func 80703d64
    void UpdateUserParam3() override; //0x28 thunk 807040b4 func 80703f00
    Handle* StartSoundLimited(u32 soundId, float localVar) override; //0x30 thunk 807040ac func 80702b00
    Handle* HoldSoundLimited(u32 soundId) override;  //0x34 thunk 807040a4 func 807030a4
    Handle* StartNewSoundLimited(u32 soundId, float volume) override; //0x3c thunk 8070409c func 807034c4
    bool StartSound(u32 soundId) override; //0x40 thunk 80704094 func 807036cc
}; //0xFC
}//namespace Audio

#endif