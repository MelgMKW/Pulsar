#include <kamek.hpp>
#include <Sound/MiscSound.hpp>

namespace Pulsar {
namespace Audio {

using namespace nw4r;
snd::SoundStartable::StartResult PlayExtBRSEQ(snd::SoundStartable& startable, AudioHandle& handle, const char* fileName, const char* labelName, bool hold) {
    snd::SoundStartable::StartInfo startInfo;
    startInfo.seqSoundInfo.startLocationLabel = labelName;
    startInfo.enableFlag |= snd::SoundStartable::StartInfo::ENABLE_SEQ_SOUND_INFO;

    void* file = ArchiveRoot::sInstance->GetFile(ARCHIVE_HOLDER_COMMON, fileName);
    if(file != nullptr) {
        startInfo.seqSoundInfo.seqDataAddress = file;
        if(hold) return startable.detail_HoldSound(&handle, SOUND_ID_MINITURBO, &startInfo);
        else return startable.detail_StartSound(&handle, SOUND_ID_MINITURBO, &startInfo);
    }
    return snd::SoundStartable::START_ERR_USER;
}

//disable TF music delay
kmWrite16(0x80711FE8, 0x00004800);
kmWrite16(0x80712024, 0x00004800);
kmWrite16(0x8071207C, 0x00004800);
kmWrite16(0x807120B8, 0x00004800);

//disable tf music reset
kmWrite32(0x80719920, 0x48000010);

//disable THP and demo by blring SingleSoundPlayer::CalcTitlePageNext
kmWrite32(0x806fa738, 0x4e800020);
}//namespace Audio
}//namespace Pulsar
