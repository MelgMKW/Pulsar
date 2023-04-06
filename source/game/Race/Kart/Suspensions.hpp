#ifndef _SUSPENSIONS_
#define _SUSPENSIONS_

#include <kamek.hpp>
#include <game/Race/Kart/WheelPhysics.hpp>
#include <game/Race/Kart/KartPart.hpp>

class KartSuspensions : public KartPart {
public:
    explicit KartSuspensions(KartValues *values); //80598b08
    void Init(); //80598bd4
    ~KartSuspensions() override; //8058f52c vtable 808b6640

    u8 unknown_0x8c[0x90 - 0x8c];
    WheelPhysicsHolder *wheelPhysicsHolder;
}; //Total size 0x94

#endif