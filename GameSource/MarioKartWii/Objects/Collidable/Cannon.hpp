#ifndef _CANNON_OBJECT_
#define _CANNON_OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {
//ObjectNum 0x17a = 378 StarRing, ObjectNum 0x259 = 601 DonkyCannonGC, ObjectNum 0x25f = 607 DonkyCannon_wii, ObjectNum 0x261 = 609 tree_cannon
class Cannon : public ObjectCollidable {
public:
    enum Type {
        DonkyCannon_wii = 0,
        DonkyCannonGC = 1,
        tree_cannon = 2,
        StarRing = 3
    };
    static u8 cannonCount; //0x809c2248
    explicit Cannon(const KMP::Holder<GOBJ>& gobjHolder); //806bfb14
    ~Cannon() override; //806bfd90 vtable 808c2fa0
    void OnStart() override; //0xC 806bfddc
    void Update() override; //0x14 806bfed0
    u32 GetPropertiesBitfield() override; //0x2c 806c04fc
    void LoadAnimations() override; //0x5c 806bfc48
    u32 GetScnObjDrawOptionsIdx() const override; //0xb0 806c0504
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