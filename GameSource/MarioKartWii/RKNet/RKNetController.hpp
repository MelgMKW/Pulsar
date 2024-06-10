#ifndef _RKNETCONTROLLER_
#define _RKNETCONTROLLER_

#include <kamek.hpp>
#include <core/egg/mem/ExpHeap.hpp>
#include <core/egg/Thread.hpp>
#include <MarioKartWii/RKNet/PacketHolder.hpp>
#include <MarioKartWii/RKNet/RACEHeader.hpp>
#include <core/rvl/DWC/Error.hpp>
#include <core/rvl/DWC/DWC.hpp>

/*
RKNetController is the class that handles the game specific network code (ex. RACE Packets) and controls DWC
Contributors:
  Seeky (main documentation)
References:
  http://wiki.tockdom.com/wiki/MKWii_Network_Protocol
*/


struct StatusData { //http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/Server/gpcm.gs.nintendowifi.net#locstring
    u32 hostDWCgroupid;
    u8 regionId; //last byte of it
    u8 status; //bitfield
    u8 playerCount;
    u8 curRace;
};

namespace RKNet {
struct Friend {
    StatusData statusData; //8 bytes, see 
    u8 unknown_0x8[4];
}; //total size 0xC

class SplitRACEPointers {
public:
    SplitRACEPointers(); //8065a3dc
    ~SplitRACEPointers(); //8065a474

    PacketHolder* header;
    PacketHolder* raceHeader1;
    PacketHolder* raceHeader2;
    PacketHolder* select; //0xc
    PacketHolder* racedata;
    PacketHolder* user;
    PacketHolder* item;
    PacketHolder* event;
}; //0x20

struct ConnectionUserData {
    u8 playersAtConsole;
    u8 unknown_0x1[3];
}; //Total size 0x4

enum ConnectionState {
    CONNECTIONSTATE_SHUTDOWN,
    CONNECTIONSTATE_LOGIN_START,
    CONNECTIONSTATE_LOGIN_AUTHORISED,
    CONNECTIONSTATE_LOGIN_FRIENDS_SYNCED,
    CONNECTIONSTATE_MATCHING,
    CONNECTIONSTATE_FAILED,
    CONNECTIONSTATE_ERROR
};

enum RoomType {
    ROOMTYPE_NONE,
    ROOMTYPE_VS_WW,
    ROOMTYPE_VS_REGIONAL,
    ROOMTYPE_BT_WW,
    ROOMTYPE_BT_REGIONAL,
    ROOMTYPE_FROOM_HOST,
    ROOMTYPE_FROOM_NONHOST,
    ROOMTYPE_JOINING_WW,
    ROOMTYPE_JOINING_REGIONAL,
};

class Controller;
void MainNetworkLoop(Controller* controller); //80657500
void* SOAlloc(u32 size); //80658418
void SOFree(void* memBlock); //80658498
void* DWCAlloc(u32 size, s32 alignment); //80658500
void DWCFree(void* memBlock); //8065858c
void RACERecvCallback(u32 aid, RACEPacketHeader* packet, u32 size); //806585f4
void LoginCallback(DWC::Error error, int profileId, Controller* controller); //80658614
void MatchedCallback();
bool ConnectionAttemptCallback(DWC::ConnectionUserData* newClientUserData, Controller* controller); //80658768  true if the player is <=12
void ConnectionClosedCallback(DWC::Error error, bool isLocal, bool isServer, u32 aid, int index, Controller* controller); //80658824
void UpdateServerCallback(int error, int isChanged, Controller* controller); //806588d8
void UpdateServerCallbackAlt(int error, int isChanged, Controller* controller); //806588fc
void FriendStatusChangeCallback(); //80658918
void BuddyFriendCallback(u32 unused, Controller* controller);          //8065891c

struct ControllerSub {
    u64 unknown_0x0; //a time for something
    u32 connectionCount; //0x8 number of consoles connected
    u32 playerCount; //0xc
    u32 availableAids; //0x10 bit flags, 1 for connected, indexed 1 << aid
    u32 directConnectedAids; //0x14 bit flags, same as above
    u32 groupId; //0x18 group id for the room
    u32 friendToJoin; //0x1c index in your friend roster of who is joined
    u8 localPlayerCount; //0x20
    u8 localAid; //0x21
    u8 hostAid; //0x22 aid of the host
    ConnectionUserData connectionUserDatas[12]; //0x24 index is aid
    bool matchingSuspended;
    u8 unknown_0x54[4];
}; //Total size 0x58

class Controller {
public:
    static Controller* sInstance; //809c20d8
    static Controller* CreateInstance(); //80655b24
    static void DestroyInstance(); //80655bac
    explicit Controller(EGG::ExpHeap* heap); //80657004
    virtual ~Controller(); //8065741c vtable 808c097c

    void ScheduleShutdown(); //806561a8
    void Init(u8 localPlayerCount); //80655c10 starts MainNetworkLoop
    void StartSearchWW(u32 localPlayerCount); //806561b4
    void StartSearchRegional(u32 localPlayerCount); //80656270
    void StartSearchBTWW(u32 localPlayerCount); //8065632C
    void StartSearchBTRegional(u32 localPlayerCount); //806563e8

