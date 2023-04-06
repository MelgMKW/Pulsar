#ifndef _ITEMOBJTHUNDER_
#define _ITEMOBJTHUNDER_
#include <kamek.hpp>
#include <game/Item/Obj/ItemObj.hpp>

//_sinit_ at 807b7d74
class ItemObjThunder : public ItemObj {
public:
    static ItemObj **CreateArray(u32 count); //807b7b00
    void InitSelf() override; //0x8 807b7c04 vtable 808d2770
};
size_assert(ItemObjThunder, 0x1a0);

#endif