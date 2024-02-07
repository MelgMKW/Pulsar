#ifndef _RKNETPACKETHOLDER_
#define _RKNETPACKETHOLDER_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>

namespace RKNet {

class PacketHolder {
public:
    explicit PacketHolder(u32 bufferSize); //8065a24c
    ~PacketHolder(); //8065a2ac

    void Init(); //8065a24c
    void Clear(); //8065a30c
    void Copy(const void* src, u32 len); //8065a34c
    void Append(const void* src, u32 len); //8065a38c

    void* packet;   //0x0 packet ptr
    u32 bufferSize; //0x4 maximum data size
    u32 packetSize; //0x8 current data size
}; //Total size 0xc
size_assert(PacketHolder, 0xc);


}//namespace RKNet
#endif