#ifndef _GT2SOCKET_
#define _GT2SOCKET_
#include <types.hpp>
#include <core/GS/GT2/GT2Core.hpp>
#include <core/GS/DArray.h>

namespace GT2 { //this is C, but don't care

struct Socket;
struct Connection;

//called when someone attempts to connect to a socket that is listening for new connections.
//latency is an estimate of the round trip time between connections.
typedef void (*ConnectAttemptCallback)(Socket socket, Connection connection, u32 ip, u16 port, int latency, Byte* message, int length);

//called when there was is an error that forces a socket to close
typedef void (*SocketErrorCallback)(Socket socket);

//called with either sent or received data
typedef void (*DumpCallback)(Socket socket, Connection connection, u32 ip, u16 port, Bool reset, const Byte* message, int len);

//called when the sock receives a message that it cannot match to an existing connection.  if the callback recognizes the message and handles it, it should return GT2True
typedef Bool(*UnrecognizedMessageCallback)(Socket socket, u32 ip, u16 port, Byte* message, int len);

struct Socket {
    SOCKET socket;  //the network socket used for all network communication

    u32 ip;  //the ip this socket is bound to
    u16 port;  //the port this socket is bound to

    void* hashTableConnections;  // the connections that are using this socket
    GS::DArray* dArrayClosedConnections;  // connections that are closed no longer get a spot in the hash table

    Bool close;  //close was attempted inside a cb, and it should be closed as soon as possible
    Bool error;  //there was a socket error using this socket

    int cbLevel;  //if >0, then we're inside a cb (or recursive cbs)
    ConnectAttemptCallback connectAttemptcb;
    SocketErrorCallback socketErrorcb;
    DumpCallback sendDumpcb;
    DumpCallback receiveDumpcb;
    UnrecognizedMessageCallback unrecognizedMessagecb;
    void* data;  //user data
    int outgoingBufferSize;  //per-connection buffer sizes
    int incomingBufferSize;
    Bool broadcastEnabled;
};

}//namespace GT2


#endif