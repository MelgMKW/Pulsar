#ifndef _OS_
#define _OS_
#include <types.hpp>
#include <core/rvl/gx/GX.hpp>

//it's not namespaced in the actual game but this makes it more readable

namespace OS {

extern u32 busClock; //800000f8
extern u32 coreClock; //800000fc

inline u32 GetTimerClock() { return busClock / 4; }
inline u32 TicksToMilliseconds(u64 ticks) { return ticks / (GetTimerClock() / 1000); }
inline u32 TicksToSeconds(u64 ticks) { return ticks / GetTimerClock(); }
inline u32 TicksToNanoseconds(u64 ticks) { return ticks * (1000000000 / GetTimerClock()); }
inline u32 NanosecondsToTicks(u32 nanoSeconds) { return nanoSeconds / (1000000000 / GetTimerClock()); }

typedef s64 Time;
typedef u32 Tick;
struct CalendarTime {
    int sec, min, hour, mday, mon, year, wday, yday, msec, usec;
};
void TicksToCalendarTime(u64 time, CalendarTime* result);

void Report(const char* format, ...);
u64 GetTime();
u32 GetTick();
void Fatal(GX::Color foreground, GX::Color background, const char* message);
int CalcCRC32(void* data, u32 length);
int DisableInterrupts(); //801a65ac
int EnableInterrupts(); //801a65c0
int RestoreInterrupts(int level); //801a65d4
int DisableScheduler();
void Restart(u32 resetCode);

void* GetArenaLo(); //801a10cc




template <typename T>
inline T MillisecondsToTicks(T ms) {
    return ms * (busClock / 1000);
}

}//namespace OS

#endif
