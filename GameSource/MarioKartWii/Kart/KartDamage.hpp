
#ifndef _KARTDAMAGE_
#define _KARTDAMAGE_
//Formerly PlayerSub14
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/Kart/KartLink.hpp>

namespace Kart {

//_sinit_ at 8056a228
struct POWParams {
    bool isPOWSmashing;
    u16 smashDuration;
    u8 powState; //POWMgr state -1 mostly
};

class Damage : public Link { //PlayerObjIdx set to 0xC if the damage shouldn't lead to item loss
public:
    enum SpinType {
        SPIN_TYPE_ONLY_SOUND_AND_ITEMLOSS,
        SPIN_TYPE_SHORT,
        SPIN_TYPE_MEDIUM,
        SPIN_TYPE_LONG,
    };
    static POWParams powParams; //809c1898

    Damage(); //805672cc

    void Reset(); //8056739c
    void Update(); //805673b0 updates the current dmg etc...


    void SetAffectedByPOW(bool isAffected); //805674f4
    void SetPOWParams(u8 powState); //805674fc
    static void SetPOWParamsStatic(u8 powState); //80567524
    bool ShouldReceivePOWDamage(); //8056754c
    static void ResetPOWParams(); //80567578
    static void UpdatePOWParams(); //80567594

    bool UpdateCurDamage(); //80567a54 inlined
    void EndCurDamage(bool resetRot); //80567a88 inlined, but can be called

    //void RemoteDestroy();
    void UpdateCurDamageSpeed(); //80567ce4
    void ApplySpinDamage(u32 spinType, u32 playerObjIdx); //80567d3c also plays the sound etc...
    void ApplyKnockback(SpinType type, float displacementX, float displacementY, float displacementZ,
        float spinCount); //80568794 type: 0 = forwards, 1 = backwards, 2 = sideways; spinCount * 360 = spinOutRot

    //These DO NOT include the loss of control, they ONLY include movement + effects + sound + held/trailed items consequences
    void ApplyBananaDamage(u32 playerObjIdx); //80567f68
    void ApplyGoombaDamage(u32 playerObjIdx); //80567fb4
    void ApplyShellFIBDamage(u32 playerObjIdx); //8056865c
    void ApplyStarDamage(u32 playerObjIdx); //80568718
    void ApplyChompDamage(u32 playerObjIdx); //80568cb8
    void ApplyCarDamage(u32 playerObjIdx); //80568fa4
    void ApplyBulletDamage(u32 playerObjIdx); //80569024
    void ApplyLaunchDamage(u32 playerObjIdx); //805690a0 explosions + cataquack
    void ApplyFireDamage(u32 playerObjIdx); //80568000
    void ApplyShockDamage(u32 playerObjIdx); //8056804c + TC
    void ApplyPOWDamage(u32 playerObjIdx); //80568064
    void ApplyThwompDamage(u32 playerObjIdx); //80569774
    void ApplyMegaDamage(u32 playerObjIdx); //80569818
    void ApplyCarSquishDamage(u32 playerObjIdx); //80569978
    void ApplyZapperDamage(u32 playerObjIdx); //80568058
    void ApplySquishRespawnDamage(u32 playerObjIdx); //805698bc

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

    virtual ~Damage(); //8056a1a8 vtable 808B5008
    virtual bool SetDamage(DamageType newDamage, u32, bool affectsMegas, DamageType* appliedDamage,
        u32 playerObjIdx, u32); //805675dc r5/r9 unused
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
    u8 unknown_0xf4[4];
    bool isAffectedByCurrentPOW; //0xf8
    u8 padding[3];
    u8 unknown_0xfc[4];
}; //Total size 0x100

}//namespace kart

#endif