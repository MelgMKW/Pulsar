#ifndef _GPTYPES_
#define _GPTYPES_
#include <types.hpp>
#include <core/GS/DArray.h>
#include <core/GS/GT2/GT2Core.hpp>
#include <core/GS/GP/GPEnum.hpp>

namespace GP {
struct Connection;
typedef void (*Callback)(Connection* connection, void* arg, void* param);

struct ICallback {
    Callback callback;
    void* param;
};

struct IBuffer {
    char* buffer;
    int size;
    int len;
    int pos;
};

struct IOperation {
    void* data;
    BOOL blocking;
    ICallback callback;
    int state;
    int id;
    Result result;
    IOperation* next;
};

struct Connection {
    char errorString[256];
    BOOL infoCaching;
    BOOL infoCachingBuddyAndBlockOnly;
    BOOL simulation;
    BOOL firewall;
    char nick[31];
    char uniquenick[21];
    char email[51];
    char password[31];
    int sessKey;
    int userid;
    int profileid;
    int partnerID;
    ICallback callbacks[6];
    int cmSocket;
    int connectState;
    IBuffer socketBuffer;
    char* inputBuffer;
    int inputBufferSize;
    IBuffer outputBuffer;
    // Replaced by UDP Layer
    //SOCKET peerSocket;
    char header[16];
    unsigned short peerPort;
    int nextOperationID;
    int numSearches;

    Enum lastStatusState;
    unsigned int hostIp;
    unsigned int hostPrivateIp;
    unsigned short queryPort;
    unsigned short hostPort;
    unsigned int sessionFlags;

    char richStatus[256];
    char gameType[33];
    char gameVariant[33];
    char gameMapName[33];

    // New Status Info extended info Keys
    GS::DArray extendedInfoKeys;

    // Deprecated
    char lastStatusString[33];
    char lastLocationString[256];

    ErrorCode errorCode;
    BOOL fatalError;
    FILE* diskCache;
    IOperation* operationList;
    void* profileList;
    void* peerList;
    void* callbackList;
    void* lastCallback;
    IBuffer updateproBuffer;
    IBuffer updateuiBuffer;
    GS::DArray transfers;
    unsigned int nextTransferID;
    int productID;
    int namespaceID;
    char loginTicket[25];
    Enum quietModeFlags;
    u32 gsi_time_kaTransmit;

}; //0x634

struct UniqueMatch {
    int pid;
    char uniqueNick[21];
};

struct GetReverseBuddiesListResponseArg {
    Result result;
    int numOfUniqueMatchs;
    UniqueMatch* matches;
};

}//namespace GP


#endif