#ifndef _EGGDECOMP_
#define _EGGDECOMP_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/rvl/arc/arc.h>

namespace EGG {
namespace Decomp {
enum CompressionType {
    COMPRESSION_NONE,
    COMPRESSION_SZS,
    COMPRESSION_ASH,
    COMPRESSION_ASR
};

u32 getExpandSize(u8 *rawFile); //8021997c size of extracted file
u32 decode(u8 *rawFile, u8 *destBuffer); //80218ba4 returns size of decoded file
u32 decodeSZS(u8 *rawFile, u8 *destBuffer); //80218c2c
u32 decodeASH(u8 *rawFile, u8 *destBuffer); //80218dc0
u32 decodeASR(u8 *rawFile, u8 *destBuffer); //80218ff0

bool checkCompressed(u8 *rawFile); //802198f8
}
}//namespace EGG

#endif