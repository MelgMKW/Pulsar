#ifndef _TYPES_
#define _TYPES_

#pragma inline_depth(8)
#pragma inline_max_auto_size(0)
#pragma inline_max_size(256)
#pragma inline_max_total_size(10000)
#pragma opt_unroll_loops off

#pragma fp_contract on
#pragma cpp1x on
#pragma arg_dep_lookup on
#pragma enumsalwaysint on
#pragma use_lmw_stmw on
#pragma instmgr_file on
#pragma no_static_dtors on
#pragma exceptions off
#pragma extended_errorcheck on
#pragma Cpp_exceptions off
#pragma float_constants on
#pragma readonly_strings on
#pragma RTTI off
#pragma warn_unusedvar on 
#pragma warn_illpragma on
#pragma warn_extracomma on
#pragma warn_possunwant on
#pragma warn_illtokenpasting off

#pragma gcc_extensions on




typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
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
typedef volatile f32 vf32;
typedef int UnkType;
typedef int BOOL; //any non-zero = true



#ifdef __INTELLISENSE__
typedef unsigned long long size_t;
#else
typedef unsigned long size_t;
#endif

struct RGBA16 {
    u16 red, green, blue, alpha;
};

#define offsetof(st, m) \
    ((const u32)&(((const st *)0)->m))

#ifdef __INTELLISENSE__
#define ASM(...)
#define volatile(...) {}
#define asm
#define __sync(...)
#define __isync(...)
#define size_assert(type, num) static_assert(sizeof(type)==(num),"type")
#define static_assert(...)
#else
#define abs __abs
#define alignas(value) __attribute((aligned(value)))
#define ASM(...) __VA_ARGS__
#define override
#define size_assert(type, num) static_assert(sizeof(type) ==num,#type)
#endif

#endif


