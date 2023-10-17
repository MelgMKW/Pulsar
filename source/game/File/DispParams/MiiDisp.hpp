#ifndef _MIIDISPPARAM_
#define _MIIDISPPARAM_
#include <kamek.hpp>

class MiiDispParam { //https://wiki.tockdom.com/wiki/Filesystem/Race/Common.szs/miiDispParam.bin
public:
    struct Entry {
        float headScale;
        Vec2 yzTranslation;
    }; //0xC

    u32 entriesCount;
    Entry entries[1];
};

#endif