#ifndef _ARCHIVEMGR_
#define _ARCHIVEMGR_
#include <kamek.hpp>
#include <core/nw4r/lyt/ArcResourceAccessor.hpp>
#include <core/nw4r/g3d/res/ResFile.hpp>
#include <MarioKartWii/Archive/ArchiveHolder.hpp>

class LayoutResources;
class LayoutResourceLink;
class RKG;
class BSP;

class ArchiveLoadHandle { //+0x338
public:
    ArchivesHolder* holder;
    ArchiveFile* file;
    u8 unknown_0x8[0xc - 0x8];
    char archivePath[0x40]; //0x10
    EGG::Heap* mountHeap; //0x4c
    EGG::Heap* dumpHeap; //0x50
}; //total size 0x54
size_assert(ArchiveLoadHandle, 0x54);

class AsyncCourseArchiveLoader : public EGG::Disposer { //+0x588
    AsyncCourseArchiveLoader(); //80541a10
    ~AsyncCourseArchiveLoader() override; //80541ac4 vtable 808b3c20
    void Init(); //80541a70
    void Load(CourseId id); //80541b58
    void CopyToHolder(ArchivesHolder* dest, EGG::Heap* heap); //80541c18

    void* startAddress;
    EGG::ExpHeap* heap; //0x14
    CourseId id;
    u32 status; //0x1c 2 means loaded
    CourseArchivesHolder* courseArchivesHolder; //0x20
}; //0x24
size_assert(AsyncCourseArchiveLoader, 0x24);

class AllkartArchivesLoader {
    enum State {
        ALLKARTARCHIVES_HASREQUEST,
        ALLKARTARCHIVES_ABOUTTOLOAD = 1,
        ALLKARTARCHIVES_ISLOADING = 3,
        ALLKARTARCHIVES_HASLOADED = 4
    };
    AllkartArchivesLoader(); //8053fe68
    virtual ~AllkartArchivesLoader(); //8053fe94 vtable 808b3c08
    EGG::Heap* mountHeap; //0x4
    EGG::Heap* dumpHeap; //0x8
    State state; //0xC
    CharacterId id;
    u32 mode; //0 battle 2 otherwise
}; //total size 0x18
size_assert(AllkartArchivesLoader, 0x18);


