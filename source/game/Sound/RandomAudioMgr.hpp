#ifndef _RANDOMAUDIOMGR_
#define _RANDOMAUDIOMGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/System/Random.hpp>

class AudioRandomMgr : public Random { //is used to get 12 seeds 809c4740 + 4728[id] which impact character sounds etc...
    static AudioRandomMgr *sInstance; //809c4738
    static AudioRandomMgr *GetStaticInstance(); //80866ddc
    static void DestroyStaticInstance(); //80866e64
    ~AudioRandomMgr() override; //80866e98 vtable 808dbdf0
    u32 RandInt(u32 min, u32 max); //80866f4c non-inclusive
    float RandFloat(float min, float max); //80866f80
    EGG::TDisposer<AudioRandomMgr> disposer; //80866d44 vtable 808dbdfc
}; //0x28

class RandomSoundPicker : public Random { //one per type
    RandomSoundPicker(); //8086708c
    ~RandomSoundPicker() override; //80863a44 vtable 808dbe08
    u32 initialSoundId; //depends on character/object Id
    u32 prevSoundId; //adds 1 to 0x18 modulo number of sounds
    u8 unknown_0x20[6];
    u8 soundCount; //0x26
    u8 unknown_0x27[0x2c - 0x27];
}; //0x30
#endif