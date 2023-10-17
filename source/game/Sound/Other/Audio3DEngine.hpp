#ifndef _AUDIO_3DMGR_
#define _AUDIO_3DMGR_

#include <kamek.hpp>
#include <core/nw4r/snd.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

using namespace nw4r;

class Audio3DEngine : public snd::Sound3DEngine {
    static snd::detail::BasicSound* curSound; //809c22d0 used by updateambientparam and then cleared
    static Audio3DEngine* sInstance; //809c2318
    static Audio3DEngine* CreateInstance(); //806f6a04
    static void DestroyInstance(); //806f6a94

    Audio3DEngine(); //806f6c68
    ~Audio3DEngine() override; //806f6d4c vtable 808c77d8

    int GetRequiredVoiceOutCount(const snd::Sound3DManager* sound3DManager, const snd::Sound3DParam* actorParam,
        u32 soundId) override; //0x14 806f7608 returns listener count, so one voice per listener
    //Fills the ambient param using actorParam, thas has been filled by the Sound3DActor itself, and the Listener list of 3DManager
    void UpdateAmbientParam(const snd::Sound3DManager* sound3DManager, const snd::Sound3DParam* actorParam, u32 soundId,
        u32 updateFlag, snd::SoundAmbientParam* ambientParam) override; //0x18 806f6df4

    void SetCurSound(snd::detail::BasicSound* sound); //806f6ac8

    EGG::TDisposer<Audio3DEngine> disposer; //806f696c vtable 808c77f4
};

#endif