#include "types.hpp"
#include <core/RK/RKSystem.hpp>
#include <core/nw4r/ut/Misc.hpp>
#include <core/rvl/dvd/dvd.hpp>
#include <core/egg/dvd/DvdRipper.hpp>
#include <game/Sound/RaceAudioMgr.hpp>
#include <PulsarSystem.hpp>

#include <Settings/Settings.hpp>
#include <Debug/Debug.hpp>
#include <IO/IO.hpp>
#include <SlotExpansion/CupsDef.hpp>

namespace Pulsar {

System* System::sInstance = nullptr;
System::Inherit* System::inherit = nullptr;


//Create Pulsar
Config* Config::LoadConfig(u32* readBytes) {
    EGG::ExpHeap* mem2Heap = RKSystem::mInstance.sceneManager->currentScene->mem2Heap;
    Config* conf = static_cast<Config*>(EGG::DvdRipper::LoadToMainRAM("Binaries/Config.pul", nullptr, mem2Heap,
        EGG::DvdRipper::ALLOC_FROM_HEAD, 0, readBytes, nullptr));
    if(conf == nullptr) Debug::FatalError(error);
    return conf;
}

void System::CreateSystem() {
    if(sInstance != nullptr) return;
    EGG::Heap* heap = RKSystem::mInstance.EGGSystem;
    const EGG::Heap* prev = heap->BecomeCurrentHeap();
    System* system;
    if(inherit != nullptr) {
        system = inherit->Create();
    }
    else system = new System();
    System::sInstance = system;
    u32 readBytes;
    Config* conf = Config::LoadConfig(&readBytes);
    system->Init(*conf);
    prev->BecomeCurrentHeap();
    conf->Destroy(readBytes);
}
BootHook CreateSystem(System::CreateSystem, 0);

System::System() :
    heap(RKSystem::mInstance.EGGSystem), taskThread(EGG::TaskThread::Create(8, 0, 0x4000, this->heap)),
    //Track blocking 
    racesPerGP(3), curArrayIdx(0) {}

void System::Init(const Config& conf) {
    strncpy(this->modFolderName, conf.header.modFolderName, IOS::ipcMaxFileName);

    this->InitInstances(conf);
    //Track blocking 
    Info* info = Info::sInstance;
    u32 trackBlocking = info->GetTrackBlocking();
    lastTracks = new PulsarId[trackBlocking];
    for(int i = 0; i < trackBlocking; ++i) lastTracks[i] = PULSARID_NONE;

    const BMGHeader* const confBMG = &conf.GetSection<BMGHeader>();
    this->rawBmg = EGG::Heap::alloc<BMGHeader>(confBMG->fileLength, 0x4, heap);
    memcpy(this->rawBmg, confBMG, confBMG->fileLength);
    this->customBmgs.Init(*this->rawBmg);
    this->AfterInit();
}

//IO
#pragma suppress_warnings on
void System::InitIO() const {
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
    IO* io = IO::CreateInstance(type, this->heap, this->taskThread);
    const char* modFolder = this->GetModFolder();
    io->CreateFolder(modFolder); //not async because it is needed asap
    char ghostPath[IOS::ipcMaxPath];
    snprintf(ghostPath, IOS::ipcMaxPath, "%s%s", modFolder, "/Ghosts");
    io->RequestCreateFolder(ghostPath);
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
    )
}
//Unlock Everything Without Save (_tZ)
kmWrite32(0x80549974, 0x38600001);

//Skip ESRB page
kmWriteRegionInstruction(0x80604094, 0x4800001c, 'E');

const char Config::error[] = "Invalid Pulsar Config";
const char System::pulsarString[] = "/Pulsar";
const char System::CommonAssets[] = "/CommonAssets.szs";
const char System::breff[] = "/Effect/Pulsar.breff";
const char System::breft[] = "/Effect/Pulsar.breft";
const char* System::ttModeFolders[] ={ "150", "200", "150F", "200F" };

}//namespace Pulsar