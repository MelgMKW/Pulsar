#ifndef _WLSCREENGC_
#define _WLSCREENGC_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/3D/TextureHolder.hpp>

namespace Objects {

class WLscreenGC : public ObjectCollidable { //ObjectNum 0x13e = 318

    static TextureHolder* screenImage; //809c44d8 RGB5A3 = 0x5 on Funky Stadium, RGBA8 everywhere else
    static u32 wlScreenGCCount; //809c44dc

    explicit WLscreenGC(const KMP::Holder<GOBJ>& gobjHolder); //8082e540
    ~WLscreenGC() override; //8082e608 vtable 808d8960
    void OnStart() override; //0xC 8082e84c
    void Update() override; //0x14 8082e850
    void LoadModels() override; //0x44 8082e6a8
}; //0xb0

}//namespace Objects



#endif