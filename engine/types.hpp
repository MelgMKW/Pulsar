#ifndef _TYPES_
#define _TYPES_
#define NULL 0
#pragma cpp1x on
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
typedef unsigned long size_t;


struct RGBA16 {
    u16 red, green, blue, alpha;
};

template<typename T>
inline T Min(T a, T b) { return a < b ? a : b; }
template<typename T>
inline T Max(T a, T b) { return a > b ? a : b; }

#define abs __abs

#define foreach(item, array, length) \
for(decltype(&array[0]) ite = (&array[0]), (item) = ite; ite < (&(array)[length]); ite++, (item) = ite)

#define offsetof(st, m) \
    ((u32)&(((st *)0)->m))

#ifdef __INTELLISENSE__
#define ASM(...)
#define asm 
#define __attribute(...)
#define __abs(n) n

#define __sync(...)
#define __isync(...)
#define size_assert(type, num) static_assert(sizeof(type)==(num),"type")
#define size_assert static_assert
#define static_assert(...)
#else
#define ASM(...) __VA_ARGS__
#define override
#define size_assert(type, num) static_assert(sizeof(type) ==num,#type)
#endif

#endif

