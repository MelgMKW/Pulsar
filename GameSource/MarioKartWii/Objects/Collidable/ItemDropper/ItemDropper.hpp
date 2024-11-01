#ifndef _ITEMDROPPER_OBJECT_
#define _ITEMDROPPER_OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

class ItemDropper : public ObjectCollidable { //base for objects that can spawn an item like leaf piles (karehayama)
public:
    enum State {
        ITEM_DROPPER_UNINITIALIZED,
        ITEM_DROPPER_ACTIVE,
        ITEM_DROPPER_DESTROYED,
        ITEM_DROPPER_RESPAWNING,
    };
    explicit ItemDropper(const KMP::Holder<GOBJ>& gobjHolder); //8076ebe0
    ~ItemDropper() override; //8076ec28 vtable 808cf1b0
    void OnStart() override; //0xc 8076ec68
    void Update() override; //0x14 8076ed1c
    u32 GetPropertiesBitfield() override; //807677e4
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 8076f0ac
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) override; //0xc4 8076f1dc

    virtual void LoadEffects(); //0xec 8076ed18
    virtual void RespawnImpl(); //0xf0 8076ed70 
    virtual void Respawn(); //0xf4 8076edd4 wrapper around impl, but can be overriden to add stuff like animations
    virtual void DropItem(u8 playerId, const Vec3& speed); //0xf8 8076ede4
    virtual void UpdateRespawn(); //0xfc 807677e0 updates the respawning process
    virtual void CreateExplosionEffect(); //0x100 8076efdc on collision, the box explodes for example
    virtual void OnNormalCollision(const Kart::Player& kartPlayer); //0x104 8076f1d4
    virtual void OnImperviousCollision(const Kart::Player& kartPlayer); //0x108 8076f1d8
    virtual void OnNormalItemCollision(const Kart::Player& kartPlayer, const Vec3& itemSpeed); //0x10c 8076f2d8
    virtual void OnImperviousItemCollision(const Kart::Player& kartPlayer, const Vec3& itemSpeed); //0x110 8076f2dc

    State state; //0xb0
    u32 respawnTimer; //0xb4
    EGG::Effect* explosionEffect; //0xb8 nullptr for karehayama
    bool unknown_0xbc;
    u8 padding4[3];
}; //0xc0

} //namespace Objects
#endif