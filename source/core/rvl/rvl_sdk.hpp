#ifndef _RVL_SDK_
#define _RVL_SDK_
#include <types.hpp>

extern char gameID[4];
extern "C" {
    void DCFlushRange(void *ptr, u32 size);
    void ICInvalidateRange(void *ptr, u32 size);
}
#endif