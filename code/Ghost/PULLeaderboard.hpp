#ifndef _SIPLEADERBOARD_
#define _SIPLEADERBOARD_
#include <kamek.hpp>
#include <File/Folder.hpp>
#include <Pulsar.hpp>

//Implements a leaderboard file; it is divided in one sub leaderboard per TT modes which holds 11 entries (top 10 + flap)
#define LDBVersion 1

enum EntryLaps {
    ENTRY_1ST,
    ENTRY_2ND,
    ENTRY_3RD,
    ENTRY_4TH,
    ENTRY_5TH,
    ENTRY_6TH,
    ENTRY_7TH,
    ENTRY_8TH,
    ENTRY_9TH,
    ENTRY_10TH,
    ENTRY_FLAP,
};
#pragma(pack, 1)
struct PULTimeEntry {
    PULTimeEntry() {
        minutes = 0;
        seconds = 0;
        milliseconds = 0;
        rkgCRC32 = 0;
    }
    RawMii mii;
    u8 padding[2];
    u32 rkgCRC32; //0x4C
    u16 minutes; //0x50
    u8 seconds; //0x52
    u16 milliseconds; //0x54
    bool isActive; //0x56
    CharacterId character; //0x58
    KartId kart; //0x5C
    u32 controllerType; //0x60
};//total size 0x64
#pragma(pop)

class PULLeaderboard {
public:
    PULLeaderboard();
    PULLeaderboard(const char *folderPath, u32 crc32);
    //void SwapEntries(LeaderboardEntry *entry1, LeaderboardEntry *entry2);
    s32 GetPosition(Timer *timer) const;
    void Update(u32 position, TimeEntry *entry, u32 crc32);
    void Save(const char *folderPath);
    void AddTrophy() { this->hasTrophy[Pulsar::sInstance->ttMode] = true; }
    const PULTimeEntry &GetEntry(EntryLaps lap) const { return this->entries[Pulsar::sInstance->ttMode][lap]; }
    void EntryToTimer(Timer &timer, u8 id) const {
        TTMode mode = Pulsar::sInstance->ttMode;
        timer.minutes = this->entries[mode][id].minutes;
        timer.seconds = this->entries[mode][id].seconds;
        timer.milliseconds = this->entries[mode][id].milliseconds;
        timer.isActive = this->entries[mode][id].isActive;
    }
    void EntryToTimeEntry(TimeEntry &entry, u8 id) {
        this->EntryToTimer(entry.timer, id);
        TTMode mode = Pulsar::sInstance->ttMode;
        memcpy(&entry.mii, &this->entries[mode][id].mii, sizeof(RawMii));
        entry.character = this->entries[mode][id].character;
        entry.kart = this->entries[mode][id].kart;
        entry.controllerType = this->entries[mode][id].controllerType;
    }
    static void CreateFile(void *crc32);

private:
    char magic[4]; //PULL
    u32 version;
    u32 crc32; //of the track
    bool hasTrophy[4];
    u32 reserved[8];
    PULTimeEntry entries[4][11]; //0x30 to 0x44C 11th = flap
}__attribute((aligned(0x20)));





PULTimeEntry *GetPULTimeEntry(u32 index);
#endif