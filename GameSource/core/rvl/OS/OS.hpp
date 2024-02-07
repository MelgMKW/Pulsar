#ifndef _OS_
#define _OS_
#include <types.hpp>
#include <core/rvl/gx/GX.hpp>

//it's not namespaced in the actual game but this makes it more readable

namespace OS {

struct CalendarTime {
    int sec, min, hour, mday, mon, year, wday, yday, msec, usec;
};
void TicksToCalendarTime(u64 time, CalendarTime* result);

void Report(const char* format, ...);
u64 GetTime();
u32 GetTick();
void Fatal(GX::Color foreground, GX::Color background, const char* message);
void LaunchTitle(UnkType r3, UnkType r4);
int CalcCRC32(void* data, u32 length);
int DisableInterrupts(); //801a65ac
int EnableInterrupts(); //801a65c0
int RestoreInterrupts(int level); //801a65d4
int DisableScheduler();
void Restart(u32 resetCode);

void* OSGetArenaLo(); //801a10cc

}//namespace OS

#endif
