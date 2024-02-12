#ifndef _RVLNAND_
#define _RVLNAND_
#include <types.hpp>
#define NANDMAXPATH 64

namespace NAND {
struct CommandBlock {
    void* userData;
    void* callback;
    void* fileInfo;
    void* bytes;
    void* inodes;
    void* status;
    u32 ownerId;
    u16 groupId;
    u8 nextStage;
    u8 padding;
    u32 attr;
    u32 ownerAcc;
    u32 groupAcc;
    u32 othersAcc;
    u32 num;
    char absPath[NANDMAXPATH];
    u32* length;
    u32* pos;
    int state;
    void* copyBuffer;
    u32 bufferSize;
    u8* type;
    u32 uniqNo;
    u32 requiredBlocks;
    u32 requiredInodes;
    u32* answer;
    u32 homeBlocks;
    u32 homeInodes;
    u32 userBlocks;
    u32 userInodes;
    u32 workBlocks;
    u32 workInodes;
    const char** dir;
    u32 flag;
};
size_assert(CommandBlock, 0xbc);

struct FileInfo {
    s32 fd;
    s32 origFd;
    char origPath[NANDMAXPATH];
    char tmpPath[NANDMAXPATH];
    u8 accType;
    u8 stage;
    u8 mark;
    u8 padding;
};
size_assert(FileInfo, 0x8c);

struct Status {
    u32 ownerId;
    u16 groupId;
    u8 attribute;
    u8 permission;
};

struct Banner {
    u32 magic;
    u32 flag;
    u16 iconAnimSpeed;
    u8 reserved[22];
    u16 comment[2][32];
    u8 bannerTexture[24576];
    u8 iconTexture[8][4608];
};

enum Type {
    NAND_TYPE_NONE,
    NAND_TYPE_FILE,
    NAND_TYPE_DIR
};

enum Perm {
    NAND_PERM_OTHER_READ   = 0x01,
    NAND_PERM_OTHER_WRITE  = 0x02,
    NAND_PERM_GROUP_READ   = 0x04,
    NAND_PERM_GROUP_WRITE  = 0x08,
    NAND_PERM_OWNER_READ   = 0x10,
    NAND_PERM_OWNER_WRITE  = 0x20

};
enum Result {
    NAND_RESULT_OK = 0,
    NAND_RESULT_ACCESS = -1,
    NAND_RESULT_ALLOC_FAILED = -2,
    NAND_RESULT_BUSY = -3,
    NAND_RESULT_CORRUPT = -4,
    NAND_RESULT_ECC_CRIT = -5,
    NAND_RESULT_EXISTS = -6,
    NAND_RESULT_INVALID = -8,
    NAND_RESULT_MAXBLOCKS = -9,
    NAND_RESULT_MAXFD = -10,
    NAND_RESULT_MAXFILES = -11,
    NAND_RESULT_NOEXISTS = -12,
    NAND_RESULT_NOTEMPTY = -13,
    NAND_RESULT_OPENFD = -14,
    NAND_RESULT_AUTHENTICATION = -15,
    NAND_RESULT_MAXDEPTH = -16,
    NAND_RESULT_UNKNOWN = -64,
    NAND_RESULT_FATAL_ERROR = -128
};

typedef void (*Callback)(s32 result, CommandBlock* block);
typedef void (*LoggingCallback)(BOOL result);

//File API
Result Create(const char* path, u8 perm, u8 attr); //8019b43c
Result Read(FileInfo* info, void* buffer, u32 length); //8019b7a4
Result ReadAsync(FileInfo* info, void* buffer, u32 length, Callback callback, CommandBlock* commandBlock); //8019b80c
Result Write(FileInfo* info, const void* buffer, u32 length); //8019b884
Result WriteAsync(FileInfo* info, const void* buffer, u32 length, Callback callback, CommandBlock* commandBlock); //8019b8ec
Result Seek(FileInfo* info, s32 offset, s32 whence); //8019b964
Result SeekAsync(FileInfo* info, s32 offset, s32 whence, Callback callback, CommandBlock* commandBlock); //8019ba04
Result Open(const char* path, FileInfo* info, u8 accType); //8019c800
Result OpenAsync(const char* path, FileInfo* info, u8 accType, Callback callback, CommandBlock* commandBlock); //8019c88c
Result Open(const char* path, FileInfo* info, u8 accType); //8019c918
Result OpenAsync(const char* path, FileInfo* info, u8 accType, Callback callback, CommandBlock* commandBlock); //8019c990
Result Close(FileInfo* info); //8019ca80
Result SafeOpen(const char* path, FileInfo* info, u8 accType, void* buffer, u32 length); //8018cb74
Result SafeClose(FileInfo* info); //8019cf28
Result CloseAsync(FileInfo* info, Callback callback, CommandBlock* commandBlock); //8019caec
Result SafeOpenAsync(const char* path, FileInfo* info, u8 accType, void* buf, u32 length,
    Callback callback, CommandBlock* commandBlock); //8019d130
Result SafeClose(FileInfo* info, Callback callback, CommandBlock* commandBlock); //8019d720

//DIR API
Result CreateDir(const char* path, u8 perm, u8 attr); //8019bbe0
Result GetCurrentDir(char* path); //8019e390
Result GetHomeDir(char* path); //8019e40c

//Both API
Result Delete(const char* path); //8019b59c
Result Move(const char* path, const char* destDIR); //8019bee8
Result GetLength(FileInfo* info, u32* length); //8019bf4c
Result GetLengthAsync(FileInfo* info, u32* length, Callback callback, CommandBlock* commandBlock); //8019c048
Result GetStatus(const char* path, Status* status); //8019c380
Result SetStatus(const char* path, const Status* status); //8019c614
Result GetType(const char* path, u8* type); //8019e770, use enum

//MISC
void SetUserData(CommandBlock* commandBlock, void* data); //8019c6dc
void* GetUserData(const CommandBlock* commandBlock); //8019c6e4
Result Init(); //8019e18c
void InitBanner(Banner* banner, u32 flag, const wchar_t* title, const wchar_t* comment); //8019e880
Result Check(u32 fsBlock, u32 inode, u32* answer); //8019ead0
Result SecretGetUsage(const char* path, u32* fsBlock, u32* inode); //8019e95c
BOOL LoggingAddMessageAsync(LoggingCallback callback, const char* format, ...); //8019ec2c 


namespace Private {
//File API
Result Create(const char* path, u8 perm, u8 attr); //8019b4b0
Result CreateAsync(const char* path, u8 perm, u8 attr, Callback callback, CommandBlock* commandBlock); //8019b524
Result SafeOpenAsync(const char* path, FileInfo* info, u8 accType, void* buffer, u32 length,
    Callback callback, CommandBlock* commandBlock); //8019d104

//DIR API
Result CreateDir(const char* path, u8 perm, u8 attr); //8019bc54
Result CreateDirAsync(const char* path, u8 perm, u8 attr, Callback callback, CommandBlock* commandBlock); //8019bcc8

//Both API
Result Delete(const char* path); //8019b64c
Result DeleteAsync(const char* path, Callback callback, CommandBlock* commandBlock); //8019b6e4
Result GetStatus(const char* path, Status* status); //8019c3e4
Result GetStatusAsync(const char* path, Status* status, Callback callback, CommandBlock* commandBlock); //8019c448
Result SetStatus(const char* path, const Status* status); //8019c678
Result GetTypeAsync(const char* path, u8* type, Callback callback, CommandBlock* commandBlock); //8019e7b4

}//namespace Private

}//namespace NAND





#endif