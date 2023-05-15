#ifndef _AUDIOINTERFACE_
#define _AUDIOINTERFACE_
#include <types.hpp>

namespace AI {
typedef void (*DCallback)();
DCallback RegisterDMACallback(DCallback callback); //80123f88

}//namespace AI

#endif