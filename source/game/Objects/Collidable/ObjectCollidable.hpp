#ifndef _OBJECTCOLLIDABLE_
#define _OBJECTCOLLIDABLE_
#include <kamek.hpp>
#include <game/Objects/Object.hpp>
#include <Item/Obj/ItemObj.hpp>
#include <game/Objects/ObjectCollision.hpp>

/*
Contributors:
-kHacker35000vr (main documentation)
-Melg
*/

class ObjectCollidable : public Object { //collision is added as there is no KCL, different shapes available cube/cylinder/sphere, depends on the obj
    explicit ObjectCollidable(KMP::GOBJHolder *gobjHolder); //8081efec
    ObjectCollidable(const char *name, Vec3 *position, Vec3 *rotation, Vec3 *scale, u32 r8); //8081f064
    ~ObjectCollidable() override; //8067e384 vtable 808d6dd8
    void Init() override; //0x20 8081f0a0 
    void LoadCollision() override; //0x60 8081f224
    void UpdateCollision() override; //0x74 8081f7c8
    float GetCollisionDiameter() const override; //0xa0 806815a0
    u32 GetDrawType() const override; //0xb0 806817ac

    virtual ObjectCollision *GetCollision() const; //0xb4 80573518
    virtual void BeforeKartCollision(Kart *kart, ObjToKartHit *objToKart, KartToObjHit *kartToObj); //0xb8 8081f66c
    virtual void BeforeItemCollision(ItemObj *item, ObjToItemInteraction *objToItem, ItemToObjInteraction *itemToObj); //0xbc 8081f778
    virtual ObjToKartHit OnCollision(Kart *kart, ObjToKartHit default, KartToObjHit kartToObj) const; //0xc0 8068179c
    //depends on factors like speed and obviously the kartToObj as a goomba does not do anything to a player in a mega
    virtual ObjToItemInteraction GetItemCollisionType(Kart *kart, ObjToItemInteraction default, ItemToObjInteraction itemToObj) const; //0xc4 806817a4
    //same as above but with items
    virtual void OnWallCollision(Kart *kart, Vec3ZeroInit position); //0xc8 8081f548 sound and playereffectsx
    //for objects that behave like walls such as goombas at low speeds
    virtual void OnNormalCollision(Kart *kart, Vec3ZeroInit position); //0xcc 8081f5d8 sound and playereffects
    virtual void CheckCollision(ObjectCollision *collision, Vec3ZeroInit position); //0xd0 80681748 only called when in range of a given object

    virtual Vec3 *GetCollisionTranslation() const; //0xd4 8068173c
    virtual bool IsSolid() const; //0xd8 80681734
    virtual void RegisterManagedObject(); //0xdc 8081f170
    virtual void UpdateDrawInfo(float f1); //0xe0 806816d8 not sure
    virtual void RegisterEntity(float radius, float maxSpeed); //0xe4 8081f180 inserts it in entityholder
    virtual Vec3 &GetSolidityCenter() const; //0xe8 806816b8

    ObjectCollision *objCollision; //0xAC
}; //0xb0
size_assert(ObjectCollidable, 0xb0);

#endif