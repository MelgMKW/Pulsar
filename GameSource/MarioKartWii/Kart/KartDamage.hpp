
#ifndef _KARTDAMAGE_
#define _KARTDAMAGE_
//Formerly PlayerSub14
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/Kart/KartLink.hpp>

namespace Kart {

class Damage {
public:
    Damage(); //805672cc

    void Reset(); //8056739c
    void UpdateCurDamage(); //805673b0
    void UpdateCurDamageSpeed(); //80567ce4
    void RemoteDestroy();
    void ApplyKnockback(u32 type, float displacementX, float displacementY, float displacementZ,
        float spinCount); //80568794 type: 0 = forwards, 1 = backwards, 2 = sideways; spinCount * 360 = spinOutRot

    //These DO NOT include the loss of control, they ONLY include movement + effects + sound + held/trailed items consequences
    void ApplyBananaDamage(u32 playerIdxItemPlayerSub); //80567f68
    void ApplyGoombaDamage(u32 playerIdxItemPlayerSub); //80567fb4
    void ApplyShellFIBDamage(u32 playerIdxItemPlayerSub); //8056865c
    void ApplyStarDamage(u32 playerIdxItemPlayerSub); //80568718
    void ApplyChompDamage(u32 playerIdxItemPlayerSub); //80568cb8
    void ApplyCarDamage(u32 playerIdxItemPlayerSub); //80568fa4
    void ApplyBulletDamage(u32 playerIdxItemPlayerSub); //80569024
    void ApplyLaunchDamage(u32 playerIdxItemPlayerSub); //805690a0 explosions + cataquack
    void ApplyFireDamage(u32 playerIdxItemPlayerSub); //80568000
    void ApplyShockDamage(u32 playerIdxItemPlayerSub); //8056804c + TC
    void ApplyPOWDamage(u32 playerIdxItemPlayerSub); //80568064
    void ApplyThwompDamage(u32 playerIdxItemPlayerSub); //80569774
    void ApplyMegaDamage(u32 playerIdxItemPlayerSub); //80569818
    void ApplyCarSquishDamage(u32 playerIdxItemPlayerSub); //80569978
    void ApplyZapperDamage(u32 playerIdxItemPlayerSub); //80568058
    void ApplySquishRespawnDamage(u32 playerIdxItemPlayerSub); //805698bc

    void UpdateSpinOutdamage(); //80568204 Banana Goomba Fire Shock Zapper TC
    void UpdateKnockbackDamage(); //80568aa8 Shell FIB Star Car
    void UpdateBigKnockbackDamage(); //80568d34 Chomp Bullet
    void UpdateLaunchDamage(); //805692b4
    void UpdatePOWDamage(); //805683b8
    void UpdateSquishDamage(); //80569a1c thwomp mega squish respawn

    void OnSpinOutDamageEnd(bool resetRot); //8056837c
    void OnShellFIBDamageEnd(bool resetRot); //805686dc
    void OnStarCarDamageEnd(bool resetRot); //80568c7c
    void OnBigKnockbackDamageEnd(bool resetRot); //80568f68
    void OnLaunchDamageEnd(bool resetRot); //805696c8
    void OnPOWDamageEnd(bool resetRot); //80568620
    void OnSquishDamageEnd(bool resetRot); //80569ad0

    Link link;

    virtual ~Damage(); //8056a1a8 vtable 808B5008
    virtual bool SetDamage(DamageType newDamage, u32, bool affectsMegas, DamageType* appliedDamage,
        u32 playerIdxItemPlayerSub, u32); //805675dc r5/r9 unused
    virtual void vf_0x10(); //0x10 80568558
    virtual void vf_0x14(); //0x14 8056a164
    virtual void ApplyDrivingDirKnockback(); //0x18 80569ae8
    virtual void ApplySidewaysKnockback(); //0x1c 80569b94

    float unknown_0x10[3];
    DamageType currentDamage; //0x1c
    u8 unknown_0x20[8];
    float unknown_0x28;
    float totalDamageRot; //0x2c
    u8 unknown_0x30[0x8c - 0x30];
    Ptmf_1A<Damage, void, u32> damageEffectApplier; //0x8c
    Ptmf_0A<Damage, bool> curDamageUpdater; //0x98 returns true when damage is done
    Ptmf_1A<Damage, void, bool> onCurDamageEndHandler; //0xa4 for example stuff like reset the rotation of the kart
    u8 unknown_0xb0[0x10];
    float* onHitSpeedMultiplier; //0xc0
    u32 curDamageCounter; //0xc4
    u8 unknown_0xc8[0xe8 - 0xc8];
    Vec3 up; //0xe8
    u8 unknown_0xf4[0x100 - 0xf4];
}; //Total size 0x100

}//namespace kart

#endif