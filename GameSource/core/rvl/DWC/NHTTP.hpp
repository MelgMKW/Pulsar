#ifndef _NHTTP_
#define _NHTTP_

#include <types.hpp>

s32 NHTTPStartup(void* alloc, void* free, u32 param_3);

void* NHTTPCreateRequest(
    const char* url, int param_2, void* buffer, u32 length, void* callback,
    void* userdata
);

s32 NHTTPSendRequestAsync(void* request);

s32 NHTTPDestroyResponse(void* response);

#endif