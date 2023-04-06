/*
KartHolder contains most player-specific data during a race
Contributors:
  stebler (main documentation)
  SwareJonge (extra methods and attributes)
  1superchip (extra timer attributes, correcting some signing of types)
  CLF78 (helped with jump pads)
References:
  http://wiki.tockdom.com/wiki/BSP_(File_Format)
  http://wiki.tockdom.com/wiki/KartParam.bin
  http://wiki.tockdom.com/wiki/KartPartsDispParam.bin
  http://wiki.tockdom.com/wiki/BikePartsDispParam.bin
*/

#ifndef _KARTHOLDER_
#define _KARTHOLDER_
#include <kamek.hpp>
#include <core/nw4r/ut/List.hpp>
#include <game/Race/Kart/Kart.hpp>

class KartHolderSub {
public:
    //vtable 802a2b48
    virtual void Unknown_0x0();
    u8 unknown_0x4[0x10 - 0x4];
}; //Total size 0x10

class KartHolder : public KartHolderSub { //vtable override 808b6408
public:
    static KartHolder *sInstance; //809c18f8
    static KartHolder *GetStaticInstance(); //8058faa8
    static nw4r::ut::List kartObjects; //809c1900 list of all kart objects offset = 4
    static void destroyStaticInstance(); //8058faf8

    KartHolder(); //8058fb2c
    Kart *GetKart(u32 idx); //80590100
    void Init(); //8058fee0
    void Update(); //8058ffe8
    Kart *SetupKart(KartId kart, CharacterId character, bool isBike); //8058f5b4  


    KartHolderSub secondPHS;
    Kart **karts;
    u8 playerCount;
    //padding 0x25 - 0x27
    u32 someBitfield; //some bits are sets depending on the played track
    u8 *array0; //contains 1 element per player, set to the player index divided by 4
    u8 *array1; //contains 1 element per player, set to the player index modulo 4
    u8 unknown_0x34[0x38 - 0x34];
}; //Total size 0x38



struct ComboIDs {
    KartId kartId;
    CharacterId characterId;
};

extern "C" {
    bool ApplyTransparency(ComboIDs *comboIDs, GFX44 *gfx44, bool isGhost, u8 playerId);
}


#endif