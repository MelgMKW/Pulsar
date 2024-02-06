#ifndef _S_ITEMBOX_
#define _S_ITEMBOX_
#include <kamek.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>
#include <game/Objects/Collidable/Itembox/Itembox.hpp>
#include <game/KCL/KCLController.hpp>

namespace Objects {


class S_Itembox : public Itembox { //ObjectNum 0x76 = 0x118
    explicit S_Itembox(const KMP::Holder<GOBJ>& gobjHolder); //80829208

    ~S_Itembox() override; //80829584 vtable 808d79e0
    //Tries to lower the box position by 1 unit until it collides with solid terrain
    void OnStart() override; //0xc 80829280
    void Update() override; //0x14 8082945c

    Vec3 realPosition; //0xc8 taking into account object's position
    Vec3 dirRelativeToObjBoxSitsOn; //0xd4
    Vec3 position2; //0xe0
    KCLTypeHolder kclType; //0xec
    CollisionInfo info; //0xf0
    CollisionInfo::ObjInfo* objCollisionInfo; //0x14c
}; //0x150


}//namespace Objects



#endif