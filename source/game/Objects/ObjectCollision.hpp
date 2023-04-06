#ifndef _OBJECTCOLLISION_
#define _OBJECTCOLLISION_
#include <kamek.hpp>

enum PlayerItemState {
    PLAYERITEMSTATE_NONE,
    PLAYERITEMSTATE_STAR,
    PLAYERITEMSTATE_MEGA,
    PLAYERITEMSTATE_BULLET,
};

class ObjectCollision { //very likely completely wrong names
    virtual ~ObjectCollision(); //unknown as abstract
    virtual void SetPositionAndScale(Mtx34 *transformationMtx, Vec3 *objScale) = 0; //c no translation
    virtual void SetPositionAndScale(Mtx34 *transformationMtx, Vec3 *objScale, Vec3 *collisionTranslation) = 0; //10 called on collision
    virtual Vec3 *GetPosition(Vec3 *unknown) const = 0; //0x14
    virtual float GetRadius() const = 0; //0x18
    bool CheckCollision(ObjectCollision *objCollision, Vec3ZeroInit *position); //80834348
    Vec3 position;
    Vec3 speed; //0x10
}; //0x1c

class ObjectCollisionSphere : public ObjectCollision { //P4 = 1, P5 is 3D Radius WanWan for example
    ObjectCollisionSphere(float radius, Vec3 *center); //808368d0
    ~ObjectCollisionSphere() override; //80836b5c vtable 808d8d58
    void SetPositionAndScale(Mtx34 *transformationMtx, Vec3 *objScale) override; //80836998
    void SetPositionAndScale(Mtx34 *transformationMtx, Vec3 *objScale, Vec3 *collisionTranslation) override; //80836a50
    Vec3 *GetPosition(Vec3 *unknown) const override; //80836920
    float GetRadius() const override; //80836b54
    bool isTranslated; //0x1c
    u8 padding[3];
    float baseRadius; //0x20
    Vec3 basePosition; //0x24 
    float radius; //0x30
    Vec3 position; //0x34
    Vec3 unknown_0x40; //0x40
    Vec3 translatedPosition; //0x4c unsure
}; //0x58

class ObjectCollisionCylinder : public ObjectCollision { //P4 = 2, P5 is 2D Radius, P6 is height Kuribo for example
public:
    ObjectCollisionCylinder(float radius, float height, Vec3 *center); //80836068
    ~ObjectCollisionCylinder() override; //808364a0 vtable 808d8d10
    void SetPositionAndScale(Mtx34 *transformationMtx, Vec3 *objScale) override; //808361f0
    void SetPositionAndScale(Mtx34 *transformationMtx, Vec3 *objScale, Vec3 *collisionTranslation) override; //80836334
    Vec3 *GetPosition(Vec3 *unknown) const override; //8083618c
    float GetRadius() const override; //80836498
    virtual Vec3 vf_0x1c(); //80836490
    u8 unknown_0x1c[4];
    float baseRadius; //0x20
    float baseHeight;
    Vec3 basePosition; //0x28
    float radius;
    float height;
    Vec3 position; //0x3c
    Vec3 unknown_0x48;
    Vec3 topMostPos; //0x54 
    Vec3 bottomMostPos; //0x60
}; //0x6c

class ObjectCollisionPolyhedra : public ObjectCollision {
    ObjectCollisionPolyhedra(u8 vertexCount, Vec3 *baseVtxPosArray = NULL); //808364e0, array that has as many vec3 as the solid has vtx
    ~ObjectCollisionPolyhedra() override; //808365a8 vtable 808d8d30
    void SetPositionAndScale(Mtx34 *transformationMtx, Vec3 *objScale) override; //808366d0
    void SetPositionAndScale(Mtx34 *transformationMtx, Vec3 *objScale, Vec3 *collisionTranslation) override; //808367c4
    Vec3 *GetPosition(Vec3 *unknown) const override; //80836628
    float GetRadius() const override; //807f957c diameter
    virtual Vec3 *vf_0x1c(); //808342e8
    virtual float SetRadius(); //8080c414
    virtual float GetDefaultDiameter() const; //8081e254
    float defaultDiameter; //unsure
    bool unknown_0x20; //is3D?
    u8 vertexCount; //0x21
    u8 padding[2];
    Vec3ZeroInit *vertexPositions; //0x24
    Vec3ZeroInit *unknown_0x24; //0x28
    float diameter; //0x2c 807f957c
    u8 unknown_0x30[0x38 - 0x30];
    Vec3 unknown_0x38;
};

class ObjectCollisionCube : public ObjectCollisionPolyhedra { //P4 = 3, P5, P6, P7 are X, Y, Z sizes DKShip64 for example
public:
    ObjectCollisionCube(float x, float y, float z, Vec3 *center); //80833840
    ~ObjectCollisionCube() override; //808342f0 vtable 808d8ce8
    void SetPositionAndScale(Mtx34 *transformationMtx, Vec3 *objScale) override; //80833b00
    void SetPositionAndScale(Mtx34 *transformationMtx, Vec3 *objScale, Vec3 *collisionTranslation) override; //80833eec

    Vec3 size; //0x44
    u8 unknown_0x50[0x5c - 0x50];
    Vec3 unknown_0x5c;
}; //0x68

class ObjectCollisionManager { //collision with anything, players/items etc...
    virtual ~ObjectCollisionManager(); //8082a654 vtable 808d7ff8
    virtual void vf_0xc(); //8082b52c just a blr
    virtual void vf_0x10();  //8082b530 just a blr
    virtual Vec3 &GetPosition() const; //0x14 8082b534
    virtual float Get_0x1c() const; //0x18 8082b524
    static PlayerItemState GetPlayerItemState(Kart *kart); //8082b4e0

    Vec3 finalPosition; //unsure
    u8 unknown_0x10[0x1c - 0x10];
    float unknown_0x1c;
    Vec3 curPosition;
}; //total size 0x2c

//if P4 = 4, object has its own KCL file 
//if P4 = 5, object has hardcoded KCL (think twisted way)
#endif