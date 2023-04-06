#ifndef _ITEMOBJSTAR_
#define _ITEMOBJSTAR_
#include <kamek.hpp>
#include <game/Item/Obj/ItemObj.hpp>

//_sinit_ at 807b70dc
class ItemObjStar : public ItemObj {
public:
    static ItemObj **CreateArray(u32 count); //807b6ff0
    void InitSelf() override; //0x8 807b70c0 vtable 808d2698
};
size_assert(ItemObjStar, 0x1a0);

#endif