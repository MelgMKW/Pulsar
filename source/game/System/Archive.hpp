#ifndef _ARCHIVE_
#define _ARCHIVE_
#include <kamek.hpp>
#include <core/nw4r/lyt/ArcResourceAccessor.hpp>
#include <core/egg/mem/ExpHeap.hpp>
#include <core/egg/Archive.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/egg/Thread.hpp>
#include <game/System/identifiers.hpp>
class LayoutResources;

class ArchiveFile {
public:
    //Load functions will also mount the file
    ArchiveFile(); //80518cc0
    virtual ~ArchiveFile(); //80518cf4 vtable 808b2c78
    void Dump(const char *path, EGG::Heap *heap, s32 allocDirection); //805190f0 will also decompress
    void Mount(EGG::Heap *heap); //80518dcc inlined in load
    void DecompressAndMount(void *compressedArchive, u32 compressedSize, EGG::Heap *decompressHeap, bool isCompressed); //80518fbc
    void Load(const char *path, EGG::Heap *decompressedHeap, bool isCompressed, s32 allocDirection,
        EGG::Heap *archiveHeap, EGG::Archive::FileInfo *info); //80518e10
    void LoadUncompressed(const char *path, u32 r5, EGG::Heap *heap); //80518fa4
    //decompressed used for archive if archive == null size set by func
    void Decompress(const char *path, EGG::Heap *heap); //80519508 r4 unused
    void *GetFile(const char *path, u32 *size); //80519420
    void Unmount(); //805192cc
    EGG::Archive *archive; //4
    void *decompressedArchive; //0x8
    u32 decompressedarchiveSize; //0xc
    EGG::Heap *decompressedArchiveHeap; //0x10
    void *rawArchive; //0x14
    u32 archiveSize; //0x18
    EGG::Heap *archiveHeap;
    u32 status; //0x20 2 loaded 3 decompressed 4 mounted
};//total size 0x24
size_assert(ArchiveFile, 0x24);

enum ArchiveSource {
    ARCHIVE_HOLDER_COMMON = 0x0, //common.szs
    ARCHIVE_HOLDER_COURSE = 0x1, //beginner_course
    ARCHIVE_HOLDER_UI = 0x2, //title.szs
    ARCHIVE_HOLDER_FONT = 0x3, //font.szs
    ARCHIVE_HOLDER_EARTH = 0x4, //earth.szs
    ARCHIVE_HOLDER_MIIBODY = 0x5, //MiiBody.szs
    ARCHIVE_HOLDER_DRIVER = 0x6, //Driver.szs
    ARCHIVE_HOLDER_UNKNOWN_7 = 0x7,
    ARCHIVE_HOLDER_BACKMODEL = 0x8,
    ARCHIVE_HOLDER_KART = 0x9
};

class ArchivesHolder {
public:
    explicit ArchivesHolder(u16 archiveCount); //0x8052a538 vtable 
    static ArchivesHolder *CreateByType(ArchiveSource type); //8052a098
    virtual ~ArchivesHolder(); //8052a6dc vtable 808b31d8
    virtual void Reset(); //8052a648 sets extensions to .szs
    void LoadCompressedArchive(const char *fileName, EGG::Heap *decompressedHeap, EGG::Heap *archiveHeap, u32 *size); //8052a954 decompresses it
    void DumpArchive(char *fileName, EGG::Heap *heap); //8052ab6c fileName with or without extension depending on sourceType
    int GetLoadedArchivesCount() const; //8052ae08
    bool HasArchives(); //8052a800
    bool FileExists(const char *fileName); //8052a864
    void *GetFile(const char *fileName, u32 length); //8052a760 gets subfile from archive
    void Unmount(); //8052aa88
    ArchiveFile *archives; //size archive count
    u16 archiveCount; //0x8
    u8 padding[2];
    void *filePtr; //only used for sourceType 2 (sets the matching Archive ptr)
    char **archiveSuffixes; //0x10 appended to the name .szs, _E.szs, _Dif.szs etc...
    u32 *fileSizes; //only used for sourceType 2
    u32 *sourceType; //0x18 name => 0 = file.extension 1 = file 2 = idk
};//total size 0x1c
size_assert(ArchivesHolder, 0x1C);

class CommonArchivesLoader : public ArchivesHolder {
    //ctor inlined
    ~CommonArchivesLoader() override; //8052a4e0 vtable 808b31a8
    void Reset() override; //8052a3c0
};

class CourseArchivesHolder : public ArchivesHolder {
    CourseArchivesHolder(); //8052a1c8
    ~CourseArchivesHolder() override; //8052a430 vtable 808b31c8
    void Reset() override; //8052a21c
};
class UIArchivesHolder : public ArchivesHolder {
    //ctor inlined
    ~UIArchivesHolder() override; //8052a488 vtable 808b31b8
    void Reset() override; //8052a2fc
};


