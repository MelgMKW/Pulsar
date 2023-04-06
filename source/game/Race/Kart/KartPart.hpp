#ifndef _KARTPART_
#define _KARTPART_
#include <kamek.hpp>
#include <game/Race/Kart/KartParams.hpp>
#include <game/Race/Kart/KartBase.hpp>

class KartPart {
public:
    KartPart(KartValues *kartParams, u32 unknown); //80592848
    KartBase base;
    virtual ~KartPart(); //0xc 8056c0cc vtable 808b6450

    Vec3 unknown_0x10;
    Mtx34 unknown_0x1c;
    Mtx34 unknown_0x4c;
    u8 unknown_0x7c[0x8c - 0x7c];
}; //Total size 0x8c

#endif