#ifndef _TABLE_BINARY_
#define _TABLE_BINARY_
#include <kamek.hpp>

struct TableBinaryHeader {
    u16 objectsCount;
};

struct IndexToIDTable {
    u16 indexToObjId; //an array, size 0x2F4 in mkwii
};
#endif