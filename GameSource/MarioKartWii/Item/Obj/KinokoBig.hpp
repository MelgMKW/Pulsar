#ifndef _ITEMOBJKINOKOBIG_
#define _ITEMOBJKINOKOBIG_
#include <kamek.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>

//_sinit_ at 807a9ec0
namespace Item {
class ObjKinokoBig : public ObjMiddle { //MEGA Mushroom
public:
    static Obj** CreateArray(u32 count); //807a9dd4

    void InitSelf() override; //0x8 807a9ea4 vtable 808d2060
};
size_assert(ObjKinokoBig, 0x1a0);
}//namespace Item

#endif