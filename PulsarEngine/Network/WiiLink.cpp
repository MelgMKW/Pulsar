#include <Network/RSA.hpp>
#include <Network/SHA256.hpp>
#include <Network/WiiLink.hpp>
#include <core/rvl/DWC/DWC.hpp>
#include <core/rvl/DWC/NHTTP.hpp>
#include <core/rvl/ipc/ipc.hpp>
#include <kamek.hpp>

#ifndef _WIILINK_
#define _WIILINK_

static u8 s_payloadBlock[PAYLOAD_BLOCK_SIZE + 0x20];
static void *s_payload = NULL;
static bool s_payloadReady = false;
static u8 s_saltHash[SHA256_DIGEST_SIZE];

extern "C"
{
    void Real_DWCi_Auth_SendRequest(
        int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);

    extern s32 *s_auth_work;
    extern s32 s_auth_error;
}

static asm void DWCi_Auth_SendRequest(
    int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    // clang-format off
    nofralloc

    stwu r1, -0x1B0(r1)
    b Real_DWCi_Auth_SendRequest
    // clang-format on
}

bool GenerateRandomSalt(u8 *out)
{
    // Generate cryptographic random with ES_Sign
    s32 fd = IOS::Open("/dev/es", IOS::MODE_NONE);
    if (fd < 0)
    {
        return false;
    }

    u8 dummy[0x20] __attribute((aligned(0x40)));
    dummy[0] = 0x7a;
    u8 eccCert[0x180] __attribute((aligned(0x40)));
    u8 eccSignature[0x3C] __attribute((aligned(0x40)));

    IOS::IOCtlvRequest vec[3] __attribute((aligned(0x40)));
    vec[0].address = &dummy;
    vec[0].size = 1;
    vec[1].address = eccSignature;
    vec[1].size = 0x3C;
    vec[2].address = eccCert;
    vec[2].size = 0x180;

    // ES_Sign
    s32 ret = IOS::IOCtlv(fd, IOS::IOCtlType(0x30), 1, 2, vec);
    IOS::Close(fd);

    if (ret < 0)
    {
        return false;
    }

    SHA256Context ctx;
    SHA256Init(&ctx);
    SHA256Update(&ctx, eccSignature, 0x3C);
    SHA256Update(&ctx, eccCert, 0x180);
    memcpy(out, SHA256Final(&ctx), SHA256_DIGEST_SIZE);
    return true;
}

s32 HandleResponse(u8 *block)
{
    register wwfc_payload *__restrict payload =
        reinterpret_cast<wwfc_payload *>(block);

    if (*reinterpret_cast<u32 *>(payload) != 0x57574643 /* WWFC */)
    {
        return WL_ERROR_PAYLOAD_STAGE1_HEADER_CHECK;
    }

    if (payload->header.total_size < sizeof(wwfc_payload) ||
        payload->header.total_size > PAYLOAD_BLOCK_SIZE)
    {
        return WL_ERROR_PAYLOAD_STAGE1_LENGTH_ERROR;
    }

    if (memcmp(payload->salt, s_saltHash, SHA256_DIGEST_SIZE) != 0)
    {
        return WL_ERROR_PAYLOAD_STAGE1_SALT_MISMATCH;
    }

    SHA256Context ctx;
    SHA256Init(&ctx);
    SHA256Update(
        &ctx, reinterpret_cast<u8 *>(payload) + sizeof(wwfc_payload_header),
        payload->header.total_size - sizeof(wwfc_payload_header));
    u8 *hash = SHA256Final(&ctx);

    if (!RSAVerify(
            reinterpret_cast<const RSAPublicKey *>(PayloadPublicKey),
            payload->header.signature, hash))
    {
        return WL_ERROR_PAYLOAD_STAGE1_SIGNATURE_INVALID;
    }

    // Flush data cache and invalidate instruction cache
    for (register u32 i = 0; i < 0x20000; i += 0x20)
    {
        asm(dcbf i, payload; sync; icbi i, payload; isync;);
    }
        
    // Disable unnecessary patches
    u32 patchMask = WWFC_PATCH_LEVEL_CRITICAL | WWFC_PATCH_LEVEL_BUGFIX |
                    WWFC_PATCH_LEVEL_SUPPORT;
    for (wwfc_patch *patch = reinterpret_cast<wwfc_patch*>(
                        block + payload->info.patch_list_offset
                    ),
                    *end = reinterpret_cast<wwfc_patch*>(
                        block + payload->info.patch_list_end
                    );
         patch < end; patch++) {
        if (patch->level == WWFC_PATCH_LEVEL_CRITICAL ||
            (patch->level & patchMask)) {
            continue;
        }

        // Otherwise disable the patch
        patch->level |= WWFC_PATCH_LEVEL_DISABLED;
    }
        
    s32 (*entryFunction)(wwfc_payload *) =
        reinterpret_cast<s32 (*)(wwfc_payload *)>(
            reinterpret_cast<u8 *>(payload) + payload->info.entry_point);

    return entryFunction(payload);
}

void OnPayloadReceived(s32 result, void *response, void *userdata)
{
    if (response == NULL)
    {
        return;
    }

    NHTTPDestroyResponse(response);

    if (result != 0)
    {
        return;
    }

    s32 error = HandleResponse(reinterpret_cast<u8*>(s_payload));
    if (error != 0)
    {
        s_auth_error = error;
        return;
    }

    s_payloadReady = true;
    s_auth_error = -1; // This error code will retry auth
}

kmBranchDefCpp(
    0x800ed6e8, 0, void, int param_1, int param_2, int param_3, int param_4,
    int param_5, int param_6)
{
    if (s_payloadReady)
    {
        DWCi_Auth_SendRequest(
            param_1, param_2, param_3, param_4, param_5, param_6);
        return;
    }

    s_payload = (void *)((u32(s_payloadBlock) + 31) & ~31);
    memset(s_payload, 0, PAYLOAD_BLOCK_SIZE);

    u8 salt[SHA256_DIGEST_SIZE];
    if (!GenerateRandomSalt(salt))
    {
        s_auth_error = WL_ERROR_PAYLOAD_STAGE1_MAKE_REQUEST;
    }

    static const char *hexConv = "0123456789abcdef";
    char saltHex[SHA256_DIGEST_SIZE * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_SIZE; i++)
    {
        saltHex[i * 2] = hexConv[salt[i] >> 4];
        saltHex[i * 2 + 1] = hexConv[salt[i] & 0xf];
    }
    saltHex[SHA256_DIGEST_SIZE * 2] = 0;

    char uri[0x100];
    sprintf(uri, "payload?g=RMC%cD00&s=%s", *(char *)0x80000003, saltHex);

    // Generate salt hash
    SHA256Context ctx;
    SHA256Init(&ctx);
    SHA256Update(&ctx, uri, strlen(uri));
    memcpy(s_saltHash, SHA256Final(&ctx), SHA256_DIGEST_SIZE);

    char url[0x100];
    sprintf(
        url, "http://nas.%s/%s&h=%02x%02x%02x%02x", WWFC_DOMAIN, uri,
        s_saltHash[0], s_saltHash[1], s_saltHash[2], s_saltHash[3]);

    void *request = NHTTPCreateRequest(
        url, 0, s_payload, PAYLOAD_BLOCK_SIZE, OnPayloadReceived, 0);

    if (request == NULL)
    {
        s_auth_error = WL_ERROR_PAYLOAD_STAGE1_MAKE_REQUEST;
        return;
    }

    s_auth_work[0x59E0 / 4] = NHTTPSendRequestAsync(request);
}

#endif
