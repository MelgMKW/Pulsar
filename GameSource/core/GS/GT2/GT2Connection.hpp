#ifndef _GT2CONNECTION_
#define _GT2CONNECTION_
#include <types.hpp>
#include <core/GS/GT2/GT2Core.hpp>
#include <core/GS/GT2/GT2Socket.hpp>

namespace GT2 { //this is C, but don't care

struct Connection;

//Called when the connect has completed
typedef void (*ConnectedCallback)(Connection* connection, Result result, Byte* message, int len);

//Called when a message is received.
typedef void (*ReceivedCallback)(Connection* connection, Byte* message, int len, Bool reliable);

//Called when the connection is closed (remotely or locally).
typedef void (*ClosedCallback)
(Connection* connection, CloseReason reason);

//When a reply is received for a ping that was sent, ping in ms
typedef void (*PingCallback)(Connection* connection, int latency);

struct ConnectionCallbacks {
    ConnectedCallback connected; //Called when gt2Connect is complete.
    ReceivedCallback received;   //Called when a message is received.
    ClosedCallback closed;       //Called when the connection is closed (remotely or locally).
    PingCallback ping;           //Called when a ping reply is received.
}; //0x10

struct Connection {
    u32 ip;  //the ip on the other side of this connection (network byte order)
    u16 port;  //the port on the other side of this connection (host byte order)
    Socket* socket;  //the parent socket
    iConnectionState state; //0xc
    Bool initialized;
    Bool freeAtAcceptReject;  //don't free the connection until accept/reject is called
    Result connectionResult;  //the result of the connect attempt
    u32 startGsiTime;  //the time the connection was created
    u32 gsitimeout;  //0x20 the timeout value passed into gt2Connect
    int cbLevel;  //if >0, then we're inside a cb (or recursive cbs)
    ConnectionCallbacks cbs;  //0x28 connection cbs
    char* initialMessage;  //0x38 this is the initial message for the client
    int initialMessageLen;  //the initial message length
    void* data;  //0x40 user data, DWCConnectionInfo
    Buffer incomingBuffer;  //0x44 incoming data
    Buffer outgoingBuffer;  //outgoing data
    GS::DArray* dArrayincomingBufferMessages;  //identifies incoming messages stored in the buffer
    GS::DArray* dArrayoutgoingBufferMessages;  //identifies outgoing messages stored in the buffer
    u16 serialNumber;
    u16 expectedSerialNumber;
    char response[32];  //after the challenge is sent during negotiation, this is the response
    u32 gsiLastSendTime;
    u32 gsiChallengeTime;
    Bool pendingAck;  //there is an ack waiting to go out, either on its own or as part of a reliable message
    u32 gsiPendingAckTime;  //the time at which the pending ack was first set
    GS::DArray* dArraySendFilters;
    GS::DArray* dArrayreceiveFilters;

};

}//namespace GT2


#endif