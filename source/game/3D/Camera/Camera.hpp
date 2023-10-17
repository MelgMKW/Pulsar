
/*
Contributors:
-Melg
*/
#ifndef _GAMECAMERA_
#define _GAMECAMERA_

#include <kamek.hpp>
#include <core/nw4r/ut/List.hpp>
#include <core/egg/3D/Camera.hpp>
#include <game/3D/Scn/GameScreen.hpp>
#include <game/AI/AIBase.hpp>
#include <game/3D/Camera/CameraBinaries.hpp>

class GameCamera;
class GameScreen;
class ScnMgr;
namespace Kart {
class Player;
}

class GameCamValues {
public:
    void Reset(); //805a1c3c
    Vec3 position; //0
    Vec3 prevPosition; //0xC
    float addedXAngleRot; //0x18
    float addedYAngleRot; //0x1c mostly Y-axis only rotation when hitting a wall at high speed
    u8 unknown_0x20[0xC];
    Vec3 addedRot; //0x2c can be used set
    Vec3 position2; //0x38
    float unknown_0x44[2];
    float cameraDist; //0x4c dist in the direction of driving
    float unknown_0x50[5];
    u16 unknown_0x64;
    u8 unknown_0x66[6];
    u32 unknown_0x6C;
    Vec3 unknown_0x70;
    float unknown_0x80[5];
    u16 unknown_0x94[3];
    u8 unknown_0x9A[2]; //mostly likely padding
    float unknown_0x9C;
    float verticalOffset; //0xa0
    float verticalOffset2; //0xa4 same effect as above
    u8 unknown_0xa8[0x10];
    Vec3 unknown_0xB8;
    float unknown_0xC4;
    u8 unknown_0xc8[2];
    u8 padding[2];
}; //0xCC

class CameraLink {
public:
    static ut::List cameraList; //809c19a8
    static void InitCameraList(); //805a1a44
    static void UpdateAllCameras(); //805a1af0
    static void InitAllCameras(); //805a1a8c

    CameraLink(GameCamera* camera, GameScreen& gameScreen); //805a1864
    virtual ~CameraLink(); //805a19d8 vtable 808b6b60
    virtual void Init() = 0;
    virtual void Update(bool r4) = 0;

    void Register(); //805a1a7c

    GameScreen& screen;
    GameCamera* camera;
    ut::Link link;
}; //0x10

class GameCamera : public EGG::LookAtCamera, public CameraLink {
public:
    GameCamera(GameScreen& gameScreen, bool registerCamera); //805a18bc

    //LookAtCamera vtable 808b6b10 at 0x0
    EGG::Matrix34f& GetViewMatrix() override; //0x8 80562bf0 
    const EGG::Matrix34f& GetViewMatrix() const override; //0xc 805a1c1c
    EGG::Vector3f GetPosition() override; //0x20 805a1c00

    //CameraLink vtable 808b6b40 at 0x88
    ~GameCamera() override; //thunk 805a1c34 func 805a1bbc
    void Init() override; //thunk 805a1c2c func 805a1bfc
    void Update(bool r4) override; //thunk 805a1c24 func 805a1a18

}; //0x9c

extern u32 screenCount; //808b4be8

#endif