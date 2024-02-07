#ifndef _KRT_
#define _KRT_
#include <kamek.hpp>

struct KRTHeader { //https://wiki.tockdom.com/wiki/KRT_(File_Format)
    char magic[4]; //RKGT
    u32 maxHiddenScore; //0x4
    u16 entryCount;
    u16 headerSize;
};//total size 0x20

struct KRTEntry {
    u16 timeLimit50cc;
    u16 timeLimit100cc;
    u16 timeLimit150cc;
    u8 padding[2];
};

struct KRT {
    KRTHeader header;
    KRTEntry entries[1]; //size entry count, orderer by special slot ID
};

#endif