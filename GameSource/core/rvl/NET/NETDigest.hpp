#ifndef _NETDIGEST_
#define _NETDIGEST_
#include <types.hpp>

namespace NET {
struct SHA1Context {
    u32 h[5];          //H0,H1,H2,H3,H4
    u8  block[64];
    u32 pool;          //message length in 'block'
    u32 blocks_low;    //total blocks (in bytes)
    u32 blocks_high;
};

void SHA1Init(SHA1Context* context);
void SHA1Update(SHA1Context* context, const void* input, u32 length);
void SHA1Fill(SHA1Context* context, u8 input, u32 length);
void SHA1GetDigest(SHA1Context* context, void* digest);

} //namespace NET
#endif

