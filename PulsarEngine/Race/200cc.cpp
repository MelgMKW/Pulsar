#include <kamek.hpp>
#include <MarioKartWii/Kart/KartManager.hpp>
#include <MarioKartWii/Effect/EffectMgr.hpp> 
#include <MarioKartWii/UI/Section/SectionMgr.hpp>
#include <Race/200ccParams.hpp>
#include <PulsarSystem.hpp>

//Unoptimized code which is mostly a port of Stebler's version which itself comes from CTGP's, speed factor is in the LapSpeedModifier code


namespace Pulsar {
namespace Race {

static void CannonExitSpeed() {
    const float ratio = System::sInstance->IsContext(PULSAR_200) ? cannonExit : 1.0f;
    register Kart::Movement* kartMovement;
    asm(mr kartMovement, r30;);
    kartMovement->engineSpeed = kartMovement->baseSpeed * ratio;
}
kmCall(0x805850c8, CannonExitSpeed);

void EnableBrakeDrifting(Input::ControllerHolder& controllerHolder) {
    if(System::sInstance->IsContext(PULSAR_200)) {
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

static void CalcBrakeDrifting() {
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
    writer->WriteFrame(controllerHolder->inputStates[0].buttonActions & ~0x20, quantisedStickX, quantisedStickY, motionControlFlickUnmirrored);
}
kmCall(0x80521828, FixGhostBrakeDrifting);


bool IsBrakeDrifting(const Kart::Status& status) {
    if(System::sInstance->IsContext(PULSAR_200)) {
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
    if(IsBrakeDrifting(*movement.pointers->kartStatus)) movement.acceleration = brakeDriftingDeceleration; //JUMP_PAD|RAMP_BOOST|BOOST
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
static int BrakeEffectBikes(Effects::Player& effects) {
    const Kart::Player* kartPlayer = effects.kartPlayer;
    if(System::sInstance->IsContext(PULSAR_200)) {
        if(IsBrakeDrifting(*kartPlayer->pointers.kartStatus)) effects.CreateAndUpdateEffectsByIdxVelocity(effects.bikeDriftEffects, 25, 26, 1);
        else effects.FollowFadeEffectsByIdxVelocity(effects.bikeDriftEffects, 25, 26, 1);
    }
    return kartPlayer->GetDriftState();
}
kmCall(0x80698f8c, BrakeEffectBikes);

kmWrite32(0x80698048, 0x60000000);
static int BrakeEffectKarts(Effects::Player& effects) {
    Kart::Player* kartPlayer = effects.kartPlayer;
    if(System::sInstance->IsContext(PULSAR_200)) {
        if(IsBrakeDrifting(*kartPlayer->pointers.kartStatus)) effects.CreateAndUpdateEffectsByIdxVelocity(effects.kartDriftEffects, 34, 36, 1);
        else effects.FollowFadeEffectsByIdxVelocity(effects.kartDriftEffects, 34, 36, 1);
    }
    return kartPlayer->GetDriftState();
}
kmCall(0x8069804c, BrakeEffectKarts);


static void FastFallingBody(Kart::Status& status, Kart::Physics& physics) { //weird thing 0x96 padding byte used
    if(System::sInstance->IsContext(PULSAR_200)) {
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
static Kart::WheelPhysicsHolder& FastFallingWheels(Kart::Sub& sub, u8 wheelIdx, Vec3& gravityVector) { //weird thing 0x96 status
    float gravity = -1.3f;
    if(System::sInstance->IsContext(PULSAR_200)) {
        Kart::Status* status = sub.kartStatus;
        if(status->airtime == 0) status->bool_0x96 = ((status->bitfield0 & 0x80) != 0) ? true : false;
        else if((status->airtime >= 2) && (!status->bool_0x96 || (status->airtime > 19))) {
            Input::ControllerHolder& controllerHolder = sub.GetControllerHolder();
            float input = controllerHolder.inputStates[0].stick.z <= 0.0f ? 0.0f
                : (controllerHolder.inputStates[0].stick.z + controllerHolder.inputStates[0].stick.z);
            gravity *= (input * fastFallingWheelGravity + 1.0f);
        }
    }
    gravityVector.y = gravity;
    return sub.GetWheelPhysicsHolder(wheelIdx);
};
kmCall(0x805973a4, FastFallingWheels);
}//namespace Race
}//namespace Pulsar