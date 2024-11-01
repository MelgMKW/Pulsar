#ifndef _RKNETCONTROLLER_
#define _RKNETCONTROLLER_

#include <kamek.hpp>
#include <core/egg/mem/ExpHeap.hpp>
#include <core/egg/Thread.hpp>
#include <core/rvl/DWC/DWCError.hpp>
#include <core/rvl/DWC/DWC.hpp>
#include <MarioKartWii/RKNet/PacketHolder.hpp>
#include <MarioKartWii/RKNet/RACEHeader.hpp>


/*
RKNetController is the class that handles the game specific network code (ex. RACE Packets) and controls DWC
Contributors:
  Seeky (main documentation)
References:
  http://wiki.tockdom.com/wiki/MKWii_Network_Protocol
*/



namespace RKNet {

enum FriendStatus {
    FRIEND_STATUS_IDLE = 2, //online, but not doing anything
    FRIEND_STATUS_FROOM_OPEN = 3,
    FRIEND_STATUS_FROOM_NON_HOST = 4,
    FRIEND_STATUS_PUBLIC_VS = 5,
    FRIEND_STATUS_PUBLIC_BATTLE = 8,
    FRIEND_STATUS_FROOM_VS_HOST = 11,
    FRIEND_STATUS_FROOM_BATTLE_HOST = 12,
    FRIEND_STATUS_FROOM_VS_NON_HOST = 13,
    FRIEND_STATUS_FROOM_BATTLE_NON_HOST = 14,
};

enum SearchType {
    SEARCH_TYPE_OPEN_ROOM = 3,
    SEARCH_TYPE_PLAYING_WITH_FRIENDS = 4,
    SEARCH_TYPE_VS_WW = 5,
    SEARCH_TYPE_VS_REGIONAL = 6,
    SEARCH_TYPE_BT_WW = 8,
    SEARCH_TYPE_BT_REGIONAL = 9,
};

struct StatusData { //http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/Server/gpcm.gs.nintendowifi.net#locstring
    u32 hostDWCgroupid;
    u8 regionId; //0x4 last byte of it
    u8 status; //see enum
    u8 playerCount;
    u8 curRace;
};
struct Friend {
    StatusData statusData; //8 bytes, see 
    u8 unknown_0x8;
    bool hasAddedBack; //0x9
    u8 unknown_0xa[2];
}; //total size 0xC

class SplitRACEPointers {
public:
    SplitRACEPointers(); //8065a3dc inlined
    ~SplitRACEPointers(); //8065a474

    template<class T>
    PacketHolder<T>* GetPacketHolder() { return (PacketHolder<T>*)(this->packetHolders[T::idx]); };
    template<class T>
    const PacketHolder<T>* GetPacketHolder() const { return (PacketHolder<T>*)(this->packetHolders[T::idx]); };
    PacketHolder<void>* packetHolders[8];

}; //0x20
size_assert(SplitRACEPointers, 0x20);

struct ConnectionUserData { //has to be a struct and needs padding because it's converted to a void* and used as DWC::MatchControl's attemptCallbackParam
    u8 playersAtConsole;
    u8 padding[3];
}; //Total size 0x4

enum ConnectionState {
    CONNECTIONSTATE_SHUTDOWN,
    CONNECTIONSTATE_LOGIN_START,
    CONNECTIONSTATE_LOGIN_AUTHORISED,
    CONNECTIONSTATE_LOGIN_FRIENDS_SYNCED,
    CONNECTIONSTATE_MATCHING,
    CONNECTIONSTATE_IDLE,
    CONNECTIONSTATE_ROOM
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



enum RACESection {
    PACKET_RACEHEADER,
    PACKET_RACEHEADER1,
    PACKET_RACEHEADER2,
    PACKET_SELECTROOM,
    PACKET_RACEDATA,
    PACKET_USER,
    PACKET_ITEM,
    PACKET_EVENT
};

class Controller;

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
    ConnectionUserData connectionUserDatas[12]; //0x23 index is aid
    bool matchingSuspended; //0x53
    u8 unknown_0x54[4];
}; //Total size 0x58
size_assert(ControllerSub, 0x58);


/*KeyIDs:
100 = mode key, called rk
101 = VR evaluation key, called ev
102 = BR evaluation key, called eb
103 = p evaluation key, called k
this class is used to generate a DWC matchKey,
by first making an evaluation string ev >= (rating - 2936[group]) and ev <= (rating + 2934[group])
and a string rk = 'mode' and evaluationString and p = int
*/
static char mode[0x7e]; //809c1fd8 'vs' for example, used as keyValue
static char evaluationString[0x7e]; //809c2058
static char matchmakingFilter[0x7e]; //809c1f58 the full string
void GPReverseBuddiesListCallback(GP::Connection* connection, GP::GetReverseBuddiesListResponseArg* arg, Controller* self); //8065a8d4
void SetGPError(GP::Result badResult); //8065a974
struct RatingRangeMaker {
    static u16* groups; //8089a1d0
    //groups for VS: 1-3000, 3000-4250, 4250-5750, 5750-7000, 7000-9999 so a rating a 5000 would return 2
    void Init(); //8065a4f8 inlined in Controller::Init
    u16 GetLowerRange(u16 rating, bool isBattle) const; //8065a5e0 returns rating - ranges[1][rating's group][isBattle]
    u16 GetUpperRange(u16 rating, bool isBattle) const; //8065a64c returns rating + ranges[0][rating's group][isBattle]
    int GetRatingGroup(u16 rating, bool isBattle) const; //8065a768

