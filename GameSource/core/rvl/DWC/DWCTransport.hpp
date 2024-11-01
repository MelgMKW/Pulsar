#ifndef _DWC_TRANSPORT_ 
#define _DWC_TRANSPORT_
#include <types.hpp>
#include <core/rvl/os/OS.hpp>
#include <core/GS/GT2/GT2.hpp>


namespace DWC { //this is C, but don't care

typedef void (*UserSendCallback)(int size, u8 aid);
typedef void (*UserRecvCallback)(u8 aid, u8* buffer, int size);
typedef void (*UserRecvTimeoutCallback)(u8 aid);
typedef void (*UserPingCallback)(int latency, u8 aid);

enum ReceiveStatus {
    DWC_TRANSPORT_RECV_NOBUF,		//Receive buffer not set
    DWC_TRANSPORT_RECV_HEADER,		//Wait to receive header
    DWC_TRANSPORT_RECV_BODY,		//Wait for data
    DWC_TRANSPORT_RECV_SYSTEM_DATA,	//Wait for data used internally
    DWC_TRANSPORT_RECV_ERROR,
    DWC_TRANSPORT_RECV_LAST
};

enum SendStatus {
    DWC_SEND_TYPE_INVALID,
    DWC_SEND_TYPE_USERDATA,							//User data
    DWC_SEND_TYPE_MATCH_SYN,						//SYN used for matchmaking end sync
    DWC_SEND_TYPE_MATCH_SYN_ACK,					//SYN-ACK used for matchmaking end sync
    DWC_SEND_TYPE_MATCH_ACK,						//ACK used for matchmaking end sync
};

struct TransportConnection {

    const u8* sendBuffer;
    u8* recvBuffer;			    //0x4 RACEPacket
    int	recvBufferSize;		    //0x8
    int	sendingSize;		    //0xc  Size of data being sent
    int	recvingSize;		    //0x10 Size of data being received
    int	requestSendSize;	    //0x14 Send request size
    int	requestRecvSize;	    //0x18 Receive request size
    u8	sendState;			    //0x1c Send status enum
    u8	recvState;			    //0x1d Receive status enum
    u8	lastRecvState;		    //0x1e Last receive status before receiving header
    u8	padding[3];             //0x1f
    u16	lastRecvType;		    //0x22Last header type received
    OS::Tick previousRecvTick;  //0x24
    u32	recvTimeoutTime;        //0x28
}; //0x2c

struct TransportInfo {
    static TransportInfo* sInstance; //80386318

    TransportConnection connections[32]; //Data used to manage each connection

    UserSendCallback sendCb;			    //0x800 A transmission completion cb
    UserRecvCallback recvCb;			    //0x804 Receive complete cb
    u32 unknown_0x808;
    UserPingCallback pingCb;			    //0x80c Ping cb

    u16	sendSplitMax;			            //0x814 Maximum split size for sending
    u8 padding[2];


    //UserRecvTimeoutCallback	recvTimeoutCb;	//0x80c Receive timeout cb



}; //0x818

BOOL SetRecvBuffer(u8 aid, void* recvBuffer, int size); //800e8750
void iInitTransport(TransportInfo* info); //800e87c8
void iRecvCallback(GT2::Connection* connection, GT2::Byte* message, int size, GT2::Bool reliable); //800e8814
void iPingCallback(GT2::Connection* connection, int latency); //800e88f8
BOOL SendUnreliable(u8 aid, const void* buffer, int size); //800e8654
}//namespace DWC


#endif