#ifndef _FRIEND_
#define _FRIEND_
#include <kamek.hpp>
#include <core/rvl/RFL/RFL.hpp>

struct FriendData {
    u64 friendCode;
    u64 wiiFC; //0x8
    u8 unknown_0x10[2];
    u16 losses; //0x12
    u16 wins; //0x14
    u16 vr; //0x16
    u16 br; //0x18
    RFL::StoreData friendMii; //0x1a
    u8 idx; //0x66
    char gameRegion; //0x67
    u8 countryID; //0x68
    u8 regionID; //0x69
    u16 city; //0x6a
    u16 globeCoords[2]; //0x6c longtitude and latitude
    u8 unknown_0x70[0x1c0 - 0x70];
};
size_assert(FriendData, 0x1c0);

class Friend {
    virtual ~Friend(); //80519670 vtable 808b2c88
    void AddFriend(u16 idx, const u64* friendCode);
    bool SetFriend(const FriendData& src); //805196b0
    void StoreFriendToDest(FriendData& dest); //805196f0 essentially for RKPD
    void AddLoss(); //805199d0
    void AddWin(); //805199e8
    //location = country/state/city as a u32
    void SetData(const RFL::StoreData& mii, u32 location, u16 longitude, u16 latitude, u32 unused, u64 wiiFC, char gameRegion); //80519980
    u8 unknown_0x4[4];
    FriendData data; //0x8
}; //0x1c0

#endif