#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/GhostReplayPause.hpp>
#include <MarioKartWii/Kart/KartManager.hpp>
#include <MarioKartWii/Mii/MiiHeadsModel.hpp>
#include <MarioKartWii/3D/Camera/CameraMgr.hpp>
#include <MarioKartWii/3D/Camera/RaceCamera.hpp>
#include <UI/UI.hpp>


//Very old code, but still does the job; clicking watch replay will add the TT interface, solidity to the main ghost, the speedometer, etc...

kmWrite32(0x80630450, 0x3880000d);  //To use the correct onInit
kmWrite32(0x80630474, 0x3880000d);
kmWrite32(0x80630498, 0x3880000d);
kmWrite32(0x80631ce4, 0x2c030035);  //Music
kmWrite32(0x806320ac, 0x2c030035);
kmWrite32(0x80711444, 0x3803ffcb);
kmWrite32(0x8071e4a0, 0x38600000);  //Lakitu
kmWrite32(0x807f1590, 0x60000000);  //Kart Name
kmWrite32(0x80856e64, 0x2c040035); //Removes fade at the end
kmWrite32(0x80857540, 0x2c000035); //Fixes instant FINISH flash at the end
kmWrite32(0x80859ed4, 0x48000048); //no immediate unload if ghost

namespace Pulsar {
static void ChangeGhostOpacity(u8 focusedPlayerIdx);

namespace UI {
static void CreateTTInterface(Section* section, PageId id) {
    section->CreateAndInitPage(PAGE_TT_INTERFACE);
    section->CreateAndInitPage(PAGE_TT_SPLITS);
    ChangeGhostOpacity(0);
}
kmCall(0x8062ccd4, CreateTTInterface);
kmCall(0x8062cc5c, CreateTTInterface);
kmCall(0x8062cc98, CreateTTInterface);

static PageId TTSplitsNextPage() {
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId == SECTION_TT || sectionId == SECTION_GHOST_RACE_1 || sectionId == SECTION_GHOST_RACE_2) return PAGE_TT_LEADERBOARDS;
    else if(sectionId == SECTION_GP) return PAGE_GPVS_LEADERBOARD_UPDATE;
    else if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) return PAGE_GHOST_REPLAY_PAUSE_MENU;
    return PAGE_NONE;
}
kmBranch(0x808561dc, TTSplitsNextPage);

static PageId TTPauseNextPage(const Pages::RaceHUD& page) {
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) return PAGE_GHOST_REPLAY_PAUSE_MENU;
    return page.GetPausePageId();
}
kmCall(0x808569e0, TTPauseNextPage);

static void OnContinueButtonTTPauseClick(Pages::GhostReplayPause& page, PageId id) {
    const u32 stage = RaceInfo::sInstance->stage;
    if(stage == 0x4) id = PAGE_TT_SPLITS; //if race is finished, repurpose the continue button
    page.nextPage = id;
    return;
}
kmCall(0x8085a1e0, OnContinueButtonTTPauseClick);

static bool WillGhostBeCompared(const RaceData& racedata) {
    const SectionMgr* sectionMgr = SectionMgr::sInstance;
    const SectionId sectionId = sectionMgr->curSection->sectionId;
    register Timer* ghostTimer;
    asm(addi ghostTimer, r15, 0x48;);
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) {
        ghostTimer->minutes = 0xFFFF; //guarantee a cheer
        return true;
    }
    else if(racedata.racesScenario.settings.gamemode == MODE_GHOST_RACE) return true;
    return false;
}
kmCall(0x808570a0, WillGhostBeCompared);
kmWrite32(0x80857088, 0x40820018);
kmWrite32(0x808570a4, 0x2C030001);
static u8 CharCheerGetCorrectArguments(int r3, u8 id) {
    u8 ret = RaceData::sInstance->racesScenario.players[id].hudSlotId;
    if(ret == -1) ret = 0;
    return ret;
}
kmCall(0x808570c4, CharCheerGetCorrectArguments);

static void PatchFinishRaceBMGID(LayoutUIControl& control, u32 bmgId, const TextInfo* text) {
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) bmgId = BMG_FINISH;
    control.SetMessage(bmgId, text);
}
kmCall(0x8085728c, PatchFinishRaceBMGID);
}//namespace UI


static int ChangePlayerType(const RaceDataPlayer& player, u8 id) {
    PlayerType type = RaceData::sInstance->racesScenario.players[id].playerType;
    if(type == PLAYER_GHOST && id == 0) return 0;
    return type;
}
kmCall(0x80594444, ChangePlayerType);
kmWrite32(0x80594434, 0x889F0010);
kmWrite32(0x80594448, 0x2c030000);
kmWrite32(0x80594450, 0x2c030001);
kmWrite32(0x80594458, 0x2c030003);