    u16 groupRanges[2][5][2]; //for VS and Battle
    //upper and lower values (2) of the range of rating for evaluation for each group (5) and for vs and battle (2)
    //for example, for group 2, the range will be rating - 750 <= ev <= rating + 750
}; //0x28

struct ErrorParams {
    u32 errorParam1; //0x2c 1 if DWC::ErrorType €[3,6], 3 if €[0,2], 5 if 7
    u32 dwcErrorCode; //0x30 1st arg of GetErrorEx
};

class Controller {
public:
    static Controller* sInstance; //809c20d8
    static Controller* CreateInstance(); //80655b24
    static void DestroyInstance(); //80655bac
    explicit Controller(EGG::ExpHeap* heap); //80657004
    virtual ~Controller(); //8065741c vtable 808c097c

    static void MainNetworkLoop(Controller* controller); //80657500
    static void* SOAlloc(u32 size); //80658418
    static void SOFree(void* memBlock); //80658498
    static void* DWCAlloc(u32 size, s32 alignment); //80658500
    static void DWCFree(void* memBlock); //8065858c
    static void LoginCallback(DWC::Error error, int profileId, Controller* self); //80658614 DWC::LoginCallback
    static void MatchedSCCallback(DWC::Error error, BOOL cancel, BOOL isSelf, BOOL isServer, int index, Controller* self); //80658718 DWC::MatchedSCCallback
    static bool ConnectionAttemptCallback(ConnectionUserData* newClientUserData, Controller* self); //80658768  true if the player is <=12, this validates the ResvPacket
    static void ConnectionClosedCallback(DWC::Error error, BOOL isLocal, BOOL isServer, u32 aid, int index, Controller* controller); //80658824 DWC::ConnectionClosedCallback
    static void UpdateServersCallback(DWC::Error error, BOOL isChanged, Controller* self); //806588d8 DWC::UpdateServersCallback
    static void UpdateServersCallbackAlt(DWC::Error error, BOOL isChanged, Controller* self); //806588fc
    static void FriendStatusCallback(int index, u8 status, const char* statusString, Controller* self); //80658918 DWC::FriendStatusCallback just a blr
    static void BuddyFriendCallback(int index, Controller* self);          //8065891c DWC::BuddyFriendCallback
    static void UserRecvCallback(u32 aid, RACEPacketHeader* packet, u32 size); //806585f4 DWC::UserRecvCallback in DWC::TransportInfo

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
    //check if any of my friends' pids match the pids that have added me back, obtained through a GP::ReverseBuddiesList search, and when that is, set the bool in the Friend structure
    void SetFriendsAddedBack(u32* pidsThatHaveAddedBack, u32 countOfPids); //80656ca0
    void SetFriendDeleted(u32 friendIdx); //80656d6c
    bool CanExchangeFriendData(); //80656d9c returns true if all these are false: checks if last error is friend related (4xxxx) or SAKE related (98xxx) or connection state is NOT idle/room
    bool IsIdle(); //80656e44 checks if MainLoop is running, which returns false (via EGG::TaskThread::IsTaskExist)
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
    void HandleError(); //806581cc gets errorcode, divides by 10000 (to get sequence), divides by 1000 to get seq + SDK src
    void* Alloc(u32 size, s32 alignment); //8065832c
    void Free(void* memBlock); //806583b4
    void SetDWCRecvBuffers(); //80658928
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
    SearchType GetFriendSearchType(u32 friendIdx) const; //80659fa4 not quite DWC::FriendStatus
    s32 GetLocalPlayerId(s32 hudSlotId) const; //80659d58
    void UpdateStatusDatas(); //8065a0b4

