#ifndef _RKNETFRIENDMGR_
#define _RKNETFRIENDMGR_
#include <kamek.hpp>
#include <core/rvl/os/mutex.hpp>
#include <core/rvl/DWC/DWC_Account.hpp>

namespace RKNet {
class FriendMgr {
public:
    static FriendMgr* sInstance; //809c2110
    static FriendMgr* CreateInstance(); //80663194
    static void DestroyInstance(); //806632bc
    virtual ~FriendMgr(); //806573dc vtable 808c0988
    bool isBuddyFriend(u8 idx); //8066375c
    OS::Mutex mutex;
    DWC::AccUserData myUserData[2]; //0x1c
    DWC::Friend friends[30][2]; //0x9c
    u32 friendPids[30]; //0x36c
    DWC::FriendUpdate* friendUpdate; //0x3e4
}; //total size 0x3e8
size_assert(RKNetFriendMgr, 0x3e8);
}//namespace RKNet
#endif