#ifndef _AUDIO_3DMGR_
#define _AUDIO_3DMGR_

#include <kamek.hpp>
#include <core/nw4r/snd.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

namespace Audio {
using namespace nw4r;

class Engine3D : public snd::Sound3DEngine {
    static snd::detail::BasicSound* curSound; //809c22d0 used by updateambientparam and then cleared
    static Engine3D* sInstance; //809c2318
    static Engine3D* CreateInstance(); //806f6a04
    static void DestroyInstance(); //806f6a94

    Engine3D(); //806f6c68
    ~Engine3D() override; //806f6d4c vtable 808c77d8

    int GetRequiredVoiceOutCount(const snd::Sound3DManager* sound3DManager, const snd::Sound3DParam* actorParam,
        u32 soundId) override; //0x14 806f7608 returns listener count, so one voice per listener
    //Fills the ambient param using actorParam, thas has been filled by the Sound3DActor itself, and the Listener list of 3DManager
    void UpdateAmbientParam(const snd::Sound3DManager* sound3DManager, const snd::Sound3DParam* actorParam, u32 soundId,
        u32 updateFlag, snd::SoundAmbientParam* ambientParam) override; //0x18 806f6df4

    void SetCurSound(snd::detail::BasicSound* sound); //806f6ac8

    EGG::TDisposer<Engine3D> disposer; //806f696c vtable 808c77f4
};
}//namespace Audio
#endif