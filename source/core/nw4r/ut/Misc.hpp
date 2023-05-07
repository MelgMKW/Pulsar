#ifndef _NW4R_UT_MISC_
#define _NW4R_UT_MISC_
#include <types.hpp>

namespace nw4r {
namespace ut {

namespace {



template <typename T>
static inline T Abs(T a) { return (a < 0) ? static_cast<T>(-a) : a; }

template<>
static inline float Abs<float>(register float value) {
    register float ret;
    asm volatile(fabs ret, value;);
    return ret;
}

template<typename T>
static inline T Min(T lhs, T rhs) { return lhs < rhs ? lhs : rhs; }

template<typename T>
static inline T Max(T lhs, T rhs) { return lhs > rhs ? lhs : rhs; }

template <typename T>
static inline T RoundUp(T value, u32 base) {
    return static_cast<T>((value + (base - 1)) & ~(base - 1));
}

static inline u32 GetIntPtr(const void* ptr) { //somehow doesn't get inlined
    return reinterpret_cast<u32>(ptr);
}

template<typename T>
static inline void* AddOffsetToPtr(void* pointer, T offset) {
    return reinterpret_cast<void*>(GetIntPtr(pointer) + offset);
}

static inline void* AddU32ToPtr(void* pointer, u32 offset) {
    return AddOffsetToPtr(pointer, offset);
}

template<typename T>
static inline const void* AddOffsetToPtr(const void* pointer, T offset) {
    return reinterpret_cast<const void*>(GetIntPtr(pointer) + offset);
}

static inline const void* AddU32ToPtr(const void* pointer, u32 offset) {
    return AddOffsetToPtr(pointer, offset);
}

inline int GetOffsetFromPtr(const void* start, const void* end){
    return static_cast<int>(GetIntPtr(end) - GetIntPtr(start));
}

static inline int ComparePtr(const void* lhs, const void* rhs) {
    return static_cast<int>(GetIntPtr(lhs) - GetIntPtr(rhs));
}

class NonCopyable {
protected:
    NonCopyable() {}
    ~NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    const NonCopyable& operator=(const NonCopyable&);
};


}
}//namespace ut
}//namespace nw4r



#endif
