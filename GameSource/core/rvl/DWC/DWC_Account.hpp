#ifndef _DWC_ACCOUNT_ //to split into multiple files ultimately
#define _DWC_ACCOUNT_
#include <types.hpp>

//Credit Seeky

namespace DWC { //this is C, but don't care

extern char loginRegion[8]; //80384fd0


struct AccFlag {
    u32         flags;
    u32         reserved;
    u32         reserved1;
};

struct AccFriendKey {
    u32         id_data;
    u32         friendkey_lo32;
    u32         friendkey_hi32;
};

struct AccLoginId {
    u32         id_data;
    u32         userid_lo32;
    u32         playerid;
};


struct AccGsProfileId {
    u32         id_data;
    int         id;
    u32         reserved;
};

struct FriendData {
    AccFlag          flags;
    AccLoginId       login_id;
    AccFriendKey     friend_key;
    AccGsProfileId   gs_profile_id;
};

u8 GetFriendStatusData(const FriendData* friendData, char* statusData, int* size);

}//namespace DWC


#endif