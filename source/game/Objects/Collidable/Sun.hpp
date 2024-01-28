#ifndef _SUN_
#define _SUN_
#include <kamek.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>

class Sun : public ObjectCollidable { //ObjectNum 0x06f = 111
public:
    ~Sun() override; //80827d58 vtable 808d77ac
    u32 GetDrawType() const override; //0xb0 80827d50
}; //0xb0

#endif