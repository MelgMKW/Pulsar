#ifndef _NWC24FRIEND_
#define _NWC24FRIEND_
#include <types.hpp>
#include <core/rvl/nwc24/NWC24Types.hpp>

namespace NWC24 { //this is C, but don't care

struct FriendAttr {
    u32 type;
    u32 status;
    u16 name[12];
    u64 fdId;
    u32 reserved[6];
};

union FriendAddr {
    u64 wiiId;
    char mailAddr[256];
};

struct FriendInfo {
    FriendAttr attr;
    FriendAddr addr;
};

Error ReadFriendInfo(FriendInfo* info, u32 index); //801e70c8
int IsFriendInfoThere(u32 index); //801e7244
Error GetNumFriendInfos(u32* num); //801e716c

}//namespace NWC24


#endif