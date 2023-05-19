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
#include <IO/File.hpp>
#include <IO/Folder.hpp>
#include <SlotExpansion/CupsDef.hpp>

namespace Pulsar {

System* System::sInstance = nullptr;
System::Inherit* System::inherit = nullptr;

template<>
inline void Binary::CheckSection<BMGHeader>(const BMGHeader& bmg) const {
    if(bmg.magic != 0x4D455347626D6731) Debug::FatalError(error);
}

template<>
inline const Binary& Binary::GetSection() const {
    return *this;
}

template<>
const InfoHolder& Binary::GetSection<InfoHolder>() const {
    const InfoHolder& infoHolder = *reinterpret_cast<const InfoHolder*>(ut::AddU32ToPtr(this, this->header.offsetToInfo));
    CheckSection(infoHolder);
    return infoHolder;
}
template<>
const CupsHolder& Binary::GetSection<CupsHolder>() const {
    const CupsHolder& cupsHolder =  *reinterpret_cast<const CupsHolder*>(ut::AddU32ToPtr(this, this->header.offsetToCups));
    CheckSection(cupsHolder);
    return cupsHolder;
}
template<>
const BMGHeader& Binary::GetSection<BMGHeader>() const {
    const BMGHeader& bmg = *reinterpret_cast<const BMGHeader*>(ut::AddOffsetToPtr(this, this->header.offsetToBMG));
    CheckSection(bmg);
    return bmg;
}


//Create Pulsar
Binary* Binary::LoadBinary(u32* readBytes) {
    EGG::ExpHeap* mem2Heap = RKSystem::mInstance.sceneManager->currentScene->mem2Heap;
    Binary* bin = static_cast<Binary*>(EGG::DvdRipper::LoadToMainRAM("Binaries/Pulsar.bin", nullptr, mem2Heap,
        EGG::DvdRipper::ALLOC_FROM_HEAD, 0, readBytes, nullptr));
    if(bin == nullptr) Debug::FatalError(error);
    return bin;
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
    Binary* bin = Binary::LoadBinary(&readBytes);
    system->Init(*bin);
    prev->BecomeCurrentHeap();
    bin->Destroy(readBytes);
}
BootHook CreateSystem(System::CreateSystem, 0);

System::System() :
    heap(RKSystem::mInstance.EGGSystem), taskThread(EGG::TaskThread::Create(8, 0, 0x4000, this->heap)),
    //Track blocking 
    racesPerGP(3), curArrayIdx(0) {}

void System::Init(const Binary& bin) {
    strncpy(this->modFolderName, bin.header.modFolderName, IOS::ipcMaxFileName);

    this->InitInstances(bin);
    //Track blocking 
    Info* info = Info::sInstance;
    u32 trackBlocking = info->GetTrackBlocking();
    lastTracks = new PulsarId[trackBlocking];
    for(int i = 0; i < trackBlocking; ++i) lastTracks[i] = PULSARID_NONE;

    const BMGHeader* const rawBinBmg = &bin.GetSection<BMGHeader>();
    this->rawBmg = EGG::Heap::alloc<BMGHeader>(rawBinBmg->fileLength, 0x4, heap);
    memcpy(this->rawBmg, rawBinBmg, rawBinBmg->fileLength);
    this->customBmgs.Init(*this->rawBmg);
    this->AfterInit();
}

//IO
void System::InitIO() {
    IO::IOType type = IO::IOType_ISO;
    s32 ret = IO::Open("file", IOS::MODE_NONE);

    if(ret >= 0) {
        type = IO::IOType_RIIVO;
        IOS::Close(ret);
    }
    else {
        ret = IO::Open("/dev/dolphin", IOS::MODE_NONE);
        if(ret >= 0) {
            type = IO::IOType_DOLPHIN;
            IOS::Close(ret);
        }
    }
    IO::File::CreateStaticInstance(type, this->heap, this->taskThread);
    IO::Folder* folder = IO::Folder::CreateStaticInstance(type, this->heap, this->taskThread);
    const char* modFolder = this->GetModFolder();
    folder->CreateFolder(modFolder); //not async because it is needed asap
    char ghostPath[IOS::ipcMaxPath];
    snprintf(ghostPath, IOS::ipcMaxPath, "%s%s", modFolder, "/Ghosts");
    folder->RequestCreateFolder(ghostPath);
}

void System::InitSettings(const u16* totalTrophyCount) {
    Settings* settings = new (this->heap) Settings;
    char path[IOS::ipcMaxPath];
    snprintf(path, IOS::ipcMaxPath, "%s/%s", this->GetModFolder(), "Settings.bin");
    settings->Init(totalTrophyCount, path); //params
    Settings::sInstance = settings;
}

asm void System::GetRaceCount() {
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

const char Binary::error[] = "Invalid Pulsar.bin";
const char System::pulsarString[] = "/Pulsar";
const char System::UIAssets[] = "/PulsarUI.szs";
const char System::CommonAssets[] = "/PulsarCommon.szs";
const char System::breff[] = "/Effect/Pulsar.breff";
const char System::breft[] = "/Effect/Pulsar.breft";
const char* System::ttModeFolders[] ={ "150", "200", "150F", "200F" };

}//namespace Pulsar