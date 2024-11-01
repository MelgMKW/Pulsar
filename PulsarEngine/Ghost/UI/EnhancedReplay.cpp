
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/GhostReplayPause.hpp>
#include <MarioKartWii/Kart/KartManager.hpp>
#include <MarioKartWii/Race/Raceinfo/Raceinfo.hpp>
#include <UI/UI.hpp>


//Very old code, but still does the job; clicking watch replay will add the TT interface, solidity to the main ghost, the speedometer, etc...
//Spectating.hpp handles the spectating side of things

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
static void CreateTTHUD(Section* section, PageId id) {
    section->CreateAndInitPage(PAGE_TT_HUD);
    section->CreateAndInitPage(PAGE_TT_SPLITS);
    ChangeGhostOpacity(0);
}
kmCall(0x8062ccd4, CreateTTHUD);
kmCall(0x8062cc5c, CreateTTHUD);
kmCall(0x8062cc98, CreateTTHUD);

static PageId TTPauseNextPage(const Pages::RaceHUD& page) {
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) return PAGE_GHOST_REPLAY_PAUSE_MENU;
    return page.GetPausePageId();
}
kmCall(0x808569e0, TTPauseNextPage);

static void OnContinueButtonTTPauseClick(Pages::GhostReplayPause& page, PageId id) {
    const u32 stage = Raceinfo::sInstance->stage;
    if(stage == 0x4) id = PAGE_TT_SPLITS; //if race is finished, repurpose the continue button
    page.nextPage = id;
    return;
}
kmCall(0x8085a1e0, OnContinueButtonTTPauseClick);

static bool WillGhostBeCompared(const Racedata& racedata) {
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
    u8 ret = Racedata::sInstance->racesScenario.players[id].hudSlotId;
    if(ret == -1) ret = 0;
    return ret;
}
kmCall(0x808570c4, CharCheerGetCorrectArguments);

static void PatchFinishRaceBMGID(LayoutUIControl& control, u32 bmgId, const Text::Info* text) {
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) bmgId = BMG_FINISH;
    control.SetMessage(bmgId, text);
}
kmCall(0x8085728c, PatchFinishRaceBMGID);
}//namespace UI


static int ChangePlayerType(const RacedataPlayer& player, u8 id) {
    PlayerType type = Racedata::sInstance->racesScenario.players[id].playerType;
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
    const u8 id = aiController.GetPlayerIdx();
    const PlayerType type = Racedata::sInstance->racesScenario.players[id].playerType;
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



void* PatchMiiHeadsOpacity(MiiHeadsModel& model, Mii* mii, MiiDriverModel* driverModel, u32 r6, nw4r::g3d::ScnMdl::BufferOption option,
    u32 r8, u32 id) {
    if(Raceinfo::sInstance != nullptr && id == 0) model.scnObjDrawOptionsIdx = 0xA;
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
    Racedata::sInstance->racesScenario.settings.hudPlayerIds[0] = focusedPlayerIdx;
}
kmBranch(0x805a9b60, ChangeGhostOpacity);




}//namespace Pulsar


//kmWrite32(0x805a84d4, 0x38000001);

//subi 50 bgt 2

//808568cc
//80856d78