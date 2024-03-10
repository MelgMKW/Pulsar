#ifndef _AUDIO_REVERBMGR_
#define _AUDIO_REVERBMGR_

#include <kamek.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/Audio/Other/AudioValues.hpp>
#include <MarioKartWii/System/Identifiers.hpp>

namespace Audio {
using namespace nw4r;

class ReverbMgr {
    static ReverbMgr* sInstance; //809c2358
    static ReverbMgr* CreateInstance(); //806fe3e4
    ReverbMgr(); //806fe584
    static void DestroyInstance(); //806fe4d0
    ~ReverbMgr(); //806fe654
    void Prepare(const snd::detail::FxReverbHiParam& params); //806fe8ac calls AudioFxMgr::CreateFxReverb and sets bool
    void Play(); //806fe944
    void Disable(); //806fe6f8
    void Disable2(); //806fe9bc
    void Clear(); //806fe71c

    EGG::TDisposer<ReverbMgr> disposer; //806fe2b8 vtable 808c7a28
    bool unknown_0x10; //0x10
    u8 padding[3];
    snd::detail::FxReverbHiParam params; //0x14
    Track volumes[4]; //0x3c
}; //ac
}//namespace Audio
#endif