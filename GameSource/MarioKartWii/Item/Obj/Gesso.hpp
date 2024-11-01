#ifndef _ITEMOBJGESSO_
#define _ITEMOBJGESSO_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>
#include <MarioKartWii/Audio/Actors/ItemActor.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>

//_sinit_ at 807a9a58
namespace Item {
class ObjGesso : public ObjMiddle {
public:
    static Obj** CreateArray(u32 count); //807a8138
    void InitSelf() override; //0x8 807a8378 vtable 808d1e48
};
size_assert(ObjGesso, 0x1a0);

class GessoScreen { //one per Screen
    GessoScreen(u32 screenId); //807a8460
    ~GessoScreen(); //807a85f4
    void UpdateModel(); //807a8750 scale, distance, visibility set by this
    u32 state;
    ModelDirector* gessoModel; //0x4
    u32 screenId; //0x8
    u8 unknown_0xc[2];
    u16 id; //0xE loop ite, init at 0xC, if 0xC then blooper not applied to that screen
    u8 unknown_0x10[0x1c - 0x10];
    bool isTwilightHouse;
    u8 padding[3];
    Audio::GessoActor actor; //0x20
    float distance; //0xc8 how far the blooper is, higher value for heavier karts
    float scale; //0xcc
}; //0xd0
size_assert(GessoScreen, 0xd0);

class GessoMgr {
public:
    static GessoMgr* sInstance; //809c3648
    static GessoMgr* CreateInstance(); //807a8f04
    static void DestroyInstance(); //807a8fa0
    GessoMgr(); //807a90a0 inlined
    static void Init(); //807a8fd8
    void Update(); //807a92b0
    void ApplyBlooper(); //807a972c applies blooper to every player in front of the one who used, r26 big loop ite is position, r25 is playerId
    void DeployBlooper(u16 playerId); //807a9128 inlined in Item::Player::UseBlooper

    //that player used a blooper which will deploy the blooper model from the character
    u32 screenCount; //0x0
    u16 blooperUserPlayerId; //0x4
    u8 padding[2];
    //another blooper cannot affect the player until this is finished
    //at 0x64 frames, the blooper appears on other players
    u32 startTimer; //0x8 

    u32 startTimerInitValue; //0xc
    u32 positionGroup[12]; //0x10 arrayIdx = playerIdx 4 - pos/4 ie 1-4 = 3; 5-8 = 2; 9-12 = 1
    u8 unknown_0x40[0x44 - 0x40];
    GessoScreen* gessoScreens[4]; //0x44
};//Total Size 0x54
size_assert(GessoMgr, 0x54);
}//namespace Item

#endif