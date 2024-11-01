#ifndef _CHANNELINSTALLER_
#define _CHANNELINSTALLER_
#include <kamek.hpp>
#include <core/rvl/os/OSTitle.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/egg/mem/Heap.hpp>

struct WadListEntry {
    u16 fsBlock;
    u16 inode;
};

struct WadList {
    u32 magic; //RKWD
    u16 entryCount;
    u16 unknown_0x6; //padding?
    WadListEntry entries[1];
};

class WadListHolder {
public:
    virtual ~WadListHolder(); //80510a50 vtable 808b2c04
    WadList* wadList;
};


//This is obviously used to install the MKChannel, but this is also how the game launches "HALP", the "Region Select" channel, it corresponds to idx 3 (see 8088f720)
class CINS { //official name? "channel installer"
public:
    enum ChannelErrCode {
        IS_INSTALLED,
        NOT_INSTALLED = 1,
        SYS_INSSPACE,
        SYS_INSINODE,
        SYS_INSCHAN,
        INVALIDPARAMS, //the wadidx led to invalid OS::CheckInstall args
    };
    static CINS* sInstance; //809bd6e0
    static CINS* CreateInstance(); //80510468
    static CINS* DestroyInstance(); //805104dc

    void Init(EGG::Heap* heap); //80510510
    void ReportInstallStatus(u32 wadIdx); //805106b0 only 0 works since the used list only has 1 entry, but the struct has support for 0-3
    bool GetReqSizeAndInode(u32 wadIdx, u16* reqSize, u16* inode) const; //80510670
    void InstallChannel(u32 wadIdx, u32 launchCodeIdx); //805107d0
    void LaunchTitleOrDisk(u32 wadIdx, u32 launchCodeIdx, const char* arg0); //8051088c

    EGG::TDisposer<CINS> disposer; //vtable 808b2c10 func 805103d0
    virtual ~CINS(); //0x10 805105d4
    WadListHolder* wadListHolder;
    DVD::DiskID dvdDiskID; //0x18 for LaunchTitleOrDisk
    u8 unknown_0x18[0x68 - 0x38];
    ChannelErrCode titleErrCodes[4]; //0x68
    u8 unknown_0x78[4];

    static const char** company; //808b2bf0 "01"
    static const char** wadListName; //808b2bf4
    static OS::InstallInfo installInfo; //808b2bd0
}; //0x7c


#endif