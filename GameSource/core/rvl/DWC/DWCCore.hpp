#ifndef _DWCCORE_ //to split into multiple files ultimately
#define _DWCCORE_

#include <types.hpp>
#include <core/GS/GT2/GT2.hpp>
#include <core/GS/GP/GP.hpp>
#include <core/rvl/DWC/DWCFriend.hpp>
#include <core/rvl/DWC/DWCLogin.hpp>
#include <core/rvl/DWC/DWCMatch.hpp>
#include <core/rvl/DWC/DWCTransport.hpp>

//Credit Seeky

namespace DWC { //this is C, but don't care

enum State {
    DWC_STATE_INIT,             //Initial state
    DWC_STATE_AVAILABLE_CHECK,  //Checking game availability status
    DWC_STATE_LOGIN,            //Processing login
    DWC_STATE_ONLINE,           //Online status after completion of login
    DWC_STATE_UPDATE_SERVERS,   //friend list synchronization in progress
    DWC_STATE_MATCHING,         //matchmaking in progress
    DWC_STATE_CONNECTED,        //Mesh-type network has been configured after matchmaking has been completed
    DWC_STATE_NUM
};

enum ReportFlag {
    DWC_REPORTFLAG_INFO        = 0x00000001,
    DWC_REPORTFLAG_ERROR       = 0x00000002,
    DWC_REPORTFLAG_DEBUG       = 0x00000004,
    DWC_REPORTFLAG_WARNING     = 0x00000008,
    DWC_REPORTFLAG_ACHECK      = 0x00000010,
    DWC_REPORTFLAG_LOGIN       = 0x00000020,
    DWC_REPORTFLAG_MATCH_NN    = 0x00000040,
    DWC_REPORTFLAG_MATCH_GT2   = 0x00000080,
    DWC_REPORTFLAG_TRANSPORT   = 0x00000100,
    DWC_REPORTFLAG_QR2_REQ     = 0x00000200,
    DWC_REPORTFLAG_SB_UPDATE   = 0x00000400,
    DWC_REPORTFLAG_SEND_INFO   = 0x00008000,
    DWC_REPORTFLAG_RECV_INFO   = 0x00010000,
    DWC_REPORTFLAG_UPDATE_SV   = 0x00020000,
    DWC_REPORTFLAG_CONNECTINET = 0x00040000,
    DWC_REPORTFLAG_AUTH        = 0x01000000,
    DWC_REPORTFLAG_AC          = 0x02000000,
    DWC_REPORTFLAG_BM          = 0x04000000,
    DWC_REPORTFLAG_UTIL        = 0x08000000,
    DWC_REPORTFLAG_GAMESPY     = 0x80000000,
    DWC_REPORTFLAG_ALL         = 0xffffffff
};

extern char loginRegion[8]; //80384fd0

//Connection close call-back cb
typedef void (*ConnectionClosedCallback)(Error error, BOOL isLocal, BOOL isServer, u8 aid, int index, void* param);

struct ConnectionInfo { //gt2 connection data, mkwii's "ConnectionUserData" is the param, and then passed to CheckResvCommand and ultimately to RKNet::ConnectionAttemptCb
    u8  index;    //Stored connection list index
    u8  aid;      //Unique ID for host
    u16 reserve;  //Reserved
    void* param;  //user data
};

struct FriendsMatchControl {
    static FriendsMatchControl* sInstance; //803862F0

    GT2::Socket* gt2Socket;   //Pointer to the GT2 socket structure of the host
    GT2::ConnectionCallbacks gt2Callbacks;  //0x4 gt2 connection call-back collection
    int gt2SendBufSize;   //0x14 GT2 socket send buffer size
    int gt2RecvBufSize;   //0x18 GT2 socket receive buffer size

    GP::Connection* gpConnection;    //0x1c Pointer to gp connection structure
    AccUserData* userdata; //0x20 Pointer to DWCUserData structure

    State state; //0x24
    State prevState; //0x28
    u8 localAid; //0x2c
    bool   ownCloseFlag; //0x2d TRUE: Closed by the game itself, FALSE: Closed by other means
    u8 padding[2];
    wchar_t  playerName[26];  //0x30 Player name
    int  profileID;        //0x64 User profile ID
    const char* gameName;  //0x6c Pointer to the game name received from GameSpy
    //const char* secretKey; //0x70

    LoginCallback loginCallback; //0x70
    void* loginParam; //0x74 RKNet::Controller in mkwii
    UpdateServersCallback updateServersCallback; //0x78
    void* updateServersParam; //0x7c RKNet::Controller in mkwii
    MatchedCallback matchedCallback; //0x80
    void* matchedParam; //0x84 
    MatchedSCCallback matchedSCCallback; //0x88
    void* matchedSCParam; //0x8c RKNet::Controller in mkwii
    ConnectionClosedCallback closedCallback; //0x90
    void* closedParam;  //0x94 RKNet::Controller in mkwii

    LoginControl loginControl;       //0x98 login control object
    FriendControl friendControl;   //0x300
    MatchControl matchControl;     //0x360
    TransportInfo transportInfo;   //0xc20 transport control object
}; //0x1438

BOOL SetupGameServer(u8 maxPlayerCount, MatchedSCCallback matchedCb, void* matchedParam, NewClientCallback newClientCb, void* newClientParam,
    ConnectionAttemptCallback attemptCb, void* attemptParam, u32 r10); //800d1984

void iSetupGameServer(u8 maxPlayerCount, MatchedSCCallback matchedCb, void* matchedParam, NewClientCallback newClientCb, void* newClientParam,
    ConnectionAttemptCallback attemptCb, void* attemptParam, u32 r10); //800d54a0

void InitFriendsMatch(FriendsMatchControl* unused, AccUserData* userdata, int productID, const char* gameName, const char* secretKey,
    int sendBufSize, int recvBufSize, AccFriendData friendList[], int friendListLen); //800d0d68

void iLoginCallback(Error error, int profileID, void* param); //800d2f1c

int Printf(u32 level, const char*, ...);

int CloseConnectionHard(u8 aid); //800d2000
}//namespace DWC


#endif