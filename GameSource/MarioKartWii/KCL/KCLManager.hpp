#ifndef _KCLMANAGER_
#define _KCLMANAGER_
#include <kamek.hpp>
#include <MarioKartWii/File/KCL.hpp>
#include <MarioKartWii/KCL/KCLController.hpp>


class KCLManager {
    static KCLManager* sInstance; //809c3c10
    static Vec3* infinitePos; //809c3c04
    static KCLManager* CreateInstance(); //807c2824
    static void DestroyInstance(); //807c2884
    void Load(const KCL& rawCourse); //807c28d8
    void Update(KCLController* other, const Vec3& position, KCLBitfield accepted, bool isBiggerThanDefaultScale,
        float accuracy, float radius); //807c293c

    bool IsColliding(KCLController* other, const Vec3& position, const Vec3& prevPosition, KCLBitfield accepted,
        CollisionInfo* info,
        KCLTypeHolder* ret, float accuracy, float radius); //807c3cf0
    bool IsCollidingAddEntry(KCLController* other, const Vec3& position, const Vec3& prevPosition, KCLBitfield accepted,
        CollisionInfo* info,
        KCLTypeHolder* ret, float accuracy, float radius); //807c4b40 
    bool IsCollidingAddEntryNoTriangleCheck(KCLController* other, const Vec3& position, const Vec3& prevPosition,
        KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, float accuracy, float radius); //807c3e84
    bool IsCollidingNoTerrainInfo(KCLController* other, const Vec3& position, const Vec3& prevPosition, KCLBitfield accepted,
        CollisionInfo* info,
        KCLTypeHolder* ret, float accuracy, float radius); //807c4648
    bool IsCollidingNoTerrainInfoNoTriangleCheck(KCLController* other, const Vec3& position, const Vec3& prevPosition, KCLBitfield accepted,
        CollisionInfo* info,
        KCLTypeHolder* ret, float accuracy, float radius); //807c39c8
    bool IsCollidingAddEntryNoTerrainInfo(KCLController* other, const Vec3& position, const Vec3& prevPosition, KCLBitfield accepted,
        CollisionInfo* info,
        KCLTypeHolder* ret, float accuracy, float radius); //807c47f0
    bool IsCollidingAddEntryNoTerrainInfoNoTriangleCheck(KCLController* other, const Vec3& position, const Vec3& prevPosition,
        KCLBitfield accepted, CollisionInfo* info,
        KCLTypeHolder* ret, float accuracy, float radius); //807c3b5c

    bool IsCollidingFillInfo(KCLController& handler, Ptmf_3A<KCLController, bool, float*, Vec3*, u16*>* trianglesCollisionChecker,
        CollisionInfo& info, KCLTypeHolder* ret); //807c2bd8
    bool IsCollidingFillInfoAddEntry(KCLController& handler, Ptmf_3A<KCLController, bool, float*, Vec3*, u16*>* trianglesCollisionChecker,
        CollisionInfo& info, KCLTypeHolder* ret); //807c36cc
    bool IsCollidingFillInfoNoTerrainInfo(KCLController& handler,
        Ptmf_3A<KCLController, bool, float*, Vec3*, u16*>* trianglesCollisionChecker,
        CollisionInfo& info, KCLTypeHolder* ret); //807c3258 doesn't fill collisionInfo's floor and wall stuff
    bool IsCollidingFillInfoAddEntryNoTerrainInfo(KCLController& handler,
        Ptmf_3A<KCLController, bool, float*, Vec3*, u16*>* trianglesCollisionChecker,
        CollisionInfo& info, KCLTypeHolder* ret); //807c2f18


    KCLController* handler;
    //Before doing calculations, the radius and positions are multiplied by the inverse
    //so with a high value, the radius is shortened 
    float someAccuracy;
    u32 unknown_0x8[2];
}; //0x10

#endif