    //these can fail ofc
    void JoinFriend(u32 friendIdx, u32 localPlayerCount); //806564a4
    void JoinRoom(u32 friendIdx, u32 localPlayerCount); //80656704
    void StartRoom(u32 localPlayerCount); //806567d8
    void ResetRH1andROOM(); //80656898 called by GlobeSearch::OnResume

    void UpdateServersAsyncAlt(); //80656aec
    void UpdateServersAsync(); //80656b44
    void UpdateFriendsStatus(); //80656b6c

    void SetFriendDeleted(u32 friendIdx); //80656d6c
    bool IsConnectedToAnyone() const; //80656f00
    void ClearSplitSendRACEPointers(); //80656f40
    void SetConnectionStateToFailed(); //80656ff8
    void MainLoop(); //80657504
    void SendPacketsAndUpdateUSER(); //80657a70
    void CombineSplitSendPackets(); //80657ab0
    void TrySendNextRACEPacket(); //80657e30
    bool SendAidNextRACEPacket(u32 aid) const; //80657fe4 if success
    int GetSplitSendPacketsTotalSize() const; //806580c4
    void SetConnectionState(ConnectionState state); //80658140
    ConnectionState GetConnectionState() const; //80658148
    void HandleError(); //806581cc
    void* Alloc(u32 size, s32 alignment); //8065832c
    void Free(void* memBlock); //806583b4
    void ProcessPlayerDisconnect(u32 aid); //80658990
    void ConnectToWFC(); //80658b9c
    void InitSubs(); //80658d3c
    void UpdateSubsAndVR(); //80658de0
    void ResetFriendArray(); //80658f80
    void StartMatching(); //80659044
    void ConnectToAnybodyAsync(); //80659170
    void SetupGameServer(); //806595b8
    void ConnectToGameServerFromGroupId(); //80659680
    void CalcRACEPacketCRC32(u32 aid); //80659a3c
    void ProcessRACEPacket(u32 aid, const RACEPacketHeader& packet, u32 size); //80659a84
    void UpdateAidsBelongingToPlayerIds(); //80659bc0
    void ResetAidsBelongingToPlayerIds(); //80659d20
    RoomType GetFriendSearchType(u32 friendIdx) const; //80659fa4
    s32 GetHudSlotId(s32 localPlayerNum) const; //80659d58
    void UpdateStatusDatas(); //8065a0b4


    u32 unkVtable;//unknown class vtable 808c0988
    OS::Mutex mutex; //0x8

    EGG::ExpHeap* expHeap; //0x20
    EGG::TaskThread* taskThread; //0x24
    ConnectionState connectionState; //0x28 
    u8 unknown_0x2c[0x38 - 0x2c];
    ControllerSub subs[2]; //0x38
    RoomType roomType; //0xe8
    u8 unknown_0xec[4];

    SplitRACEPointers* splitToSendRACEPackets[2][12]; //0xf0 split pointers for the outgoing packets, double buffered, indexed by aid
    SplitRACEPointers* splitReceivedRACEPackets[2][12]; //0x150 split pointers for the incoming packets, double buffered, indexed by aid
    PacketHolder* fullSendPackets[12]; //0x1b0 combined outgoing packets, indexed by aid
    u64 lastRACEToSendTimes[12]; //0x1e0 time when last sent to that aid
    u64 lastRACERecivedTimes[12]; //0x240 time when last received from that aid
    u64 RACEToSendTimesTaken[12]; //0x2a0 last send time minus the time of the send before it
    u64 RACEReceivedTimesTaken[12]; //0x300 last receive time minus the time of the receive before it
    u8 lastRACESendAid; //0x360 aid a packet was last sent to
    u8 fullRecivedPackets[12][0x2e0]; //0x361 1 per aid
    u8 padding[3]; //0x25e1
    StatusData localStatusData; //0x25e4 8 bytes, see http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/Server/gpcm.gs.nintendowifi.net#locstring
    Friend friends[30]; //0x25ec 
    bool friendsListIsChanged; //0x2754 true if unprocessed changes have happeend
    bool shutdownScheduled; //0x2755 will cause shutdown of wifi connection on next run of the main loop if true
    bool friendStatusUpdateScheduled; //0x2756 if true, the main loop will update all friend statuses on the next iteration
    u8 unknown_0x2757;
    bool hasprofanity; //0x2758 1 if name is bad
    u8 padding2[3];
    s32 badWordsNum; //0x275c number of bad strings in the profanity check
    u8 unknown_0x2760[3];
    s32 vr; //0x2764
    s32 br; //0x2768
    s32 lastSendBufferUsed[12]; //0x276c last full send buffer used for each aid, 0 or 1
    s32 lastReceivedBufferUsed[12][8]; //0x279c last Received buffer used for each packet per aid, 1 or 0
    s32 currentSub; //0x291c index of the current sub to use, 0 or 1
    u8 aidsBelongingToPlayerIds[12]; //0x2920 index is player id, value is aid
    u32 disconnectedAids; //0x292c 1 if disconnected, index 1 << aid
    u32 disconnectedPlayerIds; //0x2930 index 1 << playerId
    u8 unknown_0x2934[0x29c8 - 0x2934];

    static u32* splitRACEPointersBufferSizes; //8089a194
};
size_assert(Controller, 0x29c8);

}//namespace RKNet
#endif
