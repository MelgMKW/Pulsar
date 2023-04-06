#ifndef _COURSE_MODEL_
#define _COURSE_MODEL_
#include <kamek.hpp>
#include <game/Visual/Model/ModelDirector.hpp>
#include <game/Collision/Collision.hpp>

//_sinit_ at 80790ac0
class CourseModel {
public:
    static CourseModel *sInstance; //0x809c2F44
    void UpdateKCLHandler(float radius, Vec3 *position, KCLTypesBIT bitfield, u32 r6); //8078e4f0
    bool CheckCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT acceptedFlags, UnkType *normalsInfo, KCLTypeHolder &result, u32 initialTime); //8078f500
    bool ProcessCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT acceptedFlags, UnkType *normalsInfo, KCLTypeHolder &result, u32 initialTime); //807907f8
    //checks if the player is on a KCL triangle with a flag matching those of r6 (it's a bitfield, nth bit = 2^n kcl flag)
    //r7 has a bunch of vec3s related to floor/wall normals and stuff and kclFlags (r8) gets filled with the flag hit if a match is found
    bool ProcessLakituCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime); //8078f140
    bool ProcessEntityCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime); //8078f784
    bool CheckOOBCollision(float radius, Vec3 *position, Vec3 *lastPosition,
        KCLTypesBIT bitfield, UnkType *normals, KCLTypeHolder &result, u32 initialTime); //807903bc                

    ModelDirector *courseModel; //course MDL0
    ModelDirector *vrcornModel; //vrcorn MDL0
    nw4r::g3d::ResFileData *courseBRRES; //course_model.brres
    nw4r::g3d::ResFileData *courseBRRES2; //vrcorn_model.brres
    void *kclThing;
};

#endif