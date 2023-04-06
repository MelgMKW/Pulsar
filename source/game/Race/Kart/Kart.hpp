#ifndef _KART_
#define _KART_

#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
#include <game/Race/Kart/KartBase.hpp>
#include <game/Race/Kart/KartParams.hpp>
#include <game/Race/Kart/KartPointers.hpp>

class Kart {
private:
    Kart(u32 idx, KartId kart, CharacterId character, bool isBike, StatsAndBsp *statsAndBsp, void *unknown,
        UnkType *kartDriverDispParams, UnkType *kartPartsDispParams, UnkType
        *bikePartsDispParams, UnkType *driverDispParams); //8058ddbc

public:
    static ClipInfo *curKartClipInfo; //809c1954
    //Kart(u32 idx, kartId kart, CharacterId character, bool isBike); //8058f5b4
    void Init(); //8058e22c
    void UpdateKartSub(); //8058eeb4
    void Update(); //8058eebc
    void InitWheels(); //8058ea0c
    bool IsLocal() const; //80590650
    u16 GetDriftState() const; //805911d8
    void CreateModel(); //8058f820
    KartBase base;
    virtual ~Kart(); //8058def0 vtable 808b63ec
    virtual void InitSub(); //8058e188
    virtual void CreateBody(); //8058e5f8
    virtual void InitWheels(void *r4); //8058ea0c
    virtual void CreateSound(); //8058ece0
    KartSub *kartSub; //10
    KartValues *values; //14
    KartModel *model; //18
    KartPointers pointers; //1c
}; //Total size 0x80
size_assert(Kart, 0x80);

class KartBike : public Kart {
public:
    void InitWheels(); //8058f2e8
    ~KartBike() override; //8058f8b0 vtable 0x808b63d0
    void CreateBody() override; //8058f260
    void InitWheels(void *r4) override; //8058f2e8
    void CreateSound() override; //8058f56c
}; //Total size 0x80

#endif