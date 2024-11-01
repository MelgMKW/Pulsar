#ifndef _GPCALLBACK_
#define _GPCALLBACK_
#include <types.hpp>
#include <core/GS/GP/GPEnum.hpp>
#include <core/GS/GP/GPTypes.hpp>
namespace GP {
struct ICallback {
    Callback callback;
    void* param;
};
struct ICallbackData {
    ICallback callback;
    void* arg;
    int type;
    int operationID;
    struct GPICallbackData* next;
};

enum IAddCallbackType {
    GPI_ADD_NORMAL,
    GPI_ADD_ERROR,
    GPI_ADD_MESSAGE,
    GPI_ADD_NICKS,
    GPI_ADD_PMATCH,
    GPI_ADD_STATUS,
    GPI_ADD_BUDDDYREQUEST,
    GPI_ADD_TRANSFER_CALLBACK,
    GPI_ADD_REVERSE_BUDDIES,
    GPI_ADD_SUGGESTED_UNIQUE,
    GPI_ADD_BUDDYAUTH,
    GPI_ADD_BUDDYUTM,
    GPI_ADD_BUDDYREVOKE,
    GPI_ADD_REVERSE_BUDDIES_LIST,
    GPI_ADD_BUDDYKEYS,
    GPI_NUM_ADD_CALLBACK_TYPES
};

}//namespace GP


#endif