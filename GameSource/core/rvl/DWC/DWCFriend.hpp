#ifndef _DWCFRIEND_ //to split into multiple files ultimately
#define _DWCFRIEND_

#include <types.hpp>
#include <core/rvl/DWC/DWCAccount.hpp>
#include <core/rvl/DWC/DWCError.hpp>
#include <core/rvl/os/OS.hpp>

//Credit Seeky

namespace DWC { //this is C, but don't care
enum FriendState {
    DWC_FRIEND_STATE_INIT = 0,      //Initial state
    DWC_FRIEND_STATE_PERS_LOGIN,    //during persistent server login and friend list synchronization
    DWC_FRIEND_STATE_LOGON,         //After Persistent server login
    DWC_FRIEND_STATE_NUM
};

enum FriendStatus {
    DWC_FRIEND_STATUS_OFFLINE = 0,    //Offline
    DWC_FRIEND_STATUS_ONLINE,         //Online (already logged onto GP server)
    DWC_FRIEND_STATUS_PLAYING,        //During game play
    DWC_FRIEND_STATUS_MATCH_ANYBODY,  //friend unspecified peer matchmaking in progress
    DWC_FRIEND_STATUS_MATCH_FRIEND,   //friend specified peer matchmaking in progress
    DWC_FRIEND_STATUS_MATCH_SC_CL,    //client during server-client matchmaking
    DWC_FRIEND_STATUS_MATCH_SC_SV,    //server during server-client matchmaking
    DWC_FRIEND_STATUS_NUM
};

//Friend List synchronisation cb
typedef void (*UpdateServersCallback)(Error error, BOOL isChanged, void* param);

//Notification of changes in friend status cb
typedef void (*FriendStatusCallback)(int index, u8 status, const char* statusString, void* param);

//Friend roster delete cb
typedef void (*DeleteFriendListCallback)(int deletedIndex, int srcIndex, void* param);

//New friend established cb
typedef void (*BuddyFriendCallback)(int index, void* param);

//data storage server/login cb
typedef void (*StorageLoginCallback)(Error error, void* param);

//data storage server save complete cb
typedef void (*SaveToServerCallback)(BOOL success, BOOL isPublic, void* param);

//data storage server load complete cb
typedef void (*LoadFromServerCallback)(BOOL success, int index, char* data, int len, void* param);

struct FriendControl {
    static FriendControl* sInstance; //803862D0

    FriendState state;    //0x0
    GP::Connection** gpConnection;
    u32 gpProcessCount; //0x8
    u8 timeAlignementPadding[4];
    OS::Time lastGpProcess; //0x10 time at which the last gpProcess was called
    int friendListLen; //0x18
    AccFriendData* friendList; //0x1c

    u8  buddyUpdateIdx;      //0x20 Index during synchronous processing of the friend roster
    bool  friendListChanged;   //1: There has been a change to the friend roster, 0: No change
    u8  buddyUpdateState;    //Synchronous processing status of friend roster. Defined using DWC_BUDDY_UPDATE_STATE_* enumerator.
    vu8 svUpdateComplete;    //friend list synchronization complete flag synchronization complete with 2
    u32 persCallbackLevel;   //0x24 Number of callback waits for Persistent data save/load
    int localProfileID;           //0x28 
    const u16* playerName;   //0x2c

    UpdateServersCallback updateCallback;     //0x30 friend list synchronization complete callback
    void* updateParam;       //0x34
    FriendStatusCallback statusCallback;      //0x38 Callback for notification of changes to friend status
    void* statusParam; //RKNet::Controller in mkwii
    DeleteFriendListCallback deleteCallback;  //0x40 Friend roster delete callback
    void* deleteParam;
    BuddyFriendCallback buddyCallback;        //0x48 Callback for establishing friendship
    void* buddyParam; //RKNet::Controller in mkwii
    StorageLoginCallback persLoginCallback;   //0x50 Persistent server login completion notification callback
    void* persLoginParam;
    SaveToServerCallback saveCallback;        //0x58 Persistent server save callback
    LoadFromServerCallback loadCallback;      //0x5c Persistent server load callback
}; //0x60

void iFriendInit(FriendControl* control, GP::Connection* gpConnection, const u16* playerName, AccFriendData* friendList, int friendListLen); //800ce414
BOOL CanChangeFriendList(); //800ce2e4 is FriendControl ready or busy
void DeleteBuddyFriendData(AccFriendData* friendData); //800ce314
}//namespace DWC


#endif