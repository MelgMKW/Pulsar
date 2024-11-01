#ifndef _DWC_MATCH_ //to split into multiple files ultimately
#define _DWC_MATCH_
#include <types.hpp>
#include <core/GS/GT2/GT2.hpp>
#include <core/GS/GP/GP.hpp>
#include <core/rvl/DWC/DWCAccount.hpp>
#include <core/rvl/DWC/DWCError.hpp>
#include <core/rvl/os/OS.hpp>

//Credit Seeky

namespace DWC { //this is probably C, but don't care

enum MatchState {
    DWC_MATCH_STATE_INIT = 0,           //Initial state

    //Client Status
    DWC_MATCH_STATE_CL_WAITING,         //Wait status
    DWC_MATCH_STATE_CL_SEARCH_OWN,      //Searching for information on own host
    DWC_MATCH_STATE_CL_SEARCH_HOST,     //Open host search status (only when not specifying friends)
    DWC_MATCH_STATE_CL_WAIT_RESV,       //Waiting for response from server to be reserved
    DWC_MATCH_STATE_CL_SEARCH_NN_HOST,  //Searching for partner host that has been reserved
    DWC_MATCH_STATE_CL_NN,              //NAT negotiation in progress
    DWC_MATCH_STATE_CL_GT2,             //Establishing GT2 connection
    DWC_MATCH_STATE_CL_CANCEL_SYN,      //matchmaking cancellation synchronization adjustment underway for the server-client
    DWC_MATCH_STATE_CL_SYN,             //matchmaking completion synchronization adjustment underway

    //Client Status
    DWC_MATCH_STATE_SV_WAITING,         //Wait status
    DWC_MATCH_STATE_SV_OWN_NN,          //NAT negotiation with client in progress
    DWC_MATCH_STATE_SV_OWN_GT2,         //Establishing GT2 connection with client
    DWC_MATCH_STATE_SV_WAIT_CL_LINK,    //Waiting for connection between clients to complete
    DWC_MATCH_STATE_SV_CANCEL_SYN,      //Waiting for SYN-ACK for server-client matchmaking cancellation synchronization adjustment
    DWC_MATCH_STATE_SV_CANCEL_SYN_WAIT, //waiting on end to matchmaking cancellation synchronization adjustment for the server-client
    DWC_MATCH_STATE_SV_SYN,             //Waiting for matchmaking completion synchronization adjustment SYN-ACK
    DWC_MATCH_STATE_SV_SYN_WAIT,        //Waiting for matchmaking completion synchronization adjustment to complete

    //Common Status
    DWC_MATCH_STATE_WAIT_CLOSE,         //Waiting for connection close to complete

    //Status only while using matchmaking option
    DWC_MATCH_STATE_SV_POLL_TIMEOUT,    //Server is currently polling for OPTION_MIN_COMPLETE timeouts

