#ifndef _NW4R_SND3DACTOR_
#define _NW4R_SND3DACTOR_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/SoundActor.hpp>
#include <core/nw4r/snd/Sound3DManager.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace snd {
class Sound3DActor : public SoundActor, public detail::BasicSound::AmbientArgUpdateCallback {
public:
    Sound3DActor(SoundArchivePlayer *soundArchivePlayer, Sound3DManager *sound3DManager); //8009c2a0
    //SoundActor vtable 80274918
    ~Sound3DActor() override; //8009c330
    StartResult SetupSound(SoundHandle *handle, u32 soundId, const StartInfo *startInfo, void *setupArg) override; //8009c410
    //AmbientArgUpdateCallback vtable 80274934 at 0x54
    //~Sound3DActor thunk 8009c650
    void detail_UpdateAmbientArg(void *arg, const detail::BasicSound *sound) override; //thunk 8009c640 func 8009c600 arg is Sound3DParam
    void SetPosition(const math::VEC3 &position); //8009c590
    void SetVelocity(const math::VEC3 &velocity); //8009c5e0
    Sound3DManager &manager; //58
    SoundArchivePlayer *soundArchivePlayer; //5c
    u32 userParam; //60
    math::VEC3 position;
    math::VEC3 velocity;
    bool resetPositionFlag;
    u8 padding[3];
}; //total size 0x80
size_assert(Sound3DActor, 0x80);
}//namespace snd
}//namespace nw4r


#endif