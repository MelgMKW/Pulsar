#include <kamek.hpp>
#include <MarioKartWii/Race/Racedata.hpp>
#include <MarioKartWii/Race/Raceinfo/Raceinfo.hpp>
#include <MarioKartWii/Kart/KartManager.hpp>
#include <MarioKartWii/Objects/ObjectsMgr.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>
#include <MarioKartWii/3D/Camera/CameraMgr.hpp>
#include <MarioKartWii/UI/Section/SectionMgr.hpp>
#include <MarioKartWii/UI/Page/Other/Votes.hpp>
#include <MarioKartWii/UI/Page/Other/SELECTStageMgr.hpp>
#include <MarioKartWii/UI/Page/Menu/DriftSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/MultiDriftSelect.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceRankNum.hpp>
#include <MarioKartWii/Audio/Actors/KartActor.hpp>
#include <MarioKartWii/AI/AIManager.hpp>
#include <MarioKartWii/RKNet/SELECT.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceBalloon.hpp>
#include <PulsarSystem.hpp>
#include <Network/PulSELECT.hpp>
#include <Network/PacketExpansion.hpp>
#include <Gamemodes/OnlineTT/OnlineTT.hpp>
#include <Gamemodes/KO/KOMgr.hpp>
#include <Settings/Settings.hpp>

namespace Pulsar {

namespace OTT {
void CondCollisions(Kart::Collision& collision, const Kart::Player& other) {
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) return;
    collision.CheckKartCollision(other);
}
kmCall(0x80596dc8, CondCollisions);

void CondSlipstream(Kart::Movement& movement) {
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) return;
    movement.UpdateSlipstream();
}
kmCall(0x805798c0, CondSlipstream);

void CondTTObjects(u32 r3, u32 r4, u32 r5, u32 r6, bool isTT) {
    register ObjectsMgr* mgr;
    asm(mr mgr, r31;);
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) isTT = true;
    mgr->isTT = isTT;
}
kmCall(0x8082a4ec, CondTTObjects);

//TT Times 04840750 38000002
//Start with 3 shrooms part of "SetStartingItem" in MiscRace
//Display end times already part of Pulsar

void CondStartPos(KMP::Holder<KTPT>& holder, Vec3& position, Vec3& rotation, u32 playerPosition, u32 playerCount) {
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) {
        playerPosition = 1;
        playerCount = 1;
    }
    holder.CalcCoordinates_0Indexed(position, rotation, playerPosition, playerCount);
}
kmBranch(0x80514b2c, CondStartPos);

bool CondAIRelatedTTCheck(bool, const Racedata& racedata) { //most notably the animation on overtake
    const GameMode mode = racedata.racesScenario.settings.gamemode;
    bool isTT = (mode == MODE_TIME_TRIAL || mode == MODE_GHOST_RACE);
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) isTT = true;
    return isTT;
}
kmBranch(0x807396b0, CondAIRelatedTTCheck);

/*
static const RaceinfoPlayer* GetCorrectRaceinfoPlayer(const Raceinfo& raceInfo) { //TTSplits::BeforeEntranceAnimations
    return raceInfo.players[Racedata::sInstance->racesScenario.settings.hudPlayerIds[0]];
}
kmCall(0x80855b90, GetCorrectRaceinfoPlayer);
kmWrite32(0x80855b98, 0x60000000);
*/

static bool CondTTCycles(const Raceinfo& raceInfo) { //this function is only called for onlineModes, true = objects and entity get updated this frame
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) {
        const OpeningPan* pan = RaceCameraMgr::sInstance->cameras[0]->openingPan;
        if(pan->bitfield & 0x3) return true; //Is the pan not finished yet? always update the objects
    }
    return raceInfo.IsAtLeastStage(RACESTAGE_COUNTDOWN); //if the pan is finished but the countdown has not started, freeze the objects
}
kmCall(0x80554b8c, CondTTCycles);

