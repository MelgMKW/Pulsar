#ifndef _GPCONNECT_
#define _GPCONNECT_
#include <types.hpp>
#include <core/GS/GP/GPTypes.hpp>
#include <core/GS/GP/GPIOperation.hpp>

namespace GP {
void iStartConnect(Connection* connection, IOperation* operation); //800ffe28

extern const char connectionMgrURL; //8027B4D0 "GPCM"
}//namespace GP


#endif