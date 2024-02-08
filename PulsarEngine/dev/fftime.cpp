#include <dev/ff.hpp>
#include <core/rvl/OS/OS.hpp>

DWORD get_fattime(void)
{
    OS::CalendarTime time;
    OS::TicksToCalendarTime(OS::GetTime(), &time);

    DWORD val = 0;

    val |= (time.year - 1980) << 25;

    val |= (time.mon + 1) << 21;

    val |= time.mday << 16;

    val |= time.hour << 11;

    val |= time.min << 5;

    if(time.sec >= 60) {
        val |= 59 >> 1;
    }
    else {
        val |= time.sec >> 1;
    }

    return val;
}
