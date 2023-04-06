#ifndef _EGGDVDRIPPER_
#define _EGGDVDRIPPER_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>

namespace EGG {
namespace DvdRipper {
void *LoadToMainRam(const char *path, void *buffer, EGG::Heap *heap,
    u32 allocDirection, u32 offset, u32 *readBytes, u32 *size); //802226d8 directio: 1 = from head, 2 from tail

}//namespace DvdRipper
}//namespace EGG
#endif