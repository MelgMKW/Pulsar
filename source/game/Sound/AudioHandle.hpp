#ifndef _AUDIOHANDLE_
#define _AUDIOHANDLE_

#include <kamek.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

using namespace nw4r;

class AudioHandle : public snd::SoundHandle { //sound handle with a ctor
    AudioHandle(); //806f88e8
    ~AudioHandle(); //806f88f4
};

class AudioHandleHolder { //can hold 2 basicSound, for example on raceStart when the track brstm is waiting and countdown is playing
public:
    static AudioHandleHolder* sInstance; //809c2328
    static AudioHandleHolder* GetStaticInstance(); //806f8648
    static void DestroyStaticInstance(); //806f86f0
    AudioHandleHolder(); //806f886c
    ~AudioHandleHolder(); //806f8934
    EGG::TDisposer<AudioHandleHolder> disposer; //806f84a8 vtable 808c78ec
    void Calc(); //806f8a64
    void PlayBGSound(u32 groupId); //806fa604 probably from another class
    bool canCancel; //checked on a music switch then reset
    u8 padding[3];
    AudioHandle handles[2]; //0x14
    AudioHandle* activeHandle;
    AudioHandle* waitingHandle;
    u8 unknown_0x24[2];
    s16 delay; //after first ends, to start 2nd
    u32 unknown_0x28[3];
    PageId curPageId; //0x34 only updated mainMenu
    bool isDetaching;
    u8 padding2[3];
}; //0x3C




#endif