    DWC_MATCH_STATE_NUM
};

enum MatchCommand {
    MATCH_COMMAND_RESERVATION = 1,
    MATCH_COMMAND_RESV_OK = 2,
    MATCH_COMMAND_RESV_DENY = 3,
    MATCH_COMMAND_RESV_WAIT = 4,
    MATCH_COMMAND_RESV_CANCEL = 5,
    MATCH_COMMAND_TELL_ADDR = 6,
    MATCH_COMMAND_NEW_PID_AID = 7,
    MATCH_COMMAND_CANCEL = 0xc,
    MATCH_COMMAND_CANCEL_SYN = 0xd,
    MATCH_COMMAND_CANCEL_SYN_ACK = 0xe,
    MATCH_COMMAND_CANCEL_ACK = 0xf,
    MATCH_COMMAND_SL_CLOSE_CL = 0x10,
    MATCH_COMMAND_SVDOWNQUERY = 0x52,
    MATCH_COMMAND_SVDOWN_ACK = 0x53,
    MATCH_COMMAND_SVDOWN_NAK = 0x54,
    MATCH_COMMAND_SVDOWN_KEEP = 0x55,
    MATCH_COMMAND_SB_RETRY_SEARCH = 0x70,
    MATCH_COMMAND_SUSPEND_MATCH = 0x82,
    MATCH_COMMAND_SLOT_LIST = 0x83,
    MATCH_COMMAND_DUMMY = 0xff,
};

enum MatchType {
    MATCH_TYPE_ANYBODY,
    MATCH_TYPE_FRIEND,
    MATCH_TYPE_SC_SV,
    MATCH_TYPE_SV_CL
};

//friend specified/unspecified peer matchmaking completion cb
typedef void (*MatchedCallback)(Error error, BOOL cancel, void* param);

//server-client matchmaking complete cb
typedef void (*MatchedSCCallback)(Error error, BOOL cancel, BOOL self, BOOL isServer, int index, void* param);

//New connection client 
typedef void (*NewClientCallback)(int index, void* param);

//player evaluation, negative ret = no matchmaking, positive = the higher the more likely to be selected
typedef int (*EvalPlayerCallback)(int index, void* param);

//server-client matchmaking cancellation complete cb
typedef void (*StopSCCallback)(void* param);

//connection attempt (non-official)
typedef bool (*ConnectionAttemptCallback)(void* userData, void* param); //false = deny connection

struct NNInfo {
    u8  isQR2; //1: Retry unnecessary because QR2, 0: Retry required because SB
    u8  retryCount; //Counter to measure retry attempts
    u16 port; //NAT Negotiation destination port number
    u32 ip; //0x4 NAT Negotiation destination IP
    int cookie; //0x8 NAT Negotiation cookie value. 0 indicates no NN in progress
}; //0xc

struct MatchCommandControl {
    u8  command; //Send command
    u8  count; //Number of retries
    u16 port; //Send destination QR2 public port number
    u32 ip; //0x4 Send destination QR2 IP
    u32 data[32]; //0x8 Added send data
    int profileID; //0x88 Send destination profile ID
    int len; //0x8c Added send data request count
    OS::Time sendTime; //0x90 Send time
}; //0x98

struct NodeInfo {
    u8 unknown[0x1a];
    u8 aid; //0x1a
    u8 unknown_0x1b[0x30 - 0x1b];
}; //0x30

struct MatchControl {
    static MatchControl* sInstance; //8038630C

    GP::Connection** gpConnection;
    GT2::Socket* gt2Socket; //0x4
    GT2::ConnectionCallbacks* gt2Callbacks; //0x8

    u8 gt2ConnectCount; //0xc GT2 retry counter
    u8 gt2NumConnection; //Number of established GT2 connections
    u8 gt2NumValidConn; //Number of valid GT2 connections that have completed connection to all members
    u8 padding;

    void* qr2; //0x10 Pointer to QR2 object
    u8 unknown_0x14[2];
    vu8  qr2MatchType; //0x16 Matchmaking type DWC_MATCH_TYPE_* enumerator
    vu8  qr2NumEntry; //0x17 The maximum number to be gathered, excluding self
    vu8  qr2IsReserved; //0x18 1: Completed NN Reservation to self, 0: No reservation
    u8 unknown_0x19[0x30 - 0x19];
    vu8  qr2NNFinishCount; //0x30 NAT negotiation completion counter
    u8 padding2[3];

    NodeInfo nodes[32]; //0x34
    u8 unknown_0x634[4]; //0x634
    u32 serverPid; //0x638
    u8 unknown_0x63c[0x6d0 - 0x63c];
    u16  qr2Port; //0x6d0
    u8 padding3[2];
    u32  qr2IP; //0x6d4
    u8 unknown_0x6d8[4];
    void* serverBrowser; //0x6dc
    u8 unknown_0x6e0[0x6f8 - 0x6e0];
    u8  nnRecvCount; //0x6f8 Count for receiving the same NAT negotiation
    u8  nnFailureCount; //0x6f9 NN failure count
    u16 nnCookieRand; //0x6fa Random number for cookies used in NAT negotiation
    int nnLastCookie; //0x6fc Cookie for NN  received the time before
    OS::Time nnFailedTime; //0x700 Time when NAT negotiation failed
    OS::Time nnFinishTime; //0x708 Time when NAT negotiation terminated
    NNInfo nnInfo; //0x710 NAT negotiation data structure
    MatchState state; //0x71c Matchmaking progress status

