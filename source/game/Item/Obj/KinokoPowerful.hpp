#ifndef _ITEMOBJKINOKOPOWERFUL_
#define _ITEMOBJKINOKOPOWERFUL_
#include <kamek.hpp>
#include <game/Item/Obj/ItemObj.hpp>

//_sinit_ at 807a9fc8
class ItemObjKinokoPowerful : public ItemObj { //Golden Mushroom
public:
    static ItemObj **CreateArray(u32 count); //807a9ee8
    void InitSelf() override; //807a9fac vtable 808d2110
    float unknown_0x1a0;
};
size_assert(ItemObjKinokoPowerful, 0x1a4);

#endif