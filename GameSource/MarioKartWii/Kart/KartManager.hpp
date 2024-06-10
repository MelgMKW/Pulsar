#ifndef _KARTMANAGER_
#define _KARTMANAGER_
#include <kamek.hpp>
#include <core/nw4r/ut/List.hpp>
#include <MarioKartWii/Kart/KartPlayer.hpp>

namespace Kart {

class ManagerSub {
public:
    //vtable 802a2b48
    virtual void Unknown_0x0();
    u8 unknown_0x4[0x10 - 0x4];
}; //Total size 0x10

class Manager : public EGG::Disposer {
public:
    static Manager* sInstance; //809c18f8
    static Manager* CreateInstance(); //8058faa8
    static void DestroyInstance(); //8058faf8
    static nw4r::ut::List kartObjects; //809c1900 list of all kart objects offset = 4
    static ClipInfo* curKartClipInfo; //809c1954

    ~Manager() override; //8058fdd4 vtable 808b6408
    Manager(); //8058fb2c
    Player* GetKartPlayer(u32 idx) const; //80590100
    void Init(); //8058fee0
    void Update(); //8058ffe8
    static Player* SetupPlayer(u8 playerIdx, KartId kart, CharacterId character, bool isBike); //8058f5b4  

    EGG::TDisposer<Manager> disposer; //0x10 8058fa10 vtable 808b6414
    Player** players;
    u8 playerCount;
    //padding 0x25 - 0x27
    u32 someBitfield; //some bits are sets depending on the played track
    u8* array0; //contains 1 element per player, set to the player index divided by 4
    u8* array1; //contains 1 element per player, set to the player index modulo 4
    u8 unknown_0x34[0x38 - 0x34];
}; //Total size 0x38

}//namespace kart

#endif