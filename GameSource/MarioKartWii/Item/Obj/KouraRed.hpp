#ifndef _ITEMOBJKOURARED_
#define _ITEMOBJKOURARED_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObjVariants.hpp>

//_sinit_ at 807ab96c
namespace Item {
class ObjKouraRed : public ObjTargeting { //actually inherits a second class also used by blues and bombs
public:
    static Obj** CreateArray(u32 count); //807a9ff0
    static void* SendOrExtractShootEVENT(void* packet, Obj* obj, bool extractOrSend); //807ab40c

    ObjKouraRed(); //807aa1b8
    void InitSelf() override; //0x8 807ab38c vtable 808d2228
    void UpdateModelPosition() override;  //0x10 807aaa5c
    void UpdateModelPositionNoClip() override; //0x14 807aaafc
    void SpawnModel() override; //0x18 807ab854
    bool SetInitialPosition(PlayerObj& playerObj) override; //0x20 807aa688
    int OnKill() override; //0x24 807ab788
    void OnFinishKill() override; //0x2c 807ab810
    void vf_0x30() override; //0x30 807ab508

    void UpdateThunk(); //807a38f4
    void Update(); //807aa87c
    u8 GetTargetedPlayerId() const; //807ab894

    u8 unknown_0x24c[0x2e0 - 0x24c]; //will document later
};
size_assert(ObjKouraRed, 0x2e0);
}//namespace Item

#endif