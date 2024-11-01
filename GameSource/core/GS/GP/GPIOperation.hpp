#ifndef _GPOPERATION_
#define _GPOPERATION_
#include <types.hpp>
#include <core/GS/GP/GPTypes.hpp>

namespace GP {

struct IConnectData {
    char serverChallenge[128];
    char userChallenge[33];
    char passwordHash[33];
    char authtoken[256];
    char partnerchallenge[256];
    char cdkey[65];
    BOOL newuser;
};

Result iAddOperation(Connection* connection, int type, void* data, IOperation** op, Enum blocking, Callback callback, void* param);

void iRemoveOperation(Connection* connection, IOperation* operation);
}//namespace GP


#endif