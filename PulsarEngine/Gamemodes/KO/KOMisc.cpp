#include <MarioKartWii/RKNet/SELECT.hpp>
#include <MarioKartWii/RKNet/ITEM.hpp>
#include <MarioKartWii/3D/Camera/CameraMgr.hpp>

#include <MarioKartWii/UI/Page/Other/SELECTStageMgr.hpp>
#include <MarioKartWii/UI/Page/Other/VR.hpp>
#include <MarioKartWii/UI/Page/Other/Votes.hpp>
#include <MarioKartWii/UI/Page/Leaderboard/GPVSLeaderboardTotal.hpp>
#include <MarioKartWii/UI/Page/Other/WifiVSResults.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceRankNum.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceItemWindow.hpp>
#include <MarioKartWii/Race/Raceinfo/Raceinfo.hpp>
#include <MarioKartWii/Kart/KartManager.hpp>
#include <Network/PacketExpansion.hpp>
#include <Gamemodes/KO/KOMgr.hpp>
#include <Gamemodes/KO/KORaceEndPage.hpp>
#include <Gamemodes/KO/KOWinnerPage.hpp>


namespace Pulsar {
namespace KO {

static void EditLdb(CtrlRaceResult* result, u8 playerId) {
    const System* system = System::sInstance;

    if (system->IsContext(PULSAR_MODE_KO)) {
        const char* pane= "player_name";
        if (system->koMgr->IsKOdPlayerId(playerId)) {
            result->SetTextBoxMessage("player_name", UI::BMG_KO_OUT);
            result->animator.GetAnimationGroupById(4).PlayAnimationAtFrame(6, 0.0f);
            lyt::Picture* selectBase = static_cast<nw4r::lyt::Picture*>(result->layout.GetPaneByName("select_base"));
            ut::Color color = 0xff000080;
            selectBase->vertexColours[0] = color;
            selectBase->vertexColours[1] = color;
            selectBase->vertexColours[2] = color;
            selectBase->vertexColours[3] = color;
            return;
        }
    }
    result->FillName(playerId);
}
kmCall(0x8085cc04, EditLdb);

static u8 EditPosTracker(CtrlRaceRankNum& posTracker) {

    const u32 playerId = posTracker.GetPlayerId();
    const System* system = System::sInstance;
    Mgr* mgr = system->koMgr;
    if (system->IsContext(PULSAR_MODE_KO)) {
        u8 idx = posTracker.hudSlotId;
        lyt::Picture* posPane = static_cast<nw4r::lyt::Picture*>(posTracker.layout.GetPaneByName("position"));
        ut::Color color = 0xffffffff;

        if (Raceinfo::sInstance->raceFrames > 0 && mgr->GetWouldBeKnockedOut(Racedata::sInstance->racesScenario.players[playerId].hudSlotId)) {
            s32 increment = mgr->posTrackerAnmFrames[idx] >= 31 ? 8 : -8;
            color.g = posPane->vertexColours[0].g + increment;
            color.b = color.g;
            ++mgr->posTrackerAnmFrames[idx];
            if (mgr->posTrackerAnmFrames[idx] == 62) mgr->posTrackerAnmFrames[idx] = 0;
        }
        else mgr->posTrackerAnmFrames[idx] = 0;
        posPane->vertexColours[0] = color;
        posPane->vertexColours[1] = color;
        posPane->vertexColours[2] = color;
        posPane->vertexColours[3] = color;

    }
    return playerId;
}
kmCall(0x807f4b64, EditPosTracker);


/*
void KO::UpdateIds(RKNet::Controller* controller) {
    controller->UpdateAidsBelongingToPlayerIds(); //default

    KO* ko = KO::sInstance;
    RacedataScenario& scenario = Racedata::sInstance->menusScenario;
    const u8 localAid = controller->subs[controller->currentSub].localAid;
    const u32 roomMembers = controller->subs[controller->currentSub].playerCount; //total amount of people connected, including spectators

    u8 idx = 0;
    const PlayerInfo* playerInfos = &SectionMgr::sInstance->curSection->Get<Pages::SELECTStageMgr>()->infos[0];

    for(int playerId = 0; playerId < roomMembers; ++playerId) {

        if(mgr->IsKOd(playerId)) {
            continue;
        }
        const u8 curAid = controller->aidsBelongingToPlayerIds[playerId];
        //move the playerId (and its data) belonging to aid playerId to the first free slot, ie a slot occupied by a KO'd player
        u8 prevAidAtIdx = controller->aidsBelongingToPlayerIds[idx];

        //swap the values in the array, [idx] is the final value, [playerId] is needed to check if the player is local in the 2nd loop


        controller->aidsBelongingToPlayerIds[idx] = curAid;
        controller->aidsBelongingToPlayerIds[playerId] = prevAidAtIdx;
        memcpy(&scenario.players[idx], &scenario.players[playerId], sizeof(RacedataPlayer));

        if(curAid == localAid) scenario.settings.hudPlayerIds[playerInfos[playerId].vr == 0xffff] = idx;

        ++idx;
    }

    //"disable" the slots which have been moved and are not needed, have to use 2 loops because of the assignments above
    for(int playerId = 0; playerId < roomMembers; ++playerId) {
        const u8 curAid = controller->aidsBelongingToPlayerIds[playerId];
        if(mgr->IsKOd(playerId)) {
            controller->aidsBelongingToPlayerIds[playerId] = 0xFF;
            scenario.players[playerId].playerType = PLAYER_NONE;
            if(curAid == localAid) scenario.settings.hudPlayerIds[playerInfos[playerId].vr == 0xffff] = playerId;
        }
    }
    if(mgr->isSpectating) scenario.settings.gametype = GAMETYPE_ONLINE_SPECTATOR;
}
kmCall(0x80650e48, KO::UpdateIds);
*/

//Fixes for when spectating
static u8 ReturnCorrectId(u8 localId) { //TO FIX
    const System* system = System::sInstance;
    if (system->IsContext(PULSAR_MODE_KO) && system->koMgr->isSpectating) return RaceCameraMgr::sInstance->focusedPlayerIdx;
    else return localId;
}
kmBranch(0x80531f7c, ReturnCorrectId);

static GameType SyncCountdown(const Racedata& raceData) {
    GameType type = raceData.racesScenario.settings.gametype;
    const System* system = System::sInstance;
    if (system->IsContext(PULSAR_MODE_KO) && type == GAMETYPE_ONLINE_SPECTATOR) type = GAMETYPE_DEFAULT;
    return type;
}
kmCall(0x806537d8, SyncCountdown);
kmWrite32(0x806537dc, 0x2c030000);
kmWrite32(0x806537e4, 0x2c030006);




//8085cc70 patch gpvsleaderboardtotal get nextpatch on the last race, and load KOWinner instead of VSResults
//80646754 patch vsresults getnextpage on the last race, careful since this is where choosenext already hooks
//same place, patch self kicking

//80643da0 change section when vote ends
/*
WISHLIST:

*Implement KO system:
    -calc and change racecount
    -check which players should be KO'd (the last X players)
    -kick them out of the room, maybe spectating

*UI:
    -highlight kicked players in red on the total ldb page
    -custom KO winning screen
    -position tracker
 */

