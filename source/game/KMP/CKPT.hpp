#ifndef _CKPT_
#define _CKPT_
#include <game/KMP/SectionBase.hpp>

struct CKPT {
    Vec2 leftPoint;
    Vec2 rightPoint;
    u8 respawn;
    u8 type;
    u8 previous;
    u8 next;
};

typedef struct KMPSection<CKPT> CKPTSection;

#endif