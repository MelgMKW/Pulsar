#ifndef _KMP_FORMAT_
#define _KMP_FORMAT_
#include <kamek.hpp>
#include <MarioKartWii/KMP/AREA.hpp>
#include <MarioKartWii/KMP/CAME.hpp>
#include <MarioKartWii/KMP/CKPH.hpp>
#include <MarioKartWii/KMP/CKPT.hpp>
#include <MarioKartWii/KMP/CNPT.hpp>
#include <MarioKartWii/KMP/ENPH.hpp>
#include <MarioKartWii/KMP/ENPT.hpp>
#include <MarioKartWii/KMP/GOBJ.hpp>
#include <MarioKartWii/KMP/ITPH.hpp>
#include <MarioKartWii/KMP/ITPT.hpp>
#include <MarioKartWii/KMP/JGPT.hpp>
#include <MarioKartWii/KMP/KTPT.hpp>
#include <MarioKartWii/KMP/MSPT.hpp>
#include <MarioKartWii/KMP/POTI.hpp>
#include <MarioKartWii/KMP/STGI.hpp>

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
    static const u32 kmpMagic = 'RKMD'; //'RKMD'
    char magic[4]; //RKMD
    u32 fileSize; //0x4
    u16 sectionCount; //0x8 15 in mkwii
    u16 headerSize; //0xa
    u32 versionNumber; //0xc
    u32 offsetToSections[1]; //0x10 use enum
    //Sections
}; //total size 0x4c


#endif