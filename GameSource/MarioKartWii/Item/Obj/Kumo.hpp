#ifndef _ITEMOBJBANANA_
#define _ITEMOBJBANANA_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>

namespace Item {
class ObjKumo : public ObjMiddle { //TC
public:
    static Obj** CreateArray(u32 count); //807af140
    void InitSelf() override; //0x8 807af534 vtable 808d2480
    void UpdateModelPosition() override;  //0x10 807af39c
    void SpawnModel() override; //0x18 807af200
    int OnKill() override; //0x24 807b123c
    void OnFinishKill() override; //0x2c 807b0960

    void UpdateThunk(); //807a3908
    void Update(); //807af76c

    u8 unknown_0x1a0[0x200 - 0x1a0];
};
size_assert(ObjKumo, 0x200);
}//namespace Item

#endif