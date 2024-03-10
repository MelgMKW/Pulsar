#ifndef _ITEMOBJGESSO_
#define _ITEMOBJGESSO_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>
#include <MarioKartWii/Audio/Actors/ItemActor.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>

//_sinit_ at 807a9a58
namespace Item {
class ObjGesso : public Obj {
public:
    static Obj** CreateArray(u32 count); //807a8138
    void InitSelf() override; //0x8 807a8378 vtable 808d1e48
};
size_assert(ObjGesso, 0x1a0);

class GessoScreen { //one per Screen
    GessoScreen(u32 screenId); //807a8460
    ~GessoScreen(); //807a85f4
    u32 unknown_0x0;
    ModelDirector* gessoModel; //0x4
    u32 screenId; //0x8
    u8 unknown_0xc[0x1c - 0xc];
    bool isTwilightHouse;
    u8 padding[3];
    Audio::GessoActor actor; //0x20
    u8 unknown_0xc8[8]; //0xc8
}; //0xd0
size_assert(GessoScreen, 0xd0);

class GessoMgr {
public:
    static GessoMgr* sInstance; //809c3648
    static GessoMgr* CreateInstance(); //807a8f04
    static void DestroyInstance(); //807a8fa0
    GessoMgr(); //807a90a0 inlined
    static void Init(); //807a8fd8

    void DeployBlooper(u8 playerId); //807a9128 that player used a blooper which will deploy the blooper model from the character
    u32 screenCount; //0x0
    u8 unknown_0x4[0x44 - 0x4];
    GessoScreen* gessoScreens[4]; //0x44
};//Total Size 0x54
size_assert(GessoMgr, 0x54);
}//namespace Item

#endif