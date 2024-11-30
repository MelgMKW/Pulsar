#include <kamek.hpp>
#include <MarioKartWii/3D/Camera/CameraMgr.hpp>
#include <MarioKartWii/3D/Camera/RaceCamera.hpp>
#include <MarioKartWii/UI/Section/SectionMgr.hpp>
#include <MarioKartWii/Race/Raceinfo/Raceinfo.hpp>
#include <Gamemodes/KO/KOMgr.hpp>

namespace Pulsar {
namespace Race {

static const u64 CreateSwitchFocusPlayerPtmfs(u32 arg) { //extremely hacky, but it does the job for now
    static SectionId fakeSection;

    SectionId id = SectionMgr::sInstance->curSection->sectionId;
    const System* system = System::sInstance;
    if(system->IsContext(PULSAR_MODE_KO) && system->koMgr->isSpectating || id >= SECTION_WATCH_GHOST_FROM_CHANNEL && id <= SECTION_WATCH_GHOST_FROM_MENU) id = SECTION_P1_WIFI_VS_LIVEVIEW;
    fakeSection = id;
    u64 ret = ((static_cast<u64>(arg)) << 32) | (reinterpret_cast<u32>(&fakeSection) & 0xffffffffL);
    return ret;
}
kmWrite32(0x808568a0, 0x80040000);
kmCall(0x8085689c, CreateSwitchFocusPlayerPtmfs);
kmCall(0x80856d20, CreateSwitchFocusPlayerPtmfs);

asmFunc CreateSwitchFocusedPlayerPtmfs() { //when spectating
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

static void CreateAdditionalCameras(RaceCameraMgr* mgr) {
    const SectionId id = SectionMgr::sInstance->nextSectionId;
    if(id >= SECTION_WATCH_GHOST_FROM_CHANNEL && id <= SECTION_WATCH_GHOST_FROM_MENU) mgr->isOnlineSpectating = true;
    mgr->SetInstance(mgr);
}
kmCall(0x805a8520, CreateAdditionalCameras);


Racedata* RemoveLiveview() {
    register RaceCameraMgr* mgr;
    asm(mr mgr, r31;);
    const SectionId id = SectionMgr::sInstance->nextSectionId;
    if(id >= SECTION_WATCH_GHOST_FROM_CHANNEL && id <= SECTION_WATCH_GHOST_FROM_MENU) mgr->isOnlineSpectating = false;
    return Racedata::sInstance;
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

static void RaceinfoNoSpectating() {
    register Raceinfo* raceInfo;
    asm(mr raceInfo, r28;);
    const System* system = System::sInstance;
    raceInfo->isSpectating = !system->IsContext(PULSAR_MODE_KO); //default instruction would store 1, here we only store 1 if it's not ko
}
kmCall(0x80532cf8, RaceinfoNoSpectating);

static bool SkipOpeningPanCheck(const RaceCameraMgr& cameraMgr) {
    const System* system = System::sInstance;
    if(system->IsContext(PULSAR_MODE_KO) && system->koMgr->isSpectating) return true;
    else return cameraMgr.HasEveryOpeningPanEnded();
}
kmCall(0x8053342c, SkipOpeningPanCheck);

}//namespace Race
}//namespace Pulsar