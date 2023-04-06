#ifndef _ARC_
#define _ARC_
#include <types.hpp>

//https://github.com/sepalani/MHTrIDA/blob/master/server/tcp/p8200/RMHP08.rso.map
struct ARCHeader { //https://wiki.tockdom.com/wiki/U8_(File_Format)
    u32 Magic;
    u32 nodeOffset;
    u32 combinedNodeSize;
    u32 fileOffset;
    u32 reserved[4];
}; //total size 0x20

struct ARCNode {
    u32 isFolder : 4;
    u32 nameOffset : 24;
    union {
        u32 fileOffset;
        u32 fileSize;
    }file;
    union {
        u32 parent;
        u32 sibling_next;
    } folder;
}; //total size 0xc

struct ARCHandle {
    ARCHeader *header;
    ARCNode *nodes;
    void *rawFile;
    u32 entryNum;
    char *fstStringPtr;
    u32 fstSize;
    u32 curDir;
}; //total size 0x1c

struct ARCFileInfo {
    ARCHandle *handle;
    u32 startOffset;
    u32 length;
};

struct ARCDir {
    ARCHandle *handle;
    u32 entryNum;
    u32 location;
    u32 next;
};

struct ARCDirEntry {
    ARCHandle *handle;
    u32 entryNum;
    BOOL isDir;
    char *name;
};

extern "C" {
    BOOL ArcInitHandle(void *arcStart, ARCHandle *handle); //80124500
    BOOL ARCOpen(ARCHandle *handle, const char *fileName, ARCFileInfo *fileInfo); //801245a0
    BOOL ARCFastOpen(ARCHandle *handle, s32 entrynum, ARCFileInfo *fileInfo); //80124844
    s32 ARCConvertPathToEntrynum(ARCHandle *handle, const char *pathPtr); //80124894
    BOOL ARCEntrynumIsDir(const ARCHandle *handle, s32 entrynum); //80124af8
    void *ARCGetStartAddrInMem(ARCFileInfo *fileInfo); //80124cc0
    u32 ARCGetStartOffset(ARCFileInfo *fileInfo); //80124cd4
    u32 ARCGetLength(ARCFileInfo *fileInfo); //80124cdc
    BOOL ARCClose(ARCFileInfo *fileInfo); //80124ce4
    BOOL ARCChangeDir(ARCHandle *handle, const char *dirName); //80124cec
    BOOL ARCOpenDir(ARCHandle *handle, const char *dirName, ARCDir *dir); //80124d44
    BOOL ARCReadDir(ARCDir *dir, ARCDirEntry *dirent); //80124dc0
    BOOL ARCCloseDir(ARCDir *dir); //80124e78
}

#endif