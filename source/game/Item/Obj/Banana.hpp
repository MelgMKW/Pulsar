#ifndef _ITEMOBJBANANA_
#define _ITEMOBJBANANA_
#include <kamek.hpp>
#include <game/Item/Obj/ItemObj.hpp>


class ItemObjBanana : public ItemObj {
public:
    static ItemObj **CreateArray(u32 count); //807a3a24
    void InitSelf() override; //0x8 807a4070 vtable 808d1a38
    void SpawnModel() override; //0x18 807a40f0
    bool SetInitialPosition(ItemPlayer *player) override; //0x20 807a3be0
    void OnCollision() override; //0x24 807a40f4
    void vf_0x30() override; //0x30 807a400c
    float delayBeforeGroundEffect; //0x1a0
};
size_assert(ItemObjBanana, 0x1a4);

#endif