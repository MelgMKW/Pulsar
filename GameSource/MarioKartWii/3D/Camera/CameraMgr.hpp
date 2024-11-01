#ifndef _CAMERAMGR_
#define _CAMERAMGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/3D/Camera/Camera.hpp>
#include <MarioKartWii/3D/Camera/RaceCamera.hpp>
#include <MarioKartWii/3D/GameScreenEffects/GameScreenEffects.hpp>

class ClipInfo;

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
    void ApplyShaking(ClipInfo* info, u32 r5, u32 shakeParamsIdx, u32 rumbleLength);
    bool HasEveryOpeningPanEnded() const; //805a8fbc

    static void ChangeFocusedPlayer(u8 playerIdx); //805a9b04

    EGG::TDisposer<RaceCameraMgr> disposer; //0x4 805a83dc vtable 808b6c28
    RaceCamera** cameras; //0x14
    RaceCamera** sortedCameras; //0x18 sorted by whose view you are watching?
    u32 cameraCount; //0x1c == localPlayerCount except for 3P, the nonPlayerScreen has 3 cameras
    u32 localPlayerCount; //0x20
    u8 unknown_0x24;
    bool isOnlineSpectating; //0x25
    bool hasNonPlayerScreen; //0x26 only true for 3P essentially
    u8 focusedPlayerIdx; //0x27
    u8 unknown_0x28[2];
    u16 unknown_0x2a[2];
    u8 padding[2]; //0x2e

    GameScreenEffectsMgr* gameScreenEffectsMgr; //0x30
    BCP* rawBCP; //0x34

}; //0x38
size_assert(RaceCameraMgr, 0x38);

#endif