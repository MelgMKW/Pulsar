#include <kamek.hpp>
#include <game/Race/Kart/KartHolder.hpp>
#include <game/visual/effect/EffectMgr.hpp> 
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/Item/Obj/ItemObj.hpp>
#include <game/KMP/Controller.hpp>
#include <Race/200ccParams.hpp>

//Unoptimized code which is mostly a port of Stebler's version which itself comes from CTGP's, speed factor is in the LapSpeedModifier code



kmWrite32(0x805850c4, 0x7FC3F378); //to get kartMovement
void CannonExitSpeed(KartMovement *kartMovement) {
    float ratio = Pulsar::sInstance->Is200cc() ? 0.6666667f : 1.0f;
    kartMovement->kartSpeed = kartMovement->baseSpeed * ratio;
}
kmCall(0x805850c8, CannonExitSpeed);

void EnableBrakeDrifting() {
    if (Pulsar::sInstance->Is200cc()) {
        for (int i = 0; i < RaceData::sInstance->racesScenario.localPlayerCount; i++) {
            u8 hudPlayerId = RaceData::sInstance->racesScenario.settings.hudPlayerIds[i];

            u32 controllerInfo = SectionMgr::sInstance->pad.padInfos[0].controllerSlotAndTypeActive;
            ControllerType controllerType = ControllerType(controllerInfo & 0xFF);
            RealControllerHolder *controllerHolder = &InputData::sInstance->realControllerHolders[i];

            u16 inputs = controllerHolder->inputStates[0].buttonRaw;
            u32 inputsMask = 0x700;
            switch (controllerType) {
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
            if ((inputs & inputsMask) == inputsMask) controllerHolder->inputStates[0].buttonActions |= 0x10;
        }
    }
}
static RaceFrameHook BrakeDriftingCheck(EnableBrakeDrifting);

bool IsBrakeDrifting(KartStatus *status) {
    if (Pulsar::sInstance->Is200cc()) {
        u32 bitfield0 = status->bitfield0;
        ControllerHolder *controllerHolder = status->base->GetControllerHolder();
        if ((bitfield0 & 0x1F) == 0xF && (bitfield0 & 0x80100000) == 0 && (controllerHolder->inputStates[0].buttonActions & 0x10) != 0x0) return true;
    }
    return false;
}

void BrakeDrifting(KartMovement *movement) {
    movement->UpdateKartSpeed();
    if (IsBrakeDrifting(movement->base.pointers->kartStatus)) movement->acceleration = -1.5f; //JUMP_PAD|RAMP_BOOST|BOOST
}
kmCall(0x80579910, BrakeDrifting);

int BrakeDriftingSound(Kart *kart, KartStatus *status) {
    if (IsBrakeDrifting(status)) return 4;
    return status->bitfield0;
}

asm int BrakeDriftingSoundWrapper() {
    ASM(
        nofralloc;
    mflr r27;
    mr r30, r3;
    bl BrakeDriftingSound;
    mtlr r27;
    rlwinm r0, r3, 0, 31, 31;
    rlwinm r27, r3, 31, 31, 31;
    rlwinm r28, r3, 30, 31, 31;
    mr r3, r30;
    mr r30, r0;
    blr;
    )
}
kmCall(0x806faff8, BrakeDriftingSoundWrapper);

kmWrite32(0x80698f88, 0x60000000);
int BrakeEffectBikes(PlayerEffects *effects) {
    Kart *kart = effects->kart;
    if (Pulsar::sInstance->Is200cc()) {
        if (IsBrakeDrifting(kart->base.pointers->kartStatus)) effects->DisplayEffects2(effects->bikeDriftEffects, 25, 26, true);
        else effects->FadeEffects2(effects->bikeDriftEffects, 25, 26, true);
    }
    return kart->GetDriftState();
}
kmCall(0x80698f8c, BrakeEffectBikes);

kmWrite32(0x80698048, 0x60000000);
int BrakeEffectKarts(PlayerEffects *effects) {
    Kart *kart = effects->kart;
    if (Pulsar::sInstance->Is200cc()) {
        if (IsBrakeDrifting(kart->base.pointers->kartStatus)) effects->DisplayEffects2(effects->kartDriftEffects, 34, 36, true);
        else effects->FadeEffects2(effects->kartDriftEffects, 34, 36, true);
    }
    return kart->GetDriftState();
}
kmCall(0x8069804c, BrakeEffectKarts);


void FastFallingBody(KartStatus *status, KartPhysics *physics) { //weird thing 0x96 padding byte used
    if (Pulsar::sInstance->Is200cc()) {
        if ((status->airtime >= 2) && (!status->bool_0x96 || (status->airtime > 19))) {
            ControllerHolder *controllerHolder = status->base->GetControllerHolder();
            float input = controllerHolder->inputStates[0].stickY <= 0.0f ? 0.0f : (controllerHolder->inputStates[0].stickY + controllerHolder->inputStates[0].stickY);
            physics->gravity -= input * 0.39f;
        }
    }
    status->UpdateFromInput();
}
kmCall(0x805967a4, FastFallingBody);


kmWrite32(0x8059739c, 0x38A10014); //addi r5, sp, 0x14 to align with the Vec3 on the stack
WheelPhysicsHolder *FastFallingWheels(KartSub *sub, u8 wheelIdx, Vec3 *gravityVector) { //weird thing 0x96 status
    float gravity = -1.3f;
    if (Pulsar::sInstance->Is200cc()) {
        KartStatus *status = sub->kartStatus;
        if (status->airtime == 0) status->bool_0x96 = ((status->bitfield0 & 0x80) != 0) ? true : false;
        else if ((status->airtime >= 2) && (!status->bool_0x96 || (status->airtime > 19))) {
            ControllerHolder *controllerHolder = sub->base.GetControllerHolder();
            float input = controllerHolder->inputStates[0].stickY <= 0.0f ? 0.0f : (controllerHolder->inputStates[0].stickY + controllerHolder->inputStates[0].stickY);
            gravity *= (input * 0.3f + 1.0f);
        }
    }
    gravityVector->y = gravity;
    return sub->base.GetWheelPhysicsHolder(wheelIdx);
};
kmCall(0x805973a4, FastFallingWheels);
