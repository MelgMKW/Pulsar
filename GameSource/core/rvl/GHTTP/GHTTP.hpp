#ifndef _GHTTP_
#define _GHTTP_
#include <types.hpp>

//Credit Seeky

namespace GHTTP { //this is C, but don't care

enum GHTTPState {
    GHTTPHostLookup,
    GHTTPConnecting,
    GHTTPSecuringSession,
    GHTTPSendingRequest,
    GHTTPPosting,
    GHTTPWaiting,
    GHTTPReceivingStatus,
    GHTTPReceivingHeaders,
    GHTTPReceivingFile
};

enum Result {
    GHTTPSuccess,
    GHTTPOutOfMemory,
    GHTTPBufferOverflow,
    GHTTPParseURLFailed,
    GHTTPHostLookupFailed,
    GHTTPSocketFailed,
    GHTTPConnectFailed,
    GHTTPBadResponse,
    GHTTPRequestRejected,
    GHTTPUnauthorized,
    GHTTPForbidden,
    GHTTPFileNotFound,
    GHTTPServerError,
    GHTTPFileWriteFailed,
    GHTTPFileReadFailed,
    GHTTPFileIncomplete,
    GHTTPFileToBig,
    GHTTPEncryptionError
};

typedef struct GHIPost* Post;

bool PostAddXML(Post* post, void* xml);
bool PostAddFileFromMemoryA(Post* post, const char* attachedName, const void* file, int bufferLength, const char* reportFilename, const char* contentType);

}//namespace GHTTP


#endif