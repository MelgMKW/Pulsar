#ifndef _AUDIO_STREAMSMGR_
#define _AUDIO_STREAMSMGR_

#include <kamek.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/Audio/SinglePlayer.hpp>
#include <MarioKartWii/Audio/Other/AudioValues.hpp>
#include <MarioKartWii/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

namespace Audio {
using namespace nw4r;

class StreamsMgr {
public:
    static StreamsMgr* sInstance; //809c2330
    static StreamsMgr* CreateInstance(); //806fa0ac
    static void DestroyInstance(); //806fa154
    ~StreamsMgr(); //806fa208

    void PrepareStreams(Handle* handle, float* streamsVolume, u8 streamCount); //806fa2ac
    void ChangeStreamVolume(u8 streamIdx, u32 stepCount, float maxVolume); //806fa3fc
    void Calc(); //806fa420
    void ResetVolume(); //806fa5ac
    void ChangeMultipleStreamsVolume(float* volumes, u8 streamsToChange, u32 stepCount); //806faab4 changes from 0 to streamsToChange-1th
    void ChangeStream(u8 streamIdx, u32 stepCount); //806fab2c based on SoundId, this will change each stream's volume



    EGG::TDisposer<StreamsMgr> disposer; //806f9f80 vtable 808c78d4

    Track streamsVolume[10]; //0x10 first 4 for the usual 4 streams, idk of a sound with 10 streams though, maybe WFC main menu
    Handle* curHandle; //0x1d0
    u8 streamCount; //1d4
    u8 padding[3];
}; //0x1d8
}//namespace Audio



#endif