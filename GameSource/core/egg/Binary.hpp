#ifndef _EGG_BINARY_
#define _EGG_BINARY_
#include <types.hpp>
#include <core/egg/Thread.hpp>
#include <core/nw4r/ut/List.hpp>
#include <core/nw4r/ut/Color.hpp>

namespace EGG {




template<class T>
class IBinary {
public:

    struct BinaryHeader {
        char magic[4]; //LGHT for example
        u32 fileSize;
        u8 version; //0x8
        u8 padding[3];
        u32 unknown_0xC;
    }; //0x10
    typedef BinaryHeader Binary;

    virtual void SetBinaryImpl(const Binary& raw) = 0; //0x8
    virtual void GetBinaryImpl(Binary* dest) const = 0; //0xC
    virtual const char* GetBinaryType() const = 0; //0x10
    virtual u32 GetBinarySize() const = 0; //0x14
    virtual u8 GetVersion() const = 0; //0x18
    virtual void DoubleMount() = 0; //0x1c

    void SetBinary(const Binary& raw); //8022f3e8
};


}//namespace EGG
#endif