#ifndef _NW4R_SND3DMANAGER_
#define _NW4R_SND3DMANAGER_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/Sound3DListener.hpp>
#include <core/nw4r/snd/SoundActor.hpp>
#include <core/nw4r/snd/SoundArchivePlayer.hpp>
#include <core/nw4r/math/math.hpp>
#include <core/rvl/mtx/mtx.hpp>
#include <core/nw4r/snd/InstancePool.hpp>

namespace nw4r {
namespace snd {

namespace detail {
class Sound3DEngineInterface {
    virtual ~Sound3DEngineInterface() {}
};
}//namespace detail

struct Sound3DParam {
    math::VEC3 position;
    math::VEC3 velocity;
    u32 ctrlFlag;
    u8  decayCurve;
    u8  decayRatio;
    u8  dopplerFactor;
    u32 actorUserParam;
    u32 soundUserParam;
};
class Sound3DEngine;

class Sound3DManager : public detail::BasicSound::AmbientParamUpdateCallback, public detail::BasicSound::AmbientArgAllocaterCallback {
    Sound3DManager(); //8009d8a0
    //paramUpdate vtable 80274968
    ~Sound3DManager() override; //8009db40
    //argallocater vtable 80274980
    //~Sound3DManager(); //8009dbd0
    void *detail_AllocAmbientArg(u32 argSize) override; //8009dbc0 func 8009da80
    void SetEngine(Sound3DEngine *engine); //8009d9a0
    u32 GetRequiredMemSize(const SoundArchive *archive); //8009d900
    bool Setup(const SoundArchive *archive, void *buffer, u32 size); //8009d960
    detail::PoolImpl paramPool; //8
    ut::LinkList<Sound3DListener, offsetof(Sound3DListener, link)> listenerList; //0xc
    detail::Sound3DEngineInterface *sound3DEngine; //18
    s32 biquadFilterType; //24
    float panRange; //1c
    float sonicVelocity; //20
}; //total size 0x28




}//namespace snd
}//namespace nw4r
#endif
