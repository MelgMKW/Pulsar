#ifndef _OBJECT_MGR_
#define _OBJECT_MGR_
#include <kamek.hpp>
#include <MarioKartWii/File/Tables/ObjFlow.hpp>
#include <MarioKartWii/File/Tables/GeoHitTable.hpp>
#include <MarioKartWii/Objects/Object.hpp>
#include <MarioKartWii/Objects/ObjectCollision.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>


class ObjFlowHolder {
    explicit ObjFlowHolder(const char* fileName); //8082c10c
    virtual ~ObjFlowHolder(); //8082c1f4 vtable 808d8210
    u32 GetObjIDByName(const char* objName); //8082c178
    u16 objCount;
    u8 padding[2];
    ObjFlowEntry* entries; //0x8 array size objectCount
    IndexToIDTable* idxToIDTable; //0xC
}; //0x10
size_assert(ObjFlowHolder, 0x10);

class GeoHitTableHolder {
    explicit GeoHitTableHolder(const char* fileName); //807f9278
    virtual ~GeoHitTableHolder(); //807f9348 vtable 808d4160
    GeoHitTableEntry* curEntry; //0x4 used by the ctor
    u16 objCount; //0x8
    u16 itemCount; //0xA 15 in mkwii
    u16** interactions; //0xC use objId and then enum in GeoHitTable.hpp to access an object interaction with an item/the opposite
    IndexToIDTable* idxToIDTable; //0x10
};

class GeoHitTableItemHolder : public GeoHitTableHolder {
    ~GeoHitTableItemHolder() override; //8082b5fc vtable 808d8038
};

class GeoHitTableObjHolder : public GeoHitTableHolder {
    ~GeoHitTableObjHolder() override; //8082b5bc vtable 808d802c
};

class GeoHitTableKartHolder : public GeoHitTableHolder {
    ~GeoHitTableKartHolder() override; //8082b57c vtable 808d8020
};

class GeoHitTableKartObjHolder : public GeoHitTableHolder {
    ~GeoHitTableKartObjHolder() override; //8082b53c vtable 808d8014
};


enum ObjArrayList { //this is filled using GetBitfieldProperties
    OBJ_ARRAY_ALL,   //0x18
    OBJ_UPDATING,    //0x20
    OBJ_PROPERTY_8, //0x28
    OBJ_PROPERTY_2,      //0x30
    OBJ_ARRAY_SOLID  //0x38
};

struct ObjectArray {
    u16 count;
    u16 padding;
    Object** array;
}; //0x8

class ManagedObjects {
    void RegisterObject(Object* object); //806c4ed4
    Object* objects[0x3c];
    u32 managedObjCount;
}; //0xf4



class ObjectsMgr {
public:
    static ObjectsMgr* sInstance; //809c4330
    static ObjectsMgr* CreateInstance(); //8082a784 also inits
    static void DestroyInstance(); //8082a824
    static char* objectsNamesList; //808abb2c

    ObjectsMgr(); //8082a38c
    virtual ~ObjectsMgr(); //8082a694 vtable 808d7fec
    void Start(); //8082a2b4
    void Update(); //8082a8f4
    void CreateAllObjects(bool r4); //80826e8c
    void CreateObject(const KMP::Holder<GOBJ>& gobj); //80821e14 "ObjectGenerator"
    void HandleDroppedItem(ItemObj* itemEntity, const Vec3& position, float unknown); //8082adbc
    void AddObject(Object* object); //8082b0e8
    void ProcessCollision(const Kart::Player& kartPlayer, ObjectCollisionPolyhedra* collision); //8082ab04
    int GetManagedObjectsCount(); //8082b3b8
    Object* GetManagedObject(u32 idx); //8082b3a8
    void RegisterManagedObject(Object* object); //8082b3a0


    ObjFlowHolder* objFlow; //0x4
    GeoHitTableItemHolder* geoHitTableItem; //0x8
    GeoHitTableObjHolder* geoHitTableItemObj; //0xC
    GeoHitTableKartHolder* geoHitTableKart; //0x10
    GeoHitTableKartObjHolder* geoHitTableKartObj; //0x14
    ObjectArray arrays[5]; //0x18, 0x20, 0x28, 0x30, 0x38 use enum, doesn't have ObjectKCLs
    Object* object_0x40; //0x40
    Vec3** positions; //0x44, no idea,size 0xC8
    ObjToKartHit* kartInteractionArray; //0x48
    u8 unknown_0x4C[4];
    Object* pseaOrVenice_Nami; //0x50
    bool isGameModeMoreThan7; //0x54
    bool isTT; //0x55
    u8 padding6[2];
    ManagedObjects* managedObjects; //0x58 only for DC, MH, DC, rSGB, rDH, galaxy colosseum ie tracks with a object that is managed
    u8 unknown_0x5c[4];
    bool unknown_0x60;
    u8 padding7[3];
    Mtx34 transformationMatrixes[4]; //0x64
    float angles[4]; //0x124 0 45 90 135
    ObjectCollisionManager droppedItemManager; //0x134
}; //total size 0x160
size_assert(ObjectsMgr, 0x160);
#endif