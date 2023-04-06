#ifndef _OS_
#define _OS_
#include <types.hpp>
#include <core/rvl/gx/GX.hpp>


typedef struct {
    int sec, min, hour, mday, mon, year, wday, yday, msec, usec;
} OSCalendarTime;
void OSTicksToCalendarTime(u64 time, OSCalendarTime *result);

extern "C" {
    void OSReport(const char *format, ...);
    u64 OSGetTime();
    u32 OSGetTick();
    void OSFatal(GXColor foreground, GXColor background, const char *message);
    void OSLaunchTitle(UnkType r3, UnkType r4);
    int OSCalcCRC32(void *data, u32 length);
    int OSDisableInterrupts(); //801a65ac
    int OSEnableInterrupts(); //801a65c0
    int OSRestoreInterrupts(int level); //801a65d4
    int OSDisableScheduler();
    void OSRestart(u32 resetCode);
}
#endif
