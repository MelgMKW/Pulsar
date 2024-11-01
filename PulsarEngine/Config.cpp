#include <Config.hpp>
#include <core/RK/RKSystem.hpp>
#include <core/egg/mem/ExpHeap.hpp>
#include <core/egg/DVD/DvdRipper.hpp>


namespace Pulsar {

u32 ConfigFile::readBytes = 0;

//Create Pulsar
ConfigFile& ConfigFile::LoadConfig() {
    EGG::ExpHeap* mem2Heap = RKSystem::mInstance.sceneManager->currentScene->mainMEMHeap;
    ConfigFile* conf = static_cast<ConfigFile*>(EGG::DvdRipper::LoadToMainRAM("Binaries/Config.pul", nullptr, mem2Heap,
        EGG::DvdRipper::ALLOC_FROM_TAIL, 0, &readBytes, nullptr));

    if(conf == nullptr) Debug::FatalError(error);
    else {
        if(conf->header.version < 0) Debug::FatalError("Cannot use a \"Build Config Only\" file, please build full or with tracks.");
        if(conf->header.version != conf->header.CONFIGVERSION) Debug::FatalError("Old Config.pul file, please import and export it on the creator software to update it.");
        ConfigFile::CheckSection(conf->GetSection<InfoHolder>());
        ConfigFile::CheckSection(conf->GetSection<CupsHolder>());
        ConfigFile::CheckSection(conf->GetSection<PulBMG>());
    }
    return *conf;
}

const char ConfigFile::error[] = "Invalid Pulsar Config";

}//namespace Pulsar