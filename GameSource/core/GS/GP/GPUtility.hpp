#ifndef _GPUTILITY_
#define _GPUTILITY_
#include <types.hpp>
#include <core/GS/GP/GPTypes.hpp>

namespace GP {

void strzcpy(char* dest, const char* src, u32 len); //80108e78 length of buffer, including space for '\0'
}//namespace GP


#endif