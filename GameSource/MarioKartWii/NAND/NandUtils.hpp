#ifndef _NANDUTILS_
#define _NANDUTILS_
#include <kamek.hpp>
#include <core/rvl/nand.hpp>

namespace NandUtils {
enum Result {
    NAND_RESULT_OK = 0,
    NAND_RESULT_BUSY = 2,
    NAND_RESULT_ACCESS = 3,
    NAND_RESULT_NOEXISTS = 4,
    NAND_RESULT_ALLOC_FAILED = -2,
    NAND_RESULT_CORRUPT = 6,
    NAND_RESULT_CANT_SAVE = 7,
    NAND_RESULT_OTHER_ERRORS = 8, //RVL NAND result not 0, -1, -12 leads to this
};

enum Type {
    NAND_TYPE_EXISTS,
    NAND_TYPE_FILE,
    NAND_TYPE_DIR
};

//if RVL NAND result returns busy, these functions will attempt a total of 3 times (with sleep ticks in btw) and only then return BUSY
Result SafeOpen(const char* path, NAND::FileInfo* info, u8 accType, void* buffer, u32 length); //8052ae5c
Result Open(const char* path, NAND::FileInfo* info, u8 accType); //8052af64
Result Close(NAND::FileInfo* info); //8052b144
Result SafeClose(NAND::FileInfo* info); //8052b058
Result Read(NAND::FileInfo* info, void* buffer, u32 length, s32 offset); //8052b228
Result GetLength(NAND::FileInfo* info, u32* length); //8052b3f8
Result Write(NAND::FileInfo* info, void* buffer, u32 size, u32 offset); //8052b4d4
Result Check(u32 fsBlock, u32 inode, u32* answer); //8052b684
Result CreateDir(const char* path, u8 perm); //8052b754
Result GetType(const char* path, Type* type); //8052b84c
Result Create(const char* path, u8 perm); //8052b95c
Result Delete(const char* path); //8052ba54
Result SetStatus(const char* path, const NAND::Status* status); //8052bb40
Result GetStatus(const char* path, NAND::Status* status); //8052bc3c
Result FileExists(const char* path); //8052bd38 simply calls GetStatus, without a care for the result


} //namespace NandUtils

#endif