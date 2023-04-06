#ifndef _RACESCENE_
#define _RACESCENE_
#include <game/Scene/BaseScene.hpp>
#include <core/nw4r/ut/RomFont.hpp>

class RaceScene : public GameScene {
public:
    static void UpdateRaceInstances(); //80554ad4 "main_race_update"
    static void UpdateSomeInstances(); //80554d90 inlined SectionMgr but also 809c496c and 809c1f50
    RaceScene(); //80553b88
    ~RaceScene() override; //80553bd4 vtable 808b4220
    bool isSpectating() override; //0x28 80554f78
    int vf_0x2c() override; //0x2c 80554f9c
    void OnCalc() override; //0x30 80554e6c
    void OnExit() override; //0x34 805549b0
    void OnEnter() override; //0x38 80553c50
    void OnEnterEnd() override; //0x3c 8055472c
    void OnReinit() override; //0x40 80554a94
    void CreateAndInitInstances() override; //0x44 80554208
    void vf_0x48() override; //0x48 80554f88
    int GetScreenCount() override; //0x4c 80554f68, number of local players except in 3P
    int vf_0x50() override; //0x50 80554f94
    bool isPaused() override; //0x54 80554e14
    void vf_0x58() override; //0x58 805549ac
    nw4r::ut::RomFont romFont; //0x254c
    ExpHeap *kartModelHeap; //0x2568 //0x2568
}; //0x256c


#endif