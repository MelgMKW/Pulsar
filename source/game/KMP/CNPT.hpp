#ifndef _CNPT_
#define _CNPT_
#include <game/KMP/SectionBase.hpp>

struct CNPT {
    Vec3 destPos;
    Vec3 angle;
    u16 id;
    u16 type; //straight, curved, curved and slow
};

typedef struct KMPSection<CNPT> CNPTSection;

#endif