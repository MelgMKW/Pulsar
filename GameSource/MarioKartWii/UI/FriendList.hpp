#ifndef _FRIENDLIST_
#define _FRIENDLIST_
#include <kamek.hpp>
#include <MarioKartWii/System/Friend.hpp>

class FriendList;

enum FriendListStatus {
    FRIENDLIST_STATUS_NONE = -1, //dcd, not added back etc...
    FRIENDLIST_STATUS_ROOM_HOST = 3,
    FRIENDLIST_STATUS_ROOM_NONHOST = 4,
    FRIENDLIST_STATUS_PUBLIC_VS_WW = 15,
    FRIENDLIST_STATUS_PUBLIC_VS_REGIONAL = 16,

};

class FriendCodesController {
    virtual void Update(); //805d31fc vtable 808b8918 copies from FriendList and then calls SetCodes
    virtual void TrySaveMgrToRKSYS(); //805d32b8 checks bool at 0x8 and if FriendMgr is ready
    virtual void ResetMgrKeys(); //0x10 805d3450 calls RKNet::FriendMgr::SetKeysForUnusedIdxs with keys == nullptr
    virtual void SaveMgrToRKSYS(); //0x14 805d331c
    FriendList* friendList;
    bool hasNewData; //0x8
    u8 unknown_0x9[0x10 - 0x9];
    u64 friendCodes[30]; //0x10
}; //0x100
size_assert(FriendCodesController, 0x100);

class FriendReceiver { //receives data (mii) of a friend that was added (until it has been received, the friend is a ? on the friendlist)

    virtual void TrySaveToRKSYS(); //805d3460 vtable 808b8900
    virtual void TryReceiveData(); //0xc 805d34d4 checks bool at 0x8 and if ServerMgr is ready
    virtual void vf_0x10(); //0x10 805d376c
    virtual void SaveToRKSYS(); //0x14 805d36bc

    FriendList* friendList;
    bool hasNewData; //0x8
    u8 unknown_0x9[0x10 - 0x9];
    RFL::StoreData rawMii; //0x10
    u8 unknown_0x5c[4];
    //args of Friend::SetData
    u32 r9; //0x60
    u32 r10; //0x64
    u32 r5; //0x68
    u16 r6; //0x6c
    u16 r7; //0x6e
    u8 r11; //0x70
    u8 unknown_0x71[0x7c - 0x71];
    u32 friendIdx; //0x7c
}; //0x80
size_assert(FriendReceiver, 0x80);

class FriendListEntry {
    FriendListEntry(); //805d1f38
    ~FriendListEntry(); //805d1f80
    u64 friendCode;
    Friend friendInfo; //0x8
    u32 friendStatus; //0x1d0 bitfield 1 is friend, 2 = hosting a room, other values unknown (is in a WW etc...?)
    u8 unknown_0x1d4[4];
}; //0x1d8
size_assert(FriendListEntry, 0x1d8);

class FriendList {
    FriendList(); //805d1e84
    ~FriendList(); //805d2040
    void Init(); //805d20a4
    void Update(); //805d2264

    int GetFriendCount() const; //805d24c0
    u32 AddFriend(const u64& friendCode); //805d255c returns idx of new friend
    void RemoveFriend(u32 idx); //805d2700
    u32 GetFriendIdx(const u64& friendCode); //805d2778
    const FriendListEntry* GetFriendEntry(u32 idx) const; //805d2874
    const Friend* GetFriend(u32 idx) const; //805d2890
    u32 GetFriendStatus(u32 idx) const; //805d28c8 returns -1 if not friend, 0 if slot open, friendStatus otherwise
    bool IsFriendStatusLessThan25(u32 idx) const; //805d2900

    void SaveToRKSYS(); //805d21b4
    bool IsUpdated(); //805d294c
    void UpdateKeyController(); //805d2968
    void UpdateStatuses(); //805d2a50
    void UpdateFriendData(u32 aid); //805d2d44 copies/updates entry using USER packet of aid if aid is a friend


    FriendListEntry entries[30];
    FriendCodesController codesController;
    FriendReceiver receiver;
}; //0x38d0
size_assert(FriendList, 0x38d0);


#endif