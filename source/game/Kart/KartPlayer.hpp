#ifndef _KARTPLAYER_
#define _KARTPLAYER_

#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
#include <game/Kart/KartLink.hpp>
#include <game/Kart/KartValues.hpp>
#include <game/Kart/KartPointers.hpp>
#include <game/File/DispParams/BikePartsDisp.hpp>
#include <game/File/DispParams/KartPartsDisp.hpp>
#include <game/File/DispParams/DriverDisp.hpp>
#include <game/File/DispParams/KartDriverDisp.hpp>


namespace Kart {
class Player {
public:
    Player(u8 idx, KartId kart, CharacterId character, bool isBike, const StatsAndBsp& statsAndBsp, void* unknown,
        KartDriverDispParam::Entry* kartDriverDispEntry, KartPartsDispParam::Entry* kartPartsDispEntry,
        BikePartsDispParam::Entry* bikePartsDispEntry, DriverDispParam::Entry* driverDispEntry); //8058ddbc

    void Init(); //8058e22c
    void UpdateKartSub(); //8058eeb4
    void Update(); //8058eebc
    void InitWheels(); //8058ea0c
    bool IsLocal() const; //80590650
    u16 GetDriftState() const; //805911d8
    void CreateModel(); //8058f820

    Link link;
    virtual ~Player(); //8058def0 vtable 808b63ec
    virtual void InitSub(); //8058e188
    virtual void CreateBody(); //8058e5f8
    virtual void InitWheels(BRRESHandle& handle); //8058ea0c
    virtual void CreateSound(); //8058ece0

    Sub* kartSub; //10
    Values* values; //14
    DriverController* driver; //18
    Pointers pointers; //1c
}; //Total size 0x80
size_assert(Player, 0x80);

class PlayerBike : public Player {
public:
    void InitWheels(); //8058f2e8
    ~PlayerBike() override; //8058f8b0 vtable 808b63d0
    void CreateBody() override; //8058f260
    void InitWheels(BRRESHandle& handle) override; //8058f2e8
    void CreateSound() override; //8058f56c
}; //Total size 0x80

}//namespace Kart

#endif