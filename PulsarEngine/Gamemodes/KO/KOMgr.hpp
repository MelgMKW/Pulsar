#ifndef _PUL_KOMGR_
#define _PUL_KOMGR_
#include <kamek.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/UI/Page/Leaderboard/GPVSLeaderboardTotal.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <PulsarSystem.hpp>

//spectating.hpp handles the spectating side of things
namespace Pulsar {
namespace KO {
class Mgr {
public:
    struct Stats {
        Stats() : percentageSum(0.0f) {}
        struct Final {
            Final() : timeInDanger(0), almostKOdCounter(0), finalPercentageSum(0.0f) {}
            //PERMANENT, FOR KO WINNER
            u16 timeInDanger;
            u8 almostKOdCounter;
            u8 finalPercentageSum; //to be divided by racecount at the end of the GP
        };

        //For precisions
        float percentageSum;
        //UPDATED EACH FRAME IN A RACE
        bool isInDangerFrames[300];
        u32 boolCountArray;
        Final final;
    };
    static const u16 spectatorVote = 0x45;
    static const u32 arbitraryAlmostDied = 60; //60 frames in danger the last 5s = almost out

    static void Create(Page* froom, u32 director, float length);

    Mgr();
    ~Mgr();

    void ResetRace() {
        for(int i = 0; i < 2; ++i) {
            Stats& stats = this->stats[i];
            memset(&stats.isInDangerFrames[0], 0, sizeof(u8) * 300);
            stats.boolCountArray = 0;
            this->posTrackerAnmFrames[i] = 0;
        }

    }
    static void Update(); //static because RaceFrameHook
    static void ProcessKOs(Pages::GPVSLeaderboardUpdate::Player* playerArr, size_t nitems, size_t size, int (*compar)(const void*, const void*)); //calculates the new KOs and updates winnerPlayerAid if needed

    void AddRaceStats();

    SectionId GetSectionAfterKO(SectionId defaultId) const;
    u32 GetAidAndSlotFromPlayerId(u8 playerId) const;
    u8 GetBaseLocalPlayerCount() const { return this->baseLocPlayerCount; }
    bool IsKOdAid(u8 aid, u8 hudslotId) const {
        return this->isKOd[aid][hudslotId];
    }
    bool IsKOdPlayerId(u8 playerId) const {
        u32 aidSlot = this->GetAidAndSlotFromPlayerId(playerId);
        return this->IsKOdAid(aidSlot & 0xFFFF, aidSlot >> 16);
    }
    void SetKOd(u8 playerId) {
        u32 aidSlot = this->GetAidAndSlotFromPlayerId(playerId);
        this->isKOd[aidSlot & 0xFFFF][aidSlot >> 16] = true;
    }
    bool GetWouldBeKnockedOut(u8 hudSlotId) const { return this->wouldBeOut[hudSlotId]; }
    bool GetIsSwapped() const { return this->hasSwapped; }
    void PatchAids(RKNet::ControllerSub& sub) const;
    PageId KickPlayersOut();
    void SwapControllersAndUI();
private:
    bool CalcWouldBeKnockedOut(u8 playerId); //to be used DURING A RACE, returns true if playerId would be out if the race ended NOW
    bool isKOd[12][2]; //TO BE USED WITH AIDS
    u8 baseLocPlayerCount; //playerCount when the GP started
    bool hasSwapped; //controllers
    //InRaceUpdate
    bool wouldBeOut[2];
public:
    //Settings:
    u8 racesPerKO;
    u8 koPerRace;
    bool alwaysFinal;

    u8 winnerPlayerId;
    bool isSpectating;

    Stats stats[2];

    //TEMP
    u8 posTrackerAnmFrames[2];


};
}//namespace KO
}//namespace Pulsar

#endif