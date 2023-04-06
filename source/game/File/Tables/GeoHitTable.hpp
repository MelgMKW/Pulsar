#ifndef _GEOHITTABLEITEM_
#define _GEOHITTABLEITEM_
#include <game/File/Tables/Table.hpp>

//https://wiki.tockdom.com/wiki/Filesystem/Race/Common.szs/GeoHitTableItem.bin
//how objects interact with items
//https://wiki.tockdom.com/wiki/Filesystem/Race/Common.szs/GeoHitTableItemObj.bin
//how items interact with objects

enum GeoHitItemID {
    GEO_HIT_GREEN_SHELL,
    GEO_HIT_RED_SHELL,
    GEO_HIT_BANANA,
    GEO_HIT_MUSHROOM,
    GEO_HIT_STAR,
    GEO_HIT_BLUE_SHELL,
    GEO_HIT_LIGHTNING,
    GEO_HIT_FAKE_ITEM_BOX,
    GEO_HIT_MEGA_MUSHROOM,
    GEO_HIT_BOB_OMB,
    GEO_HIT_BLOOPER,
    GEO_HIT_POW,
    GEO_HIT_GOLDEN_MUSHROOM,
    GEO_HIT_BULLET_BILL,
    GEO_HIT_THUNDERCLOUD
};

enum ObjToItemInteraction {
    OBJ_ITEM_INTERACTION_CLIPS,
    OBJ_ITEM_INTERACTION_BOUNCES,
    OBJ_ITEM_INTERACTION_BREAKS,
};

enum ItemToObjInteraction {
    //idk
};

enum ObjToKartHit {
    OBJ_KART_WALL_ALL_SPEED = 0x8,
    OBJ_KART_SPIN_ALL_SPEED = 0x9, //unused
    OBJ_KART_SPIN_SOME_SPEED = 0xA,
    OBJ_KART_FIRE_SPIN = 0xB,
    OBJ_KART_CLIP_THROUGH_SOME_SPEED = 0xC,
    OBJ_KART_SMALL_LAUNCH = 0xD,
    OBJ_KART_KNOCKBACK_SOME_SPEED_LOSE_ITEM = 0xE,
    OBJ_KART_LAUNCH_SPIN_LOSE_ITEM = 0xF, //unused
    OBJ_KART_KNOCKBACK_BUMP_LOSE_ITEM = 0x10,
    OBJ_KART_LONG_CRUSH_LOSE_ITEM = 0x11,
    OBJ_KART_SMALL_BUMP = 0x12,
    OBJ_KART_BIG_BUMP = 0x13,
    OBJ_KART_SPIN_SHRINK = 0x14,
    OBJ_KART_HIGH_LAUNCH_LOSE_ITEM = 0x15,
    OBJ_KART_SPIN_HIT_SOME_SPEED = 0x16,
    OBJ_KART_WEAK_WALL = 0x17,
    OBJ_KART_WALL = 0x18,
    OBJ_KART_LAUNCH_SPIN = 0x19,
    OBJ_KART_WALL_SPARK = 0x1A,
    OBJ_KART_RUBBER_WALL = 0x1B,
    OBJ_KART_WALL2 = 0x1C,
    OBJ_KART_UNTRICKABLE_JUMP_PAD = 0x1D,
    OBJ_KART_SHORT_CRUSH_LOSE_ITEM = 0x1E,
    OBJ_KART_CRUSH_RESPAWN = 0x1F,
    OBJ_KART_EXPLOSION_LOSE_ITEM = 0x20,
    OBJ_KART_KNOCKBACK_LOSE_ITEM = 0x100
};

enum KartToObjHit {
    KART_OBJ_STATE_1 = 0x5,
    KART_OBJ_STATE_2 = 0x6, //unused
};

struct GeoHitTableEntry {
    u16 objId;
    u16 interactions; //use enums for types, entry count for amount
};


struct GeoHitTable {
    TableBinaryHeader header;
    u16 entryCount;
    GeoHitTableEntry entries;
    //IndexToIDTable idxToID;
};

#endif