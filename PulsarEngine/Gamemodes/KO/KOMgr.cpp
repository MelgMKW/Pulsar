#include <MarioKartWii/Race/Raceinfo/Raceinfo.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/Input/InputManager.hpp>
#include <GameModes/KO/KOMgr.hpp>
#include <Network/PacketExpansion.hpp>
#include <Gamemodes/KO/KORaceEndPage.hpp>

namespace Pulsar {
namespace KO {

Mgr::Mgr() : winnerPlayerId(0xFF), isSpectating(false), hasSwapped(false) /*, stillInCount(playerCount)*/ {
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
    this->baseLocPlayerCount = sub.localPlayerCount;
    for (int aid = 0; aid < 12; ++aid) {
        this->isKOd[aid][0] = false;
        this->isKOd[aid][1] = false;
    }
    this->ResetRace();
}
Mgr::~Mgr() {
    RKNet::Controller* controller = RKNet::Controller::sInstance;
    controller->subs[0].localPlayerCount = this->baseLocPlayerCount;
    controller->subs[1].localPlayerCount = this->baseLocPlayerCount;
    if (this->GetIsSwapped()) this->SwapControllersAndUI();
}

void Mgr::AddRaceStats() { //SHOULD ONLY BE CALLED AFTER PROCESSKOS
    //CALC THE STATS
    const RacedataScenario& scenario = Racedata::sInstance->racesScenario;
    for (int hudSlot = 0; hudSlot < scenario.localPlayerCount; ++hudSlot) {
        Stats& stats = this->stats[hudSlot];
        if (stats.boolCountArray >= arbitraryAlmostDied) ++stats.final.almostKOdCounter;
        const u8 pos = Raceinfo::sInstance->players[scenario.settings.hudPlayerIds[hudSlot]]->position;
        stats.percentageSum += static_cast<float>(pos) / static_cast<float>(System::sInstance->nonTTGhostPlayersCount); //this allows higher precision across multiple races
        stats.final.finalPercentageSum = static_cast<u8>(stats.percentageSum * 100);
    }

    this->ResetRace();
}

bool Mgr::CalcWouldBeKnockedOut(u8 playerId) {

    bool ret = false;
    Pages::GPVSLeaderboardUpdate::Player players[12];
    memset(&players, 0, sizeof(Pages::GPVSLeaderboardUpdate::Player) * 12);
    const RacedataScenario& scenario = Racedata::sInstance->menusScenario;
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
    const u8 playerCount = System::sInstance->nonTTGhostPlayersCount;
    const Raceinfo* raceInfo = Raceinfo::sInstance;

    const u8* pointsArray = &Racedata::pointsRoom[playerCount - 1][0];

    u32 disconnectedKOs = 0;
    for (int curPlayerId = 0; curPlayerId < playerCount; ++curPlayerId) { //init players struct
        const u8 aid = controller->aidsBelongingToPlayerIds[curPlayerId];
        if ((1 << aid & sub.availableAids) == 0) ++disconnectedKOs;
        Pages::GPVSLeaderboardUpdate::Player& cur = players[curPlayerId];
        const u8 wouldBePoints = pointsArray[raceInfo->players[curPlayerId]->position - 1];
        cur.lastRaceScore = wouldBePoints;
        cur.totalScore = scenario.players[curPlayerId].previousScore + wouldBePoints;
        cur.playerId = curPlayerId;
    }
    if (playerCount == 2 || (playerCount - disconnectedKOs) == 1) { //either it's the final race, or there were so many DCs that only one racer is left; in both cases, use position-based KOs
        if (raceInfo->players[playerId]->position != 1) ret = true;
    }
    else {
        qsort(&players, playerCount, sizeof(Pages::GPVSLeaderboardUpdate::Player), reinterpret_cast<int (*)(const void*, const void*)>(&Pages::GPVSLeaderboardTotal::ComparePlayers));

        const u32 theoreKOs = this->koPerRace - ((playerCount - this->koPerRace == 1) && this->alwaysFinal); //remove exactly 1KO from the count if always final is on and only 1 player would be left
        const s32 realKOCount = theoreKOs - disconnectedKOs; //DCd players have already been eliminated
        if (realKOCount > 0 && (SectionMgr::sInstance->sectionParams->onlineParams.currentRaceNumber + 1) % this->racesPerKO == 0) { //there are still spots left to be KOd and the race number is divisible by the setting
            for (int idx = 0; idx < realKOCount; ++idx) {
                if (players[(playerCount - 1) - disconnectedKOs - idx].playerId == playerId) ret = true;
            }
            //if 4players, 3KOs per race, 1DC, no always final: realKOCount == 2
            //start at the bottom (playerCount - 1), DC got last automatically so subtract it from the bottom, then go from the bottomup (2 1)
        }
    }
    const u8 hudSlotId =scenario.players[playerId].hudSlotId;
    if (hudSlotId != 0xFF) this->wouldBeOut[hudSlotId] = ret;
    return ret;
}

void Mgr::ProcessKOs(Pages::GPVSLeaderboardUpdate::Player* playerArr, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {

    qsort(playerArr, nitems, size, compar); //default

    const System* system = System::sInstance;
    if (system->IsContext(PULSAR_MODE_KO)) {
        Mgr* self = system->koMgr;

        const RacedataScenario& scenario = Racedata::sInstance->menusScenario;
        const RKNet::Controller* controller = RKNet::Controller::sInstance;
        const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
        const u8 playerCount = system->nonTTGhostPlayersCount;

        u8 disconnectedKOs = 0;
        for (int playerId = 0; playerId < playerCount; ++playerId) { //eliminate disconnected players

            const u8 aid = controller->aidsBelongingToPlayerIds[playerId];
            if ((1 << aid & sub.availableAids) == 0) {
                self->SetKOd(playerId);
                ++disconnectedKOs;
            }
        }

        const u8 theoreKOs = self->koPerRace - ((playerCount - self->koPerRace == 1) && self->alwaysFinal); //remove exactly 1KO from the count if always final is on and only 1 player would be left
        const s8 realKOCount = theoreKOs - disconnectedKOs; //DCd players have already been eliminated


        if (playerCount == 2 || (playerCount - disconnectedKOs) == 1) { //either it's the final race, or there were so many DCs that only one racer is left; in both cases, use position-based KOs
            Raceinfo* raceinfo = Raceinfo::sInstance;
            self->winnerPlayerId = raceinfo->playerIdInEachPosition[0];
            self->SetKOd(raceinfo->playerIdInEachPosition[1]);
        }
        else if (realKOCount > 0 && (SectionMgr::sInstance->sectionParams->onlineParams.currentRaceNumber + 1) % self->racesPerKO == 0) { //there are still spots left to be KOd and the race number is divisible by the setting
            for (int idx = 0; idx < realKOCount; ++idx) self->SetKOd(playerArr[(playerCount - 1) - disconnectedKOs - idx].playerId);
            //if 4players, 3KOs per race, 1DC, no always final: realKOCount == 2
            //start at the bottom (playerCount - 1), DC got last automatically so subtract it from the bottom, then go from the bottomup (2 1)
            if (playerCount - theoreKOs == 1) self->winnerPlayerId = playerArr[0].playerId; //only one player left
        }

        self->AddRaceStats(); //everything has been processed, add the stats and if needed, send the data via RH1Packets
    }
}
kmCall(0x8085cb94, Mgr::ProcessKOs);

void Mgr::Update() {
    const System* system = System::sInstance;
    if (system->IsContext(PULSAR_MODE_KO)) {
        Mgr* self = System::sInstance->koMgr;

        const RacedataScenario& scenario = Racedata::sInstance->racesScenario;
        for (int hudSlot = 0; hudSlot < scenario.localPlayerCount; ++hudSlot) {
            const bool wouldBeOut = self->CalcWouldBeKnockedOut(scenario.settings.hudPlayerIds[hudSlot]);
            const u32 idx = Raceinfo::sInstance->raceFrames % 300;

            Stats& stats = self->stats[hudSlot];
            if (wouldBeOut) ++stats.final.timeInDanger;
            if (stats.isInDangerFrames[idx] == false && wouldBeOut == true) ++stats.boolCountArray;
            else if (stats.isInDangerFrames[idx] == true && wouldBeOut == false) --stats.boolCountArray;
            stats.isInDangerFrames[idx] = wouldBeOut;
        }

        const u8 winnerPlayerId = self->winnerPlayerId;
        if (winnerPlayerId != 0xFF) { //if the if is taken, ProcessKOs and therefore AddRaceStats are guaranteed to have been called
            const RKNet::Controller* controller = RKNet::Controller::sInstance;
            const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
            if (controller->aidsBelongingToPlayerIds[winnerPlayerId] == sub.localAid) { //only send the data if needed 
                for (int aid = 0; aid < 12; ++aid) {
                    if ((1 << aid & sub.availableAids) == 0 || aid == sub.localAid) continue;

                    Stats& stats = self->stats[0];
                    RKNet::PacketHolder<Network::PulRH1>* holder = controller->GetSendPacketHolder<Network::PulRH1>(aid);

                    /*
                    this shouldn't be needed because the "ExportRH1ToPulRH1" always does it
                    const u32 curSize = holder->packetSize;/
                    u32 addedSize = 0;
                    if(curSize == sizeof(RKNet::RACEHEADER1Packet)) addedSize = sizeof(Network::PulRH1) - sizeof(RKNet::RACEHEADER1Packet);
                    else if(holder->packetSize == 0) addedSize = sizeof(Network::PulRH1);
                    holder->packetSize += addedSize;
                    */
                    Network::PulRH1* dest = holder->packet;
                    dest->timeInDanger = stats.final.timeInDanger;
                    dest->almostKOdCounter = stats.final.almostKOdCounter;
                    dest->finalPercentageSum = stats.final.finalPercentageSum;
                }
            }
        }
    }
}
RaceFrameHook koUpdate(Mgr::Update);

/*
void Mgr::UpdateStillInCount() {
    u32 stillIn = 0;
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const u32 availableAids =  controller->subs[controller->currentSub].availableAids;
    for(int aid = 0; aid < 12; ++aid) {
        u8 aid = controller->aidsBelongingToPlayerIds[aid];
        if((1 << aid & availableAids) == 0) { //the playerId is disconnected
            this->SetMgrd(aid);
        }
        if(this->IsMgrd(aid)) continue;
        ++stillIn;
    }
    this->stillInCount = stillIn;
}
*/

void Mgr::PatchAids(RKNet::ControllerSub& sub) const {
    u8 availableAids = sub.availableAids;
    const u8 localAid = sub.localAid;
    for (u8 aid = 0; aid < 12; ++aid) {

        bool isConsoleOut = false;
        const bool isMainOut = this->IsKOdAid(aid, 0);
        u8 aidPlayerCount = aid == localAid ? sub.localPlayerCount : sub.connectionUserDatas[aid].playersAtConsole;


        if (aidPlayerCount <= 1) isConsoleOut = isMainOut;
        else if (aidPlayerCount == 2) {
            const bool isGuestOut = this->IsKOdAid(aid, 1);
            if (isMainOut && isGuestOut) isConsoleOut = true;
            else if (isMainOut != isGuestOut) {
                aidPlayerCount = 1;
            }

        }
        if (isConsoleOut) {
            availableAids = availableAids & ~(1 << aid);
            aidPlayerCount = 0;
        }

        if (aid == localAid) sub.localPlayerCount = aidPlayerCount;
        else sub.connectionUserDatas[aid].playersAtConsole = aidPlayerCount;
    }
    sub.availableAids = availableAids;
}

u32 Mgr::GetAidAndSlotFromPlayerId(u8 playerId) const {
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
    const u8 aid = controller->aidsBelongingToPlayerIds[playerId];
    const u8 localAid = sub.localAid;
    u8 slot = 0;

    if ((aid == localAid && sub.localPlayerCount == 2) || (aid != localAid && sub.connectionUserDatas[aid].playersAtConsole == 2)) {
        if (playerId > 0 && controller->aidsBelongingToPlayerIds[playerId - 1] == aid) slot = 1;
        else if (playerId < 11 && this->isKOd[aid][0] == true && controller->aidsBelongingToPlayerIds[playerId + 1] != aid) slot = 1;
    }
    return (slot << 16) | aid; //10001
}

SectionId Mgr::GetSectionAfterKO(SectionId defaultId) const {
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
    if (this->baseLocPlayerCount == 2) {
        if (this->IsKOdAid(sub.localAid, 0) != this->IsKOdAid(sub.localAid, 1)) {
            if (defaultId == SECTION_P2_WIFI_FROOM_VS_VOTING) defaultId = SECTION_P1_WIFI_FROOM_VS_VOTING; //select section
            else if (defaultId == SECTION_P1_WIFI_FROM_FROOM_RACE) {
                defaultId = SECTION_P2_WIFI_FROM_FROOM_RACE; //after room section
                SectionMgr::sInstance->sectionParams->localPlayerCount = 2;
            }
        }
    }
    return defaultId;
}

void OnDisconnectKO(SectionMgr* sectionMgr, SectionId id) {
    const System* system = System::sInstance;
    if (system->IsContext(PULSAR_MODE_KO)) id = system->koMgr->GetSectionAfterKO(id);
    sectionMgr->SetNextSection(id, 0);
}
kmCall(0x80651814, OnDisconnectKO);

PageId Mgr::KickPlayersOut() { //only called if KOMode

    PageId ret = PAGE_WWRACEEND_WAIT;
    const System* system = System::sInstance;

    Mgr* mgr = system->koMgr;
    RacedataScenario& scenario = Racedata::sInstance->racesScenario;
    const bool isMainOut = mgr->IsKOdPlayerId(scenario.settings.hudPlayerIds[0]);
    if (system->nonTTGhostPlayersCount > 2) {
        if (scenario.localPlayerCount == 1) {
            const RKNet::Controller* controller = RKNet::Controller::sInstance;
            const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
            if (isMainOut) {
                if (sub.localAid == sub.hostAid) mgr->isSpectating = true; //force the host to spectate, they should not be allowed to quit
                else ret = static_cast<PageId>(RaceEndPage::id);
            }
        }
        else {
            const bool isGuestOut = mgr->IsKOdPlayerId(scenario.settings.hudPlayerIds[1]);
            if (isMainOut != isGuestOut) SectionMgr::sInstance->sectionParams->localPlayerCount = 1;
            if (isMainOut && !isGuestOut) {
                memcpy(&mgr->stats[0], &mgr->stats[1], sizeof(Mgr::Stats));
            }
            else if (isMainOut && isGuestOut) ret = static_cast<PageId>(RaceEndPage::id);

        }
    }
    return ret;
}

void Mgr::SwapControllersAndUI() {

    //Swap the controllers
    Input::Manager* input = Input::Manager::sInstance;

    char mainController[sizeof(Input::RealControllerHolder)];
    memcpy(&mainController, &input->realControllerHolders[0], sizeof(Input::RealControllerHolder));
    memcpy(&input->realControllerHolders[0], &input->realControllerHolders[1], sizeof(Input::RealControllerHolder));
    memcpy(&input->realControllerHolders[1], &mainController, sizeof(Input::RealControllerHolder));

    SectionMgr* sectionMgr = SectionMgr::sInstance;
    SectionPad& pad = sectionMgr->pad;
    PadInfo& main = pad.padInfos[0];
    PadInfo& guest = pad.padInfos[1];
    u32 old = main.controllerID;
    u32 oldg = guest.controllerID;
    main.controllerID = oldg;
    guest.controllerID = old;
    main.controllerIDActive = main.controllerID;
    guest.controllerIDActive = guest.controllerID;

    //Swap the characters on the UI
    SectionParams* params = sectionMgr->sectionParams;
    CharacterId mainChar = params->characters[0];
    KartId mainKart = params->karts[0];
    params->characters[0] = params->characters[1];
    params->karts[0] = params->karts[1];
    params->characters[1] = mainChar;
    params->karts[1] = mainKart;
    memcpy(&params->combos[0], &params->combos[1], sizeof(PlayerCombo));
    this->hasSwapped = !this->hasSwapped;
}
}//namespace KO
}//namespace Pulsar

//8085cc70 patch gpvsleaderboardtotal get nextpatch on the last race, and load MgrWinner instead of VSResults
//80646754 patch vsresults getnextpage on the last race, careful since this is where choosenext already hooks
//same place, patch self kicking

/*
WISHLIST:

*Implement Mgr system:
    -calc and change racecount
    -check which players should be Mgr'd (the last X players)
    -kick them out of the room, maybe spectating

*UI:
    -highlight kicked players in red on the total ldb page
    -custom Mgr winning screen
    -position tracker
 */

 /*NOTES:
 -4th anm of CtrlRaceResult is row filling
 */



