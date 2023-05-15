#ifndef _AUDIO_HEAP_MGR_
#define _AUDIO_HEAP_MGR_

#include <kamek.hpp>
#include <core/egg/Audio/AudioHeap.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

using namespace nw4r;

class AudioHeapClass {
public:
    virtual bool LoadState(u32 level); //806fe1b4 vtable 808c79f0
    virtual int GetCurrentLevel(); //806fe240
    virtual void SaveState(); //806fe0e0
    snd::SoundHeap heap; //0x4
    u8 unknown_0x30[0x60 - 0x30];
    EGG::SoundMessages messages[3]; //0x60
};

class AudioHeapMgr : public AudioHeapClass {
    static AudioHeapMgr* sInstance; //808c2350
    static AudioHeapMgr* GetStaticInstance(); //806fdc1c
    static void DestroyStaticInstance(); //806fdcec
    AudioHeapMgr(); //806fde08
    ~AudioHeapMgr(); //806fdf18
    using AudioHeapClass::LoadState; //vtable 808c7a10
    using AudioHeapClass::GetCurrentLevel;
    using AudioHeapClass::SaveState;
    EGG::TDisposer<AudioHeapMgr> disposer; //806fdae4 vtable 808c7a04
    bool unknown_0x100;
    u8 padding[3];
};




#endif