#ifndef _AIPLAYER_
#define _AIPLAYER_
#include <kamek.hpp>
#include <MarioKartWii/Input/InputState.hpp>
#include <MarioKartWii/AI/AIBase.hpp>
#include <MarioKartWii/AI/CharacterAI.hpp>
#include <MarioKartWii/AI/CPUDriving.hpp>

class KartAIController;

namespace AI {
class Player;

//AI::Actions<Player> ~PlayerActions() override; //80732360 vtable 808ca790
//AI::Actions<Player> void OnStart() override; //0xc 807330f4
//AI::Actions<Player> void Update() override; //0x10 8073313c
//AI::Actions<Player> void OnEnd() override; //0x14 8073316c

typedef Actions<Player> PlayerActions;

class Inputs {
    Inputs(); //80731960 inlined
    void Reset(); //80731984
    void AddInputs(u16 inputsToAdd); //8073199c ORs the bitfield with the internal bitfield
    void RemoveInputs(u16 inputsToRemove); //807319ac

    KartAIController& controller;
    Input::State* state; //0x4
    u32 unknown_0x8;
    u16 inputsBitfield; //1 is accelerating
    u8 padding[2];
    float unknown_0x10;
}; //0x14

class Player : public Base {
    Player(KartAIController& controller); //807319c4
    ~Player() override; //offset 0x34 807323a0 vtable 808ca73c

    virtual void Init(); //0x18 80732508
    virtual void Update(); //0x1c 80732678
    virtual void vf_0x20(); //0x20 8073269c
    virtual void OnStartPreRace(); //0x24 80732890
    virtual void UpdatePreRace(); //0x28 807328e0
    virtual void OnStartCPUDriving(); //0x2c 80732a6c
    virtual void UpdateCPUDriving(); //0x30 80732a70
    virtual void OnStartRealPlayerDriving(); //0x34 80732c6c
    virtual void UpdateRealPlayerDriving(); //0x38 80732c70 does nothing until race ends
    virtual void OnStartAction3(); //0x3c 80732d84
    virtual void UpdateAction3(); //0x40 80732d88
    virtual void OnStartPostRaceDriving(); //0x44 80732d8c
    virtual void UpdatePostRaceDriving(); //0x48 80732de0
    virtual void OnStartPostBattleDriving(); //0x4c 80732f84
    virtual void UpdatePostBattleDriving(); //0x50 80732fd4

    void SetRaceEnd(); //80732690

    PlayerActions preRace; //0x38
    PlayerActions cpuDrivingAction; //0x64
    PlayerActions realPlayerDriving; //0x90
    PlayerActions actions3; //0xbc
    PlayerActions postRaceDriving; //0xe8
    PlayerActions battleDriving; //0x114 also missions

    KartAIController& controller; //0x140

    Inputs* inputs; //0x140
    CPUDriving* cpuDriving;//0x144
    u8 unknown_0x148[4];
    u32 unknown_0x14c;
    Input::State* state; //0x150
    u32 unknown_0x154;
    Character* driverAI;
    u32 unknown_0x15c;
    u8 unknown_0x160[3];
    bool hasRaceEnded; //0x163
}; //0x164

class PlayerKart : public Player {
    PlayerKart(KartAIController& controller); //807332a4
    ~PlayerKart() override; //807332fc vtable 808ca818
    void Init() override; //0x18 80733354
    void Update() override; //0x1c 807333b8
    void vf_0x20() override; //0x20 807333bc
    void OnStartCPUDriving() override; //0x2c 807333c0
    void UpdateCPUDriving() override; //0x30 807333c4
};

class PlayerBike : public Player {
    PlayerBike(KartAIController& controller); //807331b4
    ~PlayerBike() override; //80733238 vtable 808ca7c0
    void Init() override; //0x18 80733290
    void Update() override; //0x1c 80733294
    void vf_0x20() override; //0x20 80733298
    void OnStartCPUDriving() override; //0x2c 8073329c
    void UpdateCPUDriving() override; //0x30 807332a0
};

}//namespace AI

#endif