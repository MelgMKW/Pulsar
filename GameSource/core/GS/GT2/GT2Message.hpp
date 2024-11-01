#ifndef _GT2MESSAGE_
#define _GT2MESSAGE_
#include <types.hpp>
#include <core/GS/GT2/GT2Core.hpp>
#include <core/GS/GT2/GT2Connection.hpp>

namespace GT2 { //this is C, but don't care

Bool iHandleUnreliableMessage(Connection* connection, iMessageType type, Byte* message, int recvFromRetVal);

}//namespace GT2


#endif