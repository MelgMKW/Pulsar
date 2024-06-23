#include <kamek.hpp>

#ifndef _RSA_
#  define _RSA_

#  define CONFIG_RSA_KEY_SIZE 2048
#  define RSANUMBYTES ((CONFIG_RSA_KEY_SIZE) / 8)
#  define RSANUMWORDS (RSANUMBYTES / sizeof(u32))

/**
 * RSA public key definition
 */
struct RSAPublicKey {
    u32 n0inv; // -1 / n[0] mod 2^32
    u32 n[RSANUMWORDS]; // modulus as little endian array
    u32 rr[RSANUMWORDS]; // R^2 as little endian array
};

/**
 * Verify a SHA256WithRSA PKCS#1 v1.5 signature against an expected SHA-256
 * hash.
 *
 * @param key           RSA public key
 * @param signature     RSA signature
 * @param sha           SHA-256 digest of the content to verify
 * @return True on success.
 */
bool RSAVerify(const RSAPublicKey* key, u8* signature, const u8* sha);

#endif