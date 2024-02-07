#ifndef _KARTAICONTROLLER_
#define _KARTAICONTROLLER_
#include <kamek.hpp>
#include <MarioKartWii/AI/AIPlayer.hpp>
#include <MarioKartWii/Kart/KartLink.hpp>


class KartAIController {
public:
    KartAIController(bool isBike); //80725fdc 
    void Init(); //80726110
    void Update(); //807261b8
    const Vec2& GetStick() const; //80726238
    bool IsCPU() const; //8072624c
    bool IsRealLocal() const; //80726290
    bool IsGhost() const; //8072633c
    bool HaveSameTeam(const KartAIController& other); //80726380

    bool IsOnTheGround() const; //807264e8
    bool IsInTheAir() const; //807264fc

    bool IsManuallyDrifting() const; //80726524
    bool IsHopping() const; //80726538
    bool IsAutomaticDrifting() const; //8072654c

    bool IsInABill() const; //80726560

    Kart::Link link;
    virtual ~KartAIController(); //80726088 vtable 808c98d8
    AI::Player* playerAI; //0x10
    Vec2 stick;; //0x14
    u32 unknown_0x1c;
    u32 team;

}; //0x24

#endif