class ArchiveLoadHandle {
    ArchivesHolder *ArchivesHolder;
    u8 unknown_0x4[0xc - 0x4];
    char archivePath[0x40];
    EGG::Heap *heap; //0x4c
    void *targetHeap;
}; //total size 0x54
size_assert(ArchiveLoadHandle, 0x54);

class AsyncCourseArchivesHolder : public EGG::Disposer {
    ~AsyncCourseArchivesHolder() override; //80541ac4 vtable 808b3c20
    void LoadCourseArchive(CourseId id); //80541b58
    void *startAddress;
    EGG::ExpHeap *heap; //0x14
    CourseId id;
    u32 status; //2 means loaded
    CourseArchivesHolder *courseArchivesHolder;
}; //0x24
size_assert(AsyncCourseArchivesHolder, 0x24);

class KartArchivesHolder {
    KartArchivesHolder(); //8053fe68
    virtual ~KartArchivesHolder(); //8053fe94 vtable 808b3c08
    EGG::Heap *decompressedHeap;
    EGG::Heap *compressedHeap;
    u8 unknown_0xC[0xf - 0xC];
    bool hasRequest;
    CharacterId id;
    u32 mode; //0 battle 2 otherwise
}; //total size 0x18
size_assert(KartArchivesHolder, 0x18);

class ArchiveRoot {
public:
    ArchiveRoot(); //0x8053fcec
    static ArchiveRoot *sInstance; //809bd738
    static ArchiveRoot *GetStaticInstance(); //8053fc4c
    static void DestroyStaticInstance(); //8053fc9c
    virtual ~ArchiveRoot(); //8053ff1c vtable 808b3bfc
    ArchivesHolder *LoadArchive(ArchiveSource type, EGG::Heap *heap, const char *name = NULL); //80540450 
    //if name = NULL, it is obtained via the type
    void WaitForLoad(); //805400a0
    void RequestLoadKartModels(u8 hudSlotId, CharacterId character, u32 r6); //r6 0 if battle 2 otherwise
    void RequestLoadCourseAsync(CourseId id); //805419ac
    ArchivesHolder *LoadContentArchive(u8 id, EGG::Heap *heap); //80540558
    UIArchivesHolder *LoadUIArchive(const char *path, EGG::Heap *heap); //80540680
    CourseArchivesHolder *LoadCourseArchive(CourseId id, EGG::Heap *heap, bool isMultiplayer); //80540760
    ArchivesHolder *LoadKartModel(u8 playerId, KartId kart, CharacterId character, u32 mode, u32 playerType, EGG::Heap *heap); //80540e3c
    static void LoadKartModelsAsync(u8 hudSlotId); //80541e44
    static void LoadArchiveAsync(u32 handleId); //80540038 request it as a task, can be done sync if waitforload is called after request
    void ExecuteTask(EGG::TaskThread::TaskFunction function, void *args); //80541c48
    static void LoadCourseArchiveAsync(CourseId id); //80541998
    void *GetFile(ArchiveSource type, const char *name, u32 length); //805411fc
    void *GetFileFromKartArchives(u8 idx, const char *name, u32 length); //805413c8
    int GetUIArchiveCount() const; //80541794
    void AttachLayoutDIR(nw4r::lyt::MultiArcResourceAccessor *resourceAccessor, const char *dir, LayoutResources *resources); //80541878
    void Unmount(ArchivesHolder *holder); //805411e4
    void ProcessRequestsAndShutdown(); //80541ce0 Waits for all requests to finish then shuts down (bool isFree set to false)

    ArchivesHolder **archivesHolders; //0x4 use enum for array idx
    ArchivesHolder kartModelsHolders[12]; //0x8 mr-allkart.szs, mdf_kart-mr.szs etc... in races
    ArchivesHolder unknown_Holders[12]; //0x158
    ArchiveFile contentArchives[4]; //0x2a8 contents/HomeButton.arc e.g.
    ArchiveLoadHandle loadHandles[7]; //0x338 use enum 6 contents
    EGG::TaskThread *taskThread; //0x584
    AsyncCourseArchivesHolder asyncCourseLoader; //0x588 80541ac4 vtable 808b3c20
    KartArchivesHolder kartsModelsLoaders[4]; //0x5ac kart models one per hudslotid in menus
    u8 unknown_0x60c;
    bool sceneIsExiting;
    u8 padding[2];
    EGG::Heap *heap_0x610;
    u8 unknown_0x614[4];
    bool hasRequest; //0x618
    bool isFree; //0x619
    u8 padding2[2];
}; //total size 0x61C
size_assert(ArchiveRoot, 0x61c);
#endif