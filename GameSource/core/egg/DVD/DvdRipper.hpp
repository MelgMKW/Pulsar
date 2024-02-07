#ifndef _EGGDVDRIPPER_
#define _EGGDVDRIPPER_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/DVD/DvdFile.hpp>
#include <core/egg/Stream/StreamDecomp.hpp>

namespace EGG {
namespace DvdRipper {

enum EAllocDirection {
    ALLOC_FROM_HEAD = 1,
    ALLOC_FROM_TAIL = 2
};

void* LoadToMainRAM(const char* path, void* buffer, Heap* heap,
    EAllocDirection allocDirection, u32 offset, u32* readBytes, u32* size); //802226d8 calls the 2nd one

void* LoadToMainRAM(DvdFile* file, void* buffer, Heap* heap,
    EAllocDirection allocDirection, u32 offset, u32* readBytes, u32* size); //8022277c

//non-official
void* LoadToMainRAMLZDecomp(const char* path, StreamDecompLZ* streamDecompLZ, void* buffer, Heap* heap,
    EAllocDirection allocDirection, u32 offset, u32 lengthToDecompress, u32 r10); //8022293c

void* LoadToMainRAMLZDecomp(DvdFile* file, StreamDecompLZ* streamDecompLZ, void* buffer, Heap* heap,
    EAllocDirection allocDirection, u32 offset, u32 lengthToDecompress, u32 r10); //802229e8

}//namespace DvdRipper
}//namespace EGG
#endif