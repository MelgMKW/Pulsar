#ifndef _LAKITUCONTROLLER_
#define _LAKITUCONTROLLER_
#include <kamek.hpp>


/*
Contributors:
-Melg
*/

class LakituControllerPlayer;
class UnkLakituClass2;
class Kart;

class UnkLakituClass { //likely inherited from another class 808cbc30, AI stuff
    UnkLakituClass(); //0x8074ae2c
    void *actionsHolder; //instance +0x8 on ctor, then copy of the ptr at 4
    void *currentActionHolder; //only non-0 while lakitu is active, instance + a set amount depending on what lakitu is
    virtual void func_vtable(); //at 0x8

    u32 pointerToItself;
    u8 unknown_0x10[0x38 - 0x10];
    UnkType unknownClass_0x34; //0x808cbc18, just to get o the correct size, idk because it gets overwritten
}; //unknown total size 0x38

class LakituControllerPlayer;
class LakituActionHolder {
    virtual ~LakituActionHolder(); //80721cec vtable 808c9728
    LakituControllerPlayer *lakituPlayer; //always the controllerplayer itself
    Ptmf_0A<LakituControllerPlayer, void> ptmf_0x8; //vt_0x2c
    Ptmf_0A<LakituControllerPlayer, void> ptmf_0x14; //vt_0x30
    Ptmf_0A<LakituControllerPlayer, void> ptmf_0x20; //idk
}; //total size 0x2C

class EnableLakituAction {
    EnableLakituAction(); //inlined everywhere
    virtual ~EnableLakituAction();
    virtual void ResetState(); //always called on init
    virtual void EnableAction(); //if the conditions are met
    u8 playerId;
    bool isEnabled;
    bool hasHappened; //held true forever except if certain conditions can reset the state
    u8 unknown_0x7[2];
};
class EnableCountdownAction : public EnableLakituAction {
    EnableCountdownAction(); //0x80725a78
    ~EnableCountdownAction() override; //80725a98 vtable 808c98a0
    void ResetState() override; //80725ad8
    void EnableAction() override; //80725ae8 if the conditions are met checks raceinfo state to set it 
}; //total size 0x8

class EnableDisplayLapAction : public EnableLakituAction {
    EnableDisplayLapAction(); //0x80725b48
    ~EnableDisplayLapAction() override; //80725b68 vtable 808c988c 
    void ResetState() override; //80725ba8  runs every frame the action is not enabled, enables by comparing with stored maxLap
    void EnableAction() override; //80725bd8 if the conditions are met checks raceinfo state to set it
    u8 maxLap; //0x7
}; //total size 0x8

class EnableRespawnAction : public EnableLakituAction { //this one 
    EnableRespawnAction(); //0x80725dd8
    ~EnableRespawnAction() override; //80725df8 vtable 808c9864
    void ResetState() override; //80725e38 
    void EnableAction() override; //80725e48 conditions are always met so just a blr
}; //total size 0x8

class EnableBackwardsAction : public EnableLakituAction { //this one 
    EnableBackwardsAction(); //0x80725c1c
    ~EnableBackwardsAction() override; //80725c3c vtable 808c9878
    void ResetState() override; //80725c7c 
    void EnableAction() override; //80725c98 checks raceinfoPlayer stateflags and also makes sure you are not currently hitting an item or obj
    float unknown_0x8; //unknown
}; //total size 0xC

class EnableEndingAction : public EnableLakituAction { //this one 
    EnableEndingAction(); //0x80725e4c
    ~EnableEndingAction() override; //80725e6c vtable 808c9850
    void ResetState() override; //80725eac
    void EnableAction() override; //80725ebc checks stateFlags, only if didn't finish in last and past ending camera
}; //total size 0x8


class LakituControllerPlayer { //very likely inherits from a class with vtable 808c9740
    explicit LakituControllerPlayer(Kart *kart); //80721514
    virtual void func_vtable(); //808c96a0
    void Init(); //80722504 loads jugemu.brres, rod.brres, links anims
    ModelDirector *lakituModel; //0x4
    ModelDirector *rodModel; //0x8
    ModelDirector *signalModel; //0xc
    ModelDirector *lapModel;  //0x10
    ModelDirector *finalLapModel; //0x14
    ModelDirector *reverseModel; //0x18
    ModelDirector *flagModel; //0x1c
    ModelDirector *hair; //0x20
    ModelDirector *lamp; //0x24
    UnkType *shadow; //0x28 ends at 2c
    Mtx34 unknown_0x2C;
    u8 unknown_0x5C; //ctor'd at 1
    u8 unknown_0x5D;
    UnkLakituClass unknown_0x60; //ends at 0x98
    LakituActionHolder actionHandlers[7]; //each has a specific use all are virtual, vtable 808c9728
    /*
    1st one: onNoAction
    2nd one: countdown
    3rd one: display lap
    4th one: respawn
    5th one: backwards
    6th one: ending
    7th one: unknown, doesn't have an enable
    */
    Kart *kart; //0x1CC
    u32 unknown_0x1D0;
    Vec3 position;
    u8 unknown_0x1E0;
    u8 unknown_0x1E1[3]; //seems to be padding
    u32 state; //0x1 load, 0x2 active, 0x3 unload? idk, but forcing it to 0 prevents lakitu from appearing
    u32 frames; //frames each states lasts for //8072411c for unload on lap transition
    u32 animationState; //gets set to 2 when the animation for countdown (the arm moving) starts
    u32 frames2; //only increments for state 0x2 when looking backwards
    EnableCountdownAction *enableCountdownAction; //all of these actions are check by 807234a4, which only runs when the current actionHandler is "onNoAction"
    EnableDisplayLapAction *enableDisplayLapAction;
    EnableRespawnAction *enableThirdAction;
    EnableBackwardsAction *enableBackwardsAction;
    EnableEndingAction *enableEndingAction; //0x204
    u32 unknownclass_0x208; //will do later 80721820 ctor
    u32 unknown_list0x20C;
    u32 unknownclass_0x210; //8074bf28 ctor
    u32 soundclass_0x214; //8070ca8c seems to be for sound
};//total size 0x218

class LakituController {
public:
    static LakituController *sInstance;
    static LakituController GetStaticInstance(); //8071e270
    static void DestroyStaticInstance(); //8071e2fc
    LakituController(); //8071e330 inlined
    EGG::TDisposer<LakituController> disposer; //8071e1d8 vtable 808c94bc
    virtual ~LakituController(); //8071e390 vtable 808c94b0 at 0x10
    void Init(); //8071e638
    void Update(); //8071e6c0
    LakituControllerPlayer *lakituControllerPlayers[4]; //lakitu player, one per local player
    u32 localPlayerCount; //8071e610
}; //total size 0x28
#endif