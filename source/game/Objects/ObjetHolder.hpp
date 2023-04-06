#ifndef _OBJECT_HOLDER_
#define _OBJECT_HOLDER_
#include <kamek.hpp>
#include <game/File/Tables/ObjFlow.hpp>
#include <game/File/Tables/GeoHitTable.hpp>
#include <game/Objects/Object.hpp>
#include <game/Objects/ObjectCollision.hpp>
#include <game/Item/Obj/ItemObj.hpp>
#include <game/KMP/Controller.hpp>


class ObjFlowHolder {
    explicit ObjFlowHolder(const char *fileName); //8082c10c
    virtual ~ObjFlowHolder(); //8082c1f4 vtable 808d8210
    u32 GetObjIDByName(const char *objName); //8082c178
    u16 objCount;
    u8 padding[2];
    ObjFlowEntry *entries; //0x8 array size objectCount
    IndexToIDTable *idxToIDTable; //0xC
}; //0x10
size_assert(ObjFlowHolder, 0x10);

class GeoHitTableHolder {
    explicit GeoHitTableHolder(const char *fileName); //807f9278
    virtual ~GeoHitTableHolder(); //807f9348 vtable 808d4160
    GeoHitTableEntry *curEntry; //0x4 used by the ctor
    u16 objCount; //0x8
    u16 itemCount; //0xA 15 in mkwii
    u16 **interactions; //0xC use objId and then enum in GeoHitTable.hpp to access an object interaction with an item/the opposite
    IndexToIDTable *idxToIDTable; //0x10
};

class GeoHitTableItemHolder : public GeoHitTableHolder {
    ~GeoHitTableItemHolder() override; //8082b5fc vtable 808d8038
};

class GeoHitTableItemObjHolder : public GeoHitTableHolder {
    ~GeoHitTableItemObjHolder() override; //8082b5bc vtable 808d802c
};

class GeoHitTableKartHolder : public GeoHitTableHolder {
    ~GeoHitTableKartHolder() override; //8082b57c vtable 808d8020
};

class GeoHitTableKartObjHolder : public GeoHitTableHolder {
    ~GeoHitTableKartObjHolder() override; //8082b53c vtable 808d8014
};



enum ObjArrayList {
    OBJ_ARRAY_ALL,
    OBJ_ARRAY_HAS_LOD,
    OBJ_ARRAY_2,
    OBJ_ARRAY_3,
    OBJ_ARRAY_SOLID,
};
struct ObjectArray {
    u16 count;
    u16 padding;
    Object **array;
}; //0x8

class ObjectHolder {
public:
    static ObjectHolder *sInstance; //0x809c4330
    static ObjectHolder *GetStaticInstance(); //8082a784 also inits
    static void DestroyStaticInstance(); //8082a824
    static char *objectsNamesList; //808abb2c

    ObjectHolder(); //8082a38c
    virtual ~ObjectHolder(); //8082a694 vtable 808d7fec
    void Init(); //8082a2b4
    void Update(); //8082a8f4
    void CreateAllObjects(bool r4); //80826e8c
    void CreateObject(KMP::GOBJHolder *gobj); //80821e14 "ObjectGenerator"
    void HandleDroppedItem(ItemObj *itemEntity, Vec3 *position, float unknown); //8082adbc
    void AddObject(Object *object); //8082b0e8
    void CheckCollision(Kart *kart, ObjectCollisionPolyhedra *collision); //8082ab04

    ObjFlowHolder *objFlow; //0x4
    GeoHitTableItemHolder *geoHitTableItem; //0x8
    GeoHitTableItemObjHolder *geoHitTableItemObj; //0xC
    GeoHitTableKartHolder *geoHitTableKart; //0x10
    GeoHitTableKartObjHolder *geoHitTableKartObj; //0x14
    ObjectArray arrays[5]; //0x18 use enum, doesn't have ObjectKCLs
    Object *objects_0x40; //0x40
    Vec3ZeroInit **positions; //0x44, no idea,size 0xC8
    ObjToKartHit *kartInteractionArray; //0x48
    u8 unknown_0x4C[4];
    Object *pseaOrVenice_Nami; //0x50
    bool isNotTT; //0x55
    u8 padding6[3];
    Object *managedObjects; //0x58 only for MH, DC, rSGB, rDH, galaxy colosseum ie objects with a object that is managed
    u8 unknown_0x5c[4];
    bool unknown_0x60;
    u8 padding7[3];
    Mtx34 transformationMatrixes[4]; //0x64
    float angles[4]; //0x124 0 45 90 135
    ObjectCollisionManager droppedItemManager; //0x134
}; //total size 0x160
size_assert(ObjectHolder, 0x160);
#endif