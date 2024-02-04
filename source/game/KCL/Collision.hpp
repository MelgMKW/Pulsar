#ifndef _KCLTYPEHOLDER_
#define _KCLTYPEHOLDER_
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>



struct KCLTypeHolder {
    static KCLTypeHolder* cur; //809c3be0
    void Reset(); //807bda7c resets closest collision entry and entry count to 0
    void ApplyFlagAndRegisterEntry(KCLBitfield bitfield, u16 kclFlag, float distance); //807bda9c
    bool FindClosestCollisionEntry(KCLBitfield acceptedFlags); //807bd96c use 809c3bdc after, r3 unused


    void ReplaceBLIGHTIndex(u8 newBlightIdx); //807bdb28
    void ReplaceKCLVariant(u8 newVariant); //807bdb5c
    void ReplaceWheelDepth(u8 newDepth); //807bdb90
    void ReplaceTrickableBit(bool isTrickable); //807bdbc4
    void ReplaceRejectBit(bool isTrickable); //807bdbf8
    void ReplaceSoftBit(bool isTrickable); //807bdc2c

    KCLBitfield bitfield;  //1<<KCLTYPE
};

struct CollisionEntry {
    static CollisionEntry entriesArray; //809c38d8
    static u32 entryCount; //809c3bd8
    static u32 maxCount; //0x40
    static CollisionEntry* closestEntry; //809c3bdc
    KCLTypeHolder type;
    u16 kclFlag; //0x4
    u8 padding[2];
    float distance; //0x8
}; //0xC

#endif