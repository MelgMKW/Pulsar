#ifndef _ITEMOBJSTAR_
#define _ITEMOBJSTAR_
#include <kamek.hpp>
#include <game/Item/Obj/ItemObj.hpp>

//_sinit_ at 807b70dc
namespace Item{
class ObjStar: public Obj {
public:
    static Obj** CreateArray(u32 count); //807b6ff0
    void InitSelf() override; //0x8 807b70c0 vtable 808d2698
};
size_assert(ObjStar, 0x1a0);
}//namespace Item
#endif