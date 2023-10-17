#ifndef _COURSE_MODEL_
#define _COURSE_MODEL_
#include <kamek.hpp>
#include <game/3D/Model/ModelDirector.hpp>
#include <game/KCL/KCLManager.hpp>


struct SoftWallInfo {
    static float initValue; //80892788 0.0f
    SoftWallInfo() { //inlined
        float value = initValue;
        min.x = value;
        min.y = value;
        min.z = value;
        max.x = value;
        max.y = value;
        max.z = value;
    }
    Vec3 min;
    Vec3 max;
    Vec3 softWallDir; //0x18
    float distanceToSoftWall;
    Vec3 normal;
};


//_sinit_ at 80790ac0
class CourseMgr {
public:
    static CourseMgr* sInstance; //0x809c2F44
    static CourseMgr* CreateInstance(); //8078dfe8
    static void DestroyInstance(); //8078e124
    static void LoadModels(bool hasTevColors, nw4r::g3d::ResFile* brresDest, ModelDirector** modelDest, const char* courseMdl0,
        const char* vrcornMdl0, u32 modelDirectorCtorArg); //8078e1b0 will fill model and ResFile's brres

    CourseMgr(); //8078e33c
    ~CourseMgr(); //8078e454
    void SetSoftWallInfo(SoftWallInfo* info); //8078e4e8
    void UpdateKCL(const Vec3& position, KCLTypesBitfield accepted, bool isBiggerThanDefaultScale, float radius); //8078e4f0

    /*
    Uses in game:
    -IsColliding
    -IsCollidingNoTerrainInfoNoTriangleCheck: Lakitu
    -IsCollidingNoTriangleCheck: Entities
    -IsCollidingAddEntry: Karts generic
    -IsCollidingAddEntryNoTerrainInfoNoTriangleCheck: Triggers
    -IsCollidingAddEntryNoTerrainInfo: Lakitu (for light)
    */

    //checks if the player is on a KCL triangle with a flag matching those of r6 (it's a bitfield, nth bit = 2^n kcl flag)
    //Results (r8) gets filled with the flag hit if a match is found
    bool IsColliding(const Vec3& position, const Vec3& prevPosition,
        KCLTypesBitfield acceptedFlags, CollisionInfo* collisionInfo,
        KCLTypeHolder* result, u32 initialTime, float radius); //8078f500
    bool IsCollidingNoTerrainInfo(const Vec3& position, const Vec3& prevPosition,
        KCLTypesBitfield bitfield, CollisionInfo* collisionInfo,
        KCLTypeHolder* result, u32 initialTime, float radius); //807901f0
    bool IsCollidingNoTerrainInfoNoTriangleCheck(const Vec3& position, const Vec3& prevPosition,
        KCLTypesBitfield bitfield, CollisionInfo* collisionInfo,
        KCLTypeHolder* result, u32 initialTime, float radius); //8078f140 
    bool IsCollidingNoTriangleCheck(const Vec3& position, const Vec3& prevPosition,
        KCLTypesBitfield bitfield, CollisionInfo* collisionInfo,
        KCLTypeHolder* result, u32 initialTime, float radius); //8078f784
    bool IsCollidingAddEntry(const Vec3& position, const Vec3& prevPosition,
        KCLTypesBitfield accepted, CollisionInfo* collisionInfo,
        KCLTypeHolder* result, u32 initialTime, float radius); //807907f8
    bool IsCollidingAddEntryNoTerrainInfo(const Vec3& position, const Vec3& prevPosition,
        KCLTypesBitfield bitfield, CollisionInfo* collisionInfo,
        KCLTypeHolder* result, u32 initialTime, float radius); //807903bc   
    bool IsCollidingAddEntryNoTerrainInfoNoTriangleCheck(const Vec3& position, const Vec3& prevPosition,
        KCLTypesBitfield bitfield, CollisionInfo* collisionInfo,
        KCLTypeHolder* result, u32 initialTime, float radius); //8078float0


    ModelDirector* courseModel; //0x0 course MDL0
    ModelDirector* vrcornModel; //0x4 vrcorn MDL0
    nw4r::g3d::ResFile courseBRRES; //0x8 course_model.brres
    nw4r::g3d::ResFile vrcornBRRES; //0x10 vrcorn_model.brres
    SoftWallInfo* info; //0x10

    static float modelScale; //808a4be0 ModelDirectors' ScnObj Mtx is set with a MakeS mtx using that float
}; //0x14

#endif