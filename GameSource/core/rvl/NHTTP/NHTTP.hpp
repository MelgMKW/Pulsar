#ifndef _NHTTP_
#define _NHTTP_
#include <types.hpp>

namespace NHTTP {
enum Error {
    NHTTP_ERROR_NONE = 0,
    NHTTP_ERROR_ALLOC = 1,
    NHTTP_ERROR_TOOMANYREQ = 2,
    NHTTP_ERROR_SOCKET = 3,
    NHTTP_ERROR_DNS = 4,
    NHTTP_ERROR_CONNECT = 5,
    NHTTP_ERROR_BUFFULL = 6,
    NHTTP_ERROR_HTTPPARSE = 7,
    NHTTP_ERROR_CANCELED = 8,
    NHTTP_ERROR_NITROSDK = 9,
    NHTTP_ERROR_MAX
};

enum ReqMethod {
    NHTTP_REQMETHOD_GET,
    NHTTP_REQMETHOD_POST,
    NHTTP_REQMETHOD_HEAD,
    NHTTP_REQMETHOD_MAX
};
struct Req {};
struct Res {};
BOOL AddPostDataAscii(Req* req, char* label, char* value); //801d9198
int GetBodyAll(Res* res, char** value); //801d937c
} //namespace NHTTP
#endif

