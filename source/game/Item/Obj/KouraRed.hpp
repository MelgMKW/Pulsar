#ifndef _ITEMOBJKOURARED_
#define _ITEMOBJKOURARED_
#include <kamek.hpp>
#include <game/Item/Obj/Targeting.hpp>

//_sinit_ at 807ab96c
class ItemObjKouraRed : public ItemObjTargeting { //actually inherits a second class also used by blues and bombs
public:
    static ItemObj **CreateArray(u32 count); //807a9ff0
    ItemObjKouraRed(); //807aa1b8
    void InitSelf() override; //0x8 807ab38c vtable 808d2228
    void UpdateModelPosition() override;  //0x10 807aaa5c
    void vf_0x14() override; //0x14 807aaafc
    void SpawnModel() override; //0x18 807ab854
    bool SetInitialPosition(ItemPlayer *player) override; //0x20 807aa688
    void OnCollision() override; //0x24 807ab788
    void vf_0x2c() override; //0x2c 807ab810
    void vf_0x30() override; //0x30 807ab508
    u8 unknown_0x24c[0x2e0 - 0x24c]; //will document later
};
size_assert(ItemObjKouraRed, 0x2e0);

#endif