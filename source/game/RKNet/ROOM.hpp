#ifndef _RKNETROOM_
#define _RKNETROOM_
#include <kamek.hpp>


namespace RKNet {
enum ROOMRole {
    ROOM_HOST,
    ROOM_GUEST
};

enum ROOMMessageType {
    ROOM_START = 0x1,
    ROOM_REGISTER_FRIEND = 0x2,
    ROOM_JOIN_MESSAGE = 0x3,
    ROOM_CHAT_MESSAGE = 0x4
};

#pragma pack(push, 1)
struct ROOMPacket {
    u8 messageType; //see enum
    u16 message;
    u8 unknown_0x3;
}; //0x4
#pragma pack(pop)
size_assert(ROOMPacket, 0x4);

union ROOMPacketReg {
    u32 packetArg;
    ROOMPacket packet;
};


class ROOMHandler {
public:
    static ROOMHandler* sInstance; //809c20e0
    static ROOMHandler* GetStaticInstance(); //8065aa88
    static void DestroyStaticInstance(); //8065ab4c
    ROOMHandler(); //8065af84 just a wrapper around Reset
    ~ROOMHandler(); //8065b008

    void Init(ROOMRole role); //8065ab8c
    void Reset(); //8065ac94
    void Update(); //8065ad18
    void SetAllToSendPackets(ROOMPacket packet); //8065ae70  
    ROOMPacket GetReceivedPacket(u8 aid) const; //8065af64
    void SetToSendPacket(u8 aid, ROOMPacket packet); //8065af74
    void ExportROOMandUSER(); //8065b048
    void ImportNewPackets(); //8065b194
    void ClearToSendPacket(); //8065b2ec



    u8 unknown_0x0[4];
    ROOMRole role;
    ROOMPacket toSendPackets[12];
    ROOMPacket receivedPackets[12];
    u8 lastSentToAid;
    u8 unknown_0x69[0x70 - 0x69];
    u64 lastSentTime;
    u32 unknown_0x78[2];
}; //total size 0x80
size_assert(ROOMHandler, 0x80);
}//namespace RKNet
#endif