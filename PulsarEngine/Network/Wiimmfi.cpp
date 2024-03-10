#include <kamek.hpp>


#ifndef _WIIMMFI
#define _WIIMMFI_

/*
    This file was originally reverse engineered from code in LE-Code that was written by Leseratte/Wiimm.
    It's also went through several versions across different mods and patching systems, so contains some
    edits from Seeky, TheLordScruffy, and CLF78 at various points.
*/

extern "C" {

    extern char Patch_LoginPrintHeader[], Patch_WiimmfiURLs[];
    extern const char* Patch_AuthserverHosts[3];

    extern s32 DWC_AuthServer, SSL_Initialised;
    void NETSHA1Init();
    void NETSHA1Update();
    void NETSHA1GetDigest();

}

static u32 expectedHash[] ={ 0x0FFF1F07, 0x00E638C9, 0x49FBEFFA, 0x79022D3A, 0x84AB134F };

static asmFunc wiimmfiAsm1() {
    ASM(
        nofralloc;

    // Original instruction
    cmpwi r3, 0;

    // Return workaround
    mflr r23;

    ble end;

    // r13 replacements
    lis r11, DWC_AuthServer@ha;
    lis r12, SSL_Initialised@ha;

    lwz r3, 0xC (sp);
    lwz r0, DWC_AuthServer@l(r11);
    cmpwi r0, 2;
    beq cont;

    stw r3, SSL_Initialised@l(r12);
    li r0, 2;
    stw r0, DWC_AuthServer@l(r11);
    b end;

    // Execute payload
cont:
    addi r4, r3, 3;
    rlwinm r4, r4, 0, 0, 29;
    lbz r5, 0x0 (r4);
    add r5, r4, r5;
    dcbf 0, r5;
    mtlr r5;
    blrl;

    // Original instruction
end:
    li r3, -1;
    cmpwi r3, 0;

    // Return workaround
    mtlr r23;
    li r23, 0;
    blr;
    )
}

kmCall(0x800ee3a0, wiimmfiAsm1);

asmFunc wiimmfiAsm2() {
    ASM(
        nofralloc;

    // Return workaround
    stwu sp, -8 (sp);
    mflr r3;
    stw r3, 4 (sp);

    lis r12, SSL_Initialised@ha;

    // Check if inited
    lwz r4, SSL_Initialised@l(r12);
    cmplwi r4, 1;
    ble nomatch;

    // Push stack
    stwu sp, -0x80 (sp);

    // Call NETSHA1Init
    addi r3, sp, 0x20;
    bl NETSHA1Init;

    // Call NETSHA1Update
    addi r3, sp, 0x20;
    lis r12, SSL_Initialised@ha;
    lwz r4, SSL_Initialised@l(r12);
    li r5, 0x554;
    stw r5, 0xC4 (r28);
    bl NETSHA1Update;

    // Call NETSHA1GetDigest
    addi r3, sp, 0x20;
    addi r4, sp, 0x10;
    bl NETSHA1GetDigest;

    // Setup loop
    lis r3, (expectedHash - 4)@h;
    ori r3, r3, (expectedHash - 4)@l;
    addi r4, sp, 0xC;
    li r5, 5;
    mtctr r5;

    // Loop it!
loop:
    lwzu r5, 0x4(r3);
    lwzu r6, 0x4(r4);
    cmpw r6, r5;
    bne out;
    bdnz + loop;

    // Check if we found a match and pop the stack
out:;
    cmpw r6, r5;
    addi sp, sp, 0x80;
    lis r12, SSL_Initialised@ha;
    lwz r4, SSL_Initialised@l(r12);
    beq end;

    // Return 0 otherwise
nomatch:
    li r4, 0;

end:
    // Return workaround
    lwz r3, 4 (sp);
    mtlr r3;
    addi sp, sp, 8;
    blr;
    )
}

kmCall(0x801d4efc, wiimmfiAsm2);

static void patchURL(u32 offset, const char* string)
{
    strcpy(&Patch_WiimmfiURLs[offset], string);
}

static int stringPatch()
{
    strcpy(Patch_LoginPrintHeader, "Pulsar"); // set patcher name

    Patch_AuthserverHosts[0] = "http://ca.nas.wiimmfi.de/ca";
    Patch_AuthserverHosts[1] = "http://naswii.wiimmfi.de/ac";

    // Get path
    const char* path;
    switch(*(char*)0x80000003)
    {
        case 'E':
            Patch_AuthserverHosts[2] = "https://main.nas.wiimmfi.de/pe";
            break;
        case 'J':
            Patch_AuthserverHosts[2] = "https://main.nas.wiimmfi.de/pj";
            break;
        case 'P':
            Patch_AuthserverHosts[2] = "https://main.nas.wiimmfi.de/pp";
            break;
        case 'K':
            Patch_AuthserverHosts[2] = "https://main.nas.wiimmfi.de/pk";
            break;
    }

    patchURL(0xA8, "://naswii.wiimmfi.de/pr");
    patchURL(0x964, "wiimmfi.de"); // Available
    patchURL(0x10D4, "wiimmfi.de"); // GPCM
    patchURL(0x1AEC, "wiimmfi.de"); // GPSP
    patchURL(0x2C8D, "wiimmfi.de"); // Master
    patchURL(0x38A7, "wiimmfi.de"); // Natneg
    patchURL(0x38C3, "wiimmfi.de");
    patchURL(0x38DF, "wiimmfi.de");
    patchURL(0x3A2F, "wiimmfi.de"); // MS
    patchURL(0x3AB3, "wiimmfi.de"); // SAKE

    return 0;
}
kmOnLoad(stringPatch);

// Force DWC_AUTHSERVER_DEBUG
kmWrite32(0x800ecaac, 0x3bc00000);

// Nop host header
kmWrite32(0x800ed868, 0x60000000);

#endif
