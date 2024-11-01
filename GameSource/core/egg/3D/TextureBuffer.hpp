#ifndef _EGG_TEXTURE_BUFFER_
#define _EGG_TEXTURE_BUFFER_
#include <types.hpp>
#include <core/egg/3D/Texture.hpp>
#include <core/egg/mem/Heap.hpp>

namespace EGG {

class TextureBuffer : public CapTexture {
public:
    void Initialize(u32 totalSize, EGG::Heap* heap); //80243080
    static u32 totalSize; //80386F74
    static TextureBuffer* array; //80386F70
    static TextureBuffer* cur; //80386F6C, essentially the last element of the list
    ~TextureBuffer() override; //80243284 vtable 802a3fa8 at 0x10
    void Configure(); //80242f1c 
    static TextureBuffer* Get(); //80243174 removes the last elem of the list, returns it

    void Alloc(); //8024319c
    void Free(); //80242f90
    u32 size; //0x28
    u32 state; //0x2c
    TextureBuffer* next; //0x30
    TextureBuffer* prev; //0x34
}; //0x38


//The first of the array is allocated with the maximum size (32676C bits in mkwii), 
//then every time a request is made for a buffer, the request size is subtracted from the top element, then the top of the list is updated to the next TextureBuffer

}//namespace EGG

#endif