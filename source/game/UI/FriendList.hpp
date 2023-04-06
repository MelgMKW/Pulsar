#ifndef _FRIENDLIST_
#define _FRIENDLIST_
#include <kamek.hpp>
#include <game/System/Friend.hpp>

class FriendList;

class FriendListEntry {
    FriendListEntry(); //805d1f38
    ~FriendListEntry(); //805d1f80
    u8 unknown_0x0[8];
    Friend friendData;
    u32 isFriend; //0x1d0
    u8 unknown_0x1d4[4];
}; //0x1d8
size_assert(FriendListEntry, 0x1d8);

class FriendListSub_0x3750 {
    virtual void vtable(); //805d31fc vtable 808b8918
    FriendList *friendList;
    u8 unknown_0x8[0x100 - 0x8];
}; //0x100

class FriendListSub_0x3850 {
    virtual void vtable(); //805d3460 vtable 808b8900
    FriendList *friendList;
    u8 unknown_0x4[0x80 - 0x8];
}; //0x80

class FriendList {
    FriendList(); //805d1e84
    ~FriendList(); //805d1ef8
    void Init(); //805d20a4
    FriendListEntry entries[30];
    FriendListSub_0x3750 sub_0x3750;
    FriendListSub_0x3850 sub_0x3850;
}; //0x38d0
size_assert(FriendList, 0x38d0);


#endif