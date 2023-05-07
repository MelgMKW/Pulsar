#include <Ghost/GhostManager.hpp>
#include <game/UI/Page/Other/TTSplits.hpp>
#include <UI/UI.hpp>


namespace Pulsar {
namespace Ghosts {
Manager* Manager::sInstance = nullptr;
char Manager::folderPath[IOS::ipcMaxPath] = "";



Manager::~Manager() {
    delete[] this->files; //in case Reset wasn't called before
}

Manager* Manager::CreateInstance() {
    Manager* holder = Manager::sInstance;
    if(holder == nullptr) {
        holder = new(System::sInstance->heap) Manager;
        Manager::sInstance = holder;
    }
    holder->Reset();
    return holder;
}

void Manager::DestroyInstance() {
    delete(Manager::sInstance);
    Manager::sInstance = nullptr;
}

/*
Cornerstone function; Creates the folders if they have been deleted somehow,
reads them, fetches the leaderboard, creates GhostDatas based on the rkgs, sets the expert time
*/
void Manager::Init(PulsarId id) {
    this->Reset();
    this->pulsarId = id;
    IO::Folder* folder = IO::Folder::sInstance;
    const System* system = System::sInstance;
    const CupsDef* cups = CupsDef::sInstance;
    cups->GetTrackGhostFolder(folderPath, id);

    bool exists = folder->FolderExists(folderPath); //Create "Ghosts" folder
    if(!exists) folder->RequestCreateFolder(folderPath);
    char folderModePath[IOS::ipcMaxPath];
    snprintf(folderModePath, IOS::ipcMaxPath, "%s/%s", folderPath, System::ttModeFolders[system->ttMode]); //Creates Mode Folder
    exists = folder->FolderExists(folderModePath);
    if(!exists) folder->RequestCreateFolder(folderModePath);
    else folder->ReadFolder(folderModePath); //Reads all files contained in the folder

    new (&this->leaderboard) Leaderboard(folderPath, cups->GetCRC32(id));

    this->files = new (system->heap) GhostData[folder->GetFileCount()];

    u32 counter = 0;
    for(int i = 0; i < folder->GetFileCount(); ++i) {
        rkg.ClearBuffer();
        GhostData& curData = this->files[counter];
        s32 ret = folder->ReadFile(&rkg, i, IO::FILE_MODE_READ, sizeof(RKG));
        if(ret > 0 && rkg.CheckValidity()) {
            curData.Init(rkg);
            curData.courseId = static_cast<CourseId>(id);
            if(curData.type == EXPERT_STAFF_GHOST) { //very easy to fake/manipulate, but 0 security so it doesn't matter
                this->expertGhost.minutes = rkg.header.minutes;
                this->expertGhost.seconds = rkg.header.seconds;
                this->expertGhost.milliseconds = rkg.header.milliseconds;
                this->expertGhost.isActive = true;
            }
            curData.padding = i;
            ++counter;
        }
    }
    this->rkgCount = counter;
}

void Manager::Reset() {
    IO::Folder::sInstance->CloseFolder();
    this->pulsarId = PULSARID_NONE;
    this->lastUsedSlot = 0;
    mainGhostIndex = 0xFF;
    for(int i = 0; i < 3; ++i) selGhostsIndex[i] = 0xFF;
    new(&this->expertGhost) Timer;
    delete[] this->files;
    this->files = nullptr;
    RaceData* racedata = RaceData::sInstance;
    racedata->menusScenario.players[1].playerType = PLAYER_NONE;
    racedata->menusScenario.players[2].playerType = PLAYER_NONE;
    racedata->menusScenario.players[3].playerType = PLAYER_NONE;
}

//Enables ghost for loading when GhostSelect's ToggleButton is pressed to true and when Challenge/Watch is pressed
bool Manager::EnableGhost(const GhostListEntry& entry, bool isMain) {
    bool exists = false;
    u32* index = &mainGhostIndex;
    if(!isMain) index = &selGhostsIndex[this->lastUsedSlot];
    for(int i = 0; i < this->rkgCount; ++i) {
        if(&this->files[i] == entry.data) {
            *index = i;
            exists = true;
            break;
        }
    }
    if(exists && !isMain) this->lastUsedSlot = (this->lastUsedSlot + 1) % 3;
    return exists;
}

//Used when GhostSelect' ToggleButton is pressed to false
void Manager::DisableGhost(const GhostListEntry& entry) {
    u32 index = 0xFF;
    for(int i = 0; i < this->rkgCount; ++i) {
        if(&this->files[i] == entry.data) {
            index = i;
            break;
        }
    }
    for(int i = 0; i < 3; ++i) {
        if(this->selGhostsIndex[i] == index) {
            this->lastUsedSlot = i;
            this->selGhostsIndex[i] = 0xFF;
        }
    }
}

//Loads and checks validity of a RKG
bool Manager::LoadGhost(RKG& rkg, u32 index) {
    rkg.ClearBuffer();
    IO::Folder::sInstance->ReadFile(&rkg, index, IO::FILE_MODE_READ, sizeof(RKG));
    return rkg.CheckValidity();
}

//Copies ghost from src to racedata's RKG buffers and adds mii if ghost race
void Manager::LoadAllGhosts(u32 maxGhosts, bool isGhostRace) {
    u8 position = 1;
    for(int i = 0; i < maxGhosts; ++i) {
        if(this->selGhostsIndex[i] != 0xFF) {
            if(this->LoadGhost(this->rkg, this->GetGhostData(this->selGhostsIndex[i]).padding)) {
                RaceData* racedata = RaceData::sInstance;
                RKG& dest = racedata->ghosts[position];
                if(this->rkg.header.compressed) this->rkg.DecompressTo(dest); //0x2800
                else memcpy(&dest, &this->rkg, sizeof(RKG));
                racedata->menusScenario.players[position + isGhostRace].playerType = PLAYER_GHOST;
                SectionMgr::sInstance->sectionParams->playerMiis.AddMii(position + isGhostRace, &dest.header.miiData);
                ++position;
            }
        }
    }
}

bool Manager::SaveGhost(const TimeEntry& entry, u32 ldbPosition, bool isFlap) {
    //Compare against leaderboard and save

    if(isFlap) this->leaderboard.Update(ENTRY_FLAP, entry, -1);
    GhostData data;
    data.Fill(0);
    RKG buffer;
    buffer.ClearBuffer();

    bool gotTrophy = false;
    if(data.CreateRKG(buffer) && buffer.CompressTo(this->rkg)) {
        u32 crc32 = Manager::GetRKGcrc32(this->rkg);
        if(ldbPosition >= 0) this->leaderboard.Update(ldbPosition, entry, crc32); //in this order as save opens files too
        const System* system = System::sInstance;
        system->taskThread->Request(&Manager::CreateAndSaveFiles, this, 0);

        const Timer& expert = this->GetExpert();
        if(expert.isActive && expert > entry.timer && Info::HasTrophies()) {
            gotTrophy = true;
            Settings::GetInstance()->AddTrophy(CupsDef::sInstance->GetCRC32(this->GetPulsarId()), system->ttMode);
            this->leaderboard.AddTrophy();

        }
    }
    return gotTrophy;
}

//When a request has been sent, creates and writes to a RKG, updates Settings and updates the leaderboard
void Manager::CreateAndSaveFiles(Manager* manager) {
    char path[IOS::ipcMaxPath];
    const RKG& rkg = manager->rkg;
    snprintf(path, IOS::ipcMaxPath, "%s/%01dm%02ds%03d.rkg", IO::Folder::sInstance->GetName(),
        rkg.header.minutes, rkg.header.seconds, rkg.header.milliseconds);
    IO::File* loader = IO::File::sInstance;
    loader->CreateAndOpen(path, IO::FILE_MODE_WRITE);
    loader->Overwrite(GetRKGLength(rkg), &rkg);
    loader->Close();

    const CupsDef* cups = CupsDef::sInstance;
    char folderPath[IOS::ipcMaxPath];
    cups->GetTrackGhostFolder(folderPath, manager->pulsarId);
    manager->leaderboard.Save(folderPath);
    Settings::GetInstance()->Save(); //trophies
    manager->Init(cups->winningCourse);
    SectionMgr::sInstance->sectionParams->isNewTime = true;
}

//Inits MultiGhostMgr and uses it to fill the GhostList
void Manager::InsertCustomGroupToList(GhostList* list, CourseId) { //check id here
    Manager* manager = Manager::sInstance;
    const CupsDef* cups = CupsDef::sInstance;
    manager->Init(cups->winningCourse);
    u32 index = 0;
    for(int i = 0; i < IO::Folder::sInstance->GetFileCount(); ++i) {
        if(index == 38) break;
        const GhostData& data = manager->GetGhostData(i);
        if(data.isValid) {
            list->entries[index].data = &data;
            ++index;
        }
    }
    list->count = index;
    qsort(list, list->count, sizeof(GhostListEntry), reinterpret_cast<int (*)(const void*, const void*)>(&GhostList::CompareEntries));
};
kmCall(0x806394f0, Manager::InsertCustomGroupToList);

//80856fec Race get ldr position for animation almost certainly
//80855c6c save ghost (get ldr position) r4 timer r5 savedatamanagerlicence
//8051ca80 write ghost file
s32 PlayCorrectFinishAnim(LicenseManager*, const Timer& timer, CourseId courseId) {
    return Manager::GetInstance()->GetLeaderboard().GetPosition(timer);
}
kmCall(0x80856fec, PlayCorrectFinishAnim);



//make racedata bigger to have 2 more rkgs
int IncreaseRacedataSize() {
    return 0xC3F0;
}
kmCall(0x8052fe78, IncreaseRacedataSize);
kmWrite32(0x80531f44, 0x4800001c); //make it so the game will only use the first rkg buffer for normal ghost usage

//Patch needed since we now have 4 rkgs which are used in order
bool RacedataCheckCorrectRKG(u8 id) {
    u8 offset = 0;
    if(RaceData::sInstance->menusScenario.players[0].playerType != PLAYER_GHOST) offset = 1;
    return RaceData::sInstance->ghosts[id - offset].CheckValidity();
}
kmWrite32(0x8052f5c0, 0x5763063E);
kmCall(0x8052f5c8, RacedataCheckCorrectRKG);

//Same as above
void GhostHeaderGetCorrectRKG(GhostData& header, u8 id) {
    u8 offset = 0;
    RaceData* racedata = RaceData::sInstance;
    RacedataScenario& scenario = racedata->menusScenario;
    if(scenario.players[0].playerType != PLAYER_GHOST) offset = 1;
    scenario.players[id].hudSlotId = id;
    scenario.settings.hudPlayerIds[id] = id;
    header.Init(racedata->ghosts[id - offset]);
    header.courseId = scenario.settings.courseId;
}
kmWrite32(0x8052f5dc, 0x5764063E);
kmCall(0x8052f5e4, GhostHeaderGetCorrectRKG);

//Function name says it all
void Manager::LoadCorrectMainGhost(Pages::GhostManager& ghostManager, u8 r4) {
    Manager* manager = Manager::sInstance;
    manager->LoadGhost(*ghostManager.rkgPointer, manager->GetGhostData(manager->mainGhostIndex).padding);
    if(ghostManager.state == SAVED_GHOST_RACE_FROM_MENU) ghostManager.state = STAFF_GHOST_RACE_FROM_MENU;
    //faking that it's a staff so it copies from the buffer and not savadatemanager
}
kmCall(0x805e158c, Manager::LoadCorrectMainGhost);

//Loads all the ghosts while setting up the ghost race/replay
void Manager::ExtendSetupGhostRace(Pages::GhostManager& ghostManager, bool isStaffGhost, bool replaceGhostMiiByPlayer, bool disablePlayerMii) {
    ghostManager.SetupGhostRace(true, replaceGhostMiiByPlayer, disablePlayerMii);
    Manager::sInstance->LoadAllGhosts(2, true);

}
kmCall(0x805e13ac, Manager::ExtendSetupGhostRace);
kmCall(0x805e13e4, Manager::ExtendSetupGhostRace);
kmCall(0x805e141c, Manager::ExtendSetupGhostRace);
kmCall(0x805e149c, Manager::ExtendSetupGhostRace);
kmCall(0x805e14c8, Manager::ExtendSetupGhostRace);
kmCall(0x805e14f4, Manager::ExtendSetupGhostRace);

void Manager::ExtendSetupGhostReplay(Pages::GhostManager& ghostManager, bool isStaffGhosts) {
    ghostManager.SetupGhostReplay(true);
    Manager::sInstance->LoadAllGhosts(3, false);
}
kmCall(0x805e144c, Manager::ExtendSetupGhostReplay);
kmCall(0x805e1518, Manager::ExtendSetupGhostReplay);

//m98 slot patch, used for ghost stuff (ghosts check that the rkg has the same trackID as the current for example)
void SetCorrectGhostRaceSlot(const GhostList& list, s32 entryIdx) {
    list.InitSectionParamsParams(entryIdx);
    if(entryIdx >= 0 && entryIdx < list.count) {
        const CourseId slot = CupsDef::sInstance->GetCorrectTrackSlot();
        SectionMgr::sInstance->sectionParams->courseId = slot;
    }
}
kmCall(0x805c7b6c, SetCorrectGhostRaceSlot);
kmCall(0x805c7d2c, SetCorrectGhostRaceSlot);
kmCall(0x80639e54, SetCorrectGhostRaceSlot);
kmCall(0x80639fb0, SetCorrectGhostRaceSlot);
}//namespace Ghosts
}//namespace Pulsar

