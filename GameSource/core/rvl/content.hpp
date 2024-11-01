#ifndef _CONTENT_
#define _CONTENT_
#include "types.hpp"
#include <core/rvl/arc/arc.hpp>
#include <core/rvl/MEM/MEMallocator.hpp>

namespace CNT {
struct HandleNAND {
    ARC::Handle arcHandle;
    s32 fd;
    MEM::Allocator* allocator;
};

struct FileInfoNAND {
    HandleNAND* handle;
    s32 startOffset;
    u32 size;
    s32 readOffset;
};

};

s32  contentFastOpenNAND(CNT::HandleNAND* handle, s32 entrynum, CNT::FileInfoNAND* fileInfo); //8015bc80
s32  contentConvertPathToEntrynumNAND(CNT::HandleNAND* handle, const char* path); //8015bcec
s32  contentReadNAND(CNT::FileInfoNAND* fileInfo, void* dest, u32 length, s32 offset); //8015bcf8


#endif