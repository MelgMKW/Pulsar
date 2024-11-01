
#ifndef _DWC_GHTTP_ 
#define _DWC_GHTTP_
#include <types.hpp>
#include <core/GS/GHTTP/GHTTP.hpp>

namespace DWC {

enum GHTTPState {
    DWCGHTTPFalse = -1,
    DWCGHTTPHostLookup = GHTTP::GHTTPHostLookup,
    DWCGHTTPConnecting = GHTTP::GHTTPConnecting,
    DWCGHTTPSecuringSession = GHTTP::GHTTPSecuringSession,
    DWCGHTTPSendingRequest = GHTTP::GHTTPSendingRequest,
    DWCGHTTPPosting = GHTTP::GHTTPPosting,
    DWCGHTTPWaiting = GHTTP::GHTTPWaiting,
    DWCGHTTPReceivingStatus = GHTTP::GHTTPReceivingStatus,
    DWCGHTTPReceivingHeaders = GHTTP::GHTTPReceivingHeaders,
    DWCGHTTPReceivingFile = GHTTP::GHTTPReceivingFile,

    DWC_GHTTP_FALSE = -1,
    DWC_GHTTP_HOST_LOOKUP = GHTTP::GHTTPHostLookup,
    DWC_GHTTP_CONNECTING = GHTTP::GHTTPConnecting,
    DWC_GHTTP_SECURING_SESSION = GHTTP::GHTTPSecuringSession,
    DWC_GHTTP_SENDING_REQUEST = GHTTP::GHTTPSendingRequest,
    DWC_GHTTP_POSTING = GHTTP::GHTTPPosting,
    DWC_GHTTP_WAITING = GHTTP::GHTTPWaiting,
    DWC_GHTTP_RECEIVING_STATUS = GHTTP::GHTTPReceivingStatus,
    DWC_GHTTP_RECEIVING_HEADERS = GHTTP::GHTTPReceivingHeaders,
    DWC_GHTTP_RECEIVING_FILE = GHTTP::GHTTPReceivingFile
};

enum GHTTPResult {
    //The result of an HTTP request.
    DWCGHTTPSuccess = GHTTP::GHTTPSuccess,                  //0, Successfully retrieved file.
    DWCGHTTPOutOfMemory = GHTTP::GHTTPOutOfMemory,          //A memory allocation failed.
    DWCGHTTPBufferOverflow = GHTTP::GHTTPBufferOverflow,    //The user-supplied buffer was too small to hold the file.
    DWCGHTTPParseURLFailed = GHTTP::GHTTPParseURLFailed,    //There was an error parsing the URL.
    DWCGHTTPHostLookupFailed = GHTTP::GHTTPHostLookupFailed,//Failed looking up the hostname.
    DWCGHTTPSocketFailed = GHTTP::GHTTPSocketFailed,        //Failed to create/initialize/read/write a socket.
    DWCGHTTPConnectFailed = GHTTP::GHTTPConnectFailed,      //Failed connecting to the http server.
    DWCGHTTPBadResponse = GHTTP::GHTTPBadResponse,          //Error understanding a response from the server.
    DWCGHTTPRequestRejected = GHTTP::GHTTPRequestRejected,  //The request has been rejected by the server.
    DWCGHTTPUnauthorized = GHTTP::GHTTPUnauthorized,        //Not authorized to get the file.
    DWCGHTTPForbidden = GHTTP::GHTTPForbidden,              //The server has refused to send the file.
    DWCGHTTPFileNotFound = GHTTP::GHTTPFileNotFound,        //Failed to find the file on the server.
    DWCGHTTPServerError = GHTTP::GHTTPServerError,          //The server has encountered an internal error.
    DWCGHTTPFileWriteFailed = GHTTP::GHTTPFileWriteFailed,  //An error occurred writing to the local file (for ghttpSaveFile[Ex]).
    DWCGHTTPFileReadFailed = GHTTP::GHTTPFileReadFailed,    //There was an error reading from a local file (for posting files from disk).
    DWCGHTTPFileIncomplete = GHTTP::GHTTPFileIncomplete,    //Download started but was interrupted.  Only reported if file size is known.
    DWCGHTTPFileToBig = GHTTP::GHTTPFileToBig,              //The file is to big to be downloaded (size exceeds range of internal data types)
    DWCGHTTPEncryptionError = GHTTP::GHTTPEncryptionError,  //Error with encryption engine.
    DWCGHTTPNum,