static bool CondPylonCollision(u32, u8 playerId) { //returns true if ghost collision, false if normal collision
    PlayerType type = Racedata::sInstance->racesScenario.players[playerId].playerType;
    if(System::sInstance->IsContext(PULSAR_MODE_OTT) && type != PLAYER_REAL_LOCAL) type = PLAYER_GHOST;
    else if(type == PLAYER_GHOST && playerId != 1) type = PLAYER_REAL_LOCAL; //so that when you watch a ghost, it hits the main pylon
    return type == PLAYER_GHOST;
}
kmCall(0x8082dc5c, CondPylonCollision);
kmWrite32(0x8082dc60, 0x2c030001);

static bool CondPoihanaStopOnHit(const Kart::Player& player) { //disables the poihana animating on hit if returns false
    const u32 bitfield = player.pointers.kartStatus->bitfield4;
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) return !(bitfield & 0x2); //return false if player is local, as that is the only situation where the cataquack should stop
    else return bitfield & 0x40; //return false if player is not a ghost
}
kmCall(0x807493e4, CondPoihanaStopOnHit);

static void CondTTSeed(RacedataScenario& scenario) { //real non-ghost count is stored in system
    const GameMode old = scenario.settings.gamemode;
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) scenario.settings.gamemode = MODE_TIME_TRIAL;
    scenario.InitRNG();
    scenario.settings.gamemode = old;
}
kmCall(0x8052fe18, CondTTSeed);

static void CondAIMgrIsTT(u32, u32, bool isTT) {
    register AI::Manager* mgr;
    asm(mr mgr, r31;);
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) isTT = true;
    mgr->isTT = isTT;
}
kmCall(0x80738f64, CondAIMgrIsTT);

static void CondRaceinfoRandom(Random& random) {
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) {
        const RaceStage stage = Raceinfo::sInstance->stage;
        const OpeningPan* pan = RaceCameraMgr::sInstance->cameras[0]->openingPan;
        if(stage == RACESTAGE_INTRO && (pan->bitfield & 0x8)) return; //do not update random if the pan has ended but the countdown hasn't started yet
    }
    random.Next();
}
kmCall(0x80554cf8, CondRaceinfoRandom);


void CondOpacity() {
    if(!System::sInstance->IsContext(PULSAR_MODE_OTT)) return;
    Kart::Manager* kartMgr = Kart::Manager::sInstance;
    for(int i = 0; i < kartMgr->playerCount; ++i) {

        Kart::Pointers& pointers = kartMgr->players[i]->pointers;
        u32 scnObjDrawOptionsIdx = (pointers.kartStatus->bitfield4 & 0x2) ? 0xA : 1; //is the player local?

        //MAKE SHARED FUNC WITH ENHANCED REPLAY with bool istransparent and driver as args
        DriverController* driver = pointers.driverController;
        pointers.kartBody->UpdateModelDrawPriority(scnObjDrawOptionsIdx);
        if(driver->driverModel != nullptr) driver->driverModel->UpdateDrawPriority(scnObjDrawOptionsIdx);
        if(driver->driverModel_lod != nullptr) driver->driverModel_lod->UpdateDrawPriority(scnObjDrawOptionsIdx);
        if(driver->miiHeads != nullptr) driver->miiHeads->UpdateDrawPriority(scnObjDrawOptionsIdx);
        if(driver->ticoModel != nullptr) driver->ticoModel->tico->UpdateDrawPriority(scnObjDrawOptionsIdx);
        if(driver->toadetteHair != nullptr && driver->toadetteHair->cb != 0) driver->toadetteHair->cb->hair->UpdateDrawPriority(scnObjDrawOptionsIdx);
        for(int j = 0; j < pointers.values->wheelCount0; ++j) {
            pointers.wheels[j]->UpdateModelDrawPriority(scnObjDrawOptionsIdx);
            pointers.suspensions[j]->UpdateModelDrawPriority(scnObjDrawOptionsIdx);
        }
    }
}
RaceLoadHook opacity(CondOpacity);

static void EnableOpacityFunctionality(EGG::ScnRenderer& renderer, u32 enabledEffectsFlag) {
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) enabledEffectsFlag |= 1;
    renderer.CreatePath(enabledEffectsFlag, nullptr);
}
kmCall(0x805b15e0, EnableOpacityFunctionality);

