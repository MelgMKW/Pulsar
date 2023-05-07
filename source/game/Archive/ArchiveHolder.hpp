#ifndef _ARCHIVE_
#define _ARCHIVE_
#include <kamek.hpp>
#include <core/nw4r/lyt/ArcResourceAccessor.hpp>
#include <core/egg/mem/ExpHeap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/egg/Thread.hpp>
#include <game/System/identifiers.hpp>
#include <game/Archive/ArchiveFile.hpp>

class LayoutResources;

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

enum SourceType { //conditions what "suffixes" contains
    SOURCE_TYPE_SUFFIX, //means functions are called with a name to which the suffix (.szs _E.szs) is appended
    SOURCE_TYPE_FULLNAME, //means the name functions are called with is unused and instead the "suffixes" contain the names
    SOURCE_TYPE_FULLNAME_PRELOADED //same as above but the archives are already preloaded and just need a mount
};

class ArchivesHolder {
public:
    explicit ArchivesHolder(u16 archiveCount); //0x8052a538 vtable 
    static ArchivesHolder* CreateByType(ArchiveSource type); //8052a098
    virtual ~ArchivesHolder(); //8052a6dc vtable 808b31d8
    virtual void Reset(); //8052a648 sets extensions to .szs
    void* GetFile(const char* fileName, u32* size) const; //8052a760 gets subfile from archive
    bool HasArchives() const; //8052a800
    bool FileExists(const char* fileName) const; //8052a864
    void LoadArchives(const char* fileName, EGG::Heap* mountHeap, EGG::Heap* dumpHeap, u32* size = nullptr); //8052a954 decompresses
    void UnmountArchives(); //8052aa88 also frees buffers
    void LoadFromOther(const ArchivesHolder& other, EGG::Heap* heap); //8052aae8
    void DumpArchives(char* fileName, EGG::Heap* dumpHeap); //8052ab6c just dumps without 
    void ClearArchives(); //8052ac40
    int GetTotalMountedArchivesSize() const; //8052aca0
    void* GetFirstMountedArchive() const; //8052ad08 1st in terms of memory address which is very weird
    void* GetFirstMountedArchiveEnd() const; //8052ad80 same but returns the end of the block holding the archive
    int GetLoadedArchivesCount() const; //8052ae08

    ArchiveFile* archives; //0x4 size archive count
    u16 archiveCount; //0x8
    u8 padding[2];
    void* filePtr; //only used for sourceType 2 (sets the matching Archive ptr)
    char** archiveSuffixes; //0x10 appended to the name .szs, _E.szs, _Dif.szs etc...
    u32* fileSizes; //only used for sourceType 2
    SourceType* sourceType; //0x18 name => 0 = fileName.suffix 1 = suffix 2 = idk
};//total size 0x1c
size_assert(ArchivesHolder, 0x1C);

class CommonArchivesLoader: public ArchivesHolder {
    ~CommonArchivesLoader() override; //8052a4e0 vtable 808b31a8
    void Reset() override; //8052a3c0
};

class CourseArchivesHolder: public ArchivesHolder {
    CourseArchivesHolder(); //8052a1c8
    ~CourseArchivesHolder() override; //8052a430 vtable 808b31c8
    void Reset() override; //8052a21c
};
class UIArchivesHolder: public ArchivesHolder {
    ~UIArchivesHolder() override; //8052a488 vtable 808b31b8
    void Reset() override; //8052a2fc
};

#endif