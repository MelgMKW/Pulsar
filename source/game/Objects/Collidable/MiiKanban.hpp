#ifndef _MIIKANBAN_OBJECT_
#define _MIIKANBAN_OBJECT_
#include <kamek.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {
class MiiKanban : public ObjectCollidable { //ObjectNum 0x18e = 398
public:
    explicit MiiKanban(const KMP::Holder<GOBJ>& gobjHolder); //80773930
    ~MiiKanban() override; //80773c1c vtable 808cf9e0
    void OnStart() override; //0xC 80773c08
    u32 GetPropertiesBitfield() override; //0x2c 80773c14
    void LoadModels() override; //0x44 80773970
    u32 unknown_0xb0;
}; //0xb4
} //namespace Objects
#endif