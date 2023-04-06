#ifndef _TIMER_
#define _TIMER_
#include <kamek.hpp>

class Timer {
public:
    Timer(); // 8051c374
    Timer &operator=(const Timer &src) {
        this->minutes = src.minutes;
        this->seconds = src.seconds;
        this->milliseconds = src.milliseconds;
        this->isActive = src.isActive;
        return *this;
    }

    const bool operator>(const Timer &src) const {
        if (this->isActive == false) return true;
        else if (src.minutes < this->minutes) return true;
        else if (src.minutes == this->minutes && src.seconds < this->seconds) return true;
        else if (src.minutes == this->minutes && src.seconds == this->seconds && src.milliseconds <= this->milliseconds) return true;
        return false;
    }

    virtual ~Timer(); //8051c334 vtable 808b2d44
    u16 minutes;
    u8 seconds;
    u8 padding;
    u16 milliseconds;
    bool isActive;
    u8 padding2;
}; // Total size 0xc
size_assert(Timer, 0xC);
#endif

