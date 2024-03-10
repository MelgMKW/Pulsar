#ifndef _ITEMOBJBANANA_
#define _ITEMOBJBANANA_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>

namespace Item {
class ObjBanana : public ObjThrowable {
public:
    static Obj** CreateArray(u32 count); //807a3a24
    void InitSelf() override; //0x8 807a4070 vtable 808d1a38
    void SpawnModel() override; //0x18 807a40f0
    bool SetInitialPosition(PlayerSub& playerSub) override; //0x20 807a3be0
    void OnCollision() override; //0x24 807a40f4
    void vf_0x30() override; //0x30 807a400c
};
size_assert(ObjBanana, 0x1a4);
}//namespace Item

#endif