/*
Kart::BRRESHandle* PatchOpacity(Kart::BRRESHandle& handle, Light* light, bool isGhost, u8 playerId) {
    if(playerId == 0) isGhost = false;
    return new(&handle) Kart::BRRESHandle(light, isGhost, playerId);
}
kmCall(0x8058e2b8, PatchOpacity);
kmCall(0x807c7870, PatchOpacity);

*/

bool PatchIsLocalCheck(const Kart::Player& kartPlayer) {
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) return false;
    return kartPlayer.IsLocal();
}
kmCall(0x80783770, PatchIsLocalCheck);

static bool EnableCPUDrivingAfterRace(const KartAIController& aiController) {
    const u8 id = aiController.link.GetPlayerIdx();
    const PlayerType type = RaceData::sInstance->racesScenario.players[id].playerType;
    if(type == PLAYER_GHOST && id != 0) return true;
    return false;
}
kmCall(0x80732634, EnableCPUDrivingAfterRace);

asmFunc PatchSoundIssues() {
    ASM(
        nofralloc;
    lwz r5, 0 (r4); //Default
    subi r0, r5, SECTION_WATCH_GHOST_FROM_CHANNEL;
    cmplwi r0, 2;
    bgt + end;
    li r5, 0x1f;
end:;
    blr;
    )
}
kmCall(0x80716064, PatchSoundIssues);

asmFunc CreateSwitchPlayerPtmfs() {
    ASM(
        nofralloc;
    cmpwi r0, 0x6e;
    cmpwi cr1, r0, SECTION_WATCH_GHOST_FROM_CHANNEL;
    blt + cr1, end;
    cmpwi cr1, r0, SECTION_WATCH_GHOST_FROM_MENU;
    bgt + cr1, end;
    crclr 4 * cr0 + lt;
end:
    blr;

    )
}
kmCall(0x808568b4, CreateSwitchPlayerPtmfs);
kmCall(0x80856d38, CreateSwitchPlayerPtmfs);

static void CreateAdditionalCameras(RaceCameraMgr* mgr) {
    const SectionId id = SectionMgr::sInstance->nextSectionId;
    if(id >= SECTION_WATCH_GHOST_FROM_CHANNEL && id <= SECTION_WATCH_GHOST_FROM_MENU) mgr->isOnlineSpectating = true;
    mgr->SetInstance(mgr);
}
kmCall(0x805a8520, CreateAdditionalCameras);


RaceData* RemoveLiveview() {
    register RaceCameraMgr* mgr;
    asm(mr mgr, r31;);
    const SectionId id = SectionMgr::sInstance->nextSectionId;
    if(id >= SECTION_WATCH_GHOST_FROM_CHANNEL && id <= SECTION_WATCH_GHOST_FROM_MENU) mgr->isOnlineSpectating = false;
    return RaceData::sInstance;
}
kmCall(0x805a8c68, RemoveLiveview);

static void AddOpeningPanToEveryone(RaceCamera* camera, u8 playerId, GameScreen& screen, BCP* rawBCP, u8 r7) {
    register RaceCameraMgr* mgr;
    asm(mr mgr, r31;);
    const SectionId id = SectionMgr::sInstance->nextSectionId;
    if(id >= SECTION_WATCH_GHOST_FROM_CHANNEL && id <= SECTION_WATCH_GHOST_FROM_MENU) rawBCP = mgr->rawBCP;
    new (camera) RaceCamera(playerId, screen, rawBCP, r7);
}
kmCall(0x805a8774, AddOpeningPanToEveryone);

void* PatchMiiHeadsOpacity(MiiHeadsModel& model, Mii* mii, MiiDriverModel* driverModel, u32 r6, nw4r::g3d::ScnMdl::BufferOption option,
    u32 r8, u32 id) {
    if(RaceInfo::sInstance != nullptr && id == 0) model.scnObjDrawOptionsIdx = 0xA;
    return model.InitModel(mii, driverModel, r6, option, r8, id);
}
kmCall(0x807dc0e8, PatchMiiHeadsOpacity);

static void ChangeGhostOpacity(u8 focusedPlayerIdx) {
    const SectionId id = SectionMgr::sInstance->curSection->sectionId;
    if(id < SECTION_WATCH_GHOST_FROM_CHANNEL || id > SECTION_WATCH_GHOST_FROM_MENU) return;
    Kart::Manager* kartMgr = Kart::Manager::sInstance;
    for(int i = 0; i < kartMgr->playerCount; ++i) {
        u32 scnObjDrawOptionsIdx = i == focusedPlayerIdx ? 0xA : 1;
        Kart::Pointers& pointers = kartMgr->players[i]->pointers;
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
    RaceData::sInstance->racesScenario.settings.hudPlayerIds[0] = focusedPlayerIdx;
}
kmBranch(0x805a9b60, ChangeGhostOpacity);




}//namespace Pulsar


//kmWrite32(0x805a84d4, 0x38000001);

//subi 50 bgt 2

//808568cc
//80856d78