static UnkType PreventBurnOuts(Kart::Status& status, s32 startBoostIdx) {
    if(startBoostIdx == -1 && System::sInstance->IsContext(PULSAR_MODE_OTT)) {
        startBoostIdx = 1;
        status.startBoostIdx = 1;
    }
    return status.ApplyStartBoost(startBoostIdx);
}
kmCall(0x80595ad4, PreventBurnOuts);

static void SELECTStageMgrBeforeControlUpdate(Pages::SELECTStageMgr* stageMgr) {
    System* system = System::sInstance;
    const Pages::SELECTStageMgr::Status old = stageMgr->status;
    if(system->ottVoteState != COMBO_NONE) stageMgr->status = Pages::SELECTStageMgr::STATUS_VR_PAGE; //so that the countdown shows
    stageMgr->Pages::SELECTStageMgr::BeforeControlUpdate();
    stageMgr->status = old;

    if(system->IsContext(PULSAR_MODE_OTT)) {
        const RKNet::Controller* controller = RKNet::Controller::sInstance;
        const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
        Network::ExpSELECTHandler& handler = Network::ExpSELECTHandler::Get();
        Network::PulSELECT* hostSelect;
        const u8 hostAid = sub.hostAid;
        const u8 localAid = sub.localAid;
        if(hostAid == localAid) hostSelect = &handler.toSendPacket;
        else hostSelect = &handler.receivedPackets[hostAid];

        if(hostSelect->allowChangeComboStatus > 0) {
            bool hasReceivedEveryone = true;
            bool isEveryoneWaiting = true;
            bool isEveryoneInRace = true;

            for(int i = 0; i < 12; ++i) {
                if((1 << i & sub.availableAids) == 0) continue;
                if(i == localAid) continue;
                if(system->ottVoteState == COMBO_SELECTED) {
                    if(handler.receivedPackets[i].allowChangeComboStatus < Network::SELECT_COMBO_SELECTED) hasReceivedEveryone = false;
                }
                if(hostAid == localAid) {
                    if(system->ottVoteState == WAITING_FOR_START) {
                        if(handler.receivedPackets[i].allowChangeComboStatus < Network::SELECT_COMBO_WAITING_FOR_START) isEveryoneWaiting = false;
                    }
                    else if(system->ottVoteState == HOST_START) {
                        if(Network::GetLastRecvSECTIONSize(i, Network::PulSELECT::idx) != 0) isEveryoneInRace = false;
                    }
                }
            }

            if(hasReceivedEveryone && system->ottVoteState == COMBO_SELECTED) {
                system->ottVoteState = WAITING_FOR_START;
                handler.toSendPacket.allowChangeComboStatus = Network::SELECT_COMBO_WAITING_FOR_START;
            }
            if(hostAid == sub.localAid) {
                if(isEveryoneWaiting && system->ottVoteState == WAITING_FOR_START) {
                    system->ottVoteState = HOST_START;
                    handler.toSendPacket.allowChangeComboStatus = Network::SELECT_COMBO_HOST_START;
                }
                if(isEveryoneInRace && system->ottVoteState == HOST_START) system->ottVoteState = SELECT_READY;
            }
            else if(hostSelect->allowChangeComboStatus == Network::SELECT_COMBO_HOST_START) system->ottVoteState = SELECT_READY;
        }

        if(system->ottVoteState == SELECT_READY) {
            const SectionId id = static_cast<SectionId>(SectionMgr::sInstance->curSection->sectionId + 0x10);
            stageMgr->PrepareRace();
            stageMgr->ChangeSectionBySceneChange(id, 0, 0.0f);
        }
    }
}

kmWritePointer(0x808C06E4, SELECTStageMgrBeforeControlUpdate);

