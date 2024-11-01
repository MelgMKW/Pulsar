#ifndef _KRM_
#define _KRM_
#include <kamek.hpp>

struct KRMEntry {
    u16 type1Params[2];
    u8 unknown_0x4;
    u8 type0Count;
    u8 type;
    char type0Params[2]; //0x7 sizeCount, with a terminator
}; //0x8 minimum

struct KRM { // https://wiki.tockdom.com/wiki/KRM_(File_Format) one entry for each length?
    char magic[4]; //rkrm
    u8 unknown_0x0[4];
    u16 entryCount;
    u16 headerSize;
    u32 offsetToEntry[1];
    //KRMEntry entries[1]
};

#endif