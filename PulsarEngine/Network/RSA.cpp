// Copyright (C) 2010 The Chromium OS Authors. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <Network/RSA.hpp>
#include <Network/SHA256.hpp>

/**
 * a[] -= mod
 */
static void SubMod(const RSAPublicKey* key, u32* a)
{
    s64 A = 0;
    u32 i;
    for (i = 0; i < RSANUMWORDS; ++i) {
        A += (u64) a[i] - key->n[i];
        a[i] = (u32) A;
        A >>= 32;
    }
}

/**
 * Return a[] >= mod
 */
static int GeMod(const RSAPublicKey* key, const u32* a)
{
    u32 i;
    for (i = RSANUMWORDS; i;) {
        --i;
        if (a[i] < key->n[i])
            return 0;
        if (a[i] > key->n[i])
            return 1;
    }
    return 1; // equal
}

/**
 * Montgomery c[] += a * b[] / R % mod
 */
static void
MontMulAdd(const RSAPublicKey* key, u32* c, const u32 a, const u32* b)
{
    u64 A = (u64) a * b[0] + c[0];
    u32 d0 = (u32) A * key->n0inv;
    u64 B = (u64) d0 * key->n[0] + (u32) A;
    u32 i;

    for (i = 1; i < RSANUMWORDS; ++i) {
        A = (A >> 32) + (u64) a * b[i] + c[i];
        B = (B >> 32) + (u64) d0 * key->n[i] + (u32) A;
        c[i - 1] = (u32) B;
    }

    A = (A >> 32) + (B >> 32);

    c[i - 1] = (u32) A;

    if (A >> 32) {
        SubMod(key, c);
    }
}

/**
 * Montgomery c[] = a[] * b[] / R % mod
 */
static void MontMul(const RSAPublicKey* key, u32* c, const u32* a, const u32* b)
{
    for (u32 i = 0; i < RSANUMWORDS; ++i) {
        c[i] = 0;
    }

    for (u32 i = 0; i < RSANUMWORDS; ++i) {
        MontMulAdd(key, c, a[i], b);
    }
}

/**
 * In-place public exponentiation.
 *
 * @param key		Key to use in signing
 * @param inout		Input and output big-endian byte array
 */
static void ModPow(const RSAPublicKey* key, u32* inout)
{
    u32 a[RSANUMWORDS];
    u32 aaR[RSANUMWORDS];
    u32 aaaR[RSANUMWORDS];
    u32* aaa = aaaR; // Reuse location

    // Convert from big endian byte array to little endian word array
    for (u32 i = 0; i < RSANUMWORDS; ++i) {
        a[i] = inout[RSANUMWORDS - 1 - i];
    }

    MontMul(key, aaR, a, key->rr); // aaR = a * RR / R mod M
    // Exponent 65537
    for (u32 i = 0; i < 16; i += 2) {
        MontMul(key, aaaR, aaR, aaR); // aaaR = aaR * aaR / R mod M
        MontMul(key, aaR, aaaR, aaaR); // aaR = aaaR * aaaR / R mod M
    }
    MontMul(key, aaa, aaR, a); // aaa = aaR * a / R mod M

    // Make sure aaa < mod; aaa is at most 1x mod too large
    if (GeMod(key, aaa)) {
        SubMod(key, aaa);
    }

    // Convert to big endian byte array
    for (u32 i = 0; i < RSANUMWORDS; ++i) {
        inout[i] = aaa[RSANUMWORDS - 1 - i];
    }
}

#define PKCS_PAD_SIZE (RSANUMBYTES - SHA256_DIGEST_SIZE)

/*
 * PKCS#1 padding (from the RSA PKCS#1 v2.1 standard)
 *
 * The DER-encoded padding is defined as follows :
 * 0x00 || 0x01 || PS || 0x00 || T
 *
 * T: DER Encoded DigestInfo value which depends on the hash function
 * used, for SHA-256: (0x)30 31 30 0d 06 09 60 86 48 01 65 03 04 02 01
 * 05 00 04 20 || H.
 *
 * Length(T) = 51 octets for SHA-256
 *
 * PS: octet string consisting of {Length(RSA Key) - Length(T) - 3} 0xFF
 */
static const u8 sha256Tail[20] = {0x00, 0x30, 0x31, 0x30, 0x0D, 0x06, 0x09,
                                  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04,
                                  0x02, 0x01, 0x05, 0x00, 0x04, 0x20};

/**
 * Verify a SHA256WithRSA PKCS#1 v1.5 signature against an expected SHA-256
 * hash.
 *
 * @param key           RSA public key
 * @param signature     RSA signature
 * @param sha           SHA-256 digest of the content to verify
 * @return True on success.
 */
bool RSAVerify(const RSAPublicKey* key, u8* signature, const u8* sha)
{
    ModPow(key, (u32*) signature); // In-place exponentiation

    int result = 0;
    int i = 0;

    // Check PKCS#1 padding bytes
    // First 2 bytes are always 0x00 0x01
    result |= signature[i++] ^ 0x00;
    result |= signature[i++] ^ 0x01;

    // Then 0xFF bytes until the tail
    for (u32 j = 0; j < PKCS_PAD_SIZE - sizeof(sha256Tail) - 2; j++) {
        result |= signature[i++] ^ 0xFF;
    }

    // Check the tail
    result |= memcmp(signature + i, sha256Tail, sizeof(sha256Tail));

    if (result != 0) {
        return false;
    }

    // Check the digest
    if (memcmp(signature + PKCS_PAD_SIZE, sha, SHA256_DIGEST_SIZE) != 0) {
        return false;
    }

    return true;
}