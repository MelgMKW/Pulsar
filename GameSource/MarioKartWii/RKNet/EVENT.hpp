#ifndef _RKNETEVENT_
#define _RKNETEVENT_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
//https://wiki.tockdom.com/wiki/MKWii_Network_Protocol/EVENT


namespace RKNet {
//each data is active for 200 frames

enum EVENTEntryState {
    EVENTENTRYSTATE_FREE,
    EVENTENTRYSTATE_FULL,
    EVENTENTRYSTATE_EXPIRED
};

enum EVENTAction {
    EVENTACTION_NONE,
    EVENTACTION_USE,
    EVENTACTION_SHOOT,
    EVENTACTION_HITDRAGGED,
    EVENTACTION_HITFREE,
    EVENTACTION_TC_LOST,
    EVENTACTION_6,
    EVENTACTION_DROP
};

#pragma pack(push, 1)
struct EVENTType {
    union {
        struct {
            EVENTAction action : 3;
            ItemObjId itemObjId : 5;
        };
        u8 value;
    };
};
size_assert(EVENTType, 0x1);

struct EVENTPacket {
    static const u32 idx = 7;
    EVENTType entryTypes[0x18]; //24 slots a value of 0x10 indicates no DATA on that slot
    u8 entryData[0xe0]; //not ordered, but each entry has its length
};
size_assert(EVENTPacket, 0xf8); //only as the types array and the used data entries are sent, so most times much smaller data is sent

struct EVENTEntry { //this means each entry has size up to 0x21
    u16 time;
    u8 data[0x17]; //0x2 exact size depends on action
    u8 state; //0x19 see enum
    u8 itemObjId; //0x1a
    u8 action; //0x1b see enum
    u8 dataLength; //0x1c
    u8 unknown_0x1d[3];
};
size_assert(EVENTEntry, 0x20);
#pragma pack(pop)

class EVENTHandler {
public:
    static EVENTHandler* sInstance; //809c20f0
    static EVENTHandler* CreateInstance(); //8065b4e8
    static void DestroyInstance(); //8065b600
    EVENTHandler(); //8065b640
    ~EVENTHandler(); //8065ba8c
    void Update(); //8065b730
    void AddEntry(ItemObjId itemObjId, EVENTAction action, const void* data, u32 dataLength); //8065b780
    bool HasFreeEntries() const; //8065b8d4
    void Reset(); //8065b998
    void ExportSendEntries(); //8065bb94
    void ImportReceivedEntries(); //8065bce4
    void ProcessReceivedEntries(); //8065be40
    void FreeExpiredSendEntries(); //8065bacc 200 frames + state_expired
    void ResetEntry(EVENTEntry& entry); //8065c04c
    EVENTType GetEntryType(const EVENTEntry& entry) const; //8065c078
    void SetItemAndActionFromType(EVENTType type, EVENTEntry& entry); //8065c0b0
    void ProcessEntry(u32 playerId, EVENTEntry& entry) const; //8065c0c4 inlined

    bool isPrepared;
    u8 padding[3];
    EVENTEntry toSendEntries[24]; //0x4
    EVENTEntry receivedEntries[12][24];//0x304 row is aid
    u32 hasReceivedEntry[12][24]; //0x2704 1 is an entry isn't empty
    u32 freeDataInSendBuffer; //0x2b84
};
size_assert(EVENTHandler, 0x2b88);


}//namespace RKNet

#endif