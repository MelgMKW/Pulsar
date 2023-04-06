#ifndef _FRIEND_
#define _FRIEND_
#include <kamek.hpp>
#include <game/System/SaveDataManager.hpp>

class Friend {
    virtual ~Friend(); //80519670 vtable 808b2c88
    void SetFriend(FriendData *src); //805196b0
    void StoreFriend(FriendData *dest); //805196f0 stores in RKPD
    void AddLoss(); //805199d0
    void AddWin(); //805199e8
    u8 unknown_0x4[4];
    FriendData data; //0x8
}; //0x1c0

#endif