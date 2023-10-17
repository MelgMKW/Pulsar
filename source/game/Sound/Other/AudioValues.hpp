#ifndef _AUDIO_VALUES_
#define _AUDIO_VALUES_

#include <kamek.hpp>
#include <core/egg/Audio/AudioTrack.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/Sound/SingleSoundPlayer.hpp>
#include <game/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

using namespace nw4r;

class SoundTrack : public EGG::AudioTrack {
    void Calc() override; //80717d2c vtable 808c91e0
    void SetValue(float minValue, float maxValue); //80717d08 if curVol > max then set to max, opposite for min

};//total size 0x1C

struct PitchModuler { //curModulingValue / 5 is added to curPitch; very suptle effect all things considered
    PitchModuler(float initialValue, float minValue, float incrementPerFrame); //80717d70
    float Update(); //80717d80
    float GetNextLimit(float curLimit); //80717e00 inlined
    float curModulingValue; //nextValue = curValue +- increment (based on whether above or under limit)
    float curLimit; //nextLimit = (max(1, (curLimit² + curLimit) + 1, minValue), initialized at initialValue
    float incrementPerFrame;
    float minValue;
}; //0x10

class SoundPlayersVolumeMgr {
    static SoundPlayersVolumeMgr* sInstance; //809c27ec
    static SoundPlayersVolumeMgr* CreateInstance(); //8070eff4
    static void DestroyInstance(); //8070f0e8
    ~SoundPlayersVolumeMgr(); //8070f19c
    void Calc(); //8070f3e8
    EGG::TDisposer<SoundPlayersVolumeMgr> disposer; //8070eec8 vtable 808c8f90
    static SoundTrack volumes[11]; //808b28b8 1 ramper = 1 soundPlayer
};

class SingleSoundPlayerValuesMgr { //allows a finer control of volume/pitch for one handle (ie basicsounc)
    static SingleSoundPlayerValuesMgr* sInstance; //809c232c
    static SingleSoundPlayerValuesMgr* CreateInstance(); //806f9abc
    static void DestroyInstance(); //806f9b64
    ~SingleSoundPlayerValuesMgr();//806f9c18
    void SetValue(u32 trackIdx, u32 stepCount, float maxValue); //806f9e78
    void Calc(); //806f9ce0
    void SetHandle(AudioHandle* handle); //806f9cbc inlined in SingleSoundPlayer::Calc
    void DetachHandle(); //806f9e14 inlined
    void UpdateTracks(); //806f9e20 inlined
    EGG::TDisposer<SingleSoundPlayerValuesMgr> disposer; //806f9990 vtable 808c78e0
    SoundTrack tracks[6]; //0x10 ALL volumes except index 2 which is pitch; their value is multiplied to set SoundPlayer 0 volume/pitch
    AudioHandle* curHandle; //0xb8
    u32 soundId; //0xbc
    float unknown_0xC0;
};

#endif