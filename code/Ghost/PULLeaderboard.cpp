#include <Ghost/PULLeaderboard.hpp>
#include <Ghost/MultiGhostMgr.hpp>

//CTOR to build a leaderboard from scratch
PULLeaderboard::PULLeaderboard() {
    memset(this, 0, sizeof(PULLeaderboard));
    this->magic[0] = 'P';
    this->magic[1] = 'U';
    this->magic[2] = 'L';
    this->magic[3] = 'L';
    this->version = LDBVersion;
    for (int mode = 0; mode < 4; mode++) this->hasTrophy[mode] = false;
}

//CTOR to build it from the raw file
PULLeaderboard::PULLeaderboard(const char *folderPath, u32 crc32) {
    char filePath[IPCMAXPATH];
    snprintf(filePath, IPCMAXPATH, "%s/ldb.bin", folderPath);
    PulsarIO::File *loader = PulsarIO::File::sInstance;
    s32 ret = loader->Open(filePath, PulsarIO::FILE_MODE_READ_WRITE);
    if (ret > 0) ret = loader->Read(this, sizeof(PULLeaderboard));

    if (ret <= 0 || this->crc32 != crc32 || this->magic[0] != 'P' || this->magic[1] != 'U' || this->magic[2] != 'L' || this->magic[3] != 'L') {
        Pulsar::sInstance->taskThread->Request(&PULLeaderboard::CreateFile, (void *)crc32, NULL);
        new (this) PULLeaderboard;
        this->crc32 = crc32;
    }
    loader->Close();
}

//This is its own function so that the file can be created async 
void PULLeaderboard::CreateFile(void *crc32) {
    char filePath[IPCMAXPATH];
    snprintf(filePath, IPCMAXPATH, "%s/ldb.bin", MultiGhostMgr::folderPath);
    PulsarIO::File *loader = PulsarIO::File::sInstance;
    loader->CreateAndOpen(filePath, PulsarIO::FILE_MODE_READ_WRITE);
    PULLeaderboard *temp = new (Pulsar::sInstance->heap, 0x20) PULLeaderboard;
    temp->crc32 = (u32)crc32;
    loader->Overwrite(sizeof(PULLeaderboard), temp);
    loader->Close();
    delete(temp);
};

//Get ldb position
s32 PULLeaderboard::GetPosition(Timer *srcTimer) const {
    s32 position = -1;
    Timer timer;
    for (int i = ENTRY_10TH; i >= 0; i--) {
        this->EntryToTimer(timer, i);
        if (timer > (*srcTimer)) position = i;
    }
    return position;
}

//updates the ldb with a new entry and a rkg crc32
void PULLeaderboard::Update(u32 position, TimeEntry *entry, u32 crc32) {
    TTMode mode = Pulsar::sInstance->ttMode;
    if (position != ENTRY_FLAP) { //if 10 then flap
        for (int i = ENTRY_10TH; i > position; i--) memcpy(&this->entries[mode][i], &this->entries[mode][i - 1], sizeof(PULTimeEntry));
        this->entries[mode][position].rkgCRC32 = crc32;
    }
    memcpy(&this->entries[mode][position].mii, &entry->mii, sizeof(RawMii));
    this->entries[mode][position].minutes = entry->timer.minutes;
    this->entries[mode][position].seconds = entry->timer.seconds;
    this->entries[mode][position].milliseconds = entry->timer.milliseconds;
    this->entries[mode][position].isActive = entry->timer.isActive;
    this->entries[mode][position].controllerType = entry->controllerType;
    this->entries[mode][position].character = entry->character;
    this->entries[mode][position].kart = entry->kart;
}

//saves and writes to the file
void PULLeaderboard::Save(const char *folderPath) {
    char filePath[IPCMAXPATH];
    snprintf(filePath, IPCMAXPATH, "%s/ldb.bin", folderPath);
    PulsarIO::File *loader = PulsarIO::File::sInstance;
    loader->Open(filePath, PulsarIO::FILE_MODE_WRITE);
    loader->Overwrite(sizeof(PULLeaderboard), this);
    loader->Close();
}

//PULEntry to TimeEntry
TimeEntry *GetEntry(u32 index) {
    MultiGhostMgr *manager = MultiGhostMgr::GetInstance();
    manager->GetLeaderboard()->EntryToTimeEntry(manager->entry, index);
    return &manager->entry;
}
kmWrite32(0x8085d5bc, 0x3860000a);
kmCall(0x8085d5c8, GetEntry);
kmWrite32(0x8085d784, 0x3860000b);
kmWrite32(0x8085d8c8, 0x5743063E);
kmCall(0x8085d8d0, GetEntry); //actual leaderboard
//kmWrite32(0x8085d8e8, 0x60000000);
kmWrite32(0x8085da14, 0x281a000a);
kmWrite32(0x8085da2c, 0x83230028);
kmWrite32(0x8085da4c, 0x3860000a);
kmCall(0x8085da54, GetEntry);
//kmWrite32(0x8085da6c, 0x60000000);

//Correct BMG if you beat the expert
kmWrite32(0x8085d744, 0x38805000);
int ExpertBMGDisplay() {
    MultiGhostMgr *manager = MultiGhostMgr::GetInstance();
    manager->GetLeaderboard()->EntryToTimer(manager->entry.timer, ENTRY_1ST);
    const Timer &expert = manager->GetExpert();
    if (expert.isActive && expert > manager->entry.timer) return 2;
    return 1;
}
kmCall(0x8085dc0c, ExpertBMGDisplay);
kmWrite32(0x8085dc10, 0x38000002);