 /*NOTES:
 -4th anm of CtrlRaceResult is row filling
 */

 //SPECTATING BUGS:
 /*
 -race start syncing does not exist (gametype?), packetmgr updateasracer allows the countdown to start, but is not called if spectating because of a gametype check in packetmgr::update
 DONE?
 -items are not synced
 -scores are bugged (because others don't think I'm spectating?)
 -UI is not interactable (not true?)


//SPECTATOR NON-VOTING
-go straight from vr to vote page done
-change vote count UI vote page done
-exclude them from vr page done
-exclude them from vote page done

SELECT:
-automatically make spectators vote MC not needed?
-in the selectHandler::DecideTrack func, ignore KO'd packets


 */

static void VoteCounterPatch(LayoutUIControl& voteCounter, u32 bmgId, Text::Info* info) {

    register Pages::SELECTStageMgr* mgr;
    asm(mr mgr, r31;);
    register Pages::Vote* vote;
    asm(mr vote, r25;);
    const System* system = System::sInstance;

    if (system->IsContext(PULSAR_MODE_KO)) {
        int stillIn = 0;
        for (int playerId = 0; playerId < mgr->playerCount; ++playerId) {
            if (!system->koMgr->IsKOdPlayerId(playerId)) ++stillIn;
            else if (vote->order[playerId] != -1) {
                const AnimationGroup& group = vote->votes[vote->order[playerId]].animator.GetAnimationGroupById(1);
                if (group.curAnimation == 2) --info->intToPass[0];
            }
        }
        info->intToPass[1] = stillIn;
    }
    voteCounter.SetMessage(bmgId, info);
}
//kmCall(0x80644590, VoteCounterPatch);

static void SkipVoteControlFill(VoteControl& voteControl, bool isCourseIdInvalid, u32 bmgId, const MiiGroup& miiGroup, u32 playerId, bool isLocalPlayer, u32 team) {

    register Pages::Vote* vote;
    asm(mr vote, r24;);
    vote->order[playerId] = vote->lastHandledVote;
    const System* system = System::sInstance;

    if (system->IsContext(PULSAR_MODE_KO)) {
        if (system->koMgr->IsKOdPlayerId(playerId)) {
            return;
        }
    }
    voteControl.Fill(isCourseIdInvalid, bmgId, miiGroup, playerId, isLocalPlayer, team);
    ++vote->lastHandledVote;
}
//kmCall(0x806441b8, SkipVoteControlFill);
//kmWrite32(0x806441c4, 0x60000000);
//kmWrite32(0x806441d0, 0x60000000);

static void SkipVRControlFill(Pages::VR& vr, u32 index, u32 playerId, u32 team, u8 type, bool isLocalPlayer) { //1 -> 2, index = 1
    const System* system = System::sInstance;
    if (system->IsContext(PULSAR_MODE_KO)) {
        const RKNet::Controller* controller = RKNet::Controller::sInstance;
        const Mgr* mgr = system->koMgr;
        u8 aid = controller->aidsBelongingToPlayerIds[playerId];

        vr.vrControls[index].isHidden = true;
        if (mgr->IsKOdPlayerId(playerId)) return;

        index = 0;
        for (int id = 0; id < playerId; ++id) if (!mgr->IsKOdPlayerId(id)) ++index;
        vr.vrControls[index].isHidden = false;
    }
    vr.FillVRControl(index, playerId, team, type, isLocalPlayer);
}
//kmCall(0x8064aa78, SkipVRControlFill);


static void PatchAidsBeforeSELECTStageMgrSetup(Pages::SELECTStageMgr& stageMgr) {
    const System* system = System::sInstance;

    if (system->IsContext(PULSAR_MODE_KO)) {
        Mgr* mgr = system->koMgr;
        RKNet::Controller* controller = RKNet::Controller::sInstance;
        RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
        Network::ExpSELECTHandler& handler = Network::ExpSELECTHandler::Get();
        const Network::PulSELECT* select;
        const u8 hostAid = sub.hostAid;
        if (hostAid == sub.localAid) select = &handler.toSendPacket;
        else select = &handler.receivedPackets[hostAid];
        mgr->koPerRace = select->koPerRace;
        mgr->racesPerKO = select->racesPerKO;
        mgr->alwaysFinal = select->alwaysFinal;
        mgr->PatchAids(sub);
        reinterpret_cast<RKNet::SELECTHandler&>(handler).AllocatePlayerIdsToAids();
        controller->UpdateAidsBelongingToPlayerIds();
    }

    stageMgr.SetModeTypes();

}
kmCall(0x80650494, PatchAidsBeforeSELECTStageMgrSetup);

static u8 SwapUISelectInfo() { //this can only be called if localPlayerCount > 0, ie one of the players is still in

    register u8 aid;
    register u8 localPlayerCount; //obtained from RKNet::Controller, spectators do NOT count
    register u8 curHudSlotId;
    asm(mr aid, r17;);
    asm(mr localPlayerCount, r24;);
    asm(mr curHudSlotId, r16;);

    asm(stb r16, 0x1f5 (r22);); //default
    const System* system = System::sInstance;
    if (system->IsContext(PULSAR_MODE_KO)) {
        if (localPlayerCount == 1) {
            Mgr* mgr = system->koMgr;
            curHudSlotId = mgr->IsKOdAid(aid, 0); //if only one localPlayer but slot 0 is KOd, that guarantees it was initially 2 players and the main is out
            const RKNet::Controller* controller = RKNet::Controller::sInstance;
            const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
            if (curHudSlotId == 1 && aid == sub.localAid && !mgr->GetIsSwapped()) mgr->SwapControllersAndUI();
        }
    }

    return curHudSlotId; //need to return curHudSlotId, it's not used, but it's needed otherwise the function does "nothing" c++ wise and becomes just a blr
}
kmCall(0x80651988, SwapUISelectInfo);
kmWrite32(0x8065198c, 0x5600063f);

static u8 SwapRaceMiis() { //this can only be called if localPlayerCount > 0, ie one of the players is still in, very hacky function but until a better hook is found, this'll do

    register u32 aid;
    register u8 curHudSlotId;
    register u32 playerId;
    asm(mr aid, r21;);
    asm(mr curHudSlotId, r16;);
    asm(mr playerId, r17;);
    const System* system = System::sInstance;

    bool isKO = system->IsContext(PULSAR_MODE_KO);
    if (isKO) {
        if (aid < 12) curHudSlotId = system->koMgr->IsKOdAid(aid, 0); //if only one localPlayer but slot 0 is KOd, that guarantees it was initially 2 players and the main is out
        if (curHudSlotId == 1) {
            RacedataScenario& scenario = Racedata::sInstance->menusScenario;
            char mainPlayer[sizeof(RacedataPlayer)];
            u32 guestId = playerId + 1;
            memcpy(&mainPlayer, &scenario.players[playerId], sizeof(RacedataPlayer));
            memcpy(&scenario.players[playerId], &scenario.players[guestId], sizeof(RacedataPlayer));
            memcpy(&scenario.players[guestId], &mainPlayer, sizeof(RacedataPlayer));
            scenario.players[playerId].playerType = scenario.players[guestId].playerType;
            scenario.players[guestId].playerType = PLAYER_NONE;
            scenario.players[playerId].playerType = scenario.players[guestId].playerType;
            scenario.players[guestId].playerType = PLAYER_NONE;
            curHudSlotId = 0;
        }
    }
    else if (!isKO) curHudSlotId = 0; //default
    else curHudSlotId++; //never actually reached but codegen works with this
    return curHudSlotId; //need to return curHudSlotId, it's not used, but it's needed otherwise the function does "nothing" c++ wise and becomes just a blr
}
kmCall(0x8065123c, SwapRaceMiis);

static bool CtrlRaceItemWindowIsInactive(const CtrlRaceItemWindow& itemWindow) {
    const u8 playerId = itemWindow.GetPlayerId();
    if (SectionMgr::sInstance->curSection->isPaused) return true;
    const Item::Player& itemPlayer = Item::Manager::sInstance->players[playerId];
    const Kart::Status* status = itemPlayer.pointers->kartStatus;
    if (status->bitfield0 & 0x10) return true;
    if (Racedata::sInstance->racesScenario.players[playerId].playerType == PLAYER_REAL_ONLINE && System::sInstance->IsContext(PULSAR_MODE_KO)) {
        return RKNet::ITEMHandler::sInstance->GetStoredItem(playerId) != ITEM_NONE;
    }
    else { //default behaviour
        bool isValid = true;
        if (itemPlayer.roulette.isTheRouletteSpinning == 0 || itemPlayer.inventory.currentItemId == ITEM_NONE) isValid = false;
        if (!isValid && itemPlayer.roulette.unknown_0x24 == ITEM_NONE) return true;
        return false;
    }
}
//kmWritePointer(0x808D3D10, CtrlRaceItemWindowIsInactive);

void StoreItemsForSpectating(RKNet::ITEMHandler& itemHandler) {
    itemHandler.ImportNewPackets();
    if (System::sInstance->IsContext(PULSAR_MODE_KO)) { //guaranteed to be spectating already via a check in the func
        const RacedataScenario& scenario = Racedata::sInstance->racesScenario;
        for (int playerId = 0; playerId < System::sInstance->nonTTGhostPlayersCount; ++playerId) {
            if (scenario.players[playerId].playerType != PLAYER_REAL_ONLINE) continue;
            const ItemId item = itemHandler.GetStoredItem(playerId);
            Item::Player& itemPlayer = Item::Manager::sInstance->players[playerId];
            itemPlayer.inventory.currentItemId = item;
            itemPlayer.inventory.currentItemCount = item != ITEM_NONE;
        }
    }
}
kmCall(0x8065c69c, StoreItemsForSpectating);

}//namespace KO
}//namespace Pulsar