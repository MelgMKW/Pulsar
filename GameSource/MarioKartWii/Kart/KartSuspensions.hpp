#ifndef _SUSPENSIONS_
#define _SUSPENSIONS_

#include <kamek.hpp>
#include <MarioKartWii/Kart/KartWheel.hpp>
#include <MarioKartWii/Kart/KartPart.hpp>

namespace Kart {

class Suspensions : public Part {
public:
    explicit Suspensions(const Values& values); //80598b08
    ~Suspensions() override; //8058f52c vtable 808b6640
    bool LoadModel(BRRESHandle& handle) override; //0x18 80598b50
    void UpdateMatrix() override; //0x1c 80598bec
    virtual void Reset(); //0x44 80598bdc

    void InitPhysicsHodler(); //80598bd4
    void Init(); //80598b60

    WheelPhysicsHolder* wheelPhysicsHolder;
}; //Total size 0x94

class KartSuspensionsBike : public Suspensions {
public:
    ~KartSuspensionsBike() override; //805993cc vtable 808b65f8
    bool LoadModel(BRRESHandle& handle) override; //0x18 80598fe8
    void UpdateMatrix() override; //0x1c 80598ff8


};

}//namespace kart

#endif