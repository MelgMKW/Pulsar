#ifndef _ITEMOBJFIB
#define _ITEMOBJFIB
#include <kamek.hpp>
#include <game/Item/Obj/ItemObj.hpp>

class ItemObjFIB : public ItemObj {
public:
    static ItemObj **CreateArray(u32 count); //807a78a8

    void InitSelf()  override; //807a7ac0 vtable 808d1d60
    void UpdateModelPosition() override;  //0x10 807a7fec
    void SpawnModel() override; //807a7f1c
    bool SetInitialPosition(ItemPlayer *player) override; //807a7940
    void OnCollision() override; //807a8134
    void vf_0x30() override; //807a7a5c
    u8 unknown_0x1A0[8];
    bool isLocalMultiplayer; //0x1a8 for colors
    g3d::ResMatTevColor tevColors[2]; //0x1AC
    u8 unknown_0x1b4[0x1cc - 0x1b4];
};
size_assert(ItemObjFIB, 0x1b4);

#endif