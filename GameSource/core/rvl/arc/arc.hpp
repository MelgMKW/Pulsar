#ifndef _ARC_
#define _ARC_
#include <types.hpp>

namespace ARC {
//https://github.com/sepalani/MHTrIDA/blob/master/server/tcp/p8200/RMHP08.rso.map
struct Header { //https://wiki.tockdom.com/wiki/U8_(File_Format)
    u32 Magic;
    u32 nodeOffset;
    u32 combinedNodeSize;
    u32 fileOffset;
    u32 reserved[4];
}; //total size 0x20

struct Node {
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

struct Handle {
    Header* header;
    Node* nodes;
    void* rawFile;
    u32 entryNum;
    char* fstStringPtr;
    u32 fstSize;
    u32 curDir;
}; //total size 0x1c

struct FileInfo {
    Handle* handle;
    u32 startOffset;
    u32 length;
};

struct Dir {
    Handle* handle;
    u32 entryNum;
    u32 location;
    u32 next;
};

struct DirEntry {
    Handle* handle;
    u32 entryNum;
    BOOL isDir;
    char* name;
};

BOOL InitHandle(void* Start, Handle* handle); //80124500
BOOL Open(Handle* handle, const char* fileName, FileInfo* fileInfo); //801245a0
BOOL FastOpen(Handle* handle, s32 entrynum, FileInfo* fileInfo); //80124844
s32 ConvertPathToEntrynum(Handle* handle, const char* pathPtr); //80124894
BOOL EntrynumIsDir(const Handle* handle, s32 entrynum); //80124af8
void* GetStartAddrInMem(FileInfo* fileInfo); //80124cc0
u32 GetStartOffset(FileInfo* fileInfo); //80124cd4
u32 GetLength(FileInfo* fileInfo); //80124cdc
BOOL Close(FileInfo* fileInfo); //80124ce4
BOOL ChangeDir(Handle* handle, const char* dirName); //80124cec
BOOL OpenDir(Handle* handle, const char* dirName, Dir* dir); //80124d44
BOOL ReadDir(Dir* dir, DirEntry* dirent); //80124dc0
BOOL CloseDir(Dir* dir); //80124e78

}//namespace ARC

#endif