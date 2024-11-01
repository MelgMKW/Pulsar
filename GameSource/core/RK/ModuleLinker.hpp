#ifndef _MODULELINKER_
#define _MODULELINKER_
#include <types.hpp>
#include <core/rvl/OS/OSModule.hpp>
#include <core/egg/mem/Disposer.hpp>

class ModuleLinker {
public:
    struct ModuleValues {
        OS::ModuleInfo* rawModule;
    };
    static ModuleLinker* sInstance; //80385FF8
    static ModuleLinker* CreateInstance(); //80009ff0
    EGG::TDisposer<ModuleLinker> disposer; //80009f5c vtable 80270cc4
    virtual ~ModuleLinker(); //8000a074 vtable 80270cb8

    bool Link(EGG::Heap* heapToReadIn, u8 moduleIdx); //800a188 0 = empty, does not work, 1 = staticR.rel
    void CallModule(u8 moduleIdx); //8000a3f8
    void ReportSections(OS::ModuleInfo& linkedModule); //800a440

    EGG::Heap* moduleHeaps[2]; //0x14 Link param
    OS::ModuleInfo* rawModules[2]; //0x1c
    u32 unknown_0x24[2];

}; //0x2c
#endif