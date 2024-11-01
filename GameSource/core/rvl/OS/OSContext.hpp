#ifndef _OSCONTEXT_
#define _OSCONTEXT_
#include <types.hpp>

namespace OS {
struct Context {
    u32 gpr[32]; //from 0 to c8
    u32 cr;
    u32 lr; //0x84
    u32 ctr; //0x88
    u32 xer;
    double fpr[32]; //0x90 ends at 0x190
    double fpscr;
    u32 srr0; //0x198
    u32 srr1; //0x19C
    u16 unknown_0x1A0;
    u16 unknown_0x1A2;
    u32 gqr[8]; //0x1A4 to 0x1C4
    u32 unknown_0x1C4;
    double pairedSinglesRegisters[32];
}; //total size 0x2C8
size_assert(Context, 0x2c8);


void SetCurrentContext(Context* context);
Context* GetCurrentContext(); //801a1ecc
u32 SaveContext(Context* context);
void LoadContext(Context* context);
void ClearContext(Context* context);
void InitContext(Context* context, u32 pc, u32 sp);

} //namespace OS
#endif