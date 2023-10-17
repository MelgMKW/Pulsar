#ifndef _JGPT_
#define _JGPT_
#include <game/KMP/KMPBlockBase.hpp>

struct JGPT {
    Vec3 position;
    Vec3 rotation;
    u16 id;
    u16 userData; //https://wiki.tockdom.com/wiki/KMP_(File_Format) sound trigger related
}; //total size 0x1c

typedef struct KMPBlock<JGPT> JGPTBlock;
#endif