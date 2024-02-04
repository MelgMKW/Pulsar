#ifndef _OBJECTSKCLMGR_
#define _OBJECTSKCLMGR_
#include <kamek.hpp>
#include <game/Objects/KCL/ObjectKCL.hpp>
#include <game/KCL/KCLController.hpp>

enum ObjKCLArrayList {
    OBJKCL_ARRAY_ALL,
    OBJKCL_ARRAY_HAS_LOD,
    OBJKCL_ARRAY_2,

};

struct ObjectKCLArray {
    u16 count;
    u16 padding;
    ObjectKCL** array;
}; //0x8

class ObjectsKCLMgr {
    static ObjectsKCLMgr* sInstance; //809c4310
    static ObjectsKCLMgr* CreateInstance(); //8081b428
    static void DestroyInstance(); //8081b4b0
    virtual ~ObjectsKCLMgr(); //8081b380 vtable 808d6c48
    void AddObject(ObjectKCL* object); //8081b6c8
    void Init(); //8081b500
    void Update(); //8081b618
    void UpdateKCL(const Vec3& position, KCLBitfield accepted, bool isBiggerThanDefaultScale, float radius); //8081b7cc  

    bool IsColliding(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, u32 initialTime, float radius); //8081be48
    bool IsCollidingNoTerrainInfo(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, u32 initialTime, float radius); //8081c5a0
    bool IsCollidingNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, u32 initialTime, float radius); //8081bc98
    bool IsCollidingNoTriangleCheck(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, u32 initialTime, float radius); //8081bfa0
    bool IsCollidingAddEntry(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, u32 initialTime, float radius); //8081c958
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, u32 initialTime, float radius); //8081c6b4
    bool IsCollidingAddEntryNoTerrainInfoNoTriangleCheck(const Vec3& pos, const Vec3& prevPos,
        KCLBitfield accepted, CollisionInfo* info, KCLTypeHolder* ret, u32 initialTime, float radius); //8081bd70

    ObjectKCLArray arrays[3]; //0x4
    u8 unknown_0x1c[4];
}; //0x20
#endif