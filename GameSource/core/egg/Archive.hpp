#ifndef _EGGARCHIVE_
#define _EGGARCHIVE_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/rvl/arc/arc.hpp>

namespace EGG {
class Archive : public Disposer {
public:
    struct FileInfo {
        u32 offset;
        u32 size;
    };
    Archive(); //inlined
    ~Archive() override; //8020f6ec vtable 802a2680
    static Archive* Mount(void* archive, EGG::Heap* heap, int alignment); //8020f768
    static Archive* Mount2(void* archive, EGG::Heap* heap, int alignment); //8020f768 idk, only difference is used count is set to 2
    void Unmount(); //8020fa38
    s32 ConvertPathToEntryNum(const char* path); //8020fa78
    void* GetFileFast(const char* path, FileInfo* info); //8020fa80
    bool GetFileInfo(const char* path, FileInfo* info); //8020fb14 non-official
    static void* LoadFromDisc(const char* path, EGG::Heap* heap, int alignment); //8020fb78
    u32 usedCount; //0x10 how many times this archive is referenced (ie used)
    BOOL hasLoaded; //0x14 
    ARCHandle handle; //0x18
    nw4r::ut::Link archiveList; //0x34
}; //0x3c
}//namespace EGG

#endif