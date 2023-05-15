#ifndef _AUDIO_VOLUME_
#define _AUDIO_VOLUME_

#include <kamek.hpp>
#include <core/egg/Audio/AudioTrack.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/Sound/AudioHandle.hpp>
#include <game/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

using namespace nw4r;

class SoundTrack : public EGG::AudioTrack {
    void Calc() override; //80717d2c vtable 808c91e0
    void SetVolume(float minValue, float maxValue); //80717d08 if curVol > max then set to max, opposite for min

};//total size 0x1C

class SoundPlayersVolumeMgr {
    static SoundPlayersVolumeMgr* sInstance; //809c27ec
    static SoundPlayersVolumeMgr* GetStaticInstance(); //8070eff4
    static void DestroyStaTicInstance(); //8070f0e8
    ~SoundPlayersVolumeMgr(); //8070f19c
    EGG::TDisposer<SoundPlayersVolumeMgr> disposer; //8070eec8 vtable 808c8f90
    static SoundTrack volumes[11]; //808b28b8 1 ramper = 1 soundPlayer
};

class MainSoundPlayerVolumeMgr { //allows a finer control of soundplayer 0's volume
    static MainSoundPlayerVolumeMgr* sInstance; //809c232c
    static MainSoundPlayerVolumeMgr* GetStaticInstance(); //806f9abc
    static void DestroyStaticInstance(); //806f9b64
    ~MainSoundPlayerVolumeMgr();//806f9c18
    void SetVolume(u32 trackIdx, u32 stepCount, float maxVolume); //806f9e78
    EGG::TDisposer<MainSoundPlayerVolumeMgr> disposer; //806f9990 vtable 808c78e0
    SoundTrack volumes[6]; //0x10 their volume is multiplied and used to set SoundPlayer 0's volume
    AudioHandle* curHandle; //0xb8
    u32 soundId; //0xbc
    float unknown_0xC0;
};

#endif