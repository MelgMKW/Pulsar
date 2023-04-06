#ifndef _OSCONTEXT_
#define _OSCONTEXT_
#include <types.hpp>

struct OSContext {
    u32 gpr[32]; //from 0 to c8
    u32 cr;
    u32 lr; //0x84
    u32 ctr; //0x88
    u32 xer;
    f64 fpr[32]; //0x90 ends at 0x190
    f64 fpscr;
    u32 srr0; //0x198
    u32 srr1; //0x19C
    u16 unknown_0x1A0;
    u16 unknown_0x1A2;
    u32 gqr[8]; //0x1A4 to 0x1C4
    u32 unknown_0x1C4;
    f64 pairedSinglesRegisters[32];
}; //total size 0x2C8

extern "C" {
    void OSSetCurrentContext(OSContext *context);
    OSContext *OSGetCurrentContext(); //801a1ecc
    u32 OSSaveContext(OSContext *context);
    void OSLoadContext(OSContext *context);
    void OSClearContext(OSContext *context);
    void OSInitContext(OSContext *context, u32 pc, u32 sp);
}
#endif