static void PreventVoteChangeSection(Pages::Vote& vote, SectionId id, float delay) {
    System* system = System::sInstance;
    system->ottVoteState = COMBO_NONE;
    if(system->IsContext(PULSAR_MODE_OTT)) {
        RKNet::Controller* controller = RKNet::Controller::sInstance;
        RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
        Network::ExpSELECTHandler& handler = Network::ExpSELECTHandler::Get();
        const Network::PulSELECT* select;
        const u8 hostAid = sub.hostAid;
        if(hostAid == sub.localAid) select = &handler.toSendPacket;
        else select = &handler.receivedPackets[hostAid];
        if(select->allowChangeComboStatus > 0) {
            Pages::SELECTStageMgr* page = SectionMgr::sInstance->curSection->Get<Pages::SELECTStageMgr>();
            page->countdown.SetInitial(10.0f);
            page->countdown.isActive = true;
            page->timerControl.Reset();
            if(system->IsContext(PULSAR_MODE_KO) && system->koMgr->isSpectating) {
                handler.toSendPacket.allowChangeComboStatus = Network::SELECT_COMBO_SELECTED;
                system->ottVoteState = COMBO_SELECTED;
            }
            else {
                system->ottVoteState = COMBO_SELECTION;
                handler.toSendPacket.allowChangeComboStatus = Network::SELECT_COMBO_SELECTING;
                page->AddPageLayer(PAGE_CHARACTER_SELECT, 0);
            }
            vote.EndStateAnimated(0, delay);
            return;
        }
    }
    vote.ChangeSectionBySceneChange(id, 0, delay);
}
kmCall(0x80643da0, PreventVoteChangeSection);

static void FixAfterDrift(Pages::Menu& menu, PageId id, PushButton& button) { //menu is either drift or multidrift
    System* system = System::sInstance;
    if(system->ottVoteState == COMBO_SELECTION) {
        system->ottVoteState = COMBO_SELECTED;
        Network::ExpSELECTHandler& handler = Network::ExpSELECTHandler::Get();
        handler.toSendPacket.playersData[0].character = SectionMgr::sInstance->sectionParams->characters[0];
        handler.toSendPacket.playersData[0].kart = SectionMgr::sInstance->sectionParams->karts[0];
        handler.toSendPacket.allowChangeComboStatus = Network::SELECT_COMBO_SELECTED;
        menu.EndStateAnimated(0, 0.0f);
    }
    else menu.LoadNextPageById(id, button);
}
kmCall(0x8084e698, FixAfterDrift);
//kmCall(0x8084b7d4, FixAfterDrift);


//OPTIONS
static void MuteKartSounds(Audio::EngineMgr* mgr, Audio::KartActor* actor) {
    mgr->Init(actor);
    if(System::sInstance->IsContext(PULSAR_MODE_OTT) && !actor->isLocal && Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_OTT, SETTINGOTT_MUTEPTANDPLAYERS) == true) {
        actor->isGhost = true;
    }
}
kmCall(0x80707620, MuteKartSounds);

static bool MuteCharSounds(Kart::Link* link) {
    const u32 bitfield = link->pointers->kartStatus->bitfield4;
    if(System::sInstance->IsContext(PULSAR_MODE_OTT) && Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_OTT, SETTINGOTT_MUTEPTANDPLAYERS) == true) {
        return !(bitfield & 0x2); //isLocal
    }
    return bitfield & 0x40; //isGhost
}
kmCall(0x80716208, MuteCharSounds);

static bool MutePositionTracker(CtrlRaceRankNum& tracker) { //isInactive = muted if true, bctrl = IsInactive
    asmVolatile(bctrl;);
    register bool isInactive;
    asm(mr isInactive, r3;);
    if(System::sInstance->IsContext(PULSAR_MODE_OTT) && !isInactive) isInactive = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_OTT, SETTINGOTT_MUTEPTANDPLAYERS);
    return isInactive;
}
kmCall(0x807F4AC4, MutePositionTracker);
kmCall(0x807f4b00, MutePositionTracker);

//Hide Names part of battleglitch

}//namespace OTT
}//namespace Pulsar
//TO DO:
//time diff

//OPTIONS:
//Mute position tracker, mute other players, allow change combo after vote (host only)