class ArchiveMgr {
public:
    ArchiveMgr(); //8053fcec
    static ArchiveMgr* sInstance; //809bd738
    static ArchiveMgr* CreateInstance(); //8053fc4c
    static void DestroyInstance(); //8053fc9c
    virtual ~ArchiveMgr(); //8053ff1c vtable 808b3bfc
    void WaitForLoad(); //805400a0
    /*Idx:
    0-4 -> ArchiveHolder::LoadCompressed, uses same heap to dump and decompress
    5 -> ArchiveHolder::LoadCompressed, uses different heap to dump and decompress, therefore the former has to be specified by w/e requests
    6 -> ArchiveFile::LoadUncompressed, that means the handle has to have an archive file set
    */
    static void LoadArchiveAsync(u8 handleIdx); //80540038 can be done sync if waitforload is called after TaskThread::Request
    void LoadArchive(u8 handleIdx, ArchivesHolder& holder, const char* name, EGG::Heap* heap); //8054020c
    void LoadArchive(u8 handleIdx, ArchiveFile& file, const char* name, u32 r7, EGG::Heap* heap); //805402c0
    void LoadArchive(u8 handleIdx, ArchivesHolder& holder, const char* name, EGG::Heap* decompressedHeap, EGG::Heap* archiveHeap); //80540394
    ArchivesHolder* LoadArchive(ArchiveSource type, EGG::Heap* heap, const char* name = nullptr); //80540450 if name is nullptr, obtained via the type
    ArchivesHolder* LoadContentArchive(u8 id, EGG::Heap* heap); //80540558
    UIArchivesHolder* LoadUIArchive(const char* path, EGG::Heap* heap); //80540680
    CourseArchivesHolder* LoadCourseArchive(CourseId id, EGG::Heap* heap, bool isMultiplayer); //80540760
    CourseArchivesHolder* LoadCompetitionArchives(CourseId id, u32 fileSize, void* filePtr, EGG::Heap* heap, u32 objIdx);//80540b14
    ArchivesHolder* LoadKartArchive(ArchivesHolder* holder, u32 r5, KartId kart, CharacterId character,
        bool isBike, u32 type, EGG::Heap* heap); //80540cfc base, unused, multiplayer for type
    ArchivesHolder* LoadKartArchive(u8 playerId, KartId kart, CharacterId character, u32 color, u32 type,
        EGG::Heap* decompressedHeap, EGG::Heap* archiveHeap); //80540e3c color: 0 red, 1 blue, 2 nothing, type same as above
    ArchivesHolder* LoadKartArchiveHolder2(u8 playerId, KartId kart, CharacterId character, u32 color, u32 type,
        EGG::Heap* decompressedHeap, EGG::Heap* archiveHeap); //80540f90 users 2nd array
    ArchivesHolder* LoadMenuKartArchive(u8 playerId, KartId kart, u32 type, EGG::Heap* archiveHeap, EGG::Heap* dumpHeap); //805410e4
    void Unmount(ArchiveSource source); //805411d4
    void Unmount(ArchivesHolder* holder); //805411e4
    void UnmountContentArchive(u8 contentIdx); //805411ec
    void* GetFile(ArchiveSource type, const char* name, u32* size = nullptr) const; //805411fc
    nw4r::g3d::ResFile GetMenuKartBRRES(KartId kart, u32* size = nullptr) const; //80541278 DO NOT CALL, HAS A BAD SNPRINTF
    nw4r::g3d::ResFile GetKartBRRES(u8 playerId, KartId kart, u32* size = nullptr) const; //80541320 SAME
    void* GetKartArchiveFile(u8 playerId, const char* name, u32* size = nullptr) const; //805413c8
    void* GetKartArchiveFileHolder2(u8 playerId, const char* name, u32* size = nullptr) const; //80541438 uses 2nd array
    BSP* GetBSP(u8 playerId) const; //805414a8
    void* GetContentFileNewBuffer(u8 idx, const char* path, EGG::Heap* heap, u32* size, s8 alignment) const; //8054155c
    bool HasArchives(ArchiveSource source) const; //805415b4
    bool HasKartArchive(u8 playerId) const; //805415c4
    bool HasKartArchiveHolder2(u8 playerId) const; //805415d4
    bool HasContentArchive(u8 idx); //805415e4
    void* GetArchive(ArchiveSource source, u32 archiveIdx) const; //80541614 returns ArchiveHolder[source]->file[archiveIdx]->decompressedArchive
    bool SetLayoutResources(ArchiveSource source, u16 archiveCount, LayoutResourceLink& link, const char* dir) const; //8054169c unused
    int GetArchiveCount(ArchiveSource source) const; //80541738
    int GetUIArchiveCount() const; //80541794
    void AttachUIAccessor(nw4r::lyt::ArcResourceAccessor& resourceAccessor,
        const char* dir) const; //805417a4 attaches to UI archives in mgr
    void AttachLayoutResources(nw4r::lyt::MultiArcResourceAccessor& resourceAccessor,
        const char* dir, LayoutResources& resources) const; //80541878
    static void LoadCourseArchiveAsync(CourseId id); //80541998
    void RequestLoadCourseAsync(CourseId id); //805419ac
    static const char* GetKartArchivePostfix(CharacterId character); //805419c8 fk part of labike_fk
    static const char* GetKartArchivePrefix(KartId id); //805419ec labike part of labike_fk
    bool ExecuteTask(EGG::TaskThread::TaskFunction function, void* args); //80541c48
    bool RequestTask(EGG::TaskThread::TaskFunction function, void* args, u32 r6); //80541cbc
    void ProcessRequestsAndShutdown(); //80541ce0 Waits for all requests to finish then shuts down (bool isFree set to false)
    static void LoadKartArchiveAsync(u8 hudSlotId); //80541e44
    void RequestLoadKartArchives(u8 hudSlotId, CharacterId character, u32 gamemode); //80542210 gamemode 0 for vs, 2 for battle
    void InitAllkartArchivesLoaders(u32 localPlayerCount, u8 sceneHeapIdx); //805422cc
    void ResetAllkartArchivesLoaders(); //805423bc
    EGG::Heap* GetKartLoaderHeap(u8 hudSlotId) const; //8054247c
    nw4r::g3d::ResFile& LoadEarthBrres(EGG::Heap* heap); //8054247c loads the file into specified heap
    void CreateEarthHeap(u32 size, EGG::Heap* srcHeap = nullptr); //80542524 will use cur gamescene heap if srcHeap is nullptr
    void DestroyEarthHeap(); //80542584
    static void LoadEarthBrresAsync(nw4r::g3d::ResFile& dest); //805425d0 performs LZ decomp of the file
    void LoadEarthBrres(nw4r::g3d::ResFile& dest); //80542694 same as above
    void RequestLoadEarthBrres(nw4r::g3d::ResFile& dest); //80542754
    static void LoadStaffGhostAsync(u32 type, CourseId id, RKG& dest); //805427bc type 2 -> easy else expert



    ArchivesHolder** archivesHolders; //0x4 use enum for array idx
    ArchivesHolder kartModelsHolders[12]; //0x8 mr-allkart.szs, mdf_kart-mr.szs etc... in races
    ArchivesHolder kartModelsHolders2[12]; //0x158
    ArchiveFile contentArchives[4]; //0x2a8 contents/HomeButton.arc e.g.
    ArchiveLoadHandle loadHandles[7]; //0x338 use enum 6 contents
    EGG::TaskThread* taskThread; //0x584
    AsyncCourseArchiveLoader asyncCourseLoader; //0x588 80541ac4 vtable 808b3c20
    AllkartArchivesLoader allkartsModelsLoaders[4]; //0x5ac allkart szs one per hudslotid in menus
    bool isBusyDecompressingEarth; //0x60c
    bool sceneIsExiting; //0x60d
    u8 padding[2];
    EGG::Heap* allkartModelDumpHeap; //0x610
    EGG::Heap* earthBrresHeap; //0x614
    bool hasRequest; //0x618
    bool isFree; //0x619
    u8 padding2[2];
}; //total size 0x61C
size_assert(ArchiveMgr, 0x61c);
#endif