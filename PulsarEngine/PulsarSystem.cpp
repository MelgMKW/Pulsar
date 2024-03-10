#include "types.hpp"
#include <core/RK/RKSystem.hpp>
#include <core/nw4r/ut/Misc.hpp>
#include <core/rvl/dvd/dvd.hpp>
#include <core/egg/dvd/DvdRipper.hpp>
#include <PulsarSystem.hpp>

#include <Settings/Settings.hpp>
#include <Debug/Debug.hpp>
#include <IO/IO.hpp>
#include <SlotExpansion/CupsConfig.hpp>

namespace Pulsar {

System* System::sInstance = nullptr;
System::Inherit* System::inherit = nullptr;


//Create Pulsar
ConfigFile* ConfigFile::LoadConfig(u32* readBytes) {
    EGG::ExpHeap* mem2Heap = RKSystem::mInstance.sceneManager->currentScene->mem2Heap;
    ConfigFile* conf = static_cast<ConfigFile*>(EGG::DvdRipper::LoadToMainRAM("Binaries/Config.pul", nullptr, mem2Heap,
        EGG::DvdRipper::ALLOC_FROM_HEAD, 0, readBytes, nullptr));

    if(conf == nullptr) Debug::FatalError(error);
    else {
        if(conf->header.version < 0) Debug::FatalError("Cannot use a \"Build Config Only\" file, please build full or with tracks.");
        if(conf->header.version != conf->header.curVersion) Debug::FatalError("Old Config.pul file, please import and export it on the creator software to update it.");
        ConfigFile::CheckSection(conf->GetSection<InfoHolder>());
        ConfigFile::CheckSection(conf->GetSection<CupsHolder>());
        ConfigFile::CheckSection(conf->GetSection<PulBMG>());
    }
    return conf;
}

void System::CreateSystem() {
    if(sInstance != nullptr) return;
    EGG::Heap* heap = RKSystem::mInstance.EGGSystem;
    const EGG::Heap* prev = heap->BecomeCurrentHeap();
    System* system;
    if(inherit != nullptr) {
        system = inherit->create();
    }
    else system = new System();
    System::sInstance = system;
    u32 readBytes;
    ConfigFile* conf = ConfigFile::LoadConfig(&readBytes);
    system->Init(*conf);
    prev->BecomeCurrentHeap();
    conf->Destroy(readBytes);
}
BootHook CreateSystem(System::CreateSystem, 0);

System::System() :
    heap(RKSystem::mInstance.EGGSystem), taskThread(EGG::TaskThread::Create(8, 0, 0x4000, this->heap)),
    //Track blocking 
    racesPerGP(3), curBlockingArrayIdx(0) {}

void System::Init(const ConfigFile& conf) {
    IOType type = IOType_ISO;
    s32 ret = IO::OpenFix("file", IOS::MODE_NONE);

    if(ret >= 0) {
        type = IOType_RIIVO;
        IOS::Close(ret);
    }
    else {
        ret = IO::OpenFix("/dev/dolphin", IOS::MODE_NONE);
        if(ret >= 0) {
            type = IOType_DOLPHIN;
            IOS::Close(ret);
        }
    }
    strncpy(this->modFolderName, conf.header.modFolderName, IOS::ipcMaxFileName);

    this->InitInstances(conf, type);

    //Initialize last selected cup and courses
    const PulsarCupId last = Settings::Mgr::sInstance->GetSavedSelectedCup();
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    cupsConfig->SetLayout();
    if(last != -1 && cupsConfig->IsValidCup(last) && cupsConfig->GetTotalCupCount() > 8) {
        cupsConfig->lastSelectedCup = last;
        cupsConfig->selectedCourse = static_cast<PulsarId>(cupsConfig->ConvertTrack_PulsarCupToTrack(last, 0));
        cupsConfig->lastSelectedCupButtonIdx = last & 1;
    }

    //Track blocking 
    Info* info = Info::sInstance;
    u32 trackBlocking = info->GetTrackBlocking();
    lastTracks = new PulsarId[trackBlocking];
    for(int i = 0; i < trackBlocking; ++i) lastTracks[i] = PULSARID_NONE;

    const BMGHeader* const confBMG = &conf.GetSection<PulBMG>().header;
    this->rawBmg = EGG::Heap::alloc<BMGHeader>(confBMG->fileLength, 0x4, heap);
    memcpy(this->rawBmg, confBMG, confBMG->fileLength);
    this->customBmgs.Init(*this->rawBmg);
    this->AfterInit();
}

//IO
#pragma suppress_warnings on
void System::InitIO(IOType type) const {

    IO* io = IO::CreateInstance(type, this->heap, this->taskThread);
    bool ret;
    if(io->type == IOType_DOLPHIN) ret = ISFS::CreateDir("/shared2/Pulsar", 0, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE);
    const char* modFolder = this->GetModFolder();
    ret = io->CreateFolder(modFolder);
    if(!ret && io->type == IOType_DOLPHIN) {
        char path[0x100];
        snprintf(path, 0x100, "Unable to automatically create a folder for this CT distribution\nPlease create a Pulsar folder in Dolphin Emulator/Wii/shared2", modFolder);
        Debug::FatalError(path);
    }
    char ghostPath[IOS::ipcMaxPath];
    snprintf(ghostPath, IOS::ipcMaxPath, "%s%s", modFolder, "/Ghosts");
    io->CreateFolder(ghostPath);
}
#pragma suppress_warnings reset

void System::InitSettings(u32 pageCount, const u16* totalTrophyCount) const {
    Settings::Mgr* settings = new (this->heap) Settings::Mgr;
    char path[IOS::ipcMaxPath];
    snprintf(path, IOS::ipcMaxPath, "%s/%s", this->GetModFolder(), "Settings.pul");
    settings->Init(pageCount, totalTrophyCount, path); //params
    Settings::Mgr::sInstance = settings;
}

asmFunc System::GetRaceCount() {
    ASM(
        nofralloc;
    lis r5, sInstance@ha;
    lwz r5, sInstance@l(r5);
    lbz r0, System.racesPerGP(r5);
    blr;
    )
}
//Unlock Everything Without Save (_tZ)
kmWrite32(0x80549974, 0x38600001);

//Skip ESRB page
kmWriteRegionInstruction(0x80604094, 0x4800001c, 'E');

const char ConfigFile::error[] = "Invalid Pulsar Config";
const char System::pulsarString[] = "/Pulsar";
const char System::CommonAssets[] = "/CommonAssets.szs";
const char System::breff[] = "/Effect/Pulsar.breff";
const char System::breft[] = "/Effect/Pulsar.breft";
const char* System::ttModeFolders[] ={ "150", "200", "150F", "200F" };

}//namespace Pulsar