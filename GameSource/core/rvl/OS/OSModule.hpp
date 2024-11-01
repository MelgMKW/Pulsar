#ifndef _OSMODULE_
#define _OSMODULE_
#include <types.hpp>

namespace OS {
//https://wiki.tockdom.com/wiki/REL_(File_Format)
struct ModuleQueue {
    ModuleInfo* head;
    ModuleInfo* tail;
};

struct ModuleLink {
    ModuleInfo* next;
    ModuleInfo* prev;
};

struct ModuleInfo {
    u32 moduleId; //unique identifier for the module
    ModuleLink link; //doubly linked list of modules
    u32 numSections; //# of sections
    u32 sectionInfoOffset; //0x10 offset to section info table
    u32 nameOffset; //offset to module name
    u32 nameSize; //size of module name
    u32 version; //version number
};

struct ModuleHeader {
    ModuleInfo info;
    u32 bssSize; //0x20 total size of bss sections in bytes
    u32 relOffset;
    u32 impOffset;
    u32 impSize; //size in bytes
    u8 prologSection; //0x30 section # for prolog function
    u8 epilogSection; //section # for epilog function
    u8 unresolvedSection; //section # for unresolved function
    u8 bssSection; //section # for bss section (set at run-time)
    u32 prolog; //prolog function offset
    u32 epilog; //epilog function offset
    u32 unresolved; //unresolved function offset
    u32 align; //0x40 module alignment constraint
    u32 bssAlign; //bss alignment constraint
    u32 fixSize;

};

struct SectionInfo {
    u32 offset;
    u32 size;
};

struct ImportInfo {
    u32 moduleId; //external module id
    u32 offset; //offset to OSRel instructions
};

struct Rel
{
    u16 offset; //byte offset from the previous entry
    u8 type;
    u8 section;
    u32 addend;
};

BOOL Link(ModuleInfo* newModule, void* bss); //801a72dc

} //namespace OS
#endif