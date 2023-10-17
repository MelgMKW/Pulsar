#include <UI/CtrlRaceBase/Speedometer.hpp>

namespace Pulsar {
namespace UI {
u32 CtrlRaceSpeedo::Count() {
    u32 localPlayerCount = RaceData::sInstance->racesScenario.localPlayerCount;
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) localPlayerCount += 1;
    return localPlayerCount;
}
void CtrlRaceSpeedo::Create(Page& page, u32 index, u32 count) {
    u8 speedoType = (count == 3) ? 4 : count;
    for(int i = 0; i < count; ++i) {
        CtrlRaceSpeedo* som = new(CtrlRaceSpeedo);
        page.AddControl(index + i, *som, 0);
        char variant[0x20];
        snprintf(variant, 0x20, "Speedo_%1d_%1d", speedoType, i);
        som->Load(variant, i);
    }
}
static CustomCtrlBuilder SOM(CtrlRaceSpeedo::Count, CtrlRaceSpeedo::Create);

void CtrlRaceSpeedo::Load(const char* variant, u8 id) {
    this->hudSlotId = id;
    ControlLoader loader(this);
    const char* anims[16] ={ "Hundreds", "Hundreds", nullptr,
     "Tens", "Tens", nullptr,
     "Units", "Units", nullptr,
     "Dot", "Dot",nullptr,
     "Decimals", "Decimals",nullptr, nullptr };

    loader.Load(UI::raceFolder, "speedometer", variant, anims);

    this->Animate();
    return;
}

void CtrlRaceSpeedo::Init() {
    this->HudSlotColorEnable("speed0", true);
    this->HudSlotColorEnable("speed1", true);
    this->HudSlotColorEnable("speed2", true);
    this->HudSlotColorEnable("speed3", true);
    this->HudSlotColorEnable("speed4", true);
    this->HudSlotColorEnable("kmh", true);
    LayoutUIControl::Init();
    return;
}

void CtrlRaceSpeedo::OnUpdate() {
    this->UpdatePausePosition();
    const Kart::Pointers& pointers = Kart::Manager::sInstance->players[this->GetPlayerId()]->pointers;
    const Kart::Physics* physics = pointers.kartBody->kartPhysicsHolder->physics;

    Vec3 sum;
    PSVECAdd(&physics->engineSpeed, &physics->speed2, &sum);
    PSVECAdd(&physics->speed3, &sum, &sum);
    float speed = PSVECMag(&sum);
    float speedCap = pointers.kartMovement->hardSpeedLimit;
    if(speed > speedCap) speed = speedCap;
    const u32 speedValue = static_cast<u32>(speed * 10.0f);

    u32 decimals =speedValue % 10 / 1;
    u32 dot = 11;
    u32 units = speedValue % 100 / 10;
    u32 tens = speedValue % 1000 / 100;
    u32 hundreds = speedValue % 10000 / 1000;
    if(speedValue < 100) {
        hundreds = units;
        tens = dot;
        units = decimals;
        dot = 10;
        decimals = 10;
    }
    else if(speedValue < 1000) {
        hundreds = tens;
        tens = units;
        units = dot;
        dot = decimals;
        decimals = 10;
    }
    SpeedArg args(hundreds, tens, units, dot, decimals);
    this->Animate(&args);
    return;
}

void CtrlRaceSpeedo::Animate(const SpeedArg* args) {
    for(int i = 0; i < 5; ++i) {
        AnimationGroup& group = this->animator.GetAnimationGroupById(i);
        float frame = 0.0f;
        if(args != nullptr) frame = static_cast<float>(args->values[i]);
        group.PlayAnimationAtFrameAndDisable(0, frame);
    }
}
}//namespace UI
}//namespace Pulsar