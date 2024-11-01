#ifndef _ITEMEVENT_
#define _ITEMEVENT_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/RKNet/EVENT.hpp>

namespace Item {

class Obj;
struct ShootEntry { //used for SHOOT, HITDRAGGED and DROP
    u16 bitfield;
    u32 objBitfield78;
    s16 xPosDivBy4; //0x6
    s16 yPosDivBy4;
    s16 zPosDivBy4;
    s8 xPosDiffDivBy2;
    s8 yPosDiff;
    s8 zPosDiff;
    s8 xSpeedDivBy2;
    s8 ySpeed;
    s8 zSpeedDivBy2;
}; //0x12 +2 for time u16 = 0x14

//these are only used for shoot packets
struct ShootTargetingEntry : public ShootEntry {
    u8 itpt;
}; //0x14

struct ShootBombEntry : public ShootEntry {
    s8 bombObjFloat1d0Times64;
};

struct HitFreeEntry {
    u16 eventBitfield; //0x0 of recv shoot/hitdragged/drop
    u8 bitfield; //0x2 playerId is the first 4 bits, type of break is the last 4
}; //0x3 +2 for time u16 = 0x5

struct UseEntry {
    u8 playerId;
}; //0x1 +2 for time u16 = 0x3

struct TCLostEntry { //ItemObjId itemObjId, u8 playerId, u8 r5, u16 eventBitfield, u32 kumo1a8, u32 r8 args of the add func
    u16 bitfield; //0x2 combines playerId (1st 4 bits) and eventBitfield and kumo1a8 (last 12)
    u8 bitfield2; //0x3 combines r5 and r8
}; //0x3 +2 for time u16 = 0x5

class EVENTBuffer {
public:
    struct Entry {
        u8 data[0x18];
        ItemObjId objId; //0x18
        RKNet::EVENTAction action; //0x1c
        u32 time; //0x20
    }; //0x24

    struct SendEntryValues {
        u8 idx; //if 0xff, entry is used, otherwise it means it's free
        u8 unknown;
        u8 entrySize;
        u8 padding;
    }; //0x4

    struct RecvEntryValues {
        u8 idx; //if 0xff, entry is used, otherwise it means it's free
        u8 unknown;
        u16 unknown_0x2;
    }; //0x4
    static void* curPacket; //809c3624, size 0x21, stores a packet for the currently calc'd item
    static EVENTBuffer* sInstance; //809c3620
    static void CreateInstance(); //8079a8a4
    static void DestroyInstance(); //8079ab68

    EVENTBuffer(); //8079d3dc
    ~EVENTBuffer(); //8079d674 

    void UpdateSend(); //8079bd94 will send the queued send entries if space is freed up
    void UpdateReceive(); //8079bed0

    void QueueSendEntry(ItemObjId itemObjId, RKNet::EVENTAction action, void* data, u32 dataLength); //8079bfec
    void QueueReceivedEntry(ItemObjId itemObjId, RKNet::EVENTAction action, u32 unused, void* data, u32 time = 0); //8079c0ac

    //fill if bool is true, return new position of packet
    static void* FillOrExtractBitfield(u16* packetEntry, u16* dest, u8* collisionPlayerId, bool extractOrFill); //8079b338 dest is essentially always Obj::eventBitfield, returns the new position of the packet
    static void* FillOrExtractShootPos(s16* shootPacketPosPtr, Vec3* position, bool extractOrFill); //8079ad38 inlined in fillorextractshoot
    static void* FillOrExtractShoot(ShootEntry* shootPacket, Obj* obj, bool extractOrFill); //8079b4ac returns ptr to position in the packet
    static void* FillOrExtractPosDiff(void* packetPosDiffPtr, Vec3& objPos, Vec3& lastObjPos, bool extractOrFill); //8079af08
    static void* FillOrExtractTargetingShoot(void* targetingShootItptPtr, u8* itpt, bool extractOrFill); //8079b398
    static void* FillOrExtractBombShoot(void* bombShootPacketFloatPtr, float* objBomb1d0, bool extractOrFill); //8079b440
    static u8 GetPlayerIdFromBitfield(u16 bitfield); //8079ad30
    static u8 GetUSEPlayerId(const UseEntry& entry); //8079c8e4 only works for entries where it makes sense to have a playerId (mostly USE)
    static u16 GetEntryBitfield(const ShootEntry& entry, ItemObjId itemObjId); //8079c8c8 used for shoot/hit dragged/drop
    static void GetHitFreeEntryPlayerIdAndType(u8* playerId, u32* type); //8079c880

    EGG::TDisposer<EVENTBuffer> disposer; //8079a778 vtable 808d1970
    u8 lastSendEntryIdx; //0x11
    u8 nextSendEntryIdx;
    u8 padding[2];
    SendEntryValues* sendEntryValues; //0x14 0xa2 size if 0xff, that idx is already used, otherwise, just the value
    Entry* sendQueuePosition; //0x18 in case there's a lack of space in EVENTMgr
    u32 unknown_0x1c;

    u8 lastReceivedEntryIdx; //0x20
    u8 nextReceivedEntryIdx; //0x21
    u8 padding2[2];
    RecvEntryValues* receivedEntryValues; //0x24
    Entry* receivedQueue; //0x28


}; //0x44

}//namespace Item
#endif