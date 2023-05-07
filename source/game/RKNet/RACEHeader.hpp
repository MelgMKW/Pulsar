#ifndef _RKNETRACEHEADER_
#define _RKNETRACEHEADER_
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>


namespace RKNet {
struct RACEPacketHeader {
    u32 magic;
    u32 crc32;
    u8 headerSize;
    u8 rh1Size;
    u8 rh2Size;
    u8 selectSize;
    u8 racedataSize;
    u8 userSize;
    u8 itemSize;
    u8 eventSize;
};
size_assert(RACEPacketHeader, 0x10);


}//namespace RKNet
#endif