#ifndef _DARCH_ //to split into multiple files ultimately
#define _DARCH_
#include <types.hpp>


namespace DARCH { //this is C, but don't care

struct FileInfo {
    const char* pathName;
    void* rawFile;
    u32   fileSize;

};

u32 DARCHGetArcSize(const FileInfo* fileInfo, const u32 fileInfoCount); //8015d0fc
BOOL DARCHCreate(void* arcStart, u32 arcSize, const FileInfo* fileInfo, const u32 fileInfoCount); //8015d254

}//namespace DARCH


#endif