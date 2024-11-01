#ifndef _OBJECTCOLLIDABLE_
#define _OBJECTCOLLIDABLE_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Object.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>
#include <MarioKartWii/Objects/ObjectCollision.hpp>

/*
Contributors:
-kHacker35000vr (main documentation)
-Melg
*/

class ObjectCollidable : public Object { //collision is added as there is no KCL, different shapes available cube/cylinder/sphere, depends on the obj
    explicit ObjectCollidable(const KMP::Holder<GOBJ>& gobjHolder); //8081efec
    ObjectCollidable(u16 objId, const Vec3& position, const Vec3& rotation, const Vec3& scale); //8081f028
    ObjectCollidable(const char* name, const Vec3& position, const Vec3& rotation, const Vec3& scale, u32 r8); //8081f064
    ~ObjectCollidable() override; //8067e384 vtable 808d6dd8
    void Init() override; //0x20 8081f0a0 
    void LoadCollision() override; //0x60 8081f224
    void UpdateCollision() override; //0x74 8081f7c8
    float GetCollisionDiameter() const override; //0xa0 806815a0
    u32 GetScnObjDrawOptionsIdx() const override; //0xb0 806817ac

    virtual ObjectCollision* GetCollision() const; //0xb4 80573518
    virtual void BeforeKartCollision(const Kart::Player& kartPlayer, ObjToKartHit* objToKart, KartToObjHit& kartToObj); //0xb8 8081f66c
    virtual void BeforeItemCollision(const ItemObj& item,
        ObjToItemInteraction* objToItem, ItemToObjInteraction& itemToObj); //0xbc 8081f778
    virtual ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj); //0xc0 8068179c
    //depends on factors like speed and obviously the kartToObj as a goomba does not do anything to a player in a mega
    virtual ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed); //0xc4 806817a4
    //same as above but with items
    virtual void OnWallCollision(const Kart::Player& kartPlayer, Vec3 position); //0xc8 8081f548 sound and playereffectsx
    //for objects that behave like walls such as goombas at low speeds
    virtual void OnNormalCollision(const Kart::Player& kartPlayer, Vec3 position); //0xcc 8081f5d8 sound and playereffects
    virtual void ProcessCollision(ObjectCollision* collision, Vec3 position); //0xd0 80681748 only called when in range of a given object

    virtual const Vec3& GetCollisionTranslation() const; //0xd4 8068173c
    virtual bool IsSolid() const; //0xd8 80681734
    virtual void RegisterManagedObject(); //0xdc 8081f170
    virtual void InitEntity(float maxSpeed); //0xe0 806816d8 not sure
    virtual void RegisterEntity(float radius, float maxSpeed); //0xe4 8081f180 inserts it in EntityManager
    virtual const Vec3& GetSolidityCenter() const; //0xe8 806816b8

    ObjectCollision* objCollision; //0xAC
}; //0xb0
size_assert(ObjectCollidable, 0xb0);

class UnkCollidableSub {
public:
    UnkCollidableSub(); //8074792c
    virtual ~UnkCollidableSub(); //80747974 vtable 808cb8e8
    virtual void Reset(); //0xc 807479b4
    virtual void Update(const Vec3& vec, float f1, float f2); //0x10 807479d4
    virtual bool vf_0x14() const; //80747c18

    u8 unknown_0x4[0x10 - 0x4];
    u32 unknown_0x10;
    u32 playerCount; //0x14
    u32 unknown_0x18[3];
    float unknown_0x24;

}; //0x28

#endif