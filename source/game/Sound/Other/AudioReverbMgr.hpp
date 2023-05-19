#ifndef _AUDIO_REVERBMGR_
#define _AUDIO_REVERBMGR_

#include <kamek.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/Sound/Other/AudioValues.hpp>
#include <game/System/Identifiers.hpp>

using namespace nw4r;

class AudioReverbMgr {
    static AudioReverbMgr* sInstance; //809c2358
    static AudioReverbMgr* GetStaticInstance(); //806fe3e4
    AudioReverbMgr(); //806fe584
    static void DestroyStaticInstance(); //806fe4d0
    ~AudioReverbMgr(); //806fe654
    EGG::TDisposer<AudioReverbMgr> disposer; //806fe2b8 vtable 808c7a28
    void Disable(); //806fe6f8
    void Clear(); //806fe71c
    bool unknown_0x10;
    u8 padding[3];
    snd::detail::FxReverbHiParam params;
    SoundTrack volumes[4];
}; //ac

#endif