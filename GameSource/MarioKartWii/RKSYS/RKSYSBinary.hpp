#ifndef _RKSYS_
#define _RKSYS_
#include <kamek.hpp>
#include <MarioKartWii/RKSYS/RKPD.hpp>
#include <MarioKartWii/RKSYS/RKGD.hpp>
#include <MarioKartWii/File/RKG.hpp>

namespace RKSYS {
#pragma pack(push, 1)
struct Ghosts {
    RKG pbs[32]; //0
    RKG dldGhosts[32]; //0x50000
    RKG lastDLdGhostRace; //0xc8000
    RKG lastCompetitionGhost; //0xca800
}; //0xa5000
size_assert(Ghosts, 0xa5000);

struct Core {
    u32 magic; //RKSD 
    u32 version; //"0006"
    RKPD licenses[4]; //0x8
    RKGD globalData; //0x23308
    u8 unknown_0x26b0c[0x14f0]; //0x26b0c
    u32 crc32; //0x27ffc
};

struct Binary {
    Core core;
    Ghosts ghosts[4]; //0x28000
}; //0x2bc000
size_assert(Binary, 0x2bc000);
#pragma pack(pop)

}//namespace RKSYS

#endif