#ifndef _ITEMOBJPOW_
#define _ITEMOBJPOW_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>

//_sinit_ at 807b2ed0
namespace Item {
class ObjPow : public ObjMiddle {
public:
    static Obj** CreateArray(u32 count); //807b1ab0
    void InitSelf() override; //0x8 807b1ba4 vtable 808d2530
};
size_assert(ObjPow, 0x1a0);

class PowScreen { //one per Screen
    PowScreen(u32 screenId); //807b2540
    void UpdateModel(); //807b29dc
    ModelDirector* powModel; //0x0
    u32 screenId; //0x4
    u32 playerId; //0x8 reset at 12 when pow inactive
    u8 unknown_0xc[4];
}; //0x10
size_assert(PowScreen, 0x10);

class PowMgr {
public:
    static PowMgr* sInstance; //809c3660
    static PowMgr* CreateInstance(); //807b1bc0
    static void DestroyInstance(); //807b1c70
    PowMgr(); //807b1d18 inlined
    static void Init(); //807b1ca8
    static bool IsPowActive(); //807b2e90
    static int GetFramesUntilPOWSmash(); //807b2eac if negative, no pow smash
    static u8 GetPowUserPlayerId(); //807b2ec0
    void Update(); //807b22f8

    void DeployPow(u16 playerId); //807b1db4
    void AnimateModel(u8 state); //807b1eec 1 = firstAnim, model appears, 2, model squishes and shakes, 3 model squishes further and disappears
    void CreateShockwave(u8 state); //807b20bc physics, sound, visual shaking and graphics
    u32 decrementingTimer; //init at 159 on deploy
    u32 screenCount; //0x4
    u8 powUserPlayerId; //0x8
    bool shouldBeAffectedByPOW[12]; //0x9 everyone in front of userId, or everyone on the other team (battle)
    u8 padding[3]; //0x11
    u8 unknown_0x14[4];
    PowScreen* powScreens[4]; //0x18
};//Total Size 0x54
size_assert(PowMgr, 0x28);
}//namespace Item

#endif