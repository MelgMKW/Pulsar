#ifndef _AUDIO_STREAMSMGR_
#define _AUDIO_STREAMSMGR_

#include <kamek.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/Sound/AudioHandle.hpp>
#include <game/Sound/Other/AudioVolume.hpp>
#include <game/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

using namespace nw4r;

class AudioStreamsMgr {
    static AudioStreamsMgr* sInstance; //809c2330
    static AudioStreamsMgr* GetStaticInstance(); //806fa0ac
    static void DestroyStaticInstance(); //806fa154
    ~AudioStreamsMgr(); //806fa208
    void ChangeStream(u8 streamId, u32 delay); //806fab2c
    void Calc(); //806fa420
    EGG::TDisposer<AudioStreamsMgr> disposer; //806f9f80 vtable 808c78d4

    SoundTrack streamsVolume[10]; //first 4 for the usual 4 streams, idk of a sound with 10 streams though
    AudioHandle* curHandle; //0x1d0
    u8 streamCount; //1d4
    u8 padding[3];
}; //0x1d8




#endif