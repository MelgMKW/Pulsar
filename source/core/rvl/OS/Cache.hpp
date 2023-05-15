#ifndef _OS_
#define _OS_
#include <types.hpp>
#include <core/rvl/gx/GX.hpp>

//it's not namespaced in the actual game but this makes it more readable

namespace OS {

//DATA CACHE
//Store a range of cached data at addr (dcbst, sync)
void DCStoreRange(void* addr, u32 size); //801a165c
//Invalidates a range of cached data, so that when that data is read, it is read from main memory (so is guaranteed to be correct)
void DCInvalidateRange(void* addr, u32 size); //801a1600

//LOCKED CACHE
void LCEnable(); //801a1834
void LCDisable(); //801a186c

}//namespace OS

#endif
