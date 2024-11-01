#ifndef _CNPT_
#define _CNPT_
#include <MarioKartWii/KMP/KMPBlockBase.hpp>

struct CNPT {
    Vec3 destPos;
    Vec3 angle; //0xC
    s16 id; //0x18
    s16 type; //0x1a straight, curved, curved and slow
}; //0x1c

typedef struct KMPBlock<CNPT> CNPTBlock;

#endif