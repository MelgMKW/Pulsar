#ifndef _OSTITLE_
#define _OSTITLE_
#include <types.hpp>
#include <core/rvl/dvd/dvd.hpp>

//it's not namespaced in the actual game but this makes it more readable

namespace OS {

enum InstallReturn {
    OSINSTALL_RETURN_OK            = 0x00000000, // No error
    OSINSTALL_RETURN_INVALID       = 0x00000001, // Invalid parameters
    OSINSTALL_RETURN_INIT_FAILED   = 0x00000002, // Failed to initialize
    OSINSTALL_RETURN_NOEXISTS      = 0x00000004, // Wad file does not exist in disc
    OSINSTALL_RETURN_EXISTS        = 0x00000008, // All files are already installed
    OSINSTALL_RETURN_MAXBLOCKS     = 0x00000010, // Ran out of FS blocks
    OSINSTALL_RETURN_MAXFILES      = 0x00000020, // Ran out of inode entries 
    OSINSTALL_RETURN_MAXCHANNELS   = 0x00000040, // Ran out of channel entries
    OSINSTALL_RETURN_IMPORT_FAILED = 0x00000080, // Failed to import
    OSINSTALL_RETURN_UNKNOWN       = 0x40000000, // Uknown error
    OSINSTALL_RETURN_FATAL_ERROR   = 0x80000000 // Fatal error (never return to app)
};

enum InstallAnswer {
    OSINSTALL_CHECK_SYS_INSSPACE = 0x00000001,
    OSINSTALL_CHECK_SYS_INSINODE = 0x00000002,
    OSINSTALL_CHECK_SYS_INSCHAN  = 0x00000004,
};

struct InstallInfo {
    char* fileName;  //channel application's file name to install
    wchar_t* titleName; //channel application's title name to draw on screen
};

BOOL IsTitleInstalled(u64 titleId);
void __LaunchTitle(u32 launchCode, u32 titleID);
InstallReturn CheckInstall(u32 num, u32 fsBlock, u32 inode, InstallAnswer* answer); //801ad1d4
void LaunchInstaller(u32 launchCode, u16* gameTitleName, InstallInfo* info); //801a4828
void LaunchDiskl(DVD::DiskID* id, u32 LaunchCode, const char* arg0, .../*, (char*)NULL */); //801a3cec

}//namespace OS

#endif
