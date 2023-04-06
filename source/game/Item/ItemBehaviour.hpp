
/*
ItemBehaviour is a struct containing various information about how an item should behave
Contributors:
  Seeky (main documentation)
  TheLordScruffy (object id field)
References:
  http://wiki.tockdom.com/wiki/Filesystem/rel/StaticR.rel#Item_behaviour_modifier
*/
#ifndef _ITEMBEHAVIOUR_
#define _ITEMBEHAVIOUR_
#include <kamek.hpp>
#include <game/Item/ItemManager.hpp>
#include <game/System/Identifiers.hpp>

enum ItemUseType {
    ITEMUSE_USE,
    ITEMUSE_FIRE,
    ITEMUSE_TAIL,
    ITEMUSE_CIRCLE
};

typedef struct ItemBehaviour {
    static ItemBehaviour itemBehaviourTable[19]; //809c36a0, index item id, see http://wiki.tockdom.com/wiki/List_of_Identifiers#Items
    u8 unknkown_0x0;
    u8 unknkown_0x1;
    u8 padding[2]; // Ignored when copying to array
    ItemObjId objId; // see http://wiki.tockdom.com/wiki/List_of_Identifiers#Items
    u32 numberOfItems;
    u32 unknown_0xc;
    u8 unknown_0x10;
    u8 padding2[3]; // Ignored when copying to array
    ItemUseType useType;
    void (*useFunction)(ItemPlayer *itemPlayer); // Item is draggable if this is null
}; // Total size 0x1c

void CopyItemBehaviourFromRelToTable(); // 807bcae0, copies individual structs from rodata into table
#endif