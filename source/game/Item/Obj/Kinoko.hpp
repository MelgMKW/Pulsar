#ifndef _ITEMOBJKINOKO_
#define _ITEMOBJKINOKO_
#include <kamek.hpp>
#include <game/Item/Obj/ItemObj.hpp>

//_sinit_ at 807a9dac
class ItemObjKinoko : public ItemObj {
public:
    static ItemObj **CreateArray(u32 count); //807a9cc0
    void InitSelf() override; //0x8 807a9d90 vtable 808d1fb0
};
size_assert(ItemObjKinoko, 0x1a0);

#endif