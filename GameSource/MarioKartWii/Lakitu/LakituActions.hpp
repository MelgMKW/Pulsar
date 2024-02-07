#ifndef _LAKITUACTIONS_
#define _LAKITUACTIONS_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/AI/AIBase.hpp>

/*
Contributors:
-Melg
*/

namespace Lakitu {

class Player;

//AI::Actions<Player> ~Action() override; //80721cec vtable 808c9728
//AI::Actions<Player> void OnStart() override; //0xc 807255b0
//AI::Actions<Player> void Update() override; //0x10 807255f8
//AI::Actions<Player> void OnEnd() override; //0x14 80725628

typedef AI::Actions<Player> Action;

class EnableLakituAction {
    virtual ~EnableLakituAction(); //80725a0c vtable 808c98b4
    virtual void ResetState(); //80725a4c
    virtual void EnableAction() = 0; //if the conditions are met

    bool HasActionHappened() const; //80725a5c
    u8 playerId;
    bool isEnabled;
    bool hasHappened; //held true forever except if certain conditions can reset the state
    u8 unknown_0x7[2];
};

class EnableCountdownAction : public EnableLakituAction {
    EnableCountdownAction(u8 playerId); //80725a78
    ~EnableCountdownAction() override; //80725a98 vtable 808c98a0
    void ResetState() override; //80725ad8
    void EnableAction() override; //80725ae8 if the conditions are met checks raceinfo state to set it 
}; //total size 0x8

class EnableDisplayLapAction : public EnableLakituAction {
    EnableDisplayLapAction(u8 playerId); //80725b48
    ~EnableDisplayLapAction() override; //80725b68 vtable 808c988c 
    void ResetState() override; //80725ba8  runs every frame the action is not enabled, enables by comparing with stored maxLap
    void EnableAction() override; //80725bd8 if the conditions are met checks raceinfo state to set it
    u8 maxLap; //0x7
}; //total size 0x8

class EnableRespawnAction : public EnableLakituAction { //this one 
    EnableRespawnAction(u8 playerId); //80725dd8
    ~EnableRespawnAction() override; //80725df8 vtable 808c9864
    void ResetState() override; //80725e38 
    void EnableAction() override; //80725e48 conditions are always met so just a blr

}; //total size 0x8

class EnableBackwardsAction : public EnableLakituAction { //this one 
    EnableBackwardsAction(u8 playerId); //80725c1c
    ~EnableBackwardsAction() override; //80725c3c vtable 808c9878
    void ResetState() override; //80725c7c 
    void EnableAction() override; //80725c98 checks raceinfoPlayer stateflags and also makes sure you are not currently hitting an item or obj
    float unknown_0x8; //unknown
}; //total size 0xC

class EnableEndingAction : public EnableLakituAction { //this one 
    EnableEndingAction(u8 playerId); //80725e4c
    ~EnableEndingAction() override; //80725e6c vtable 808c9850
    void ResetState() override; //80725eac
    void EnableAction() override; //80725ebc checks stateFlags, only if didn't finish in last and past ending camera
}; //total size 0x8

}//namespace Lakitu
#endif