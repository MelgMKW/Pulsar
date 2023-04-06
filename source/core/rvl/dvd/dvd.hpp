#ifndef _DVD_
#define _DVD_
#include <types.hpp>

/*
Contributors:
-kHacker35000vr, Melg
*/
struct DVDCommandBlock;
struct DVDFileInfo;

typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);
typedef void (*DVDCallback)(s32 result, DVDFileInfo *fileInfo);

struct DVDDiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize; // 0 = default
    u8 padding[14];      // 0's are stored
    u32 rvlMagic;         // Revolution disk magic number
    u32 gcMagic;          // GC magic number is here
};

struct DVDCommandBlock {
    DVDCommandBlock *next;
    DVDCommandBlock *prev; //4
    u32 command; //8
    u32 state; //c
    u32 offset; //10
    u32 size; //14
    void *buffer; //18
    u32 curTransferSize; //1c 
    u32 transferredSize; //20
    DVDDiskID *id; //0x24
    DVDCBCallback callback; //0x28
    void *userData; //0x2c
};
size_assert(DVDCommandBlock, 0x30);

struct DVDFileInfo {
    DVDCommandBlock commandBlock;
    u32             startAddr;      // disk address of file
    u32             length;         // file size in bytes
    DVDCallback     callback;
};
size_assert(DVDFileInfo, 0x3c);

extern "C" {
    s32 DVDConvertPathToEntryNum(const char *pathPtr); //8015df4c
    BOOL DVDFastOpen(s32 entrynum, DVDFileInfo *fileInfo); //8015e254
    BOOL DVDOpen(const char *fileName, DVDFileInfo *fileInfo); //8015e2bc
    BOOL DVDClose(DVDFileInfo *fileInfo); //8015e568
    BOOL DVDEntrynumIsDir(s32 entrynum); //8015e58c
    BOOL DVDReadAsyncPrio(DVDFileInfo *fileInfo, void *buffer, s32 length, s32 offset, DVDCallback callback, s32 prio); //8015e74c
    s32  DVDReadPrio(DVDFileInfo *fileInfo, void *buffer, s32 length, s32 offset, s32 prio); //8015e834
    void DVDInit(); //8015ea1c
    s32 DVDReadAbsAsyncPrio(DVDFileInfo *handle, void *buffer, u32 size, u32 offset, DVDCallback callback, s32 prio); //801628cc
    s32 DVDInquiryAsync(DVDFileInfo *handle, void *buffer, char *company); //801629b0
    s32 DVDGetCommandBlockStatus(const DVDCommandBlock *block); //80162a88
    s32 DVDGetDriveStatus(); //80162b50
    BOOL DVDSetAutoInvalidation(BOOL autoInval); //80162bec
    void DVDPause(); //80162bfc
    void DVDResume(); //80162c38
    BOOL DVDCancelAsync(DVDCommandBlock *block, DVDCBCallback callback); //80162c88
    s32 DVDCancel(DVDCommandBlock *block); //80162fec
    s32 DVDCancelAll(); //801630d0
    DVDDiskID *DVDGetCurrentDiskID(); //8016321c
    BOOL DVDCompareDiskID(const DVDDiskID *id1, const DVDDiskID *id2); //8016411c
    DVDDiskID *DVDGenerateDiskID(DVDDiskID *id, const char *game, const char *company, u8 diskNum, u8 version); //8016420c
    BOOL DVDSetAutoFatalMessaging(BOOL enable); //80164364
}
#endif