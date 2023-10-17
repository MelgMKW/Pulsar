#ifndef _KARTDRIVERDISPPARAM_
#define _KARTDRIVERDISPPARAM_
#include <kamek.hpp>

class KartDriverDispParam { //https://wiki.tockdom.com/wiki/KartDriverDispParam.bin
public:
    struct Entry {
        Vec2 driverYZPos;
        float bonesValues[12];
    }; //0x38

    u32 kartsCount;
    u32 driverCount;
    Entry entries[1][1]; //karts = row, driver = column
};

#endif