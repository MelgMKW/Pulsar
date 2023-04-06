#ifndef _JGPT_
#define _JGPT_
#include <game/KMP/SectionBase.hpp>

struct JGPT {
    Vec3 position;
    Vec3 rotation;
    u16 id;
    u16 range;
}; //total size 0x1c

typedef struct KMPSection<JGPT> JGPTSection;
#endif