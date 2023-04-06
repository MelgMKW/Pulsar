#include <UI/CtrlRaceBase/Speedometer.hpp>

namespace PulsarUI {
u32 CtrlRaceSpeedo::Count() {
    u32 localPlayerCount = RaceData::sInstance->racesScenario.localPlayerCount;
    SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if (sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) localPlayerCount += 1;
    return localPlayerCount;
}
void CtrlRaceSpeedo::Create(Page *page, u32 index) {
    u32 localPlayerCount = RaceData::sInstance->racesScenario.localPlayerCount;
    SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if (sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) localPlayerCount += 1;
    u8 speedoType = (localPlayerCount == 3) ? 4 : localPlayerCount;
    for (int i = 0; i < localPlayerCount; i++) {
        CtrlRaceSpeedo *som = new(CtrlRaceSpeedo);
        page->AddControl(index + i, som, 0);
        char variant[0x20];
        snprintf(variant, 0x20, "CtrlRaceSpeedo_%1d_%1d", speedoType, i);
        som->Load(variant, i);
    }
}
static CustomCtrlBuilder SOM(CtrlRaceSpeedo::Count, CtrlRaceSpeedo::Create);

void CtrlRaceSpeedo::Load(const char *variant, u8 id) { //blatant copy
    this->hudSlotId = id;
    ControlLoader loader(this);
    const char *anims[16] = { "eHundreds", "texture_pattern_0_9_0", NULL,
     "eTens", "texture_pattern_0_9_1", NULL,
     "eUnits", "texture_pattern_0_9_2", NULL,
     "eDot", "texture_pattern_0_9_3",NULL,
     "eDecimals", "texture_pattern_0_9_4",NULL, NULL };

    loader.Load("game_image", "speedometer", variant, anims);
    AnimationGroup *paneGroup = this->animator.GetAnimationGroupById(0);
    paneGroup->PlayAnimationAtFrameAndDisable(0, 0.0f);

    paneGroup = this->animator.GetAnimationGroupById(1);
    paneGroup->PlayAnimationAtFrameAndDisable(0, 0.0f);

    paneGroup = this->animator.GetAnimationGroupById(2);
    paneGroup->PlayAnimationAtFrameAndDisable(0, 0.0f);

    paneGroup = this->animator.GetAnimationGroupById(3);
    paneGroup->PlayAnimationAtFrameAndDisable(0, 0.0f);

    paneGroup = this->animator.GetAnimationGroupById(4);
    paneGroup->PlayAnimationAtFrameAndDisable(0, 0.0f);
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
    u8 id = this->GetPlayerId();

    KartPointers *pointers = &KartHolder::sInstance->karts[id]->pointers;
    KartPhysicsHolder *physicsHolder = pointers->kartBody->kartPhysicsHolder;
    KartPhysics *physics = physicsHolder->kartPhysics;

    Vec3 sum;
    PSVECAdd(static_cast<Vec *>(&physics->engineSpeed), &physics->speed2, &sum);
    PSVECAdd(&physics->speed3, &sum, &sum);
    float speed = PSVECMag(&sum);
    float speedCap = pointers->kartMovement->hardSpeedLimit;
    if (speed > speedCap) speed = speedCap;


    u32 engineSpeed = (u32)(speed * 10.0f);

    float decimals = (float)(engineSpeed % 10 / 1);
    float dot = 11.0f;
    float units = (float)(engineSpeed % 100 / 10);
    float tens = (float)(engineSpeed % 1000 / 100);
    float hundreds = (float)(engineSpeed % 10000 / 1000);
    if (engineSpeed < 100) {
        hundreds = units;
        tens = dot;
        units = decimals;
        dot = 10.0f;
        decimals = 10.0f;
    }
    else if (engineSpeed < 1000) {
        hundreds = tens;
        tens = units;
        units = dot;
        dot = decimals;
        decimals = 10.0f;
    }
    AnimationGroup *paneGroup = this->animator.GetAnimationGroupById(3);
    paneGroup->PlayAnimationAtFrameAndDisable(0, decimals);

    paneGroup = this->animator.GetAnimationGroupById(4);
    paneGroup->PlayAnimationAtFrameAndDisable(0, dot);

    paneGroup = this->animator.GetAnimationGroupById(2); //third digit
    paneGroup->PlayAnimationAtFrameAndDisable(0, units);

    paneGroup = this->animator.GetAnimationGroupById(1); //second digit
    paneGroup->PlayAnimationAtFrameAndDisable(0, tens);

    paneGroup = this->animator.GetAnimationGroupById(0); //first digit
    paneGroup->PlayAnimationAtFrameAndDisable(0, hundreds);
    return;
}
}//namespace PulsarUI