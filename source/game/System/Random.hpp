/*
Random is the game's class used for RNG
Contributors:
    Kevin (main documentation)
    Melg (double functions)
*/

#ifndef _RANDOM_
#define _RANDOM_
#include <kamek.hpp>

class Random {
public:
    Random(); // 80555464
    explicit Random(s32 seed); //80555514
    virtual ~Random(); // 80555538 vtable 808b42e0
    s32 Reset(); //805554d0 returns the tbl
    s32 Next(); // 80555578
    s32 NextLimited(int limit); // 805555cc
    float NextFloat(); //80555628
    float NextFloatLimited(float limit); //805556a8
    u8 unknown_0x4[0x8 - 0x4];
    s32 lastResult; //0x8 stored by next
    s32 lastResult2; //0xC gets init with the tbl
    u8 unknown_0x10[0x14 - 0x10];
    s32 seed; //0x14 gets init with the tbl
}; // Total size 0x18
#endif