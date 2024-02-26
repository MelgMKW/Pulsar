#ifndef _JGPT_
#define _JGPT_
#include <MarioKartWii/KMP/KMPBlockBase.hpp>

struct JGPT {
    Vec3 position; //0x0
    Vec3 rotation; //0xc
    s16 id; //0x18
    s16 userData; //0x1a https://wiki.tockdom.com/wiki/KMP_(File_Format) sound trigger related
}; //total size 0x1c

typedef struct KMPBlock<JGPT> JGPTBlock;
#endif