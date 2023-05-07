#ifndef _DWC_MATCHCOMMAND_ //to split into multiple files ultimately
#define _DWC_MATCHCOMMAND_
#include <types.hpp>
#include <core/rvl/DWC/DWC.hpp>

//Credit Seeky

namespace DWC { //this is probably C, but don't care

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
    MATCH_COMMAND_SLOT_LIST = 0x83
};

enum MatchType {
    MATCH_TYPE_ANYBODY,
    MATCH_TYPE_FRIEND,
    MATCH_TYPE_SC_SV,
    MATCH_TYPE_SV_CL
};

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

void SendMatchCommand(MatchCommand type, u32 pid, u32 ip, u16 port, void* data, u32 dataSize); //800dbd38
void SendResvCommand(u32 pid, u32 r4); //800deddc
void ProcessRecvMatchCommand(MatchCommand type, u32 pid, u32 qr2IP, u32 qr2Port, void* data, u32 dataSize); //800dc234
MatchCommand CheckResvCommand(u32 pid, u32 publicIP, u16 port, MatchType matchType, u32 isFriend, ConnectionUserData* userData); //800de6b8


}//namespace DWC


#endif