#ifndef _DWC_ //to split into multiple files ultimately
#define _DWC_
#include <types.hpp>

//Credit Seeky

namespace DWC { //this is C, but don't care

extern char loginRegion[8]; //80384fd0


struct ConnectionUserData {
    u8 localPlayerCount;
    u8 unknown_0x1[3];
};



int Printf(u32 level, const char*, ...);
s32 GetLastErrorEx(u32* errorCode, u32* errorType); //800ccb64

}//namespace DWC


#endif