#include <Ghost/PULLeaderboard.hpp>
#include <Ghost/GhostManager.hpp>
#include <SlotExpansion/UI/ExpansionUIMisc.hpp>
#include <IO/IO.hpp>


namespace Pulsar {
namespace Ghosts {
const char Leaderboard::filePathFormat[] = "%s/ldb.pul";
//CTOR to build a leaderboard from scratch
Leaderboard::Leaderboard() {
    memset(this, 0, sizeof(Leaderboard));
    this->magic = Leaderboard::fileMagic;
    this->version = curVersion;
    for(int mode = 0; mode < 4; mode++) this->hasTrophy[mode] = false;
}

//CTOR to build it from the raw file
Leaderboard::Leaderboard(const char* folderPath, PulsarId id) {
    char path[IOS::ipcMaxPath];
    snprintf(path, IOS::ipcMaxPath, filePathFormat, folderPath);
    IO* io = IO::sInstance;
    s32 ret = io->OpenFile(path, FILE_MODE_READ_WRITE);
    if(ret) ret = io->Read(sizeof(Leaderboard), this);

    if(!ret || this->crc32 != crc32 || magic != fileMagic) {
        this->CreateFile(id);
        //System::sInstance->taskThread->Request(&Leaderboard::CreateFile, id, 0);
        new (this) Leaderboard;
        this->SetTrack(id);
    }
    io->Close();
}

//This is its own function so that the file can be created async 
void Leaderboard::CreateFile(PulsarId id) {
    char path[IOS::ipcMaxPath];
    snprintf(path, IOS::ipcMaxPath, filePathFormat, Manager::folderPath);
    IO* io = IO::sInstance;
    io->CreateAndOpen(path, FILE_MODE_READ_WRITE);
    alignas(0x20) Leaderboard tempCopy;
    tempCopy.SetTrack(id);
    io->Overwrite(sizeof(Leaderboard), &tempCopy);
    io->Close();
};

void Leaderboard::SetTrack(PulsarId id) {
    if(CupsConfig::IsReg(id)) return;
    this->crc32 = CupsConfig::sInstance->GetCRC32(id);
    char trackName[0x100];
    UI::GetTrackBMG(trackName, id);
    snprintf(this->name, trackNameLen, "%s", trackName);
}


//Get ldb position
s32 Leaderboard::GetPosition(const Timer& other) const {
    s32 position = -1;
    Timer timer;
    for(int i = ENTRY_10TH; i >= 0; i--) {
        this->EntryToTimer(timer, i);
        if(timer > other) position = i;
    }
    return position;
}

s8 Leaderboard::GetRepeatCount(const RKG& rkg) const {
    const TTMode mode = System::sInstance->ttMode;
    const RKGHeader& header = rkg.header;
    s8 repeats = 0;
    for(int i = 0; i < 11; ++i) {
        const PULTimeEntry& cur = this->entries[mode][i];
        if(cur.milliseconds == header.milliseconds && cur.seconds == header.seconds && cur.minutes == header.minutes) repeats++;
    }
    return repeats;
}

//updates the ldb with a new entry and a rkg crc32
void Leaderboard::Update(u32 position, const TimeEntry& entry, u32 rkgCRC32) {
    const TTMode mode = System::sInstance->ttMode;
    if(position != ENTRY_FLAP) { //if 10 then flap
        for(int i = ENTRY_10TH; i > position; i--) memcpy(&this->entries[mode][i], &this->entries[mode][i - 1], sizeof(PULTimeEntry));
        this->entries[mode][position].rkgCRC32 = rkgCRC32;
    }
    memcpy(&this->entries[mode][position].mii, &entry.miiData, sizeof(RFL::StoreData));
    this->entries[mode][position].minutes = entry.timer.minutes;
    this->entries[mode][position].seconds = entry.timer.seconds;
    this->entries[mode][position].milliseconds = entry.timer.milliseconds;
    this->entries[mode][position].isActive = entry.timer.isActive;
    this->entries[mode][position].controllerType = entry.controllerType;
    this->entries[mode][position].character = entry.character;
    this->entries[mode][position].kart = entry.kart;
}

//saves and writes to the file
void Leaderboard::Save(const char* folderPath) {
    char path[IOS::ipcMaxPath];
    snprintf(path, IOS::ipcMaxPath, filePathFormat, folderPath);
    IO* file = IO::sInstance;;
    file->OpenFile(path, FILE_MODE_WRITE);
    file->Overwrite(sizeof(Leaderboard), this);
    file->Close();
}

void Leaderboard::EntryToTimer(Timer& dest, u8 id) const {
    TTMode mode = System::sInstance->ttMode;
    dest.minutes = this->entries[mode][id].minutes;
    dest.seconds = this->entries[mode][id].seconds;
    dest.milliseconds = this->entries[mode][id].milliseconds;
    dest.isActive = this->entries[mode][id].isActive;
}

void Leaderboard::EntryToTimeEntry(TimeEntry& dest, u8 id) const {
    this->EntryToTimer(dest.timer, id);
    TTMode mode = System::sInstance->ttMode;
    memcpy(&dest.miiData, &this->entries[mode][id].mii, sizeof(RFL::StoreData));
    dest.character = this->entries[mode][id].character;
    dest.kart = this->entries[mode][id].kart;
    dest.controllerType = this->entries[mode][id].controllerType;
}

//PULEntry to TimeEntry
const TimeEntry* Leaderboard::GetEntry(u32 index) {
    Manager* manager = Manager::sInstance;
    manager->GetLeaderboard().EntryToTimeEntry(manager->entry, index);
    return &manager->entry;
}
kmWrite32(0x8085d5bc, 0x3860000a);
kmCall(0x8085d5c8, Leaderboard::GetEntry);
kmWrite32(0x8085d784, 0x3860000b);
kmWrite32(0x8085d8c8, 0x5743063E);
kmCall(0x8085d8d0, Leaderboard::GetEntry); //actual leaderboard
//kmWrite32(0x8085d8e8, 0x60000000);
kmWrite32(0x8085da14, 0x281a000a);
kmWrite32(0x8085da2c, 0x83230028);
kmWrite32(0x8085da4c, 0x3860000a);
kmCall(0x8085da54, Leaderboard::GetEntry);
//kmWrite32(0x8085da6c, 0x60000000);

//Correct BMG if you beat the expert
kmWrite32(0x8085d744, 0x38805000);
int Leaderboard::ExpertBMGDisplay() {
    Manager* manager = Manager::sInstance;
    manager->GetLeaderboard().EntryToTimer(manager->entry.timer, ENTRY_1ST);
    const Timer& expert = manager->GetExpert();
    if(expert.isActive && expert > manager->entry.timer) return 2;
    return 1;
}
kmCall(0x8085dc0c, Leaderboard::ExpertBMGDisplay);
kmWrite32(0x8085dc10, 0x38000002);

}//namespace Ghosts
}//namespace Pulsar