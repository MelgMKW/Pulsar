#ifndef _RVLNAND_
#define _RVLNAND_
#include <types.hpp>
#define NAND_MAX_PATH 64

struct NANDFileInfo {
    s32 fd;
    s32 origFd;
    char origPath[NAND_MAX_PATH];
    char tmpPath[NAND_MAX_PATH];
    u8 accType;
    u8 stage;
    u8 mark;
    u8 padding;
};
size_assert(NANDFileInfo, 0x8c);
#endif