
/*
Contributors:
-Melg
*/
#ifndef _CAMERA_
#define _CAMERA_
#include <kamek.hpp>

struct mystruct {
    int yeah;
};


struct UnkCameraStruct {
    UnkCameraStruct(); //805a1d10
    virtual void func_vtable(); //0x808b6c40, also inherits from a bunch
    Mtx34 worldView;
    u8 unknown_0x34[0x348 - 0x34];
}; //total size 0x348

class RaceCameraManager {
public:
    RaceCameraManager(); //8056581c
    void SetProjection(u32 id, u32 r5);
    u8 unknown_0x0[0x38 - 0x0]; //bunch of inherited structs
    virtual void func_vtable(); //808b4c20
    u8 unknown_0x3C[0x6C - 0x3C];
    UnkCameraStruct *unkStruct;
    u8 unknown_0x70[0x10C - 0x70];
}; //total size 0x10C



class CameraHandler {
public:
    static CameraHandler sInstance;
    virtual void func_vtable();
    u32 hudCount;
    RaceCameraManager **cameraArray; //one per hudSlot, actually also exists outside of races
};

#endif