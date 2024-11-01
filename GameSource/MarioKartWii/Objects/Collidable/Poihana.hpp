#ifndef _POIHANA_OBJECT_
#define _POIHANA_OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/AI/AIBase.hpp>

namespace Objects {

class Poihana;
class PoihanaBase : public ObjectCollidable, public AI::Base { //likely not specific to poihana (it doesn't appear they share the same cpp file)
public:
    explicit PoihanaBase(const KMP::Holder<GOBJ>& gobjHolder); //80747198
    class SubChild : public UnkCollidableSub {
    public:
        SubChild(); //80747c40
        ~SubChild() override; //80747c98 vtable 808cb8d0
        void Reset() override; //0xc 80747cd8
        void Update(const Vec3& vec, float f1, float f2) override; //0x10 80747cfc
        bool vf_0x14() const override; //80748138
        u8 unknown_0x28;
        u8 paddding[3];
    }; //0x2c
    //ObjectCollidable vtable 808cb7c8 at 0x0
    ~PoihanaBase() override; //80747208
    void OnStart() override; //0xC 80747248
    void Update() override; //0x14 807472f4
    u32 GetPropertiesBitfield() override; //0x2c 8074815c

    //AI::Base vtable 808cb8b4 at 0xe4
    //~PoihanaBase(); //thunk 80748164 func 80747208

    Vec3 GetTranslation() const; //80747308 returns translation col of transMtx2

    u32 unknown_0xe8;
    UnkCollidableSub* sub; //0xec Poihana::SubChild here
    u8 unknown_0xf0[0x108 - 0xf0];
    Mtx34 transMtx2; //0x108
    u8 unknown_0x138[0x168 - 0x138];
    float unknown_0x168[2];
}; //0x170

//AI::Actions<Poihana> virtual ~PoihanaActions(); //8074887c vtable 808cbbd0
//AI::Actions<Poihana> virtual void OnStart(); //0xc 8074ad64
//AI::Actions<Poihana> virtual void Update(); //0x10 8074adac
//AI::Actions<Poihana> virtual void OnEnd(); //0x14  8074addc

class Poihana : public PoihanaBase { //ObjectNum 0x197 = 407
public:
    typedef AI::Actions<Poihana> Actions;

    explicit Poihana(const KMP::Holder<GOBJ>& gobjHolder); //8074816c

    //ObjectCollidable vtable 808cba80 at 0x0
    ~Poihana() override; //807488bc
    void OnStart() override; //0xC 80748958
    void Update() override; //0x14 80748b70

    void LoadAnimations() override; //0x5c 80748cec
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 80749378
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) override; //0xc4 80749504

    //AI::Base vtable 808cbb6c at 0xe4, all vf offsets from start of Collidable's vtable
    //~Poihana(); //thunk 8074ae24 func 807488bc
    virtual void OnStartIdle(); //0x104 807498ac
    virtual void UpdateIdleAndAction1(); //0x108 80749924
    virtual void OnStartChase(); //0x10c 80749ae8
    virtual void UpdateChase(); //0x110 80749b00
    virtual void OnStarCatapult(); //0x114 80749f70
    virtual void UpdateCatapult(); //0x118 8074a104
    virtual void OnEndCatapult(); //0x11c 8074a180
    virtual void OnStartCatapultNoMove(); //0x120 8074a18c 
    virtual void UpdateCatapultNoMove(); //0x124 8074a1dc
    virtual void OnEndCatapultNoMove(); //0x128 8074a28c
    virtual void Topple(); //0x12c 8074a298
    virtual void OnStartToppleNormal(); //0x130 8074a4a4
    virtual void OnStartToppleInverted(); //0x134 8074a4bc
    virtual void UpdateTopple(); //0x138 8074a4d8
    virtual void OnEndTopple(); //0x13c 8074a720
    virtual void OnStartToppleNoBury(); //0x140 8074a75c 
    virtual void UpdateToppleNoBury(); //0x144 8074a8ac
    virtual void OnEndToppleNoBury(); //0x148 8074ad58


    u8 unknown_0x170[4];
    Actions idle; //0x174
    Actions action1; //0x1a0
    Actions chase; //0x1cc chases a player
    Actions catapult; //0x1f8 catapults a player
    Actions catapultNoMove; //0x224 same as above but the poihana does not move during the action, this is used in TTs to guarantee proper ghost replay/syncing

    //Topple: if VS, first normal topple and if already toppled on item hit, toppleInverted/in TT, topple no bury always
    Actions toppleNormal; //0x250 on item hit, topples over and lands on its back, then stays buried for a duration
    Actions toppleInverted; //0x27c on item hit, topples over and lands on its legs, then stays buried for a duration
    Actions toppleNoBury; //0x2a8 topples over, but does NOT stay buried for a duration and instantly goes to idle on topple end

    u8 unknown_0x2d4[0x31c - 0x2d4]; //0x2d4
    Vec3 kartPosOnCollision; //0x31c position of the player who collided with the poihana
    u8 unknown_0x328[0x334 - 0x328]; //0x2d4
    float unknown_0x334; //0x334
    u32 unknown_0x338; //0x338
    u8 unknown_0x33c[0x34b - 0x33c];
    bool isTTOrGameMode7OrMore; //0x34b
    u8 unknown_0x34c[0x370 - 0x34c];

    EGG::Effect* rk_poihanaExclm; //0x370
}; //0x374

} //namespace Objects
#endif