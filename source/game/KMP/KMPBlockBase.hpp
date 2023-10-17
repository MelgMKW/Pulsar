#ifndef _KMP_SECTION_BASE_
#define _KMP_SECTION_BASE_
#include <kamek.hpp>

struct PointGroup {
    u8 start;
    u8 length;
    u8 prevLinks[6]; //0x2
    u8 nextLinks[6]; //0x8
    u16 unknown_0xE;
}; //total size 0x10

struct BlockHeader {
    u32 magic; //eg KTPT
    u16 entryCount;
    union {
        s16 flag; //total point count, etc...
        u8 flags[2];
    };
}; //0x8

template<class T>
struct KMPBlock {
    BlockHeader header;
    T entries;
};

#endif
