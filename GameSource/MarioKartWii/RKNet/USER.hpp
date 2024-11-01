#ifndef _RKNETUSER_
#define _RKNETUSER_

#include <kamek.hpp>
#include <core/rvl/RFL/RFLWifi.hpp>
#include <MarioKartWii/Mii/Mii.hpp>

/*
RKNetController is the class that handles the game specific network code (ex. RACE Packets) and controls DWC
Contributors:
  Seeky (main documentation)
References:
  https://wiki.tockdom.com/wiki/Network_Protocol/USER
*/

namespace RKNet {

struct USERPacket {
    static const u32 idx = 5;
    RFL::WiFiPacket rflPacket;
    u64 wiiFC; //0xa0
    u64 fc; //0xa8

    u8 country; //0xb0
    u8 state;
    u16 city;
    u16 locationLongitude; //0xb4
    u16 locationLatitude; //0xb6

    u16 vr; //0xb8
    u16 br; //0xba
    char gameRegion; //0xbc P,E,J,K
    u8 regionId; //0xbd  0=NTSC-J, 1=NTSC-U, 2=PAL/EUR, 3=PAL/AUS, 4=Taiwan 5=South Korea
    u16 unknown_0xbe;
};
size_assert(USERPacket, 0xc0);


class USERHandler {
    static USERHandler* sInstance; //809c2108
    static void CreateInstance(); //80662778
    static void DestroyInstance(); //806627f8
    USERHandler(); //80662e08 inlined
    ~USERHandler(); //80662e64 inlined

    void Prepare(); //8066284c
    void Update(); //806629c0
    void Reset(); //80662944
    void CopySendToPacketHolder(u8 aidToSendTo); //80662abc
    void ProcessPlayerDisconnect(u8 aid);

    void SetSendVR(); //80662d80 obtained from save
    void SetSendBR(); //80662dc4

    void ImportNewPackets(); //80662ebc
    void CreateSendPacket(); //8066300c

    bool isInitialized;
    u8 unknown_0x1[7];

    USERPacket toSendPacket; //0x8
    USERPacket receivedPackets[12]; //0xc8

    RFL::WiFiInformation rflWifiInfo; //0x9c8
    void* rflWifiInfoBuffer; //0x9d8 just an array of RFL::WiFiPackets

    u8 unknown_0x9dc[4];
    u32 aidBitflag; //0x9e0
    u32 aidsThatHaveGivenMiis; //0x9e4
    u32 aidBitFlag2; //0x9e8
    u8 unknown_0x9ec[4];
};

}//namespace RKNet
#endif
