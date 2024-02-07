#ifndef _ITEMSLOTDATA_
#define _ITEMSLOTDATA_

#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/System/Identifiers.hpp>

/*
ItemSlotData is the class that handles data from ItemSlot.bin / ItemSlotTable.slt

Contributors:
  Seeky (main documentation)
  Star (checkSpawnTimer)
References:
  http://wiki.tockdom.com/wiki/Filesystem/Race/Common.szs/ItemSlot.bin
*/

struct ItemSlotBinary {
    struct Table {
        u8 columnsCount; //12 in race modes, 3 in battle modes, 16 for special boxes
        u8 rowsCount; //always 19
        u32 probabilityTimes2[1][1]; //row is ItemId, column is position/coins behind 1st/balloon scored behind 1st
    };
    u8 tablesCount;
    Table tables[1]; //size tablesCount
};

namespace Item {
class Player;
class ItemSlotData {
public:
    struct Probabilities {
        u32 rowCount; //almost always raw's columnsCount since this is inverted
        u16* probabilities; //obviously multiplied by 2 as usual
        //array of size [COLUMNSCOUNT][19], ie inverted relative to the raw bin, probabilities[3][4] would be the probability that 4th place gets a Mushroom 
    }; // Total size 0x8

    struct RouletteItems { //visual only
        RouletteItems(); //807bb374, no dtor
        u32 itemCount;
        ItemId items[19];
    };
    size_assert(RouletteItems, 0x50);

    static ItemSlotData* sInstance(); //809c3670
    static ItemSlotData* CreateInstance(); //807ba77c
    static void DestroyInstance(); //807bda814
    ItemSlotData(); //807ba8c8 inlined
    ~ItemSlotData(); //807ba934
    void Init(); //807ba7d8
    //takes a pointer to a raw table in an item slot file, processes the values and 
    //writes them to the probabilities field of the table holder, then returns the pointer to the start of the next table
    ItemSlotBinary::Table* ProcessTable(ItemSlotBinary::Table* rawTable, Probabilities* probabilities,
        bool updateRoulette, bool isSpecialTable); //807ba9d8
    void PostProcessVSTable(Probabilities* probabilities); //807bad20 rescales the table based on something and playerCount
    ItemId DecideItem(u16 itemBoxType, u8 position, bool isHuman, bool hasTripleItem, Player* itemHolderPlayer); //807bb42c
    //for the roulette, r7 based on boxType (is true if type == 0xFF but idk how that can happen)
    ItemId DecideRouletteItem(u16 itemBoxType, u8 position, ItemId prevRandomItem, bool r7); //807bb8d0 
    void ResetLightningTimer(); //807bb9bc
    void ResetBlueShellTimer(); //807bb9c8, inlined
    void ResetBlooperTimer(); //807bb9d4
    void ResetPowTimer(); //807bb9e0
    void UpdateTimers(); //807bb9ec, also resets them
    //function returns false if r5 is false OR the item is "valid", ie itemTimer < 300 (or the item has no timer); return true otherwise
    bool CanItemNotBeObtained(ItemObjId objId, bool r5); //807bb380 https://decomp.me/scratch/h5jTs 
    //These are inlined
    void SetupBattleProbabilities(); //807bbb00
    void SetupOnlineVSProbabilities(); //807bbd60
    void SetupVSProbabilities(); //807bbef8
    void SetupGPProbabilities(); //807bc000
    static ItemId RandomizeRouletteItem(RouletteItems* rouletteItems, ItemId prevRouletteItem); //807baed4 inlined
    static ItemSlotBinary::Table* GetNextTable(ItemSlotBinary* table); //807bad08 inlined
    static ItemSlotBinary* GetBinary(); //807bba94

    EGG::TDisposer<ItemSlotData> disposer; //807ba650 vtable 808b27b4
    Probabilities playerChances; //0x10
    Probabilities cpuChances; //0x18
    Probabilities specialChances; //0x20
    RouletteItems* normalBoxes; //0x28 only 1 obviously
    RouletteItems* unknown; //0x2c 12 rouletteItems, not used in VS
    RouletteItems* specialBoxes; //0x30 as many as there are special box settings in the bin, so mostly 10

    u32 itemSpawnTimers[4]; //0x34 frames for when an item can next be pulled 0 = lightning, 1 = blue shell, 2 = blooper, 3 = pow
    u32 playerCount; //0x44 used to check when the player count changes online
}; // Total size 0x48
size_assert(ItemSlotData, 0x48);

}//namespace Item

#endif