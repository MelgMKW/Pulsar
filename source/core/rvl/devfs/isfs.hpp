
#ifndef _ISFS_
#define _ISFS_
#include <types.hpp>
#include <core/rvl/ipc/ipc.hpp>


namespace ISFS {
enum Mode {
    MODE_NONE = 0x0,
    MODE_READ = 0x1,
    MODE_WRITE = 0x2,
    MODE_READ_WRITE = MODE_READ | MODE_WRITE
};

enum ISFSError {
    ERROR_INVALID_ARG = -101,
    ERROR_PERMISSION_DENIED = -102,
    ERROR_CORRUPTED = -103,
    ERROR_FILE_EXISTS = -105,
    ERROR_FILE_NOT_FOUND = -106,
    ERROR_TOO_MANY_FILES_OPEN = -107,
    ERROR_MEMORY_FULL = -108,
    ERROR_TOO_MANY_FILES_OPEN2 = -109,
    ERROR_TOO_LONG_PATH = -110,
    ERROR_ALREADY_OPEN = -111,
    ERROR_ECC_ERROR = -114,
    ERROR_DIR_NOT_EMPTY = -115,
    ERROR_MAX_DIR_DEPTH = -116,
    ERROR_BUSY = -118,
    ERROR_FATAL = -119
};

s32 Open(char *path, Mode mode);
s32 GetFileStats(u32 fd, IOS::FileStats *stats);
s32 Read(s32 fd, void *buffer, u32 length);
s32 Rename(char *filepathOld, const char *filepathNew);
s32 Delete(char *path);
s32 Close(s32 fd);
s32 Seek(s32 fd, s32 offset, s32 whence);
s32 CreateFile(const char *filepath, u8 attributes, IOS::Mode ownerperms, IOS::Mode groupperms, IOS::Mode otherperms);
s32 Write(s32 fd, void *buffer, u32 length);
s32 ReadDir(const char *folder, void *r4, u32 *num);
s32 CreateDir(const char *filepath, u8 attributes, IOS::Mode userperms, IOS::Mode groupperms, IOS::Mode otherperms);
s32 GetAttr(const char *filepath, u32 *uid, u16 *gid, u8 *attributes, IOS::Mode *userperms, IOS::Mode *groupperms, IOS::Mode *otherperms);


}//namespace ISFS
#endif