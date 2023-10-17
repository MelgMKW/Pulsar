#ifndef _DRIVERDISPPARAM_
#define _DRIVERDISPPARAM_
#include <kamek.hpp>

class DriverDispParam { //https://wiki.tockdom.com/wiki/DriverDispParam.bin
public:
    struct Entry {
        u32 unused[2];
        Vec2 coinStackYZOffset;
    }; //0x10

    u32 driverCount;
    Entry entries[1];
};

#endif