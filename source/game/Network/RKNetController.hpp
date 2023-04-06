#ifndef _RKNETCONTROLLER_
#define _RKNETCONTROLLER_

#include <kamek.hpp>
#include <core/egg/mem/ExpHeap.hpp>
#include <core/egg/Thread.hpp>

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
struct RKNetFriend {
    StatusData statusData; //8 bytes, see 
    u8 unknown_0x8[4];
}; //total size 0xC

class PacketHolder {
public:
    explicit PacketHolder(u32 bufferSize); //8065a24c
    ~PacketHolder(); //8065a2ac

    void Init(); //8065a24c
    void Clear(); //8065a30c
    void Copy(void *src, u32 len); //8065a34c
    void Append(void *src, u32 len); //8065a38c

    void *packet; //data buffer pointer
    u32 bufferSize; //maximum data size
    u32 packetSize; //current data size
}; //Total size 0xc

class SplitRACEPointers {
    SplitRACEPointers(); //8065a3dc
    ~SplitRACEPointers(); //8065a474

    PacketHolder *header;
    PacketHolder *raceHeader1;
    PacketHolder *raceHeader2;
    PacketHolder *select;
    PacketHolder *racedata;
    PacketHolder *user;
    PacketHolder *item;
    PacketHolder *event;
}; //Total size 0x20

struct ConnectionUserData {
    u8 playersAtConsole;
    u8 unknown_0x1[3];
}; //Total size 0x4

struct RKNetControllerSub {
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

enum RKNetConnectionState {
    STATE_SHUTDOWN,
    STATE_LOGIN_START,
    STATE_LOGIN_AUTHORISED,
    STATE_LOGIN_FRIENDS_SYNCED,
    STATE_MATCHING,
    STATE_FAILED,
    STATE_ERROR
};

enum RKNetSearchType {
    SEARCH_VS_WW,
    SEARCH_VS_REGIONAL,
    SEARCH_BT_WW,
    SEARCH_BT_REGIONAL
};

class RKNetController {
public:
    static RKNetController *sInstance; //809c20d8
    static RKNetController *GetStaticInstance(); //80655b24
    static void DestroyStaticInstance(); //80655bac
    explicit RKNetController(EGG::ExpHeap *heap); //80657004
    virtual ~RKNetController(); //8065741c vtable 808c097c
    void ClearSplitSendPacketHolders(); //80656f40
    void CombineSplitSendPackets(); //80657ab0
    void ConnectToAnybodyAsync(); //80659170
    void ConnectToGameServerFromGroupId(); //80659680
    void ConnectToWFC(); //80658b9c
    s32 GetFriendSearchType(s32 friendNumber); //80659fa4
    s32 GetLocalPlayerId(s32 localPlayerNum); //80659d58
    u32 GetSplitSendPacketsTotalSize(u32 aid); //806580c4
    void HandleError(); //806581cc
    void ResetSubs(); //80658d3c
    bool IsConnectedToAnyone(); //80656f00
    void MainLoop(s32 r4, s32 r5, s32 r6); //80657504
    void ProcessPlayerDisconnect(u32 aid); //80658990
    void ProcessRACEPacket(u32 aid, void *packet, u32 size); //80659a84
    void ResetAidsBelongingToPlayerIds(); //80659d20
    void ScheduleShutdown(); //806561a8
    bool SendAidNextRACEPacket(u32 aid); //80657fe4
    void SendPacketsAndUpdateUSER(); //80657a70
    void SetupGameServer(); //806595b8
    void StartMatching(); //80659044
    void StartMainLoop(); //80655c10
    void TrySendNextRACEPacket(); //80657e30
    void UpdateAidsBelongingToPlayerIds(); //80659bc0
    void UpdateStatusDatas(); //8065a0b4
    void UpdateSubsAndVr(); //80658de0

    u8 unknown_0x4[0x20 - 0x4];//unknown class vtable 808c0988
    EGG::ExpHeap *expHeap;
    EGG::TaskThread *taskThread;
    RKNetConnectionState connectionState;
    u8 unknown_0x2c[0x38 - 0x2c];
    RKNetControllerSub subs[2]; //0x38
    RKNetSearchType searchType;
    u8 unknown_0xec[4];
    SplitRACEPointers *splitToSendRACEPackets[2][12]; //0xf0 split pointers for the outgoing packets, double buffered, indexed by aid
    SplitRACEPointers *splitReceivedRACEPackets[2][12]; //0x150 split pointers for the incoming packets, double buffered, indexed by aid
    PacketHolder *fullSendPackets[12]; //0x1b0 combined outgoing packets, indexed by aid
    u64 lastRACEToSendTimes[12]; //0x1e0 time when last sent to that aid
    u64 lastRACERecivedTimes[12]; //0x240 time when last received from that aid
    u64 RACEToSendTimesTaken[12]; //0x2a0 last send time minus the time of the send before it
    u64 RACERecivedTiemsTaken[12]; //0x300 last receive time minus the time of the receive before it
    u8 lastRACESendAid; //0x360 aid a packet was last sent to
    u8 fullRecivedPackets[12][0x2e0]; //0x361 1 per aid
    u8 padding[3]; //0x25e1
    StatusData localStatusData; //0x25e4 8 bytes, see http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/Server/gpcm.gs.nintendowifi.net#locstring
    RKNetFriend friends[30]; //0x25ec 
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
    s32 lastRecivedBufferUsed[12][8]; //0x279c last Recived buffer used for each packet per aid, 1 or 0
    s32 currentSub; //0x291c index of the current sub to use, 0 or 1
    u8 aidsBelongingToPlayerIds[12]; //0x2920 index is player id, value is aid
    u32 disconnectedAids; //0x292c 1 if disconnected, index 1 << aid
    u32 disconnectedPlayerIds; //0x2930 index 1 << playerId
    u8 unknown_0x2934[0x29c8 - 0x2934];
};
size_assert(RKNetController, 0x29c8);

namespace RKNet {
void userRecivedCallback(u32 aid, void *packet, u32 size); //806585f4
void *DWCAlloc(s32 r3, u32 size, s32 alignment); //80658500
void DWCFree(s32 r3, void *buffer); //8065858c
void *SOAlloc(s32 r3, u32 size); //80658418
void SOFree(s32 r3, void *buffer); //80658498
}//namespace RKNet
#endif
