#ifndef _GT2CORE_
#define _GT2CORE_
#include <types.hpp>



namespace GT2 { //this is C, but don't care

enum iConnectionState {
    //client-only states
    GTI2AwaitingServerChallenge,  //sent challenge, waiting for server's challenge
    GTI2AwaitingAcceptance,       //sent response, waiting for accept/reject from server

    //server-only states
    GTI2AwaitingClientChallenge,  //receiving challenge from a new client
    GTI2AwaitingClientResponse,   //sent challenge, waiting for client's response
    GTI2AwaitingAcceptReject,     //got client's response, waiting for app to accept/reject

    //post-negotiation states
    GTI2Connected,                //connected
    GTI2Closing,                  //sent a close message (GTI2Close or GTI2Reject), waiting for confirmation
    GTI2Closed
};

enum iMessageType {
    //reliable messages
    //all start with <magic-string> <type> <serial-number> <expected-serial-number>
    //type is 1 bytes, SN and ESN are 2 bytes each
    GTI2MsgAppReliable,       //reliable application message
    GTI2MsgClientChallenge,   //client's challenge to the server (initial connection request)
    GTI2MsgServerChallenge,   //server's response to the client's challenge, and his challenge to the client
    GTI2MsgClientResponse,    //client's response to the server's challenge
    GTI2MsgAccept,            //server accepting client's connection attempt
    GTI2MsgReject,            //server rejecting client's connection attempt
    GTI2MsgClose,             //message indicating the connection is closing
    GTI2MsgKeepAlive,         //keep-alive used to help detect dropped connections

    GTI2NumReliableMessages,

    //unreliable messages
    GTI2MsgAck = 100,         //acknowledge receipt of reliable message(s)
    GTI2MsgNack,              //alert sender to missing reliable message(s)
    GTI2MsgPing,              //used to determine latency
    GTI2MsgPong,              //a reply to a ping
    GTI2MsgClosed             //confirmation of connection closure (GTI2MsgClose or GTI2MsgReject) - also sent in response to bad messages from unknown addresses
};
enum Result {
    GT2_RESULT_SUCCESS,             //success
    //ERRORS:
    GT2_RESULT_OUTOFMEMORY,         //ran out of memory
    GT2_RESULT_REJECTED,            //attempt rejected
    GT2_RESULT_NETWORKERROR,        //networking error (could be local or remote)
    GT2_RESULT_ADDRESSERROR,        //invalid or unreachable address
    GT2_RESULT_DUPLICATEADDRESS,    //a connection was attempted to an address that already has a connection on the socket
    GT2_RESULT_TIMEDOUT,            //time out reached
    GT2_RESULT_NEGOTIATIONERROR     //there was an error negotiating with the remote side
};

enum CloseReason {
    GT2_CLOSE_REASON_LOCALCLOSE,         //The connection was closed with gt2CloseConnection.
    GT2_CLOSE_REASON_REMOTECLOSE,        //The connection was closed remotely.
    //ERRORS:
    GT2_CLOSE_REASON_COMMUNICATIONERROR, //An invalid message was received (it was either unexpected or wrongly formatted).
    GT2_CLOSE_REASON_SOCKETERROR,        //An error with the socket forced the connection to close.
    GT2_CLOSE_REASON_NOTENOUGHMEMORY     //There wasn't enough memory to store an incoming or outgoing message.
};

typedef int Bool;
typedef int SOCKET;
typedef u8 Byte;

struct Buffer {
    Byte* buffer;
    int size; //buffer size
    int len;  //actual datalength
};

}//namespace GT2


#endif