#ifndef _ITEM_PLAYER_
#define _ITEM_PLAYER_

#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/Kart/KartPointers.hpp>

namespace Item {
class Player;

class Point {
public:
    u8 ITPT;
    u8 unknown_0x1[3];
    Vec3 position;
};//Total Size 0x10

class PlayerRoulette { //only exists for local players
public:
    bool Update(); //807ba37c returns true when the roulette just ended
    void OnRouletteEnd(); //807ba2d8
    //r4 is the GOBJ setting (either player or CPU based on isHuman bool), position means different things based on gamemode ofc
    void DecideItem(u16 itemBoxType, u8 position, bool isHuman, u32 lotteryType); //807b9fb0
    Player* itemPlayer;
    u32 isTheRouletteSpinning;
    u32 frames; //how many frames has the roulette been spinning for
    u32 totalSpinDuration;
    float unknown_0x10[2];
    ItemId currentRandomItem; //0x18
    ItemId nextRandomItem; //0x1c
    ItemId nextItemId; //0x20
    u32 unknown_0x24;
    u16 setting;
    u8 position;
    u8 unknown_0x2B[0x30 - 0x2b];
    u32 itemNum; //how many items have you pulled so far, useful for mushroom bug
}; //Total Size 0x34

class PlayerInventory {
public:
    void Update(); //807bc6e8
    void SetItem(ItemId id, u8 r5); //807bc940
    void RemoveItems(u32 count); //807bc97c if count would be 0 after removing count items, clears the inventory
    Player* itemPlayer;
    ItemId currentItemId;
    u32 currentItemCount;
    u8 unknown_0xC[0x1C - 0xC];
    bool hasGolden;
    u8 unknown_0x1D[0x22 - 0x1D];
    u16 goldenTimer;
    u8 unknown_0x24[0x2C - 0x24];
}; //Total Size 0x2C

class PlayerSub {
public:
    static Ptmf_0A<PlayerSub, void> OnActivateHandlers[5]; //808d1900, on per use type
    void OnTrailActivate(); //80792c68
    void OnTripleTrailActivate(); //8079356c
    void OnSpinActivate(); //80794694
    void Update(); //80795668
    void ActivateItem(); //8079231c spawns item, plays sounds and animations
    void UseItem(bool r4); //80791914 r4 might be isRemote?
    void LoseItem(u32 playerIdx); //80795350 unsure what playerIdx does, only used in onlineRaces

    Kart::Pointers* kartPointers;
    Player* itemPlayer;
    u8 unknown_0x8[4];
    Player* itemPlayer2; //0xC
    u8 id; //0x10
    u8 unknown0x11[0x14 - 0x11];
    ItemObjId itemObjId; //0x14 seems to only change for items you can hold "behind" (including triple shells)
    ItemId itemId; //same 0x18
    u32 useType; //0x1c 0x1 if trailing behind 0x2 if trailing behind triples, 0x3 if spinning, 0x4 if no item
    u8 unknown_0x20[0x50 - 0x20]; //this whole part only changes when trailing/using bananas/shells
    u32 activeItemCount; // eg 0x2 if 2 remaining spinning shells
    ItemObjId unknown_0x54;
    Vec3 playerLeft;
    Vec3 playerUp;
    Vec3 playerFront;
    Vec3 pos; //0x7c
    Vec3 unknown_0x88;
    u8 unknown_0x94[0xb0 - 0x94];
    Vec3 itemScale;
    u8 unknown_0xbc[0xc0 - 0xbc];
    Vec3 unknown_0xc0;
    u8 unknown_0xcc[0xd0 - 0xcc];
    Vec2 rotatingRadius;
    float unknown_0xd8[2];
    float itemScaleFactor;
    Vec3 itemPos; //relative to the player 0xE4
    u8 unknown_0xf0[0x154 - 0xF0];
    bool isNotDragged; //0x154
    u8 unknown_0x155[0x174 - 0x155];
    u16 spawnedObjs[3]; //0x174
    u8 unknown_0x17a[0x180 - 0x17a];
}; //Total Size 0x180
size_assert(PlayerSub, 0x180);

class Player {
public:
    Player(); //8079754c
    ~Player(); //8079951c
    void Update(); //80797928
    void UseBlooper(); //807a81b4
    void UsePow(); //807b1b2c
    void UseBullet(); //807a9afc
    void UseMushroom(); //807a9d3c
    void UseMegaMushroom(); //807a9e50
    void UseGoldenMushroom(); //807a9f6
    void UseTC(); //807af1bc
    void UseStar(); //807b706c
    void UseThunder(); //807b7b7c
    void ActivateMegaMushroom(); //807986b4
    //r4, r5 straight from GOBJ, r6 also from GOBJ but transform the setting into values depending on duration
    void DecideItem(u16 playerItemBoxType, u16 cpuItemBoxType, u32 lotteryType); //80798c38 
    bool HasTripleItems(u8 checkRouletteOrInventory); //80798dbc r4 == 1 -> checks inventory

    Kart::Pointers* kartPointers; //0x0
    DriverController* model; //0x4
    u8 unknown_0x8[4];
    u16 bitfield; /*
    Bitfield bits:
    1 = 0x2:  has inventory item
    2 = 0x4: is releasing dragged item (NOT triple items)
    4 = 0x10: is holding throw button
    5 = 0x20: is holding place item button
    6 = 0x40: can use item (ie is not in hitstun)
    8 = 0x100: is dragging item
    10 = 0x400: is hitting an item
    12 = 0x1000: has an active item (dragging a FIB or holding a triple or having an active golden/bill counts as having an active)
    13 = 0x2000: is using item
    14 = 0x4000: decrement current item
    */

    u8 unknown_0xE[0x18 - 0xE];
    u8 id; //0x18
    bool isHuman; //0x19
    bool isRemote; //0x1a
    bool isBike; //0x1b
    Kart::Player* kartPlayer; //0x1c
    DriverController* model2;
    Vec3 unknown_0x24;
    u8 unknown_0x30[0x44 - 0x30];
    Point itemPoint;
    PlayerRoulette roulette; //0x54
    PlayerInventory inventory; //0x88
    PlayerSub itemPlayerSub; //b4
    u32 hudSlotId; //0x234
    u8 unknown_0x238[0x248 - 0x238];
}; //Total Size 0x248
size_assert(Player, 0x248);
}//namespace Item

#endif