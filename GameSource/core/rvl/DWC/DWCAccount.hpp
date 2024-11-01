#ifndef _DWC_ACCOUNT_ //to split into multiple files ultimately
#define _DWC_ACCOUNT_
#include <types.hpp>

//Credit Seeky

namespace DWC { //this is C, but don't care

struct AccLoginID {
    u32 userId;
    u32 userIdLo;
    u32 playerId;
};

struct AccUserData { //https://wiki.tockdom.com/wiki/Rksys.dat#DWC_User_Data
    u32 size;
    AccLoginID pseudoId;
    AccLoginID authenticID;
    int gsProfileId; //0x1c
    int flag; //0x20
    u32 gamecode; //0x24 always RMCJ
    u32 reserved[5];
    u32 crc32;
}; //0x40
size_assert(AccUserData, 0x40);

struct AccFlag {
    u32         flags;
    u32         reserved;
    u32         reserved1;
};

struct AccFriendKey {
    u32         id_data;
    u32         friendCode_lo32;
    u32         friendCode_hi32;
};

struct AccLoginId {
    u32         id_data;
    u32         userid_lo32;
    u32         playerid;
}; //0xc


struct AccGsProfileId {
    u32         id_data;
    int         id;
    u32         reserved;
};

union AccFriendData {
    AccFlag flags;
    AccLoginID loginId;
    AccFriendKey friendKey;
    AccGsProfileId gsProfileId;
}; //0xc
size_assert(AccFriendData, 0xc);

struct FriendUpdate {
    u8 unknown[4];
    u32 pid;
};

//char* statusData = GameSpy status, handled by the game itself, in mkwii, RKNet::StatusData
BOOL IsBuddyFriendData(const AccFriendData* frienddata); //800eb870
u8 GetFriendStatusData(const AccFriendData* friendData, char* statusData, int* size); //800ce190
void CreateUserData(AccUserData* userdata, u32 gamecode); //800ebf9c
BOOL CheckUserData(const AccUserData* userdata); //800ebfd4
BOOL CheckDirtyFlag(const AccUserData* userdata); //800ec314
void ClearDirtyFlag(AccUserData* userdata); //800ec320

u64 CreateFriendKey(const AccUserData* userData); //800ec6bc creates a friend code from userdata
BOOL CheckFriendKey(const AccUserData* userdata, u64 friendkey); //800eb8d8
void CreateFriendKeyToken(AccFriendData* dest, u32 unused, u64 friendCode); //800ec764
BOOL IsEqualFriendData(const AccFriendData* lhs, const AccFriendData* rhs); //800ec9cc
BOOL SetOwnStatusData(const char* statusData, u32 size); //800ce24c
BOOL CheckHasProfile(const AccUserData* userdata); //800ec150 has created a PID

BOOL IsValidFriendData(const AccFriendData* frienddata); //800ebf84

int
GetGsProfileId(const AccUserData* userdata, const AccFriendData* frienddata); //800ec498
}//namespace DWC


#endif