    DWCGHTTPMemoryError = DWCGHTTPNum + 1,           //DWC memory allocation failed.

    //Correction of naming rule errors
    DWC_GHTTP_SUCCESS = GHTTP::GHTTPSuccess,                    //0, Successfully retrieved file.
    DWC_GHTTP_OUT_OF_MEMORY = GHTTP::GHTTPOutOfMemory,          //A memory allocation failed.
    DWC_GHTTP_BUFFER_OVERFLOW = GHTTP::GHTTPBufferOverflow,     //The user-supplied buffer was too small to hold the file.
    DWC_GHTTP_PARSE_URL_FAILED = GHTTP::GHTTPParseURLFailed,    //There was an error parsing the URL.
    DWC_GHTTP_HOST_LOOKUP_FAILED = GHTTP::GHTTPHostLookupFailed,//Failed looking up the hostname.
    DWC_GHTTP_SOCKET_FAILED = GHTTP::GHTTPSocketFailed,         //Failed to create/initialize/read/write a socket.
    DWC_GHTTP_CONNECT_FAILED = GHTTP::GHTTPConnectFailed,       //Failed connecting to the http server.
    DWC_GHTTP_BAD_RESPONSE = GHTTP::GHTTPBadResponse,           //Error understanding a response from the server.
    DWC_GHTTP_REQUEST_REJECTED = GHTTP::GHTTPRequestRejected,   //The request has been rejected by the server.
    DWC_GHTTP_UNAUTHORIZED = GHTTP::GHTTPUnauthorized,          //Not authorized to get the file.
    DWC_GHTTP_FORBIDDEN = GHTTP::GHTTPForbidden,                //The server has refused to send the file.
    DWC_GHTTP_FILE_NOT_FOUND = GHTTP::GHTTPFileNotFound,        //Failed to find the file on the server.
    DWC_GHTTP_SERVER_ERROR = GHTTP::GHTTPServerError,           //The server has encountered an internal error.
    DWC_GHTTP_FILE_WRITE_FAILED = GHTTP::GHTTPFileWriteFailed,  //An error occurred writing to the local file (for ghttpSaveFile[Ex]).
    DWC_GHTTP_FILE_READ_FAILED = GHTTP::GHTTPFileReadFailed,    //There was an error reading from a local file (for posting files from disk).
    DWC_GHTTP_FILE_INCOMPLETE = GHTTP::GHTTPFileIncomplete,     //Download started but was interrupted.  Only reported if file size is known.
    DWC_GHTTP_FILE_TOO_BIG = GHTTP::GHTTPFileToBig,             //The file is to big to be downloaded (size exceeds range of internal data types)
    DWC_GHTTP_ENCRYPTION_ERROR = GHTTP::GHTTPEncryptionError,   //Error with encryption engine.
    DWC_GHTTP_NUM,

    DWC_GHTTP_MEMORY_ERROR = DWC_GHTTP_NUM + 1           //DWC memory allocation failed.
};

typedef void (*GHTTPCompletedCallback)(const void* buf, int len, GHTTPResult result, void* param);
typedef void (*GHTTPProgressCallback)(GHTTPState state, const void* buf, int len, int bytesReceived, int totalSize, void* param);

bool ProcessGHTTP(); //800cd4a8
bool InitGHTTP(const char* gameName); //800cd3b0 just call with nullptr, gameName is unused
bool ShutdownGHTTP(); //800cd3f4


int GetGHTTPDataEx(const char* url, u32 bufferSize, bool clearBuffer, GHTTPProgressCallback progressCB, GHTTPCompletedCallback compleCB, void* param);  //800cd864



void GHTTPNewPost(GHTTP::Post* post); //800cd66c 
int PostGHTTPData(const char* url, GHTTP::Post* post, GHTTPCompletedCallback compleCB, void* param); //800cd6d4

}//namespace DWC

#endif