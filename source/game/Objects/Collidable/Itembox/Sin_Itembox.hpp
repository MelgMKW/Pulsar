#ifndef _SIN_ITEMBOX_
#define _SIN_ITEMBOX_
#include <kamek.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>
#include <game/Objects/Collidable/Itembox/Itembox.hpp>

namespace Objects {


class Sin_Itembox : public Itembox { //ObjectNum 0xee = 0x238
    explicit Sin_Itembox(const KMP::Holder<GOBJ>& gobjHolder); //8077cec8

    ~Sin_Itembox() override; //8077cf04 vtable 808d0ed0
    //Tries to lower the box position by 1 unit until it collides with solid terrain
    void OnStart() override; //0xc 8077cf44
    void Update() override; //0x14 8077d024
    u32 GetPropertiesBitfield() override; //0x2c 8077d274

    u32 state;
    float halfRouteDistance; //0xd0
    float actualDistance; //0xd4 halfDistance*sin(angle)
    float period; //0xd8 360/setting1
    float angle; //0xdc in deg + period every frame
    u32 delay; //0xe0 setting5

}; //0xe4


}//namespace Objects



#endif