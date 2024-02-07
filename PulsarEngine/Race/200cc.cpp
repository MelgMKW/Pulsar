#include <kamek.hpp>
#include <MarioKartWii/Input/InputManager.hpp>
#include <MarioKartWii/Kart/KartManager.hpp>
#include <MarioKartWii/3D/Effect/EffectMgr.hpp> 
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <Race/200ccParams.hpp>


//Unoptimized code which is mostly a port of Stebler's version which itself comes from CTGP's, speed factor is in the LapSpeedModifier code


namespace Pulsar {
namespace Race {



//kmWrite32(0x805850c4, 0x7FC3F378); //to get kartMovement
void CannonExitSpeed() {
    const float ratio = Info::Is200cc() ? cannonExit : 1.0f;
    register Kart::Movement* kartMovement;
    asm(mr kartMovement, r30;);
    kartMovement->engineSpeed = kartMovement->baseSpeed * ratio;
}
kmCall(0x805850c8, CannonExitSpeed);

void EnableBrakeDrifting(Input::ControllerHolder& controllerHolder) {
    if(Info::Is200cc()) {
        const ControllerType controllerType = controllerHolder.curController->GetType();
        const u16 inputs = controllerHolder.inputStates[0].buttonRaw;
        u16 inputsMask = 0x700;

        switch(controllerType) {
            case(NUNCHUCK):
                inputsMask = 0xC04;
                break;
            case(CLASSIC):
                inputsMask = 0x250;
                break;
            case(GCN):
                inputsMask = 0x320;
                break;
        }
        if((inputs & inputsMask) == inputsMask) controllerHolder.inputStates[0].buttonActions |= 0x10;
    }
}

void CalcBrakeDrifting() {
    const SectionPad& pad = SectionMgr::sInstance->pad;
    for(int hudSlotId = 0; hudSlotId < 4; ++hudSlotId) {
        Input::ControllerHolder* controllerHolder = pad.GetControllerHolder(hudSlotId);
        if(controllerHolder != nullptr) EnableBrakeDrifting(*controllerHolder);
    }
}
static RaceFrameHook BrakeDriftingCheck(CalcBrakeDrifting);

void FixGhostBrakeDrifting(Input::GhostWriter* writer, u16 buttonActions, u8 quantisedStickX,
    u8 quantisedStickY, u8 motionControlFlickUnmirrored) {
    register Input::ControllerHolder* controllerHolder;
    asm(mr controllerHolder, r30;);
    EnableBrakeDrifting(*controllerHolder);
    writer->WriteFrame(controllerHolder->inputStates[0].buttonActions, quantisedStickX, quantisedStickY, motionControlFlickUnmirrored);
}
kmCall(0x80521828, FixGhostBrakeDrifting);


bool IsBrakeDrifting(const Kart::Status& status) {
    if(Info::Is200cc()) {
        u32 bitfield0 = status.bitfield0;
        const Input::ControllerHolder& controllerHolder = status.link->GetControllerHolder();
        if((bitfield0 & 0x40000) != 0 && (bitfield0 & 0x1F) == 0xF && (bitfield0 & 0x80100000) == 0
            && (controllerHolder.inputStates[0].buttonActions & 0x10) != 0x0) {
            return true;
        }
    }
    return false;
}

void BrakeDriftingAcceleration(Kart::Movement& movement) {
    movement.UpdateKartSpeed();
    if(IsBrakeDrifting(*movement.link.pointers->kartStatus)) movement.acceleration = brakeDriftingDeceleration; //JUMP_PAD|RAMP_BOOST|BOOST
}
kmCall(0x80579910, BrakeDriftingAcceleration);

asmFunc BrakeDriftingSoundWrapper() {
    ASM(
        nofralloc;
    mflr r27;
    mr r28, r3;
    mr r30, r4;
    mr r3, r28;
    bl IsBrakeDrifting;
    lwz r0, 0x4 (r30);
    cmpwi r3, 0;
    beq + normal;
    li r0, 2;
normal:
    mtlr r27;
    mr r3, r28;
    rlwinm r27, r0, 30, 31, 31;
    rlwinm r28, r0, 31, 31, 31;
    rlwinm r30, r0, 0, 31, 31;
    blr;
    )
}
kmCall(0x806faff8, BrakeDriftingSoundWrapper);

kmWrite32(0x80698f88, 0x60000000);
int BrakeEffectBikes(PlayerEffects& effects) {
    const Kart::Player* kartPlayer = effects.kartPlayer;
    if(Info::Is200cc()) {
        if(IsBrakeDrifting(*kartPlayer->link.pointers->kartStatus)) effects.DisplayEffects2(effects.bikeDriftEffects, 25, 26, true);
        else effects.FadeEffects2(effects.bikeDriftEffects, 25, 26, true);
    }
    return kartPlayer->GetDriftState();
}
kmCall(0x80698f8c, BrakeEffectBikes);

kmWrite32(0x80698048, 0x60000000);
int BrakeEffectKarts(PlayerEffects& effects) {
    Kart::Player* kartPlayer = effects.kartPlayer;
    if(Info::Is200cc()) {
        if(IsBrakeDrifting(*kartPlayer->link.pointers->kartStatus)) effects.DisplayEffects2(effects.kartDriftEffects, 34, 36, true);
        else effects.FadeEffects2(effects.kartDriftEffects, 34, 36, true);
    }
    return kartPlayer->GetDriftState();
}
kmCall(0x8069804c, BrakeEffectKarts);


void FastFallingBody(Kart::Status& status, Kart::Physics& physics) { //weird thing 0x96 padding byte used
    if(Info::Is200cc()) {
        if((status.airtime >= 2) && (!status.bool_0x96 || (status.airtime > 19))) {
            Input::ControllerHolder& controllerHolder = status.link->GetControllerHolder();
            float input = controllerHolder.inputStates[0].stick.z <= 0.0f ? 0.0f :
                (controllerHolder.inputStates[0].stick.z + controllerHolder.inputStates[0].stick.z);
            physics.gravity -= input * fastFallingBodyGravity;
        }
    }
    status.UpdateFromInput();
}
kmCall(0x805967a4, FastFallingBody);


kmWrite32(0x8059739c, 0x38A10014); //addi r5, sp, 0x14 to align with the Vec3 on the stack
Kart::WheelPhysicsHolder& FastFallingWheels(Kart::Sub& sub, u8 wheelIdx, Vec3& gravityVector) { //weird thing 0x96 status
    float gravity = -1.3f;
    if(Info::Is200cc()) {
        Kart::Status* status = sub.kartStatus;
        if(status->airtime == 0) status->bool_0x96 = ((status->bitfield0 & 0x80) != 0) ? true : false;
        else if((status->airtime >= 2) && (!status->bool_0x96 || (status->airtime > 19))) {
            Input::ControllerHolder& controllerHolder = sub.link.GetControllerHolder();
            float input = controllerHolder.inputStates[0].stick.z <= 0.0f ? 0.0f
                : (controllerHolder.inputStates[0].stick.z + controllerHolder.inputStates[0].stick.z);
            gravity *= (input * fastFallingWheelGravity + 1.0f);
        }
    }
    gravityVector.y = gravity;
    return sub.link.GetWheelPhysicsHolder(wheelIdx);
};
kmCall(0x805973a4, FastFallingWheels);
}//namespace Race
}//namespace Pulsar