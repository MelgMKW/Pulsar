#ifndef _DWC_ACCOUNT_ //to split into multiple files ultimately
#define _DWC_ACCOUNT_
#include <types.hpp>

//Credit Seeky

namespace DWC { //this is C, but don't care

struct AccLoginID {
    u64 userId;
    u32 playerId;
};

struct AccUserData { //https://wiki.tockdom.com/wiki/Rksys.dat#DWC_User_Data
    u32 size;
    AccLoginID pseudoId;
    AccLoginID authenticID;
    int gsProfileId; //0x1c
    int flag;
    u32 gamecode; //always RMCJ
    u32 reserved[5];
    u32 crc32;
};

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

struct AccFriendData {
    AccFlag          flags;
    AccLoginId       login_id;
    AccFriendKey     friend_key;
    AccGsProfileId   gs_profile_id;
};

struct Friend {
    u32 bitflag;
    u32 pid;
    u32 unknown_0x4;
};

struct FriendUpdate {
    u8 unknown[4];
    u32 pid;
};

u8 GetFriendStatusData(const AccFriendData* friendData, char* statusData, int* size);
u64 CreateFriendKey(const AccUserData* userData); //800ec6bc creates a friend code from userdata
void CreateFriendKeyToken(const AccFriendData* friendData, u32 unused, u64 friendCode); //800ec764


}//namespace DWC


#endif