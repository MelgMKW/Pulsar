#ifndef _PARAMETERFILE_
#define _PARAMATERFILE_
#include <types.hpp>
#include <core/nw4r/ut/List.hpp>
#include <core/egg/mem/Heap.hpp>

struct RKParameter { //non-official
    nw4r::ut::Link link;
    void* parameter;
    u32 size;
};

class RKParameterFile {
    RKParameterFile(const char* filePath, u32 r5); //80009c8c
    virtual ~RKParameterFile(); //80009ce0 vtable 80270c98
    virtual void ReadParameterFile(EGG::Heap* heap); //80009ddc
    virtual void vf_0x10(); //80009f58
    virtual void vf_0x14(); //80009f54
    virtual void vf_0x18(); //80009f50

    void AddParameter(void* parameter, u32 size, EGG::Heap* heap); //80009d6c
    nw4r::ut::List parameterList; //0x4 list of pointers, these will be read from the file if it exists...except it doesn't 
    u32 totalParamsSize; //0x10
    char* filePath; //0x14
    u32 r5Arg; //0x18
}; //0x1c
#endif