et#ifndef _ITEMBOX_
#define _ITEMBOX_
#include <kamek.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

class Itembox : public ObjectCollidable, public ObjectCycleManager { //0x65 = 101
    explicit Itembox(KMP::GOBJHolder *gobjHolder); //808285b0

    ~Itembox() override; //806c4f74 vtable 808d7bc0
    void Update() override; //0x14 80828860
    bool HasLod() override; //0x2c 806c69fc
    void LoadShadow() override; //0x50 806c69e8
    void UpdateModelMatrix() override; //0x6c 806c69e4
    void UpdateShadow() override; //0x70 806c6a84
    void UpdateModelScale() override; //0x78 806c69e0
    ObjToKartHit OnCollision(Kart *kart, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 80828cb8
    void OnWallCollision(Kart *kart, Vec3ZeroInit position) override; //0xc8 806c69dc
    bool IsSolid() const override; //806c69d4
    virtual bool IsActive() const; //806c69c0

    u32 isActive; //0xb0 set to 0 when the box is destroyed, set to 1 when it respawns/is created
    u32 timer; //0xb4 resets on player hit
    u32 respawnTime; //0xb8 based on setting 5
    u16 randomSeedMaybe; //0xBC random value 0-180
    u16 shadowSetting; //0xbe shadows disabled if set
    u8 unknown_0xc0[0xc8 - 0xc0];
}; //0xc8

}//namespace Objects



#endif