    ErrorParams GetErrorParams() const; //806569b4 
    void ResetErrorParams(); //80656a30
    u32 GetSubTickDiff() const; //80656a8c returns ((u32)sub.unk0-(u32)OS::GetTime)/(busClock / 4)
    template<class T>
    PacketHolder<T>* GetSendPacketHolder(u8 aid) const {

        return this->splitToSendRACEPackets[this->lastSendBufferUsed[aid]][aid]->GetPacketHolder<T>();
    }
    template<class T>
    PacketHolder<T>* GetReceivedPacketHolder(u8 aid) const {

        u32 idx = T::idx;
        return this->splitReceivedRACEPackets[this->lastReceivedBufferUsed[aid][idx]][aid]->GetPacketHolder<T>();
    }
    u32 unkVtable;//unknown class vtable 808c0988
    OS::Mutex mutex; //0x8

    EGG::Heap* Heap; //0x20
    EGG::TaskThread* taskThread; //0x24
    ConnectionState connectionState; //0x28 

    ErrorParams errorParams; //0x2c

    u32 unknown_0x34;

    ControllerSub subs[2]; //0x38
    RoomType roomType; //0xe8
    u8 unknown_0xec[4];

    SplitRACEPointers* splitToSendRACEPackets[2][12]; //0xf0 split pointers for the outgoing packets, double buffered, indexed by aid
    SplitRACEPointers* splitReceivedRACEPackets[2][12]; //0x150 split pointers for the incoming packets, double buffered, indexed by aid
    PacketHolder<void>* fullSendPackets[12]; //0x1b0 combined outgoing packets, indexed by aid
    u64 lastRACEToSendTimes[12]; //0x1e0 time when last sent to that aid
    u64 lastRACERecivedTimes[12]; //0x240 time when last received from that aid
    u64 RACEToSendTimesTaken[12]; //0x2a0 last send time minus the time of the send before it
    u64 RACEReceivedTimesTaken[12]; //0x300 last receive time minus the time of the receive before it
    u8 lastRACESendAid; //0x360 aid a packet was last sent to
private: //because it's modified in pulsar
    u8 fullReceivedPackets[12][0x2e0]; //0x361 1 per aid
    u8 padding[3]; //0x25e1
public:
    StatusData localStatusData; //0x25e4 8 bytes, see http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/Server/gpcm.gs.nintendowifi.net#locstring
    Friend friends[30]; //0x25ec
    bool friendsListIsChanged; //0x2754 true if unprocessed changes have happeend
    bool shutdownScheduled; //0x2755 will cause shutdown of wifi connection on next run of the main loop if true
    bool friendStatusUpdateScheduled; //0x2756 if true, the main loop will update all friend statuses on the next iteration
    bool nwc24Related; //0x2757
    bool hasprofanity; //0x2758 1 if name is bad
    u8 padding2[3];
    s32 badWordsNum; //0x275c number of bad strings in the profanity check
    u32 pParamForSearchString; //0x2760
    s32 vr; //0x2764
    s32 br; //0x2768
    u32 lastSendBufferUsed[12]; //0x276c last full send buffer used for each aid, 0 or 1
    u32 lastReceivedBufferUsed[12][8]; //0x279c last Received buffer used for each packet per aid, 1 or 0
    s32 currentSub; //0x291c index of the current sub to use, 0 or 1
    u8 aidsBelongingToPlayerIds[12]; //0x2920 index is player id, value is aid
    u32 disconnectedAids; //0x292c 1 if disconnected, index 1 << aid
    u32 disconnectedPlayerIds; //0x2930 index 1 << playerId
    RatingRangeMaker rangeMaker; //0x2934
    u8 paddingu64[4]; //0x295c
    u64 selectTime350DivTime3B0[12]; //0x2960
    u32 biggestRH1Timer; //0x29c0
    u8 unknown_0x29c4[4];

    static u32* splitRACEPointersBufferSizes; //8089a194 same order as split packets header, raceHeader1, raceHeader2, select, 2 * racedata, user, 2 * item, event,
};
size_assert(Controller, 0x29c8);

}//namespace RKNet
#endif
