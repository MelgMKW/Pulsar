#ifndef _CANNON_OBJECT_
#define _CANNON_OBJECT_
#include <kamek.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {
class Cannon : public ObjectCollidable { //378 StarRing, 601 DonkyCannonGC, 607 DonkyCannon_wii, 609 tree_cannon
public:
    enum Type {
        DonkyCannon_wii = 0,
        DonkyCannonGC = 1,
        tree_cannon = 2,
        StarRing = 3,
    };
    static u8 cannonCount; //0x809c2248
    explicit Cannon(KMP::GOBJHolder *gobjHolder); //806bfb14
    ~Cannon() override; //806bfd90 vtable 808c2fa0
    void OnStart() override; //0xC 806bfddc
    void Update() override; //0x14 806bfed0
    bool HasLod() override; //0x2c 806c04fc
    void LoadAnimations() override; //0x5c 806bfc48
    u32 GetDrawType() const override; //0xb0 806c0504
    virtual int vf_0xec(); //0xec 806c04f4
    void OnActivation(); //806c040c inlined
    Mtx34 scnMtxPos; //0xb0
    Type type; //0xe0
    float chr0FrameCount; //0xe4
    u8 idx; //0xe8 809c2248
    u8 unknown_0xE9;
    u16 unknown_0xEA;
    u16 unknown_0xEC;
    u8 unknown_0xEE;
    u8 padding2;
}; //0xf0
} //namespace Objects
#endif