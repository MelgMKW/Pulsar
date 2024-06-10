#ifndef _EGGAJPG_
#define _EGGAJPG_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>

namespace EGG {

class AJPGCreator { //unofficial name
public:
    AJPGCreator(u32 size, EGG::Heap* heap); //80234950
    u32 CreateImage(const void* sourceImage, u16 width, u16 height, u32 r7, void* workBuffer); //802349b0 returns size of the created image
    void* ajpgBuffer; //0x0
    u8 bufferSize; //0x4
};


//name obtained through a OSReport in create, creates a AJPG file (format used by the wii message board)
//might be able to create other formats
class CompressGBAOdh {
    struct Resolution {
        u16 width;
        u16 height;
    };
    struct Params {
        u16 width;
        u16 height;
        u8 r7arg;
        u8 padding;
        u16 widthDiv8Ceil;
        u16 heightDiv8Ceil; //0x8

        u8 unknown_0x5[0x2c - 0x5];
        void* workBuffer; //0x2c
        u8 unknown_0x30[0x230 - 0x30];
        void* destBuffer; //0x230
        u8 unknown_0x234[0x200];
        u32 destImageBufferSize; //0x434
        u8 unknown_0x438[0x47c - 0x438];
    }; //0x47c

    u32 CreateImage(const void* sourceImage, void* destBuffer, u16 width, u16 height, u32 r7OfFuncAbove,
        u32 destBufferSize, void* workBuffer, u32 r11); //8023321c returns size of the created image
    s32 Initialize(Params& params, const Resolution& resolution, u32 r7OfFuncAbove,
        void* workBuffer, void* destBuffer, u32 destBufferSize); //802333bc ret value of 0 = success
    s32 ColorConversion(const Params& params, const void* sourceImage, u32 r11); //80233d00
    s32 Process(Params& params); //8023354c returns the size of the created image if success
    void WriteImageHeader(const Params& params, u32 totalImageSize); //80233c94 "AJPG"

    void* processedImage; //after the header, can be the compressed ajpg or the decompressed (ajpg to raw)
};

}//namespace EGG


#endif