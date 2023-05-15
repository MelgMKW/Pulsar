#ifndef _THPLIB_
#define _THPLIB_
#include <types.hpp>

namespace THP {
BOOL Init(); //801b6ee0
s32 VideoDecode(void* file, void* tileY, void* tileU, void* tileV, void* work); //801b3bac
u32 AudioDecode(s16* buffer, u8* audioFrame, s32 flag);


}//namespace THP
#endif