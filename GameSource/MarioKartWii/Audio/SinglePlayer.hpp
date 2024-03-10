#ifndef _AUDIO_SINGLEPLAYER_
#define _AUDIO_SINGLEPLAYER_

#include <kamek.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

namespace Audio {
using namespace nw4r;

class Handle : public snd::SoundHandle { //sound handle with a ctor
    Handle(); //806f88e8
    ~Handle(); //806f88f4
};

class AutoStrmHandle : public snd::StrmSoundHandle { //auto detaches the sound
    ~AutoStrmHandle(); //806f98ac
};

//Has 2 handles but only one can be played at any point; for example on raceStart the track brstm is waiting and countdown is playing,
//starting the track brstm will stop the countdown
//Mostly useful when trying to prevent overlaps (BG music, countdown into race music etc...)
//as this has bools and checks in place to cancel the already playing/prepared sound should you try to start a new sound 
class SinglePlayer {
public:
    static SinglePlayer* sInstance; //809c2328
    static SinglePlayer* CreateInstance(); //806f8648
    static void DestroyInstance(); //806f86f0
    SinglePlayer(); //806f886c
    ~SinglePlayer(); //806f8934
    void Calc(); //806f8a64 decrements the delay and starts the activeHandle once it reaches 0

    //Plays the specified sound. If it is already prepared, uses that handle. Otherwise calls StartSound with a free handle. 
    //If it can't find one, overwrites the preparedHandle
    //Returns nullPtr if soundId already is the activeHandle, ie nothing was started
    Handle* PlaySound(u32 soundId, s16 delay); //806f8b7c

    //Prepare the specified sound. Will cancel the already prepared sound (if it exists) if r5 == true OR if there is no free handle
    //It can then be started by calling PlaySound with the same id 
    //OR by calling PlayPreparedSound (assuming prepareSound wasn't called again in btw)
    Handle* PrepareSound(u32 soundId, bool cannotBeOverwritten); //806f8dcc r5 == 0x24 bool

    //Plays the prepared sound irrespective of its soundId (no id arg) by moving it to activeHandle
    Handle* PlayPreparedSound(s16 delay); //806f9034

    void BlockActiveSoundChange(); //806f90b8 simply sets canNotCancel
    void StopSound(); //806f90c4 Stops the activeHandle
    bool StartSound(Handle* handle, u32 soundId); //806f913c
    void SetupActiveHandle(Handle* handle); //806f933c pauses the BasicSound of the handle and sets up MainVolumeMgr/StreamsMgr

    //Starts the activeHandle irrespective of any delay
    Handle* StartActiveSound(); //806f95d8

    //Finds the 1st free handle, and if there isn't one, stops prepared sound and uses that one
    Handle* GetFreeHandle(); //806f9698 inlined
    void PlayBGSound(u32 groupId); //806fa604 probably from another class

    void UpdateWaitTime(); //806fa678 inlined
    void CalcTitlePageNext(); //806fa738
    static void CalcWaitTime(u32 samplesPlayed, u32* samplesPlayedDest, u32* waitTime); //806f8220 this may reset samplePlayed
    float GetFanfareLength() const; //806f9728 returns -1 if not a fanfare
    void StopInactiveSounds(); //806f9900 stops sounds if their handle isn't active or prepared

    EGG::TDisposer<SinglePlayer> disposer; //806f84a8 vtable 808c78ec
    bool canNotCancel; //0x10 All functions that may start/stop a sound check this bool, if it is true, they do nothing
    u8 padding[3];
    Handle handles[2]; //0x14
    Handle activeHandle; //0x1c
    Handle preparedHandle; //0x20
    bool canNotPrepareOther; //0x24 if true, when trying to prepare a sound, if there already is a prepared sound, it cannot be overwritten
    u8 padding2;
    s16 delay; //after first ends, to start 2nd
    u32 samplesPlayedTitleWave; //not exacted samplesPlayed as it can be reset
    PageId nextMainMenuPageId; //0x34 used to check whether to go in the demo
    bool isDetaching;
    u8 padding3[3];
}; //0x3C
}//namespace Audio



#endif