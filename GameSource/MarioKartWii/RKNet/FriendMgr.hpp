#ifndef _RKNETFRIENDMGR_
#define _RKNETFRIENDMGR_
#include <kamek.hpp>
#include <core/rvl/os/OSmutex.hpp>
#include <core/rvl/DWC/DWC.hpp>

namespace RKNet {
class FriendMgr {
public:
    static FriendMgr* sInstance; //809c2110
    static FriendMgr* CreateInstance(); //80663194
    static void DestroyInstance(); //806632bc
    FriendMgr(); //806639a0 inlined
    virtual ~FriendMgr(); //806573dc vtable 808c0988



    void ReadDataFromRKSYS(); //806632fc
    void Update(); //80663444
    void CreateAccUserData(u32 gameCode); //806635a8
    bool CheckAccUserData() const; //806635b0
    bool IsAccUserDataDirty() const; //806635e0
    void ClearAccUserDataDirtyFlag(); //80663610
    u64 CreateFriendCode() const; //80663618
    void SetCodesForUnusedIdxs(u64* friendCodes); //80663644
    bool IsAvailable() const; //8066374c IsFriendCodes == nullptr
    bool IsBuddyFriend(u8 idx) const; //8066375c
    bool IsValidFriend(const DWC::AccFriendData* data) const; //80663794
    bool CheckFriendCode(const u64& friendCode) const; //806637c4
    s32 GetFriendIdx(const u64& friendCode) const; //806637fc returns -1 if code is not a friend
    s32 GetFriendCodeLicenseIdx(const u64& friendCode) const; //80663874 returns -1 if code is not one of the licenses
    u64 GetLicenseFriendCode(u8 licenseIdx) const; //80663918
    s32 GetFirstFreeFriendIdx() const; //80663940 goes through every frienddata until one is valid, and return its idx, else return -1
    OS::Mutex mutex;
    DWC::AccUserData myUserData[2]; //0x1c
    DWC::AccFriendData friends[30][2]; //0x9c
    u32 friendPids[30]; //0x36c GPProfiles
    u64* friendCodes; //0x3e4
}; //total size 0x3e8
size_assert(RKNetFriendMgr, 0x3e8);
}//namespace RKNet
#endif