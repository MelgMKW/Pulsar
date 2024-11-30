#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <MarioKartWii/AI/KartAIController.hpp>
#include <MarioKartWii/Kart/KartPointers.hpp>
#include <Ghost/GhostManager.hpp>
#include <Settings/Settings.hpp>
#include <IO/IO.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <Ghost/UI/ExpGhostSelect.hpp>

namespace Pulsar {
namespace OTT {


bool IsVSGhost(u32 playerId) {
    if(System::sInstance->IsContext(PULSAR_MODE_OTT)) {
        const Racedata* racedata = Racedata::sInstance;
        if(racedata->racesScenario.players[playerId].playerType == PLAYER_GHOST) return true;
    }
    return false;
}
inline s32 GetVSGhostId() {
    const u32 playerId = Racedata::sInstance->racesScenario.playerCount - 1;
    if(IsVSGhost(playerId)) return playerId;
    return -1;
}

void AddGhostToVS() {
    const System* system = System::sInstance;
    Racedata* racedata = Racedata::sInstance;
    if(GameScene::GetCurrent()->id == SCENE_ID_RACE && system->IsContext(PULSAR_MODE_OTT) && racedata->menusScenario.settings.gametype != GAMETYPE_ONLINE_SPECTATOR) {
        u8 playerCount;
        u8 screenCount;
        u8 localCount;
        racedata->menusScenario.ComputePlayerCounts(&playerCount, &screenCount, &localCount);
        if(racedata->menusScenario.settings.gamemode >= MODE_PRIVATE_VS) {
            if(playerCount == 12) return; //we do not want to replace a human player
        }
        if(playerCount < 12) ++playerCount; //add a player to be the ghost

        const EngineClass cc = racedata->menusScenario.settings.engineClass;
        if(racedata->menusScenario.settings.modeFlags & 0x1 != 0) return; //mirror
        if(cc == CC_100 && system->GetInfo().Has200cc() == false) return; //100 but the pack does not have 200 so no ghost to be found
        //only 150 and 200 are possible

        char folderPath[IOS::ipcMaxPath];
        const PulsarId id = CupsConfig::sInstance->GetWinning();
        const CupsConfig* cupsConfig = CupsConfig::sInstance;
        cupsConfig->GetTrackGhostFolder(folderPath, id);

        alignas(0x20) Ghosts::Leaderboard leaderboard(folderPath, id, false);
        const TTMode ttMode = static_cast<TTMode>(racedata->menusScenario.settings.engineClass % 2 + 2 * system->IsContext(PULSAR_FEATHER)); //CC_150 (2) becomes 0 (TT_MODE_150), CC_100 (1) becomes 1 (TT_MODE_100)
        const char* favGhost = leaderboard.GetFavGhost(ttMode);
        char initial = favGhost[0];

        if(initial == '\0') return; //no fav ghost for this track


        IO* io = IO::sInstance;
        RKG* rkg = io->Alloc<RKG>(sizeof(RKG));

        racedata->ghosts[0].ClearBuffer();
        char ghostPath[IOS::ipcMaxPath];
        if(initial == '?') { //the fav is the expert
            cupsConfig->GetExpertPath(ghostPath, id, ttMode);
            DVD::FileInfo info;
            DVD::Open(ghostPath, &info);
            DVD::ReadPrio(&info, rkg, info.length, 0, 2);
            DVD::Close(&info);
        }
        else { //the fav is a user ghost
            snprintf(ghostPath, IOS::ipcMaxPath, "%s/%s/%s", folderPath, System::ttModeFolders[ttMode], favGhost);
            io->OpenFile(ghostPath, FILE_MODE_READ);
            io->Read(sizeof(RKG), rkg);
            io->Close();
        }
        if(rkg->CheckValidity()) {
            if(rkg->header.kartId > HONEYCOUPE || rkg->header.driftType == 1 || system->IsContext(PULSAR_UMTS)) {
                RKG* dest = &racedata->ghosts[0];
                racedata->menusScenario.rkg = dest;
                if(rkg->header.compressed) {
                    rkg->DecompressTo(*dest); //0x2800
                }
                else memcpy(dest, rkg, sizeof(RKG));
                racedata->menusScenario.players[playerCount - 1].playerType = PLAYER_GHOST;
            }
        }
        delete rkg;
    }
}

void FinishGhostRace() {
    register Input::GhostActionStream* stream;
    asm(mr stream, r31;);
    stream->mode = Input::GhostStream::MODE_OFF;
    s32 id = GetVSGhostId();
    if(id != -1) {
        Timer timer(0);
        Raceinfo::sInstance->players[id]->EndRace(timer, false, 1);
    }
}
kmCall(0x80523010, FinishGhostRace);

kmCall(0x8078d0b8, System::GetNonTTGhostPlayersCount);

bool CPUItemFix(KartAIController& kartAI) {
    if(IsVSGhost(kartAI.pointers->values->playerIdx)) return true;
    return kartAI.IsCPU();
}
//kmCall(0x807414d8, CPUItemFix);

u32 LdbRows(u32 def) {
    return System::sInstance->nonTTGhostPlayersCount;
}
kmBranch(0x8085c500, LdbRows);


void FixPositions(RaceinfoPlayer& player) {
    register u32 idx;
    asm(mr idx, r29);
    if(IsVSGhost(idx)) {
        GhostData ghost(Racedata::sInstance->ghosts[0]);
        SectionMgr* sectionMgr = SectionMgr::sInstance;
        sectionMgr->sectionParams->playerMiis.LoadMii(idx, &ghost.miiData);
        //Racedata::sInstance->racesScenario.players[idx].mii = *sectionMgr->sectionParams->playerMiis.GetMii(idx);
        return;
    }
    player.position = idx + 1;
    player.Init();
}
kmCall(0x80533040, FixPositions);


void DoNotSetGhostsDCd(Raceinfo& raceInfo, u8 playerId) {
    if(IsVSGhost(playerId)) return;
    raceInfo.SetPlayerDisconnected(playerId);
}
kmCall(0x80654478, DoNotSetGhostsDCd);


void Update(Raceinfo& raceinfo) {
    RacedataScenario& scenario = Racedata::sInstance->racesScenario;

    const u8 old = scenario.playerCount;
    scenario.playerCount = System::sInstance->nonTTGhostPlayersCount;
    raceinfo.Update();
    scenario.playerCount = old;
}
kmCall(0x80554b50, Update);

asmFunc PatchImportRH2() {
    ASM(
        nofralloc;
    lwz r0, 0x38 (r3); //default
    cmpwi r0, 3;
    bne + end;
    li r0, 0; //fake that the ghost is a local player
end:
    blr;
        )
}
kmCall(0x8053e4a4, PatchImportRH2);

}//namespace Ghosts
}//namespace Pulsar

