#ifndef _KAREHAYAMA_OBJECT_
#define _KAREHAYAMA_OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ItemDropper/ItemDropper.hpp>

namespace Objects {

class Karehayama : public ItemDropper { //ObjectNum 0x176 = 374
public:
    explicit Karehayama(const KMP::Holder<GOBJ>& gobjHolder); //80766f4c
    ~Karehayama() override; //80766f88 vtable 808ce020
    void OnStart() override; //80766fe0
    const char* GetBRRESName() const override; //0x34 8076784c
    const char* GetSubFileName() const override; //0x38 807678a0
    void LoadShadow() override; //0x50 80767704
    void LoadAnimations() override; //0x5c 807677ec
    void OnWallCollision(const Kart::Player& kartPlayer, Vec3 position) override; //0xc8 80767848

    void LoadEffects() override; //0xec 80767038
    void Respawn() override; //0xf4 80767250
    void DropItem(u8 playerId, const Vec3& speed) override; //0xf8 807672a4
    void CreateExplosionEffect() override; //0x100 8076724c just a blr
    void OnNormalCollision(const Kart::Player& kartPlayer) override; //0x104 8076734c
    void OnImperviousCollision(const Kart::Player& kartPlayer) override; //0x108 80767448
    void OnNormalItemCollision(const Kart::Player& kartPlayer, const Vec3& itemSpeed) override; //0x10c 8076757c
    void OnImperviousItemCollision(const Kart::Player& kartPlayer, const Vec3& itemSpeed) override; //0x110 80767648
    virtual int vf_0x114(); //0x114 80767840 
    virtual void CreateCollisionEffectSoft(); //0x118 80767114 leaves flying close to the ground, 1st effect
    virtual void CreateCollisionEffect(); //0x11c 807671dc leaves flying high to the ground, 2nd effect

    EGG::Effect* rk_karehayama; //0xc0 or S version
    EGG::Effect* rk_karehayama0; //0xc4
}; //0xc8

} //namespace Objects
#endif