#include <Ghost/UI/MultiGhostDiff.hpp>

namespace Pulsar {
namespace UI {
//brctr change to PULtTime
kmWrite24(0x808a9af9, 'PUL');

MultiGhostDiff* MultiGhostDiff::Create(Pages::RaceHUD* page, u8 idx) {
    MultiGhostDiff* ghostDiff = new(MultiGhostDiff);
    page->AddControl(idx, *ghostDiff, 0);
    ghostDiff->Load();
    return ghostDiff;
}
kmWrite32(0x8085844c, 0x48000060);
kmCall(0x808584c0, MultiGhostDiff::Create); //skip inlined ctor of usual ghostdiff
kmWrite32(0x808584d4, 0x60000000); //nop load of usual ghostdiff

MultiGhostDiff::MultiGhostDiff() {
    RacedataScenario* scenario = &RaceData::sInstance->menusScenario;
    if(scenario->players[0].playerType == PLAYER_GHOST) this->isGhostReplay = true;
    u32 count = 0;
    for(int i = 1; i < 4; i++) if(scenario->players[i].playerType == PLAYER_GHOST) count++;
    this->diffTimeCount = count;
}

void MultiGhostDiff::Load() {
    if(this->diffTimeCount > 0) {
        this->diffTimes = new CtrlRaceGhostDiffTime[this->diffTimeCount];
        this->InitControlGroup(this->diffTimeCount);
        char variantName[0x80];
        for(int i = 0; i < this->diffTimeCount; i++) {
            this->AddControl(i, &this->diffTimes[i]);
            snprintf(variantName, 0x80, "TimeDiffGhost_%d", i);
            this->diffTimes[i].Load(variantName);
            this->diffTimes[i].ghostData.Init(RaceData::sInstance->ghosts[i + this->isGhostReplay]);
        }
    }

}

/*
void MultiGhostDiff::Init() {
    RaceData* racedata = RaceData::sInstance;
    for(int i = 0; i < this->diffTimeCount; i++) this->diffTimes[i].ghostData.Init(racedata->ghosts[i + this->isGhostReplay]);
    UIControl::Init();
}
*/
kmWrite32(0x807ee500, 0x48000010);
}//namespace UI
}//namespace Pulsar