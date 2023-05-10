#include <kamek.hpp>


namespace Pulsar {
namespace Network {


#pragma pack(push, 1)
struct CustomRH1Packet {
    u32 timer;
    u32 selectId; //0x4
    u16 team[2]; //0x8
    u16 lagFrames; //0xc
    u16 kartAndCharacter[2]; //0xe treated as a u16 ingame
    u16 countdownTime; //0x12
    u8 starRankHud0 : 4; //0x14
    u8 starRankHud1 : 4; //0x14.5
    u16 trackId; //0x15, before was at 0x16
    u8 unknown_0x17;
    u8 aidsBelongingToPlayer[12]; //0x18
    u8 engineClass; //0x24
    u8 unknown_0x25[3];
}; //0x28
size_assert(CustomRH1Packet, 0x28);
#pragma pack(pop)


}//namespace Network
}//namespace Pulsar