    u8 unknown_0x720[0x778 - 0x720];
    volatile int profileID; //0x778 This players Profile ID
    int reqProfileID; //0x77c Profile ID of partner that send NN request for friend specified peer matching
    u8 unknown_0x780[4];
    const char* gameName; //0x784 GameSpy
    const char* secretKey; //0x788 GameSpy
    const AccFriendData* friendList; //0x78c Pointer to Friend roster
    int friendListLen; //0x790  Friend roster length
    u8  friendIdxList[64]; //0x794 Matchmaking friend index list
    int friendIdxListLen; //0x7d4 Matchmaking friend index list length
    MatchCommandControl commandControl; //0x7d8 Matchmaking command control structure
    MatchedSCCallback matchedCallback; //0x870
    void* matchedParam;
    NewClientCallback newClientCallback; //0x878
    void* newClientParam;
    EvalPlayerCallback evalCallback; //0x880
    void* evalParam;
    StopSCCallback stopSCCallback; //0x888 server-client matchmaking cancellation complete callback
    void* stopSCParam; //0x88c RKNet::Controller in mkwii

    u8 unknown_0x890[0x8a4 - 0x890];
    ConnectionAttemptCallback attemptCallback; //0x8a4
    u32 userData; //0x8a8 RKNet::ConnectionUserData in mkwii
    void* attemptCallbackParam; //0x8ac RKNet::Controller in mkwii

    u8 unknown_0x8b0[0x10];
}; //0x8c0



struct MatchCommandHeader {
    u32 identifier; //magic
    u32 version; //0x4
    u8 type; //0x8 see enum
    u8 sizeAppended; //0x9
    u16 qr2port; //0xa
    u32 qr2IP; //0xc
    u32 pid; //0x10
    //followed by data
};

struct Reservation { //little endian
    MatchType type;
    u32 publicIP; //0x4
    u32 publicPort; //0x8
    u32 localIP; //0xc
    u32 localPort; //0x10
    u32 unknown_0x14; //0x
    u32 isFriend;
    u32 localPlayerCount;
    u32 resvCheckValue;
}; //0x24

struct ResvOk {
    u32 maxPlayers;
    u32 clientSlotIndexSender;
    u32 pid;
    u32 publicIP;
    u32 publicPort;
    u32 localIP;
    u32 localPort;
    u32 unknown_0x1c;
    u32 localPlayerCount;
    u32 groupId;
    u32 clientSlotIndexReceiver;
    u32 consoleCountInRoom;
    u32 resvCheckValue;
}; //0x34

struct ResvDeny {
    u32 errorId;
    /* 0x10 = room is full (but not on suspend) (never seen in-game, but is implemented in the game code)
       0x11 = Room has already started playing since you tried joining
       0x12 = Room is on suspend.
    */
};


void iMatchInit(MatchControl* control, GP::Connection* gpConnection, GT2::Socket* gt2Socket, GT2::ConnectionCallbacks* gt2Callbacks,
    const char* gameName, const char* secretKey, const AccFriendData friendList[], int  friendListLen); //800d4bbc

void SendMatchCommand(MatchCommand type, u32 pid, u32 ip, u16 port, void* data, u32 dataSize); //800dbd38
void SendResvCommand(u32 pid, u32 r4); //800deddc
void ProcessRecvMatchCommand(MatchCommand type, u32 pid, u32 qr2IP, u32 qr2Port, void* data, u32 dataSize); //800dc234
MatchCommand CheckResvCommand(u32 pid, u32 publicIP, u16 port, MatchType matchType, BOOL isPriorityNN, void* userdata); //800de6b8 userdata = RKNet::ConnectionUserData in mkwii
u8  AddMatchKeyString(u8 keyID, const char* keyString, const char* valueSrc); //800d45f4
u8  AddMatchKeyInt(u8 keyID, const char* keyString, const int* valueSrc); //800d4258
BOOL ConnectToAnybodyAsync(u8  numEntry, const char* addFilter, MatchedCallback matchedCallback, void* matchedParam,
    EvalPlayerCallback evalCallback, void* evalParam); //800d1840
}//namespace DWC


#endif