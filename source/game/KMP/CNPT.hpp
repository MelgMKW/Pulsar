#ifndef _CNPT_
#define _CNPT_
#include <game/KMP/KMPBlockBase.hpp>

struct CNPT {
    Vec3 destPos;
    Vec3 angle; //0xC
    u16 id; //0x18
    u16 type; //0x1a straight, curved, curved and slow
};

typedef struct KMPBlock<CNPT> CNPTBlock;

#endif