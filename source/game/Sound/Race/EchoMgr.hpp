#ifndef _ECHOMGR_
#define _ECHOMGR_
#include <kamek.hpp>
#include <game/Sound/Other/AudioValues.hpp>

struct Echo {
    u32 unknown_0x0;
    SoundTrack volume;
    SoundTrack echo;
}; //0x3c

class EchoMgr {
public:
    static EchoMgr* sInstance; //809c28a0
    static EchoMgr* CreateInstance(); //80717f60
    static void DestroyInstance(); //80718014
    EchoMgr(); //807180c8
    ~EchoMgr(); //80718150
    void Init(float volume, float echo); //807181f4
    void Update(); //8071821c
    void SetVolume(u8 hudSlotId, u32 stepCount); //807182b8
    void SetEcho(u8 hudSlotId, u32 stepCount, float value); //807182d0

    EGG::TDisposer< EchoMgr> disposer; //80717e34 vtable 808c91f0
    Echo echos[4]; //0x10
}; //0x100


#endif
