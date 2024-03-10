#ifndef _ITEMOBJBOMB_
#define _ITEMOBJBOMB_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>

//_sinit_ at 807a62d8
namespace Item {
class ObjBomb : public ObjThrowable {
public:
    static Obj** CreateArray(u32 count); //807a41c4
    ObjBomb(); //807a4850 inlined
    void RemoveFromScn() override; //807a5b80 vtable 808d1be0
    void InitSelf() override; //0x8 807a5144
    void UpdateModelPosition() override;  //0x10 807a5340
    void vf_0x14() override; //0x14 807a59e0
    void SpawnModel() override; //0x18 807a5bc4
    void vf_0x1c() override; //0x1c 807a5cfc
    bool SetInitialPosition(PlayerSub& playerSub) override; //0x20 807a4a18
    void OnCollision() override; //0x24 807a5f6c
    void vf_0x28() override; //0x28 807a60f8
    void vf_0x2c() override; //0x2c 807a619c
    void vf_0x30() override; //0x30 807a500c
    void vf_0x34() override; //0x34 807a5090
    u8 unknown_0x1a4[0x1d4 - 0x1a4];
    ModelDirector* bombCore; //0x1d4
    u8 unknown_0x1d8[0x4];
    u32 timer; //0x1dc how long a bomb lasts before exploding
    u8 unknown_0x1e0[0x1f0 - 0x1e0];
};
size_assert(ObjBomb, 0x1f0);
}//namespace Item

#endif