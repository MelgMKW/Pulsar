#ifndef _NW4R_SND3DMANAGER_
#define _NW4R_SND3DMANAGER_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/Sound3DListener.hpp>
#include <core/nw4r/snd/SoundActor.hpp>
#include <core/nw4r/snd/SoundArchivePlayer.hpp>
#include <core/nw4r/math.hpp>
#include <core/rvl/mtx/mtx.hpp>
#include <core/nw4r/snd/InstancePool.hpp>

namespace nw4r {
namespace snd {
class Sound3DManager;

namespace detail {
class Sound3DEngineInterface {
    virtual ~Sound3DEngineInterface();
    virtual void UpdateAmbientParam(const Sound3DManager* manager, const Sound3DParam* actorParam, u32 soundId,
        int voiceOutCount, SoundAmbientParam* param) = 0;
    virtual int GetAmbientPriority(const Sound3DManager* manager, const Sound3DParam* actorParam, u32 soundId) = 0;
    virtual int GetRequiredVoiceOutCount(const Sound3DManager* manager, const Sound3DParam* actorParam, u32 soundId) = 0;
};
}//namespace detail

struct Sound3DParam {
    Sound3DParam(); //8009db10
    math::VEC3 position;
    math::VEC3 velocity;
    u32 ctrlFlag; //1 = don't control volume, 2 = don't control pan, 3 = don't control surround pan, 4 = don't control priority
    u8 decayCurve;
    u8 decayRatio;
    u8 dopplerFactor;
    u32 actorUserParam;
    u32 soundUserParam;
};
class Sound3DEngine;

class Sound3DManager : public detail::BasicSound::AmbientParamUpdateCallback, public detail::BasicSound::AmbientArgAllocaterCallback {
public:
    typedef ut::LinkList<Sound3DListener, offsetof(Sound3DListener, link)> ListenerList;

    Sound3DManager(); //8009d8a0
    //AmbientParamUpdateCallback vtable 80274968
    ~Sound3DManager() override; //8009db40
    //Fills the ambient param using arg, which is almost always a Sound3DParam (the actor) that has been filled by ArgUpdateCB
    void detail_UpdateAmbientParam(const void* arg, u32 soundId, int voiceOutCount, SoundAmbientParam* param) override; //8009d9b0
    int detail_GetAmbientPriority(const void* arg, u32 soundId) override; //8009da00
    int detail_GetRequiredVoiceOutCount(const void* arg, u32 soundId) override; //8009da40

    //AmbientArgAllocaterCallback vtable 80274980 at 0x4
    //~Sound3DManager() override; //thunk 8009dbd0 func 
    void* detail_AllocAmbientArg(u32 argSize) override; //thunk 8009dbc0 func 8009da80
    void detail_FreeAmbientArg(void* arg, const detail::BasicSound* sound) override; //thunk 8009dbb0 func 8009daf0

    bool Setup(const SoundArchive* archive, void* buffer, u32 size); //8009d960
    void SetEngine(Sound3DEngine* engine); //8009d9a0
    u32 GetRequiredMemSize(const SoundArchive* archive); //8009d900

    detail::InstancePool<Sound3DParam> sound3DParamPool; //8
    ListenerList listenerList; //0xc
    detail::Sound3DEngineInterface* sound3DEngine; //18
    s32 maxPriorityReduction; //0x1c
    float panRange; //20
    float sonicVelocity; //24
}; //total size 0x28

extern Sound3DEngine engine; //802d5ba8 default engine?

}//namespace snd
}//namespace nw4r
#endif
