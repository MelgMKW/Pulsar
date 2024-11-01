#ifndef _HIGHWAY_OBJECT_
#define _HIGHWAY_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>

namespace Objects {
class HighwayCar;
class K_car_tire;
class K_truck_tire;
class K_car_light;
class K_truck_light;
class K_bomb_tire00;
class Kbomneji;

class HighwayManager : public ObjectCollidable {
public:
    HighwayManager(); //806d2908
    ~HighwayManager() override; //806d2fe8 vtable 808c55b8
    void OnStart() override; //0xC 806d332c
    void Update() override; //0x14 806d345c
    u32 GetPropertiesBitfield() override; //0x2c 806d5c6c
    void LoadModels() override; //0x44 806d5c68
    void LoadClipInfo() override; //0x58 806d5c5c
    void LoadCollision() override; //0x60 806d5c60
    void LoadRoute() override; //0x64 806d5c64

    u32 k_tireCount; //0xb0
    u32 k_lightCount; //0xb4
    K_car_tire** carTires; //0xb8
    K_truck_tire** truckTires; //0xbc
    K_car_light** carLights; //0xb8
    K_truck_light** truckLights; //0xbc
    HighwayCar** car_Bodies; //0xc8
    HighwayCar** kart_trucks; //0xcc
    HighwayCar** k_bomb_cars; //0xd0
    HighwayCar** ksticketcs; //0xD4
    HighwayCar** allVehicles; //0xd8
    u32 car_bodyCount; //0xdc
    u32 kart_truckCount; //0xe0 
    u32 ksticketcCount; //0xe4
    u32 k_bomb_carCount; //0xe8
    u32 registeredVehicles; //0xec sum of car_body, kart_truck and k_bomb_car
    u32 registeredCarBodies; //0xf0
    u32 registeredkart_trucks; //0xf4
    u32 registeredKsticketcs; //0xf8
    u32 registeredK_bomb_cars; //0xfc

    u32 playerCount; //0x100
    u16* asManyPointsAsRoute0; //0x104
    u16* asManyPointsAsRoute1; //0x108
    u16 maxRoute0Route1PointCount; //0x10c
    u16 unknown_0x10e;
    u8 unknown_0x110[0x120 - 0x110];
    void* unknown_0x120; //0x120 size 4 * playerCount
    u8 unknown_0x124[8];
}; //0x12c


//ObjectNum 0xd0 = 208 kart_truck, ObjectNum 0xd1 = 209  car_body, ObjectNum 0xde = 222 K_bomb_car, ObjectNum 0xf3 = 243 K_bomb_car1
class HighwayCar : public ObjectCollidable, public StatePtmfTrigger<HighwayCar> {
public:
    enum Type {
        TYPE_CAR_BODY,
        TYPE_KART_TRUCK,
        TYPE_K_BOMB_CAR,
    };
    explicit HighwayCar(const KMP::Holder<GOBJ>& gobjHolder); //806d5ee4

    //ObjectCollidable vtable 808c58e8
    ~HighwayCar() override; //806d691c
    void OnStart() override; //0xC 806d6b14
    void Update() override; //0x14 806d6ecc
    u32 GetPropertiesBitfield() override; //0x2c 806da7ac
    const char* GetBRRESName() const override; //0x34 806d68b0
    const char* GetSubFileName() const override; //0x38 806da7a4
    const char* GetShadowResName() const override; //0x40 806da79c
    void LoadModels() override; //0x44 806d6988
    void LoadCollision() override; //0x60 806d7af8
    void UpdateShadow() override; //0x70 806da728
    void UpdateCollision() override; //0x74 806d7bf8
    float GetCollisionDiameter() const override; //0xa0 806d69c0
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 806d7328
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) override; //0xc4 806d7780
    void ProcessCollision(ObjectCollision* collision, Vec3 position) override; //0xd0 806da660
    const Vec3& GetSolidityCenter() const override; //0xe8 806d7cf8

    //StatePtmfTrigger vtable 808c59d4 at 0xb0
    //~HighwayCar thunk 806da90c

    K_bomb_tire00* bomb_tire; //0xd0 only if type == bomb
    Kbomneji* bomneji; //0xd4

    HighwayManager* manager; //0xd8
    ModelDirector* bombCore; //0xdc bomb explosion
    EGG::Effect* rk_K_bomb_car; //0xe0

