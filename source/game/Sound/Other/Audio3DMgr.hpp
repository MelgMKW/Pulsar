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

class Audio3DMgr : public snd::Sound3DEngine {
    static snd::detail::BasicSound* curSound; //809c22d0 used by updateambientparam and then cleared
    static Audio3DMgr* sInstance; //809c2318
    static Audio3DMgr* GetStaticInstance(); //806f6a04
    static void DestroyStaticInstance(); //806f6a94
    ~Audio3DMgr() override; //806f6d4c vtable 808c77d8
    int GetAmbientPriority(
        const snd::Sound3DManager* sound3DManager,
        const snd::Sound3DParam* sound3DParam,
        u32 soundId
    ) override; //806f7608
    void UpdateAmbientParam(
        const snd::Sound3DManager* sound3DManager,
        const snd::Sound3DParam* sound3DParam,
        u32 soundId,
        int voiceOutCount,
        snd::SoundAmbientParam* ambientParam
    ) override; //806f6df4
    EGG::TDisposer<Audio3DMgr> disposer; //806f696c vtable 808c77f4
};

#endif