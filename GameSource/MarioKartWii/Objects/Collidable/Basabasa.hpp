#ifndef _BASABASA_OBJECT_
#define _BASABASA_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>

namespace Objects {

class BasabasaMgr;

class Basabasa : public ObjectCollidable, public StatePtmfTrigger<Basabasa> {
public:
    static u32 curIdx; //809c21f8
    Basabasa(const KMP::Holder<GOBJ>& gobjHolder, BasabasaMgr* mgr); //806b5c84
    ~Basabasa() override; //806b7630 vtable 808c20ac
    void OnStart() override; //0xC 806b5e80
    void vf_0x10() override; //0x10 806b6028
    void Update() override; //0x14 806b602c

    const char* GetName() const override; //0x28 806b76e8
    u32 GetPropertiesBitfield() override; //0x2c 806b7700
    const char* GetSubFileName() const override; //0x38 806b76f4
    void LoadAnimations() override; //0x5c 806b76a4
    void UpdateShadow() override; //0x70 806b6eac

    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 806b6874
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) override; //0xc4 806b6a18

    //StatePtmfTrigger vtable 808c2198 at 0xb0
    // ~Basabasa() override; thunk 806b7708 

    BasabasaMgr* mgr; //0xd0
    float speed; //0xd4 setting0
    u32 idx; //0xd8
    u16 dummyObjId; //0xdc only on ddr
    bool isetting8Equal1; //0xde
    u8 padding4;
    u8 unknown_0xe0[0xf0 - 0xe0]; //0xe0
    bool unknown_0xf0;
    u8 padding5[3];
    u8 unknown_0xf4[0x15c - 0xf4];

}; //0x15c

class BasabasaMgr : public ObjectCollidable { //ObjectNum 0xcd = 205
public:
    static float distanceBtwSwoops; //809c21fc setting6
    static float dispersion; //809c2200 setting4
    static float maxHeight; //809c2204 setting5

    explicit BasabasaMgr(const KMP::Holder<GOBJ>& gobjHolder); //806b70d0
    ~BasabasaMgr() override; //806b72f4 vtable 808c1fc0
    void OnStart() override; //0xC 806b7334
    void vf_0x10() override; //0x10 806b74c0
    void Update() override; //0x14 806b74c4
    u32 GetPropertiesBitfield() override; //0x2c 806b7628
    void LoadModels() override; //0x44 806b7624
    void LoadClipInfo() override; //0x58 806b7618
    void LoadCollision() override; //0x60 806b761c
    void LoadRoute() override; //0x64 806b7620

    Basabasa** basabasas; //0xb0
    u32 delayBetweenEachGroup; //0xb4 setting2
    u32 swoopPerGroup;  //0xb8 setting3
    u32 startDelay; //0xbc setting7
    u32 totalNumberOfSwoops; //0xc0 = ceiling((totalRouteDistance/speed)/delayBtwEachGroup) * swoopPerGroup where speed is setting0
    u32 timePerSwoop; //0xc4 = (distanceBtwEachSwoop/speed)/swoopPerGroup
    u32 frameCounter; //0xc8
    u8 unknown_0xcc[4];
    u32 swoopsSpawning; //0xd0
}; //0xd4
} //namespace Objects
#endif