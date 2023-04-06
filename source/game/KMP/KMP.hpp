#ifndef _KMP_FORMAT_
#define _KMP_FORMAT_
#include <kamek.hpp>
#include <game/KMP/AREA.hpp>
#include <game/KMP/CAME.hpp>
#include <game/KMP/CKPH.hpp>
#include <game/KMP/CKPT.hpp>
#include <game/KMP/CNPT.hpp>
#include <game/KMP/ENPH.hpp>
#include <game/KMP/ENPT.hpp>
#include <game/KMP/GOBJ.hpp>
#include <game/KMP/ITPH.hpp>
#include <game/KMP/ITPT.hpp>
#include <game/KMP/JGPT.hpp>
#include <game/KMP/KTPT.hpp>
#include <game/KMP/MSPT.hpp>
#include <game/KMP/POTI.hpp>
#include <game/KMP/STGI.hpp>

enum Sections {
    KMP_SECTION_KTPT,
    KMP_SECTION_ENPT,
    KMP_SECTION_ENPH,
    KMP_SECTION_ITPT,
    KMP_SECTION_ITPH,
    KMP_SECTION_CKPT,
    KMP_SECTION_CKPH,
    KMP_SECTION_GOBJ,
    KMP_SECTION_POTI,
    KMP_SECTION_AREA,
    KMP_SECTION_CAME,
    KMP_SECTION_JGPT,
    KMP_SECTION_CNPT,
    KMP_SECTION_MSPT,
    KMP_SECTION_STGI
};

struct KMPHeader {  //https://wiki.tockdom.com/wiki/KMP_(File_Format)
    char magic[4]; //RKMD
    u32 fileSize;
    u16 sectionCount; //15 in mkwii
    u16 headerSize;
    u32 versionNumber;
    u32 offsetToSectionArray; //0xC use enum
    //Sections
}; //total size 0x4c


#endif