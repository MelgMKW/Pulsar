#ifndef _ITEMOBJKOURAGREEN_
#define _ITEMOBJKOURAGREEN_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>

namespace Item {
class ObjKouraGreen : public ObjThrowable {
public:
    static Obj** CreateArray(u32 count); //807aeaec
    void InitSelf() override; //0x8 807aefb4 vtable 808d2430
    void UpdateModelPosition() override;  //0x10 807aed2c
    void vf_0x14() override; //0x14 807aedcc
    void SpawnModel() override; //0x18 807af100
    bool SetInitialPosition(PlayerSub& playerSub) override; //0x20 807aeb98
    void OnCollision() override; //0x24 807af034
    void vf_0x2c() override; //0x2c 807af0bc
    void vf_0x30() override; //0x30 807aef38
    u8 unknown_0x1a4[0x1c8 - 0x1a4];
    u32 mode; //0x1c8 battle 7, otherwise 9? not sure
    bool unknown_0x1CC;
    bool unknown_0x1CD;
    u8 unknown_0x1CE[0x1ec - 0x1ce];
};
size_assert(ObjKouraGreen, 0x1ec);
}//namespace Item

#endif