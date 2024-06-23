#include <kamek.hpp>

#ifndef _SHA256_
#  define _SHA256_

#  define SHA256_DIGEST_SIZE 32
#  define SHA256_BLOCK_SIZE 64

/* SHA256 context */
struct SHA256Context {
    u32 h[8];
    u32 tot_len;
    u32 len;
    u8 block[2 * SHA256_BLOCK_SIZE];
    u8 buf[SHA256_DIGEST_SIZE]; /* Used to store the final digest. */
};

void SHA256Init(SHA256Context* ctx);
void SHA256Update(SHA256Context* ctx, const void* data, u32 len);
u8* SHA256Final(SHA256Context* ctx);

#endif