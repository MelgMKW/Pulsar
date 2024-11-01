#ifndef _RKNETPACKETHOLDER_
#define _RKNETPACKETHOLDER_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>

namespace RKNet {

/*
class PacketHolder {
public:
    explicit PacketHolder(u32 bufferSize); //8065a24c inlined
    ~PacketHolder(); //8065a2ac

    void Clear(); //8065a30c
    void Copy(const void* src, u32 len); //8065a34c
    void Append(const void* src, u32 len); //8065a38c

    void* packet;   //0x0 packet ptr
    u32 bufferSize; //0x4 maximum data size 0x50
    u32 packetSize; //0x8 current data size 0x38 -> 0x38 + len
}; //Total size 0xc
size_assert(PacketHolder, 0xc);
*/

template<class T>
class PacketHolder;

typedef PacketHolder<void> DefaultPacketHolder;

template<class T>
class PacketHolder {
public:
    explicit PacketHolder(u32 bufferSize);
    ~PacketHolder(); //8065a2ac

    void Clear() { reinterpret_cast<DefaultPacketHolder*>(this)->Clear(); }
    void Copy(const T* src, u32 len) { reinterpret_cast<DefaultPacketHolder*>(this)->Copy(src, len); }
    void Append(const void* src, u32 len) { reinterpret_cast<DefaultPacketHolder*>(this)->Append(src, len); }


    T* packet;   //0x0 packet ptr
    u32 bufferSize; //0x4 maximum data size 0x50
    u32 packetSize; //0x8 current data size 0x38 -> 0x38 + len
}; //Total size 0xc

template<>
class PacketHolder<void> {
public:
    explicit PacketHolder(u32 bufferSize);
    ~PacketHolder(); //8065a2ac

    void Clear();
    void Copy(const void* src, u32 len);
    void Append(const void* src, u32 len);

    void* packet;   //0x0 packet ptr
    u32 bufferSize; //0x4 maximum data size
    u32 packetSize; //0x8 current data size
}; //Total size 0xc


}//namespace RKNet
#endif