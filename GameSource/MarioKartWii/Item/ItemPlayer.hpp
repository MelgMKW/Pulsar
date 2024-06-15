#ifndef _ITEM_PLAYER_
#define _ITEM_PLAYER_

#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/Kart/KartPointers.hpp>
#include <MarioKartWii/Item/PlayerObj.hpp>

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
    PlayerRoulette(); //807b9f48
    void Init(Player* itemPlayer); //807b9f80
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
    u32 itemNum; //0x30 how many items have you pulled so far, useful for mushroom bug
}; //Total Size 0x34

class PlayerInventory {
public:
    PlayerInventory(); //807bc0f8
    void Init(Player* itemPlayer); //807bc130
    void Update(); //807bc6e8
    void SetItem(ItemId id, u8 r5); //807bc940
    void RemoveItems(u32 count); //807bc97c if count would be 0 after removing count items, clears the inventory
    void ClearAll(); //807bc9c0
    Player* itemPlayer;
    ItemId currentItemId; //0x4
    u32 currentItemCount; //0x8
    u8 unknown_0xC[0x1C - 0xC];
    bool hasGolden;
    u8 unknown_0x1D[0x22 - 0x1D];
    u16 goldenTimer;
    u8 unknown_0x24[0x2C - 0x24];
}; //Total Size 0x2C

class Player {
public:
    Player(); //8079754c
    ~Player(); //8079951c
    void Init(u8 playerId); //807976e0
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

    int GetHeldCount(ItemObjId objId) const; //80798f0c
    Kart::Link kartLink;
    u16 bitfield; /* 0xc
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
    PlayerObj itemPlayerSub; //0xb4
    u32 hudSlotId; //0x234
    u8 unknown_0x238[0x240 - 0x238];
    s32 decrementTimer; //0x240
    u8 unknown_0x244[4];
}; //Total Size 0x248
size_assert(Player, 0x248);
}//namespace Item

#endif