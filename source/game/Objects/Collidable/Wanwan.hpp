#ifndef _WANWAN_
#define _WANWAN_
#include <kamek.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>

//Chomp with a wedge (pile)
namespace Objects {
class Pile : public ObjectCollidable {
    //ctor inlined
    ~Pile() override; //806e9568 vtable 808c73b8
    void OnStart() override; //0xC 806e3e20
    void Update() override; //0x14 806e3edc
    const char *GetName() const override; //0x28 806e953c
    bool HasLod() override; //0x2c 806e9560
    char *GetBRRESName() const override; //0x34 806e9554
    char *GetSubFileName() const override; //0x38 806e9548
    u32 unknown_0xb0;
    Mtx34 transformationMtx; //0xb4 unsure why copy*
    u8 unknown_0xe4[0xf0 - 0xe4];
    float unknown_0xf0[3];
}; //total size 0xfc
size_assert(Pile, 0xfc);

class Wanwan_Chn : public ObjectCollidable {
    //ctor inlined, takes wanwan's gobjholder as a param
    ~Wanwan_Chn() override; //806e94fc vtable 808c72cc
    void OnStart() override; //0xC 806e4a64
    void Update() override; //0x14 806e4208
    const char *GetName() const override; //0x28 806e94dc
    bool HasLod() override; //0x2c 806e94f4
    char *GetSubFileName() const override; //0x38 806e94e8
    void LoadCollision() override; //0x60 806e41a4
    void UpdateCollision() override; //0x74 806e4220
    float GetCollisionDiameter() const override; //0xa0 806e94c4
    virtual ObjToKartHit OnCollision(Kart *kart, ObjToKartHit default, KartToObjHit kartToObj) const; //0xc0 806e4218
    float unknown_0xb0[4];
}; //0xc0


class Wanwan : public ObjectCollidable, public ObjectCycleManager {
    Wanwan(KMP::GOBJHolder *gobjHolder); //806e4224
    ~Wanwan() override; //806e4aec vtable 808c71c4
    void OnStart() override; //0xC 806e4b9c
    void vf_0x10() override; //0x10 806e4b98
    void Update() override; //0x14 806e4f2c
    bool HasLod() override; //0x2c 806e94bc
    virtual void LoadAnimations(); //0x5c 806e9468
    virtual void UpdateModelMatrix(); //0x6c 806e9464
    virtual ObjToKartHit OnCollision(Kart *kart, ObjToKartHit default, KartToObjHit kartToObj) const; //0xc0 806e526c
    //depends on factors like speed and obviously the kartToObj as a goomba does not do anything to a player in a mega
    virtual ObjToItemInteraction GetItemCollisionType(Kart *kart, ObjToItemInteraction default, ItemToObjInteraction itemToObj) const; //0xc4 806e546c

    //CycleManager vtable 808c72b0 at 0xb0, 7 ptmfs
    //~Kuribo() override; thunk 806e95a8
    int vf_0xC() override; //806e94b4 returns 1

    //Ptmf functions
    void BeforeWanderB(); //806e6208
    void WanderBUpdate(); //806e63a4
    void BeforeWanderA(); //806e6730
    void WanderAUpdate(); //806e6838
    void BeforeLookUp(); //806e6b58
    void LookUpUpdate(); //806e6b7c
    void BeforeDigDown(); //806e6c54
    void DigDownUpdate(); //806e6c98
    void BeforeLookStraight(); //806e6dd4
    void LookStraightUpdate(); //806e6dd8
    void BeforeAttack(); //806e6eb0
    void AttackUpdate(); //806e6f6c
    void BeforeRetreat(); //806e73c4
    void RetreatUpdate(); //806e7494


    Wanwan_Chn *chain; //0xd0
    Wanwan_Chn **chainLinks; //0xd4
    Pile *pile; //0xd8
    void *unknown_0xdc;
    void *unknown_0xe0;
    u8 unknown_0xe4[0x438 - 0xe4];
    float chainLength; //0x438 kmp setting
    float setting3; //0x43c
    u32 setting2; //0x440
    Vec2 snapRange; //0x444 based on settings 4 and 5
    u32 chainLinksCount; //0x44c based on scale/chain length
    u8 unknown_0x450[0x474 - 0x450];
    Vec3 topPilePosition; //0x474
    u8 unknown_0x480[0x4e0 - 0x480];
    u32 wanderPeriod; //0x4e0 setting 6
    float wedgeWidth; //0x4e4 setting 7 (width - 35 /2 in deg)
    u8 unknown_0x4e8[0x520 - 0x4e8];
    Mtx34 unknown_0x520; //0x520
}; //total size 0x550
size_assert(Wanwan, 0x550);
}



#endif