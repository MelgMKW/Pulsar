#ifndef _OSERROR_
#define _OSERROR_
#include <types.hpp>

enum OSError {
    OSERROR_DSI = 2,
    OSERROR_ISI = 3,
    OSERROR_FLOATING_POINT = 7,
    OSERROR_FPE = 8
};
#endif