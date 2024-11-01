#ifndef _RKNETRH2_
#define _RKNETRH2_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>


namespace RKNet {
struct RACEHEADER2Packet {
    static const u32 idx = 2;
    u8 _[0x28];
}; //0x28


}//namespace RKNet
#endif