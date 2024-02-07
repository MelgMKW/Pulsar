#ifndef _KRM_
#define _KRM_
#include <kamek.hpp>

struct KRM { // https://wiki.tockdom.com/wiki/KRM_(File_Format)
    char magic[4]; //rkrm
    u8 unknown_0x0;
};

#endif