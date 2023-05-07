#include <game/Race/RaceInfo/RaceInfo.hpp>
#include <game/Race/RaceData.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/UI/Page/RaceHUD/RaceHUD.hpp>
#include <game/UI/Page/RaceMenu/GhostReplayPause.hpp>
#include <game/Race/Kart/KartHolder.hpp>
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
namespace UI {
void CreateTTInterface(Section* section, PageId id) {
    section->CreateAndInitPage(PAGE_TT_INTERFACE);
    section->CreateAndInitPage(PAGE_TT_SPLITS);
}
kmCall(0x8062ccd4, CreateTTInterface);
kmCall(0x8062cc5c, CreateTTInterface);
kmCall(0x8062cc98, CreateTTInterface);

PageId TTSplitsNextPage() {
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId == SECTION_TT || sectionId == SECTION_GHOST_RACE_1 || sectionId == SECTION_GHOST_RACE_2) return PAGE_TT_LEADERBOARDS;
    else if(sectionId == SECTION_GP) return PAGE_GPVS_LEADERBOARD_UPDATE;
    else if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) return PAGE_GHOST_REPLAY_PAUSE_MENU;
    return PAGE_NONE;
}
kmBranch(0x808561dc, TTSplitsNextPage);

PageId TTPauseNextPage(const Pages::RaceHUD& page) {
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) return PAGE_GHOST_REPLAY_PAUSE_MENU;
    return page.GetPausePageId();
}
kmCall(0x808569e0, TTPauseNextPage);

void OnContinueButtonTTPauseClick(Pages::GhostReplayPause& page, PageId id) {
    const u32 stage = RaceInfo::sInstance->stage;
    if(stage == 0x4) id = PAGE_TT_SPLITS; //if race is finished, repurpose the continue button
    page.nextPage = id;
    return;
}
kmCall(0x8085a1e0, OnContinueButtonTTPauseClick);

bool WillCharCheer(const RaceData& racedata) {
    const SectionMgr* sectionMgr = SectionMgr::sInstance;
    const SectionId sectionId = sectionMgr->curSection->sectionId;
    register Timer* ghostTimer;
    asm volatile(addi ghostTimer, r15, 0x48;);
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) {
        ghostTimer->minutes = 0xFFFF;
        return true;
    }
    else if(racedata.racesScenario.settings.gamemode == MODE_GHOST_RACE || ghostTimer->isActive) return true;
    return false;
}
kmCall(0x808570a0, WillCharCheer);
kmWrite32(0x80857088, 0x40820018);
kmWrite32(0x808570a4, 0x2C030001);
u8 CharCheerGetCorrectArguments(int r3, u8 id) {
    u8 ret = RaceData::sInstance->racesScenario.players[id].hudSlotId;
    if(ret == -1) ret = 0;
    return ret;
}
kmCall(0x808570c4, CharCheerGetCorrectArguments);

void PatchFinishRaceBMGID(LayoutUIControl& control, u32 bmgId, const TextInfo* text) {
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) bmgId = BMG_FINISH;
    control.SetMsgId(bmgId, text);
}
kmCall(0x8085728c, PatchFinishRaceBMGID);
}//namespace UI
}//namespace Pulsar

int ChangePlayerType(const RaceDataPlayer& player, u8 id) {
    PlayerType type = RaceData::sInstance->racesScenario.players[id].playerType;
    if(type == PLAYER_GHOST && id == 0) return 0;
    return type;
}
kmCall(0x80594444, ChangePlayerType);
kmWrite32(0x80594434, 0x889F0010);
kmWrite32(0x80594448, 0x2c030000);
kmWrite32(0x80594450, 0x2c030001);
kmWrite32(0x80594458, 0x2c030003);

bool PatchOpacity(ComboIDs* comboIDs, GFX44* gfx44, bool isGhost, u8 playerId) {
    if(playerId == 0) isGhost = false;
    return ApplyTransparency(comboIDs, gfx44, isGhost, playerId);
}
kmCall(0x8058e2b8, PatchOpacity);
kmCall(0x807c7870, PatchOpacity);

void* PatchMiiHeadsOpacity(MiiHeadsModel& model, Mii* mii, ModelDirector* driverModel, u32 r6, nw4r::g3d::ScnMdl::BufferOption option,
    u32 r8, u32 id) {
    if(id == 0) model.isTransparent = false;
    return model.InitModel(mii, driverModel, r6, option, r8, id);
}
kmCall(0x807dc0e8, PatchMiiHeadsOpacity);

bool PatchIsLocalCheck(const Kart& kart) {
    const SectionId sectionId = SectionMgr::sInstance->curSection->sectionId;
    if(sectionId >= SECTION_WATCH_GHOST_FROM_CHANNEL && sectionId <= SECTION_WATCH_GHOST_FROM_MENU) return false;
    return kart.IsLocal();
}
kmCall(0x80783770, PatchIsLocalCheck);

bool EnableCPUDrivingAfterRace(const KartBase& kartBase) { //not actually Base, but it has kartbase
    const u8 id = kartBase.GetPlayerIdx();
    const PlayerType type = RaceData::sInstance->racesScenario.players[id].playerType;
    if(type == PLAYER_GHOST && id != 0) return true;
    return false;
}
kmCall(0x80732634, EnableCPUDrivingAfterRace);

asm void PatchSoundIssues() {
    ASM(
        nofralloc;
    lwz r5, 0 (r4); //Default
    cmpwi r5, SECTION_WATCH_GHOST_FROM_CHANNEL;
    blt + end;
    cmpwi r5, SECTION_WATCH_GHOST_FROM_MENU;
    bgt + end;
    li r5, 0x1f;
end:;
    blr;
    )
}
kmCall(0x80716064, PatchSoundIssues);