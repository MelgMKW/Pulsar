#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <UI/UI.hpp>
#include <Ghost/UI/MultiGhostDiff.hpp>
#include <UI/CtrlRaceBase/CustomCtrlRaceBase.hpp>
#include <PulsarSystem.hpp>

namespace Pulsar {
namespace UI {
//brctr change to PULtTime
kmWrite24(0x808a9af9, 'PUL');

u32 MultiGhostDiff::Count() {
    return System::sInstance->IsContext(PULSAR_MODE_OTT);
}
void MultiGhostDiff::Create(Page& page, u32 idx, u32 unused) {
    MultiGhostDiff* ghostDiff = new(MultiGhostDiff);
    page.AddControl(idx, *ghostDiff, 0);
    ghostDiff->Load();
}
kmWrite32(0x8085844c, 0x48000060);
kmCall(0x808584c0, MultiGhostDiff::Create); //skip inlined ctor of usual ghostdiff
kmWrite32(0x808584d4, 0x60000000); //nop load of usual ghostdiff

static CustomCtrlBuilder GhostDiff(MultiGhostDiff::Count, MultiGhostDiff::Create);

MultiGhostDiff::MultiGhostDiff() {
    u32 count = 0;
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) count = 2;
    else {
        RacedataScenario* scenario = &Racedata::sInstance->menusScenario;
        if(scenario->players[0].playerType == PLAYER_GHOST) this->isGhostReplay = true;
        for(int i = 1; i < 4; ++i) if(scenario->players[i].playerType == PLAYER_GHOST) ++count;
    }
    this->diffTimeCount = count;
}

void MultiGhostDiff::Load() {
    if(this->diffTimeCount > 0) {
        if(System::sInstance->IsContext(PULSAR_MODE_OTT)) this->diffTimes = new OTTGhostDiff[this->diffTimeCount];
        else this->diffTimes = new CtrlRaceGhostDiffTime[this->diffTimeCount];

        this->InitControlGroup(this->diffTimeCount);
        char variantName[0x80];
        for(int i = 0; i < this->diffTimeCount; ++i) {
            this->AddControl(i, &this->diffTimes[i]);
            snprintf(variantName, 0x80, "TimeDiffGhost_%d", i);
            this->diffTimes[i].Load(variantName);
            if(!System::sInstance->IsContext(PULSAR_MODE_OTT)) this->diffTimes[i].ghostData.Init(Racedata::sInstance->ghosts[i + this->isGhostReplay]);
            else reinterpret_cast<OTTGhostDiff&>(this->diffTimes[i]).SetIdx(i);
        }
    }

}

//Idx: 0 is for 1st and to 1st, 1 is for player in front (but not for 2nd since only first is in front)
void OTTGhostDiff::OnUpdate() {
    this->UpdatePausePosition();
    const u8 playerId = this->GetPlayerId();
    const Raceinfo* raceInfo = Raceinfo::sInstance;
    const RaceinfoPlayer* curPlayer = raceInfo->players[playerId];
    u8 maxLap = curPlayer->maxLap;
    const u8 curPos = curPlayer->position;
    RaceinfoPlayer* target = nullptr;
    if(this->GetIdx() == 0) {
        if(curPos == 1) {
            target = raceInfo->players[raceInfo->playerIdInEachPosition[1]]; //I'm in 1st, target is 2nd
            maxLap = target->maxLap; //change max lap to the target as the control can only display once they have crossed
        }
        else target = raceInfo->players[raceInfo->playerIdInEachPosition[0]]; //I'm not in 1st, target is 1st
    }
    else if(curPos > 2) target = raceInfo->players[raceInfo->playerIdInEachPosition[curPos - 2]]; //I'm in >3rd, target is the position in front
    if(this->curLap != maxLap && target != nullptr) {
        this->timers[1] = target->lapSplits[target->maxLap - 2];
        this->timers[0] = curPlayer->lapSplits[curPlayer->maxLap - 2];
        Text::Info info;

        const bool amISlower = this->timers[0] > this->timers[1];
        const Timer res = this->SubtractTimers(this->timers[!amISlower], this->timers[amISlower]);
        TimerToTextInfo(res, info);
        this->animator.GetAnimationGroupById(0).PlayAnimationAtFrame(amISlower, 0.0f);
        u32 bmgId;
        if(amISlower) {
            info.intToPass[0] = target->position;
            bmgId = BMG_OTT_TIME_DIFF;
        }
        else bmgId = BMG_TIMER_DIFF_MINUS;
        this->SetMessage(bmgId, &info);
    }
    this->curLap = maxLap;
}

/*
void MultiGhostDiff::Init() {
    Racedata* racedata = Racedata::sInstance;
    for(int i = 0; i < this->diffTimeCount; i++) this->diffTimes[i].ghostData.Init(racedata->ghosts[i + this->isGhostReplay]);
    UIControl::Init();
}
*/
kmWrite32(0x807ee500, 0x48000010);
}//namespace UI
}//namespace Pulsar