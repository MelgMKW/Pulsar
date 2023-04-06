#ifndef _NAND_
#define _NAND_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#define NAND_MAX_PATH 64
#define NAND_MAX_NAME 12

namespace NAND {

enum Mode {
    MODE_NONE = 0x0,
    MODE_READ = 0x1,
    MODE_WRITE = 0x2,
    MODE_READ_WRITE = MODE_READ | MODE_WRITE
};

enum Error {
    ERROR_OK = 0,
    ERROR_BUSY = -3,
    ERROR_EXISTS = -6,
    ERROR_NOT_EXISTS = -12
};

enum Perm {
    PERM_READ = 0x10,
    PERM_WRITE = 0x20,
    PERM_READ_WRITE = PERM_READ | PERM_WRITE,
};

struct FileInfo { //used by nw4r and nand
    u8 unknown_0x0[0x8C];
}; //total size 0x8C


class Manager {
public:
    static Manager *sInstance;
    Manager(); //8052becc, is often inlined
    EGG::Disposer disposer; //808b3250 also has a virtual dtor
    virtual ~Manager(); //0x8052bf44 vtable 808b3244
    void Read(void *buffer, u32 size, u32 offset, bool r7); //8052c0b0
    u8 unknown_0x14;
    u8 unknown_0x15;
    u8 unknown_0x16[2]; //padding?
    u32 unknown_0x18;
    UnkType *saveBanner; //pointer to savebanner.tpl
    u32 *array;
    UnkType *ptr; //related to banner.bin
}; //total size 0x28


s32 Create(const char *filename, u8 permissions, u8 attributes);
s32 Read(FileInfo *info, void *buf, u32 length);
s32 GetLength(FileInfo *info, u32 *length);
s32 Open(const char *path, FileInfo *info, u8 accType); //1 to read, 2 to write
s32 Close(FileInfo *info);
s32 Write(FileInfo *fileInfo, void *buffer, u32 size);
s32 Seek(FileInfo *info, s32 offset, s32 whence);
s32 GetHomeDir(char path[NAND_MAX_PATH]);
s32 Move(const char *path, const char *destDir);

}//namespace NAND
#endif