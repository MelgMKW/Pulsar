#ifndef _ARCHIVEFILE_
#define _ARCHIVEFILE_
#include <kamek.hpp>
#include <core/egg/Archive.hpp>

enum ArchiveStatus {
    ARCHIVE_STATUS_NONE,
    ARCHIVE_STATUS_DUMPED = 2,
    ARCHIVE_STATUS_DECOMPRESSED,
    ARCHIVE_STATUS_MOUNTED
};

class ArchiveFile {
public:
    //Load functions will also mount the file
    ArchiveFile(); //80518cc0
    virtual ~ArchiveFile(); //80518cf4 vtable 808b2c78
    void Mount(EGG::Heap* heap); //80518dcc inlined in load
    void Load(const char* path, EGG::Heap* mountHeap, bool isCompressed, s32 allocDirection,
        EGG::Heap* dumpHeap = nullptr, EGG::Archive::FileInfo* info = nullptr); //80518e10 uses 1st heap if dumpHeap is nullptr
    void LoadUncompressed(const char* path, u32 r5, EGG::Heap* heap); //80518fa4 r5 unused
    //for example if the archive is included in static code
    void MountFromRawArchive(void* compressedArchive, u32 compressedSize, EGG::Heap* mountHeap, bool isCompressed); //80518fbc
    //useful if the archive is to be unmounted after
    void* GetFileNewBuffer(const char* path, EGG::Heap* heap, u32* size, s8 alignment) const; //80519040 
    void Dump(const char* path, EGG::Heap* heap, s32 allocDirection); //805190f0
    bool TryDump(const char* path, EGG::Heap* heap, s32 allocDirection); //805191a4 does not update status, inlined in Dump
    void ClearAll(); //80519240 WILL NOT UNMOUNT, mostly to be used after dumping
    void Unmount(); //805192cc also frees buffers
    void ClearArchive(); //80519370 WILL NOT UNMOUNT, only frees archive at 0x8
    void ClearDump(); //805193c8 WILL NOT UNMOUNT, only frees dump at 0x14
    void* GetFile(const char* path, u32* size) const; //80519420
    void Decompress(const char* path, EGG::Heap* heap, EGG::Archive::FileInfo* info = nullptr); //80519508 r4/r6 unused
    void SetDumpToDecompressed(); //805195a4 moves dump to archive and sets status to decompressed
    void MountFromRawArchive(const ArchiveFile& other, EGG::Heap* archiveHeap); //805195d8

    EGG::Archive* archive; //4
    void* rawArchive; //0x8
    u32 archiveSize; //0xc
    EGG::Heap* archiveHeap; //0x10
    /* freed when (if) the archive gets mounted; if just dumped they'll be set*/
    void* compressedArchive; //0x14
    u32 compressedArchiveSize; //0x18
    EGG::Heap* dumpHeap;
    ArchiveStatus status; //0x20
};//total size 0x24
size_assert(ArchiveFile, 0x24);
#endif