#ifndef _NW4R_DB_CONSOLE_
#define _NW4R_DB_CONSOLE_
#include <types.hpp>

namespace nw4r {
namespace db {
namespace detail {

struct ConsoleHead {
    void *textBuffer;
    u16 width; //4
    u16 height; //0x6
    u16 priority; //0x8
    u16 attr; //0xa
    u16 printTop; //0xc
    u16 printXPos; //0xe
    u16 ringTop; //0x10
    s32 ringTopLineCnt; //0x14
    s32 viewTopLine; //0x18
    s16 viewPosX; //0x1c
    s16 viewPosY; //0x1e
    u16 viewLines; //0x20
    bool isVisible; //0x22 
    u8 padding;
    void *writer; //0x24
    ConsoleHead *next; //0x28
};

}//namespace detail
}//namespace db
}//namespace nw4r
#endif