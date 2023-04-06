#include <core/RK/RKSystem.hpp>
#include <core/rvl/dvd/dvd.hpp>
#include <core/egg/DvdRipper.hpp>
#include <game/Sound/RaceAudioManager.hpp>
#include <Pulsar.hpp>
#include <Settings/PlayerData.hpp>
#include <File/File.hpp>
#include <File/Folder.hpp>


const char Pulsar::pulsarString[8] = "/Pulsar";
const char Pulsar::UIAssets[15] = "/PulsarUI.szs";
const char Pulsar::CommonAssets[18] = "/PulsarCommon.szs";
const char Pulsar::breff[25] = "/Effect/Pulsar.breff";
const char Pulsar::breft[26] = "/Effect/Pulsar.breft";
const char Pulsar::controlFolder[8] = "control";
const char Pulsar::buttonFolder[7] = "button";
const char Pulsar::raceFolder[11] = "game_image";
const char Pulsar::bgFolder[3] = "bg";
const char *Pulsar::ttModeFolders[4] = { "150", "200", "150F", "200F" };
const u8 Pulsar::idToCourseId[42] = {
    0x08, 0x01, 0x02, 0x04, //mushroom cup
    0x10, 0x14, 0x19, 0x1A, //shell cup
    0x00, 0x05, 0x06, 0x07, //flower cup   
    0x1B, 0x1F, 0x17, 0x12,
    0x09, 0x0F, 0x0B, 0x03,
    0x15, 0x1E, 0x1D, 0x11,
    0x0E, 0x0A, 0x0C, 0x0D,
    0x18, 0x16, 0x13, 0x1C

};
const u32 Pulsar::RegsCRC32[32] = {
    0x4C430000,      //LC
    0x4D4D4D00,      //MMM
    0x4D470000,      //MG
    0x54460000,      //TF

    0x72504200,      //rPB
    0x72594600,      //rYF
    0x72475600,      //rGV
    0x724D5200,      //rMR

    0x4D430000,      //MC
    0x434D0000,      //CM
    0x444B5300,      //DKS
    0x57474D00,      //WGM

    0x72534C00,      //rSL
    0x53474200,      //SGB
    0x72445300,      //rDS
    0x72575300,      //rWS

    0x44430000,      //DC
    0x4B430000,      //KC
    0x4D540000,      //MT
    0x47560000,      //GV

    0x72444800,     //rDH
    0x42433300,      //BC3
    0x72444B00,      //rDK
    0x724D4300,      //rMC

    0x44445200,      //DDR
    0x4D480000,      //MH
    0x42430000,      //BC
    0x52520000,      //RR

    0x4D433300,      //MC3
    0x72504700,      //rPG
    0x444B4D00,      //DKM
    0x72424300       //rBC
};
Pulsar *Pulsar::sInstance = NULL;


//Create Pulsar
void Pulsar::GetStaticInstance() {
    RKSystem *rkSystem = &RKSystem::mInstance;
    EGG::ExpHeap *mem2Heap = rkSystem->sceneManager->currentScene->mem2Heap;

    DVDFileInfo fileInfo;

    Binary *bin = (Binary *)EGG::DvdRipper::LoadToMainRam("Pulsar/Pulsar.bin", NULL, mem2Heap, 1, 0, NULL, NULL);

    EGG::ExpHeap *heap = RKSystem::mInstance.EGGSystem;
    Pulsar *pulsar = (Pulsar *)EGG::Heap::alloc(Pulsar::GetClassSize(bin), 0x4, heap);
    new (pulsar) Pulsar(bin, heap);
    Pulsar::sInstance = pulsar;
    EGG::Heap::free(bin, mem2Heap);

}
BootHook CreatePulsar(Pulsar::GetStaticInstance, 0);

//IO
void Pulsar::InitIO() {
    Pulsar *pulsar = Pulsar::sInstance;
    PulsarIO::File::CreateStaticInstance(pulsar->taskThread);
    PulsarIO::Folder *folder = PulsarIO::Folder::CreateStaticInstance(pulsar->taskThread);
    const char *modFolder = Pulsar::sInstance->GetModFolder();
    folder->CreateFolder(modFolder); //not async because it is needed asap
    char ghostPath[IPCMAXPATH];
    snprintf(ghostPath, IPCMAXPATH, "%s%s", modFolder, "/Ghosts");
    folder->RequestCreateFolder(ghostPath);
}
BootHook Folders(Pulsar::InitIO, 1);

Pulsar::Pulsar(Binary *bin, EGG::ExpHeap *heap):
    heap(heap), taskThread(EGG::TaskThread::Create(8, 0, 0x2000, NULL)), ctsCupCount(0),
    //Cup actions initialization
    hasOddCups(false), winningCourse((CourseId)-1), selectedCourse((CourseId)0), lastSelectedCup(0), lastSelectedButtonIdx(0),
    //Track blocking 
    curArrayIdx(0)
{
    //InfoHolder
    if (bin->infoHolder.header.magic == 0x50554C53) {
        memcpy(&this->userInfo, &bin->infoHolder.info, bin->infoHolder.header.length);
        if (userInfo.regsMode == 2) {
            lastSelectedCup = 0x40;
            selectedCourse = (CourseId)0x100;
        }
    }
    if (bin->cupsHolder.header.magic == 0x43555053) {
        u32 count = bin->cupsHolder.ctsCupCount;
        if (count & 1) {
            count++;
            hasOddCups = true;
        }
        ctsCupCount = count;
        memcpy(&this->cups, &bin->cupsHolder.cups, bin->cupsHolder.header.length - sizeof(ctsCupCount) - 4 * sizeof(u16));
    }
    BMGHeader *rawBinBmg = (BMGHeader *)((u8 *)bin + 2 * sizeof(BinaryHeader) + bin->infoHolder.header.length + bin->cupsHolder.header.length);
    this->rawBmg = (BMGHeader *)EGG::Heap::alloc(rawBinBmg->fileLength, 0x4, this->heap);
    memcpy(this->rawBmg, rawBinBmg, rawBinBmg->fileLength);
    this->customBmgs.Init(this->rawBmg);

    //Track blocking 
    lastTracks = new (heap) u32[userInfo.trackBlocking];
    for (int i = 0; i < userInfo.trackBlocking; i++) lastTracks[i] = -1;
}

