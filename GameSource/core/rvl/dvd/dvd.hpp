#ifndef _DVD_
#define _DVD_
#include <types.hpp>

/*
Contributors:
-kHacker35000vr, Melg
*/

namespace DVD {

struct CommandBlock;
struct FileInfo;

typedef void (*CBCallback)(s32 result, CommandBlock* block);
typedef void (*Callback)(s32 result, FileInfo* fileInfo);

struct DiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber; //0x6
    u8 gameVersion;
    u8 streaming; //0x8
    u8 streamingBufSize; //0x9 0 = default
    u8 padding[14];      //0xa 0's are stored
    u32 rvlMagic;         //0x18 Revolution disk magic number
    u32 gcMagic;          //0x1c GC magic number is here
}; //0x20

struct CommandBlock {
    CommandBlock* next;
    CommandBlock* prev; //4
    u32 command; //8
    u32 state; //c
    u32 offset; //10
    u32 size; //14
    void* buffer; //18
    u32 curTransferSize; //1c 
    u32 transferredSize; //20
    DiskID* id; //0x24
    CBCallback callback; //0x28
    void* userData; //0x2c
};
size_assert(CommandBlock, 0x30);

struct FileInfo {
    CommandBlock commandBlock;
    u32             startAddr;      //0x30 disk address of file
    u32             length;         //0x34 file size in bytes
    Callback     callback;
};
size_assert(FileInfo, 0x3c);

struct Dir {
    u32 entryNum;
    u32 location;
    u32 next;
};
size_assert(Dir, 0xc);

s32 ConvertPathToEntryNum(const char* path); //8015df4c
BOOL FastOpen(s32 entrynum, FileInfo* fileInfo); //8015e254
BOOL Open(const char* fileName, FileInfo* fileInfo); //8015e2bc
BOOL Close(FileInfo* fileInfo); //8015e568
BOOL EntrynumIsDir(s32 entrynum); //8015e58c
BOOL ReadAsyncPrio(FileInfo* fileInfo, void* buffer, s32 length, s32 offset, Callback callback, s32 prio); //8015e74c
s32  ReadPrio(FileInfo* fileInfo, void* buffer, s32 length, s32 offset, s32 prio); //8015e834
void Init(); //8015ea1c
s32 ReadAbsAsyncPrio(FileInfo* handle, void* buffer, u32 size, u32 offset, Callback callback, s32 prio); //801628cc
s32 InquiryAsync(FileInfo* handle, void* buffer, char* company); //801629b0
s32 GetCommandBlockStatus(const CommandBlock* block); //80162a88
s32 GetDriveStatus(); //80162b50
BOOL SetAutoInvalidation(BOOL autoInval); //80162bec
void Pause(); //80162bfc
void Resume(); //80162c38
BOOL CancelAsync(CommandBlock* block, CBCallback callback); //80162c88
s32 Cancel(CommandBlock* block); //80162fec
s32 CancelAll(); //801630d0
DiskID* GetCurrentDiskID(); //8016321c
BOOL CompareDiskID(const DiskID* id1, const DiskID* id2); //8016411c
DiskID* GenerateDiskID(DiskID* id, const char* game, const char* company, u8 diskNum, u8 version); //8016420c
BOOL SetAutoFatalMessaging(BOOL enable); //80164364

}//namespace DVD
#endif