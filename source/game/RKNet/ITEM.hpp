#ifndef _RKNETITEM_
#define _RKNETITEM_
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
//https://wiki.tockdom.com/wiki/MKWii_Network_Protocol/SELECT


namespace RKNet {

struct ITEMPacket {
    u8 timer; //start time in 8/60s
    u8 storedItem;
    u8 draggedItem;
    u8 mode; //0x3 0 = no item, 1-7 = handshake, 1 means newItem, start handshake
    u8 tailMode;
    u8 acknowledge; //0 = ok, 1 = fail for each player at console
    u8 acknowledgeTimer1;
    u8 acknowledgeTimer2;
};
size_assert(ITEMPacket, 0x8);

class ITEMHandler {
public:
    static ITEMHandler* sInstance; //809c20f8
    static ITEMHandler* GetStaticInstance(); //8065c0ec
    static void DestroyStaticInstance(); //8065c368
    ITEMHandler(); //8065c3a8
    ~ITEMHandler(); //8065dc2c unsure
    void Update(); //80656c5e8

    int GetStoredItemCount(ItemObjId itemObjId, u32* playerIds) const; //8065f6dc fills playerIds with ids that hold the item
    void UpdateItemStatusAndSums(); //8065e0a0
    void AcknowledgeAid(u8 hudSlotId, u8 aid); //8065e644
    void ExportSendPackets(); //8065dc6c
    void ImportNewPackets(); //8065dd3c
    ItemId GetStoredItem(u8 playerId) const; //8065d21c
    ItemId GetDraggedItem(u8 playerId) const; //8065d2b0
    u8 GetStoredItemMode(u8 playerId) const;  //8065d364
    u8 GetDraggedItemMode(u8 playerId) const; //g065d3f8
    u8 GetTimer(u8 playerId) const; //8065d4ac
    bool IsDraggingItem(u8 playerId) const; //8065d608
    bool HasStartedDraggingItem(u8 playerId, u32 r5) const; //8065d6e4

    bool IsPlayerIdConnected(u8 playerId) const; //8065d55c
    bool IsItemNew(u8 playerId) const; //8065d568, checks if mode == 1
    void SetItem(u8 playerId, ItemId itemId); //8065c6c0
    void SetItemAndMode(u8 playerId, u8 mode, ItemId itemId); //8065cfc4
    void SetDraggedItemAndMode(u8 playerId, u8 mode, ItemId itemId); //8065d0e0
    void RemoveItem(u8 playerId); //8065c74c
    void OnRouletteEnd(u8 playerId); //8065c7e0
    void UpdateLocalPlayers(); //8065f068
    void UpdateLocalPlayersItems(); //8065e8a8 never called or inlined
    void UpdateStoredItem(u8 playerId); //8065e938
    void UpdateDraggedItem(u8 playerId); //8065ed74

    int GetModeRelatedInt(u8 playerId) const;

    ITEMPacket toSendPackets[2]; //one per player at console
    ITEMPacket receivedPackets[12];
    u32 itemStatus[12]; //0x70 0 none, 1 valid item, 2 invalid (over the limit?)
    u32 startTimes[12]; //0xa0 60x packets timers
    u32 itemObjSums[15][3]; //0xb0 row is itemObj, col is stored/dragged/unknown
};
size_assert(ITEMHandler, 0x184);
}//namespace RKNet

#endif