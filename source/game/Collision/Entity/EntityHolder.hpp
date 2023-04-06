#ifndef _ENTITYMANAGER_
#define _ENTITYMANAGER_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>

class Object;
class ItemObj;
class Kart;
class ObjectKCL;
class ObjectCollidable;

//class that links karts/objects/items etc.. into a single trait

class Entity {
    Entity(); //80786ed0
    ~Entity(); //80786ef4
    void Init(Vec3 *position, u32 params, ObjectKCL *subject, float radius, float maxSpeed); //80786f34
    void Prepare(u32 entitiesIsSolidWith); //80786fa8 for example calling with 0x10 means it'll only be solid with objectKCLs
    void MakeDynamic(); //80786f6c
    void Resize(float radius, float maxSpeed); //80786f7c
    Vec3 *position;
    float radius;
    float range;
    u32 paramsBitfield; //based on r5
    /*
    0x1 = Kart
    0x2 = ItemObj
    0x4 = some ObjectCollidable
    0x8 = other ObjectCollidable woodbox for example
    0x10 = ObjectKCL
    0x200 = collision disabled
    */
    void *subject; //Kart, ItemObj, Object etc...
    u8 unknown_0x14[0x18 - 0x14];
    Vec2 xSegment; //min max
}; //0x20

class EntityManager : public EGG::Disposer {
    static EntityManager *sInstance; //0x809c2ef0
    static EntityManager *GetStaticInstance(); //807855dc
    static void DestroyStaticInstance(); //8078562c
    EntityManager(); //807856e0
    ~EntityManager() override; //807854e4 vtable 808d17e8

    Kart *GetNextKart(); //80785d8c 
    ItemObj *GetNextItemEntity();  //80785df4
    ObjectCollidable *GetNextObjectCollidable();  //80785e5c
    ObjectKCL *GetNextObjectKCL();  //80785ec4

    void InsetKart(Vec3 *position, u32 params, Kart *subject, float radius, float maxSpeed); //80786050
    void InsertItemEntity(Vec3 *position, u32 params, ItemObj *subject, float radius, float maxSpeed); //80786064
    void InsertObjectCollidable(Vec3 *position, u32 params, ObjectCollidable *subject, float radius, float maxSpeed); //80786078
    void InsertObjectKCL(Vec3 *position, u32 params, ObjectKCL *subject, float radius, float maxSpeed); //80786120
    void InsertEntity(Vec3 *position, u32 params, void *subject, float radius, float maxSpeed); //80786134

    /*two ways to fill the closeTo array, either via en entity itself, or via a sphere (position vector + radius, such as the player's position)
    both are used to locate close entities, fill the array accordingly and then the Idx is obtained */

    void PrepareFromEntity(Entity *entity, u32 entitiesIsSolidWith); //80786774 for example calling with 0x10 means it'll only be solid with objectKCLs
    void FindEntitiesCloseToEntity(Entity *entity, u32 entitiesIsSolidWith); //807868c0

    void PrepareFromSphere(Vec3 *center, u32 entitiesIsSolidWith, float radius); //80786b14
    void FindEntitiesCloseToSphere(Vec3 *center, u32 entitiesIsSolidWith, float radius);
    void UpdateIndexes(); //80785f2c often inlined, updates index so that GetNextX can be used

    bool IsPrepared(Vec3 *position, u32 params); //80786e60 checks if cur entity is already of the type indicated by params

    void *unknown_0x10;
    void *unknown_0x14;
    Entity *entities; //0x18 array size 100
    Entity **closeToEntities; //0x1C unsure
    u32 countArray[0x100]; //0x20 no idea

    u32 entityCount; //0x420
    u32 entityCount2; //0x424
    u32 nextKartIdx; //0x428
    u32 nextItemIdx; //0x42c
    u32 nextObjectIdx; //0x430
    u32 nextObjectKCLIdx; //0x434
    u32 nextTypeCount; //0x438
    u32 unknown_0x438;
    Vec3 curEntityPosition; //0x440
    float curEntityRange; //0x44c
    u32 curEntityParams; //0x450
}; //0x454

#endif