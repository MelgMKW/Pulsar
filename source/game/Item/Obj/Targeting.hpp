#ifndef _ITEMOBJTARGETING_
#define _ITEMOBJTARGETING_
#include <kamek.hpp>
#include <game/Item/Obj/ItemObj.hpp>

class ItemObjTargeting : public ItemObj {
public:
    //vtable 808d2280 idk why it has a vtable of its own
    u8 unknown_0x1a0[0x1ec - 0x1a0];
    Vec3ZeroInit unknown_vec3s[8]; //0x1ec
};
size_assert(ItemObjTargeting, 0x24c);

#endif