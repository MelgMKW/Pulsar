#ifndef _OBJECTSPECIALHOLDER_
#define _OBJECTSPECIALHOLDER_
#include <kamek.hpp>
#include <game/Objects/KCL/ObjectKCL.hpp>

enum ObjKCLArrayList {
    OBJKCL_ARRAY_ALL,
    OBJKCL_ARRAY_HAS_LOD,
    OBJKCL_ARRAY_2,

};

struct ObjectKCLArray {
    u16 count;
    u16 padding;
    ObjectKCL **array;
}; //0x8

class ObjectKCLHolder {
    static ObjectKCLHolder *sInstance; //809c4310
    static ObjectKCLHolder *GetStaticInstance(); //8081b428
    static void DestroyStaticInstance(); //8081b4b0
    virtual ~ObjectKCLHolder(); //8081b380 vtable 808d6c48
    void AddObject(ObjectKCL *object); //8081b6c8
    void Init(); //8081b500
    void Update(); //8081b618
    void UpdateKCLHandler(float radius, Vec3 *position, KCLTypesBIT bitfield, u32 r6); //8081b7cc  
    bool ProcessLakituCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime); //8081bc98
    void CheckCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime); //8081be48                         
    bool ProcessCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime); //8081c958        
    bool ProcessEntityCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime); //8081bfa0
    bool CheckOOBCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime); //8081c6b4


    ObjectKCLArray arrays[3]; //0x4
    u8 unknown_0x1c[4];
}; //0x20
#endif