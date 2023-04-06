#ifndef _RKNETPACKETCREATOR_
#define _RKNETPACKETCREATOR_
#include <kamek.hpp>
#include <core/rvl/os/mutex.hpp>
#include <core/rvl/DWC/DWC.hpp>

struct EVENTPacket {
    u8 unknown[0xf8];
};
class RKNetPacketCreator {
public:
    static RKNetPacketCreator *sInstance; //809c1f50
    static RKNetPacketCreator *GetStaticInstance(); //80653208
    static void DestroyStaticInstance(); //80653284
    u8 unknown_0x0;
    bool isSomoneLagging;
    u8 unknown_0x2[2];
    u32 aidsWithSelectId;
    u32 aidsWithNewRoomOrSelect;
    u32 unknown_0xC;
    u16 localLagFrames;
    u16 countdownTime;
    u8 unknown_0x14[0x94 - 0x14];
    EVENTPacket sendEVENTPacket;
    u8 unknown_0x18c[4];
    u64 lastFriendUpdateTime;
    u32 playerRH1Timers[12];
}; //total size 0x1c8
size_assert(RKNetPacketCreator, 0x1c8);
#endif