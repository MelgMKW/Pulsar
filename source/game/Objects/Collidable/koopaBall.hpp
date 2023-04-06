er#ifndef _KOOPABALL_
#define _KOOPABALL_
#include <kamek.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

class KoopaBall : public ObjectCollidable { //0xcf = 207
    explicit KoopaBall(KMP::GOBJHolder *gobjHolder); //80770384
    ~KoopaBall() override; //80771f70 vtable 808cf410
    void OnStart() override; //0xC 807703d0
    void Update() override; //0x14 80770adc
    bool HasLod() override; //0x2c 80771f68
    void UpdateShadow() override; //0x70 80771e24
    ObjToKartHit OnCollision(Kart *kart, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 80771bf4
    Vec3 *GetCollisionTranslation() const override; //0xd4 80771f60

}; //0x130

}//namespace Objects



#endif