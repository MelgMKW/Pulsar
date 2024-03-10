#include <kamek.hpp>
#include <core/nw4r/ut/Misc.hpp>
#include <core/nw4r/snd/StrmFile.hpp>
#include <core/nw4r/snd/StrmSound.hpp>
#include <core/nw4r/snd/DVDSoundArchive.hpp>

namespace Pulsar {
namespace Sound {
using namespace nw4r;
//Reimplementation of CTGP's BRSTM volume patch
bool LoadBRSTMVolume(snd::detail::StrmFileLoader& fileLoader, snd::detail::StrmFileReader::StrmInfo* info) {

    u8 volume = *reinterpret_cast<const u8*>(ut::AddU32ToPtr(fileLoader.fileReader.header, 0x3F));
    if(volume != 0) {
        register snd::detail::StrmSound* sound;
        asm(subi sound, r29, 0x100);
        const u32 maxVolume = 0x7F;
        if(volume > maxVolume) volume = maxVolume;
        sound->mainOutVolume = (float)volume / (float)maxVolume;
    }
    return fileLoader.ReadStrmInfo(info);
}
kmCall(0x800a66f4, LoadBRSTMVolume);
//kmWrite32(0x800a66f0, 0x389DFF00);

//Automatic BRSAR patching from Elias_
void BRSAREntrySizePatch(snd::DVDSoundArchive::DVDFileStream* stream, u32 begin, u32 r5) {
    stream->size = 0x7FFFFFFF;
    stream->Seek(begin, r5);
}
kmCall(0x80091354, BRSAREntrySizePatch);




}//namespace Audio
}//namespace Pulsar