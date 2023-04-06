
#ifndef _NW4R_UTBINARYFILEFORMAT_
#define _NW4R_UTBINARYFILEFORMAT_
#include <types.hpp>
namespace nw4r {
namespace ut {
struct BinaryBlockHeader {
    u32 magic;
    u32 size;
};

struct BinaryFileHeader {
    u32 magic;
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
};

}//namespace ut
}//namespace nw4r
#endif