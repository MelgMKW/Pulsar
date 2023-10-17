#ifndef _CAMERAMGR_
#define _CAMERAMGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/3D/Camera/Camera.hpp>


class RaceCamMgrSub30 {
    RaceCamMgrSub30(u32 screenCount); //8054eb54
    virtual ~RaceCamMgrSub30(); //8054f120 vtable 808b3e04
    u8 _[0x18];
}; //0x1c

class CameraMgr {
public:
    static CameraMgr* sInstance; //809c19a4
    CameraMgr(); //805a1a34
    static void SetInstance(CameraMgr* mgr); //805a1a64 can only have 1
    virtual ~CameraMgr(); //805a1b7c vtable 808b6b00
    virtual void Update(); //805a1b78
};

class RaceCameraMgr : public CameraMgr {
public:
    static RaceCameraMgr* sInstance; //809c19b8
    static RaceCameraMgr* CreateInstance(); //805a83e4
    static void DestroyInstance(); //805a8434
    RaceCameraMgr(); //805a8468
    ~RaceCameraMgr() override; //805a8cdc vtable 808b6c18
    void Update() override; //805a900c

    static void ChangeFocusedPlayer(u8 playerIdx); //805a9b04

    EGG::TDisposer<RaceCameraMgr> disposer; //0x4 805a83dc vtable 808b6c28
    RaceCamera** cameras; //0x14
    RaceCamera** cameras2; //0x18
    u32 cameraCount; //0x1c == localPlayerCount except for 3P, the nonPlayerScreen has 3 cameras
    u32 localPlayerCount; //0x20
    u8 unknown_0x24;
    bool isOnlineSpectating; //0x25
    bool hasNonPlayerScreen; //0x26 only true for 3P essentially
    u8 focusedPlayerIdx;
    u8 unknown_0x28[2];
    u16 unknown_0x2a[2];
    u8 unknown_0x2c[4];
    RaceCamMgrSub30* sub30; //0x30
    BCP* rawBCP; //0x34

}; //0x38

#endif