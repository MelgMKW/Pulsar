#ifndef _RKNETRACEHEADER_
#define _RKNETRACEHEADER_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>


namespace RKNet {
struct RACEPacketHeader {
    static const u32 idx = 0;
    u32 magic;
    u32 crc32; //0x4
    u8 sizes[8];
    /*
    u8 headerSize; //0x8 counts this as the actual header
    u8 rh1Size; //0x9
    u8 rh2Size; //0xa
    u8 selectSize; //0xb
    u8 racedataSize; //0xc
    u8 userSize; //0xd
    u8 itemSize; //0xe
    u8 eventSize; //0xf
    */
    //void *data; //0x10

};
size_assert(RACEPacketHeader, 0x10);


}//namespace RKNet
#endif