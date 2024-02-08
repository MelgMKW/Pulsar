#ifndef _TYPES_
#define _TYPES_

#pragma opt_unroll_loops off
#pragma ppc_unroll_instructions_limit 0

#pragma cpp1x on
#pragma gcc_extensions on
#pragma fp_contract on
#pragma Cpp_exceptions off
#pragma exceptions off
#pragma enumsalwaysint on
#pragma use_lmw_stmw on
#pragma instmgr_file on
#pragma no_static_dtors on
#pragma extended_errorcheck on
#pragma float_constants on
#pragma readonly_strings on
#pragma RTTI off

#pragma inline_depth(8)
#pragma inline_max_auto_size(0)
#pragma inline_max_size(256)
#pragma inline_max_total_size(10000)

#pragma warn_unusedvar on 
#pragma warn_illpragma on
#pragma warn_extracomma on
#pragma warn_possunwant on
#pragma warn_illtokenpasting off


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long ul;
typedef unsigned long long u64;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef float f32;

typedef double f64;
typedef volatile s64 vs64;
typedef volatile s32 vs32;
typedef volatile s16 vs16;
typedef volatile s8 vs8;
typedef volatile u64 vu64;
typedef volatile u32 vu32;
typedef volatile u16 vu16;
typedef volatile u8 vu8;
typedef volatile f64 vf64;
typedef volatile float vfloat;
typedef int UnkType;
typedef int BOOL; //any non-zero = true


struct RGBA16 {
    u16 red, green, blue, alpha;
};

#define offsetof(st, m) \
    ((const u32)&(((const st *)0)->m))

#ifdef __INTELLISENSE__
#define ASM(...)
#define asm(...) {}
#define asmVolatile asm
#define asmFunc void
#define __sync(...)
#define __isync(...)
#define size_assert(type, num) static_assert(sizeof(type)==(num),"type")
#define static_assert(...)
#else
#define asmFunc asm void
#define asmVolatile asm volatile
#define abs __abs
#define alignas(value) __attribute((aligned(value)))
#define ASM(...) __VA_ARGS__
#define override
#define size_assert(type, num) static_assert(sizeof(type) ==num,#type)
#endif



#endif


