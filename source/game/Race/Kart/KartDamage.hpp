
#ifndef _KARTDAMAGE_
#define _KARTDAMAGE_
//Formerly PlayerSub14
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
#include <game/Race/Kart/KartBase.hpp>

class KartPointers;


class KartDamage {
public:
    KartDamage(); //805672cc
    ~KartDamage(); //8056a1a8
    void UpdateCollisionEffect(); //805673b0
    void UpdateCollisionSpeed(); //80567ce4
    void RemoteDestroy();
    KartBase base;
    virtual void Func_vtable1(); //0xC vtable 0x808B5008
    virtual void Update(DamageType newDamage, UnkType r5, int r6, u32 r7, u32  r8, u32 r9); //805675dc
    float unknown_0x10[3];
    DamageType currentDamage;
    u8 unknown_0x20[0x100 - 0x20];
}; //Total size 0x100

#endif