#ifndef _HHWANWAN_
#define _HHWANWAN_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/Objects/Collidable/Itembox/Itembox.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>

//Hwanhwan contains a ball (the chomp itself), a chain, chain links and optional item boxes
namespace Objects {

class HwanwanBall : public ObjectCollidable, public StatePtmfTrigger<HwanwanBall> {
public:
    explicit HwanwanBall(const KMP::Holder<GOBJ>& gobjHolder); //806e95b0
    //ObjectCollidable vtable 808c7554
    ~HwanwanBall() override; //806ec6e0
    void OnStart() override; //0xC 806e9724
    void Update() override; //0x14 806e9a78
    u32 GetPropertiesBitfield() override; //0x2c 806ec7b8
    const char* GetSubFileName() const override; //0x38 806ec7ac
    void LoadAnimations() override; //0x5c 806ec750
    void LoadRoute() override; //0x64 806ec7a8
    void UpdateModelMatrix() override; //0x6c 806ec74c
    void UpdateShadow() override; //0x70 806ebe90
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 806e9cac
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) override; //0xc4 806e9d6c

    //StatePtmfTrigger vtable 808c7640 at 0xb0
    //~HwanwanBall() override; thunk 806ec7c0
    virtual void vf_0xc(); //806ec7a0
    u8 unknown_0xd0[0x4a0 - 0xd0];
}; //0x4a0

class Hwanwan_Chn : public ObjectCollidable {
public:
    ~Hwanwan_Chn() override; //806c6adc vtable 808c41d8
    void OnStart() override; //0xC 806c6a8c
    const char* GetName() const override; //0x28 806c6b24
    u32 GetPropertiesBitfield() override; //0x2c 806c6b3c
    const char* GetSubFileName() const override; //0x38 806c6b30

    void LoadCollision() override; //0x60 806c6b1c
    void LoadRoute() override; //0x64 806c6b20
    void ToggleVisible(bool isVisible) override; //0x68 806c6ad8
    u8 unknown_0xb0[0x10];
}; //0xc0

class HwanwanItembox : public Itembox {
public:
    HwanwanItembox(u16 routeId, float baseSpeed); //806c4ef0
    ~HwanwanItembox() override; //806c6a40 vtable 808c3ff8
    void OnStart() override; //0xC 806c4ff4
    void Update() override; //0x14 806c5070

    u16 GetID() const override; //0x24 806c6a28
    const char* GetName() const override; //0x28 806c6a1c
    const char* GetBRRESName() const override; //0x34 806c6a04
    const char* GetSubFileName() const override; //0x38 806c6a10
    void LoadRoute() override; //0x64 806c6a80
    void UpdateShadow() override; //0x70 806c5254
    u8 unknown_0xc8[0xe0 - 0xc8];
}; //0xe0

class Hwanwan : public ObjectCollidable { //ObjectNum 0xe9 = 233
    Hwanwan(const KMP::Holder<GOBJ>& gobjHolder, u8 chainLinkCount, u32 unused); //806c5354
    ~Hwanwan() override; //806c56dc vtable 808c3f08
    void OnStart() override; //0xC 806c571c
    void Update() override; //0x14 806c5ac4
    u32 GetPropertiesBitfield() override; //0x2c 806c69b8
    void LoadModels() override; //0x44 806c69b4
    void LoadClipInfo() override; //0x58 806c69ac
    void LoadCollision() override; //0x60 806c69b0
    virtual void vf_0xec(); //806c5bcc

    HwanwanBall* hwanhwan; //0xb0
    Hwanwan_Chn* chain; //0xb4
    Hwanwan_Chn* chainLinks; //0xb8
    HwanwanItembox* itemBoxes; //0xbc
    void* unknown_class0xc0; //0xc0
    u8 itemBoxCount; //0xc4 setting1
    u16* unknown_0xc8; //0xc8 size itemboxcount * 2
    u8 chainLinkCount; //0xcc minimum 4
    bool hasItemBoxes; //0xcd
    u8 padding[2];
    float unknown_0xd0;
}; //total size 0xd4
size_assert(Hwanwan, 0xd4);
}//namespace Objects
#endif