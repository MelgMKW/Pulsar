#ifndef _ITEMOBJKINOKOBIG_
#define _ITEMOBJKINOKOBIG_
#include <kamek.hpp>
#include <game/Item/Obj/ItemObj.hpp>

//_sinit_ at 807a9ec0
class ItemObjKinokoBig : public ItemObj { //MEGA Mushroom
public:
    static ItemObj **CreateArray(u32 count); //807a9dd4
    void InitSelf() override; //0x8 807a9ea4 vtable 808d2060
};
size_assert(ItemObjKinokoBig, 0x1a0);

#endif