using IOS::Open2ndInst;
asm s32 Pulsar::Open(const char *path, IOS::Mode mode) { //wiimmfi patch...
    ASM(
        nofralloc;
    stwu sp, -0x0020 (sp);
    b Open2ndInst;
    )
}



void Pulsar::ChangeImage(LayoutUIControl *control, const char *paneName, const char *tplName) {
    void *tplRes = control->layout.resources->multiArcResourceAccessor.GetResource(res::RESOURCETYPE_TEXTURE, tplName);
    if (tplRes != NULL) control->layout.GetPaneByName(paneName)->GetMaterial()->GetTexMapAry()->ReplaceImage((TPLPalettePtr)tplRes);
};

//When a course button is pressed, CourseSelect::LoadNextPage calls this
void Pulsar::SaveSelectedCourse(PushButton *courseButton) {
    this->selectedCourse = (CourseId)(this->lastSelectedCup * 4 + courseButton->buttonId);
    this->winningCourse = selectedCourse;
}

//Converts trackID to track slot using table
CourseId Pulsar::GetCorrectTrackSlot() const {
    CourseId realId = this->ConvertTrack_PulsarIdToRealId(this->winningCourse);
    if (this->IsReg(this->winningCourse)) return realId;
    else return (CourseId)cups[realId / 4].tracks[realId % 4].slot;
}

//MusicSlot
int Pulsar::GetCorrectMusicSlot() const {
    CourseId realId = RaceAudioMgr::sInstance->courseId;
    if (realId <= 0x1F) { //!battle
        realId = this->ConvertTrack_PulsarIdToRealId(this->winningCourse);
        if (!this->IsReg(this->winningCourse)) realId = (CourseId)cups[realId / 4].tracks[realId % 4].musicSlot;
    }
    return RaceAudioMgr::trackToMusicIDTable[realId];
}

int GetCorrectMusicSlotWrapper() {
    return Pulsar::sInstance->GetCorrectMusicSlot();
}
kmCall(0x80711fd8, GetCorrectMusicSlotWrapper);
kmCall(0x8071206c, GetCorrectMusicSlotWrapper);

bool Pulsar::CheckHAWConditions() const {
    bool isHAW = true;
    bool isHAWSet = PulsarSettings::GetInstance()->GetSettings()->pages[OPT_HOST_SETTINGS].radioSetting[OPT_RADIO_HOSTWINS];
    if (!isHAWSet && !this->userInfo.forcedHostAlwaysWins) isHAW = false;
    return isHAW;
}


int Pulsar::GetCRC32(CourseId pulsarId) const {
    if (IsReg(pulsarId)) return RegsCRC32[pulsarId];
    else {
        CourseId realId = this->ConvertTrack_PulsarIdToRealId(pulsarId);
        return this->cups[realId / 4].tracks[realId % 4].crc32;
    }
}

void Pulsar::GetTrackGhostFolder(char *dest, CourseId pulsarId) const {
    u32 crc32 = this->GetCRC32(pulsarId);
    if (IsReg((pulsarId))) {
        snprintf(dest, IPCMAXPATH, "%s/Ghosts/%s", this->GetModFolder(), &crc32);
    }
    else snprintf(dest, IPCMAXPATH, "%s/Ghosts/%08x", this->GetModFolder(), crc32);
}


u32 Pulsar::GetNextCupId(u32 pulsarId, s32 direction) const {
    u32 nextIdx = (ConvertCup_PulsarIdToIdx(pulsarId) + direction + this->GetTotalCupCount()) % this->GetTotalCupCount();
    return this->ConvertCup_IdxToPulsarId(nextIdx);

    /*
       int next = cupId + direction;
       if(next < 0) next += 0x40; //mushroom cup becomes last ct cup
       else if(next > 7 && next < 16 ) next += 0x38; //special cup becomes 1st ct cup
       else if(this->HasRegs()){
          if(next > 16 && next < 0x40) next -= 0x38; //1st ct cup becomes special cup
          else if(next >= ctsCupCount + 0x40)   next -= 0x40 + ctsCupCount; //last ct cup becomes mushroom cup
       }
       if(next < 8){
          next = (next + 8) % 8; //REGS
       }else{
          next = ((next - 0x40 + ctsCupCount) % ctsCupCount) + 0x40; //CTS
       }
       return next;
    */
}

CourseId Pulsar::RandomizeTrack(Random *random) const {
    u32 courseId;
    if (this->HasRegs()) {
        courseId = random->NextLimited(this->GetTotalTrackCount());
        if (courseId > 31) courseId += (0x100 - 32);
    }
    else courseId = random->NextLimited(this->GetCtsTrackCount()) + 0x100;
    return (CourseId)courseId;
}

//Unlock Everything Without Save (_tZ)
kmWrite32(0x80549974, 0x38600001);

//Skip ESRB page
kmWriteRegionInstruction(0x80604094, 0x4800001c, 'E');