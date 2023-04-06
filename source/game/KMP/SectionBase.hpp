#ifndef _KMP_SECTION_BASE_
#define _KMP_SECTION_BASE_
#include <kamek.hpp>

struct PointGroup {
    u8 start;
    u8 length;
    u8 prevLinks[6];
    u8 nextLinks[6];
    u16 unknown_0xE;
}; //total size 0x10

struct SectionHeader {
    char magic[4]; //eg KTPT
    u16 entryCount;
    s16 flag; //total point count, etc...
}; //0x8

template<class T>
struct KMPSection {
    SectionHeader header;
    T entries;
};

#endif
