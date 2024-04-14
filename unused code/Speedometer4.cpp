/*#include <UI/CtrlRaceBase/Speedometer4.hpp>
#include <Settings/Settings.hpp>

namespace Pulsar {
namespace UI {
u32 CtrlRaceSpeedo4::Count() {
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_RACE, SETTINGRACE_RADIO_SOM) == RACESETTING_SOM_DISABLED) return 0;
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_RACE, SETTINGRACE_RADIO_SOM) == RACESETTING_SOM_LEFT) return 0;
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_RACE, SETTINGRACE_RADIO_SOM) == RACESETTING_SOM_RIGHT) return 0;
    u32 localPlayerCount = RaceData::sInstance->racesScenario.localPlayerCount;
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) localPlayerCount += 1;
    return localPlayerCount;
}
void CtrlRaceSpeedo4::Create(Page& page, u32 index, u32 count) {
    u8 speedoType = (count == 3) ? 4 : count;
    for(int i = 0; i < count; ++i) {
        CtrlRaceSpeedo4* som = new(CtrlRaceSpeedo4);
        page.AddControl(index + i, *som, 0);
        char variant[0x20];
        int pos = i;
        if(i == 0 && Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_RACE, SETTINGRACE_RADIO_SOM) == RACESETTING_SOM_LEFT2) pos = 1;
        snprintf(variant, 0x20, "Speedo4_%1d_%1d", 4, 3);
        som->Load(variant, i);
    }
}
static CustomCtrlBuilder SOM(CtrlRaceSpeedo4::Count, CtrlRaceSpeedo4::Create);

void CtrlRaceSpeedo4::Load(const char* variant, u8 id) {
    this->hudSlotId = id;
    ControlLoader loader(this);
    const char* anims[] ={
        "Hundreds", "Hundreds", nullptr,
        "Tens", "Tens", nullptr,
        "Units", "Units", nullptr,
        "Dot", "Dot",nullptr,
        "Tenths", "Tenths", nullptr,
        "Hundredths", "Hundredths", nullptr,
        "Thousandths", "Thousandths", nullptr,
        nullptr
    };

    loader.Load(UI::raceFolder, "PULSpeedo4", variant, anims);

    this->Animate();
    return;
}

void CtrlRaceSpeedo4::Init() {
    this->HudSlotColorEnable("speed0", true);
    this->HudSlotColorEnable("speed1", true);
    this->HudSlotColorEnable("speed2", true);
    this->HudSlotColorEnable("speed3", true);
    this->HudSlotColorEnable("speed4", true);
    this->HudSlotColorEnable("speed5", true);
    this->HudSlotColorEnable("speed6", true);
    this->HudSlotColorEnable("kmh", true);
    LayoutUIControl::Init();
    return;
}

void CtrlRaceSpeedo4::OnUpdate() {
    this->UpdatePausePosition();
    const u8 digits = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_RACE, SETTINGRACE_SCROLL_SOM);
    const Kart::Pointers& pointers = Kart::Manager::sInstance->players[this->GetPlayerId()]->pointers;
    const Kart::Physics* physics = pointers.kartBody->kartPhysicsHolder->physics;

    Vec3 sum;
    PSVECAdd(&physics->engineSpeed, &physics->speed2, &sum);
    PSVECAdd(&physics->speed3, &sum, &sum);
    float speed = PSVECMag(&sum);
    float speedCap = pointers.kartMovement->hardSpeedLimit;
    if(speed > speedCap) speed = speedCap;


    const u32 speedValue = static_cast<u32>(speed * 1000.0f);

    //10 means empty, 11 dot
    u32 hundreds = speedValue % 1000000 / 100000;
    u32 tens = speedValue % 100000 / 10000;
    u32 units = speedValue % 10000 / 1000;
    u32 dot = digits >= 1 ? 11 : 10;
    u32 tenths = digits >= 1 ? speedValue % 1000 / 100 : 10;
    u32 hundredths = digits >= 2 ? speedValue % 100 / 10 : 10;
    u32 thousandths = digits == 3 ? speedValue % 100 / 10 : 10;

    if(speedValue < 10000) { //shift everything by 2 to the left
        hundreds = units;
        tens = dot;
        units = tenths;
        dot = hundredths;
        tenths = thousandths;
        hundredths = 10;
        thousandths = 10;
    }
    else if(speedValue < 100000) {
        hundreds = tens;
        tens = units;
        units = dot;
        dot = tenths;
        tenths = hundredths;
        hundredths = thousandths;
        thousandths = 10;
    }

    SpeedArg args(hundreds, tens, units, dot, tenths, hundredths, thousandths);
    this->Animate(&args);
    return;
}

void CtrlRaceSpeedo4::Animate(const SpeedArg* args) {
    for(int i = 0; i < 7; ++i) {
        AnimationGroup& group = this->animator.GetAnimationGroupById(i);
        float frame = 0.0f;
        if(args != nullptr) frame = static_cast<float>(args->values[i]);
        group.PlayAnimationAtFrameAndDisable(0, frame);
    }
}
}//namespace UI
}//namespace Pulsar*/