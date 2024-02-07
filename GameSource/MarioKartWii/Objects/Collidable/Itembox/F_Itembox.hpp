#ifndef _F_ITEMBOX_
#define _F_ITEMBOX_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/Objects/Collidable/Itembox/Itembox.hpp>

namespace Objects {

class F_Itembox : public Itembox { //ObjectNum 0xc9 = 201
    explicit F_Itembox(const KMP::Holder<GOBJ>& gobjHolder); //80828f44

    ~F_Itembox() override; //808295c4 vtable 808d7ad0
    //Tries to lower the box position by 1 unit until it collides with solid terrain
    void OnStart() override; //0xc 80828f98
    void Update() override; //0x14 80829074

    u16 routeStartPoint; //0xc8 setting5
    u8 padding4[2];
}; //0xcc

}//namespace Objects



#endif