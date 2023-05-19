#ifndef _SOUNDTRIGGERMGR_
#define _SOUNDTRIGGERMGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>

class Kart;

class SoundTriggerMgr {
public:
    static SoundTriggerMgr* sInstance; //809c28a8
    static SoundTriggerMgr* GetStaticInstance(); //80718414
    static void DestroyStaticInstance(); //80718498
    SoundTriggerMgr(); //8071854c
    ~SoundTriggerMgr(); //807185a4
    void Update(); //80718f48 effectively does nothing
    void Init(); //80718720 just calls ApplyTrigger
    void ApplyTrigger(s32 variant, s32 hudSlotId, Kart* kart); //80719044
    bool IsAPlayerOnVariant(s32 variant) const; //80718ef8
    bool IsPlayerAheadOfOtherLocal(u8 hudSlotId); //80718f84 inlined 

    EGG::TDisposer< SoundTriggerMgr> disposer; //807182e8 vtable 808c9418
    bool unknown_0x10;
    u8 localPlayerCount; //0x11
    u8 curVariant[4]; //0x12
    u8 padding[2];
}; //0x18


#endif