    ObjectCollision* tireCollision; //0xe4 cylinder small and tall, might be something other than tires
    u32 texturing; //0xe8 setting4
    float speed1; //0xec setting3
    float speed0; //0xf0 setting2
    char brresName[0x20]; //0xf4 based on objId
    char modelName[0x20]; //0x114 based on brresName and texturing setting
    char shadowModelName[0x20]; //0x134
    Type type; //0x154
    u16 dummyObjId; //0x158
    u8 screenCount; //0x15a
    u8 padding4; //0x15b
    float xScale; //0x15c
    bool isGamemodeTTOrMoreThan7; //0x160
    u8 padding5; //0x161
    u16 unknown_0x162[2];
    u8 padding6[2]; //0x166
    Vec3 direction; //0x168 baseSpeed * RouteController unitDir
    float baseSpeed; //0x174 from RouteController
    u8 unknown_0x178[0x190 - 0x178];
    Vec3 curRoutePointNormal; //0x190
    Vec3 nextRoutePointNormal; //0x19c
    u32 blightIndex; //0x1a8 only if cur and next route point have same index (1 or 2), else 0
    u32 state; //0x1ac 3 moving normally
    u8 unknown_0x1b0[0x1be - 0x1b0]; //0x1b0
    u8 padding7[2]; //0x1be
    u32 unknown_0x1c0;
    float unknown_0x1c4;
    u8 unknown_0x1c8[0x218 - 0x1c8];
    u8 unknown_0x218; //0x218
    u8 padding8[3]; //0x219
    float unknown_0x21c;
    float unknown_0x220;
    float unknown_0x224;
    u32 unknown_0x228;
    u8 unknown_0x22c[0x234 - 0x22c];
}; //0x234

class K_car_tire : public ObjectCollidable {
public:
    ~K_car_tire() override; //806d5c1c vtable 808c54c8
    u16 GetID() const override; //0x24 806d5c14
    u32 GetPropertiesBitfield() override; //0x2c 806d5c0c
    const char* GetBRRESName() const override; //0x34 806d5c00
    const char* GetSubFileName() const override; //0x38 806d5bf4
    void LoadAnimations() override; //0x5c 806d5ba0
    void LoadCollision() override; //0x60 806d5bec
    void LoadRoute() override; //0x64 806d5bf0

    u8 unknown_0xb0;
    u8 padding4[3];
    u32 unknown_0xb4;
};

class K_truck_tire : public ObjectCollidable {
public:
    ~K_truck_tire() override; //806d5b58 vtable 808c53d8
    u16 GetID() const override; //0x24 806d5b50
    u32 GetPropertiesBitfield() override; //0x2c 806d5b48
    const char* GetBRRESName() const override; //0x34 806d5b3c
    const char* GetSubFileName() const override; //0x38 806d5b30
    void LoadAnimations() override; //0x5c 806d5adc
    void LoadCollision() override; //0x60 806d5b28
    void LoadRoute() override; //0x64 806d5b2c

    u8 unknown_0xb0;
    u8 padding4[3];
    u32 unknown_0xb4;
};

class K_car_light : public ObjectCollidable {
public:
    ~K_car_light() override; //806d5a94 vtable 808c52e8
    u16 GetID() const override; //0x24 806d5a8c
    u32 GetPropertiesBitfield() override; //0x2c 806d5a84
    const char* GetBRRESName() const override; //0x34 806d5a78
    const char* GetSubFileName() const override; //0x38 806d5a6c
    void LoadAnimations() override; //0x5c 806d59d4
    void LoadCollision() override; //0x60 806d5a64
    void LoadRoute() override; //0x64 806d5a68

    u8 unknown_0xb0;
    u8 padding4[3];
    u32 unknown_0xb8;
};

class K_truck_light : public ObjectCollidable {
public:
    ~K_truck_light() override; //806d598c vtable 808c51f8
    u16 GetID() const override; //0x24 806d5984
    u32 GetPropertiesBitfield() override; //0x2c 806d597c
    const char* GetBRRESName() const override; //0x34 806d5970
    const char* GetSubFileName() const override; //0x38 806d5964
    void LoadAnimations() override; //0x5c 806d58cc
    void LoadCollision() override; //0x60 806d595c
    void LoadRoute() override; //0x64 806d5960

    u8 unknown_0xb0;
    u8 padding4[3];
    u32 unknown_0xb8;
};

class K_bomb_tire00 : public ObjectCollidable {
public:
    ~K_bomb_tire00() override; //806da8cc vtable 808c5ad0
    u32 GetPropertiesBitfield() override; //0x2c 806da8c4
    const char* GetSubFileName() const override; //0x38 806da8b8
    void LoadAnimations() override; //0x5c 806da864
    void LoadCollision() override; //0x60 806da8b0
    void LoadRoute() override; //0x64 806da8b4
    u8 unknown_0xb0[0x20];

}; //0xd0

class Kbomneji : public ObjectCollidable { //the big screw
public:
    ~Kbomneji() override; //806da81c vtable 808c59e0
    u32 GetPropertiesBitfield() override; //0x2c 806da814
    const char* GetSubFileName() const override; //0x38 806da808
    void LoadAnimations() override; //0x5c 806da7bc
    void LoadCollision() override; //0x60 806da800
    void LoadRoute() override; //0x64 806da804
    u8 unknown_0xb0[0x20];
}; //0xd0

} //namespace Objects


#endif