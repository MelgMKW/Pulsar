#include <kamek.hpp>
#include <core/nw4r/ut/Misc.hpp>
#include <core/nw4r/snd/StrmFile.hpp>
#include <core/nw4r/snd/StrmSound.hpp>
#include <core/nw4r/snd/SoundStartable.hpp>
#include <core/nw4r/snd/DVDSoundArchive.hpp>

namespace Pulsar {
namespace Sound {
using namespace nw4r;
//Reimplementation of CTGP's BRSTM volume patch, and fix for a snd "bug":
//A track won't loop properly if it doesn't have the required channel count (most notable on KC)
//The game reads blocks of the BRSTM every time the prev block has ended, but if the brsar entry says there are X channels, it reads X blocks (one for each channel)
//On a file that actually only has 1 channel, these superfluous reads can overflow the file length when the block index is close to the total block count, 
//which leads to a read error and a playback stop, so we fix the issue by taking the smallest channel count btw the file and the entry. 
//Track Count also needs to be reduced, otherwise the game will play track which are not populated with data
bool LoadBRSTMVolumeAndFixTrackCount(snd::detail::StrmFileLoader& fileLoader, snd::detail::StrmFileReader::StrmInfo& info) {
    register snd::detail::StrmSound* sound;
    asm(subi sound, r29, 0x100);

    u8 volume = *reinterpret_cast<const u8*>(ut::AddU32ToPtr(fileLoader.fileReader.header, 0x3F));
    if (volume != 0) {

        const u32 maxVolume = 0x7F;
        if (volume > maxVolume) volume = maxVolume;
        sound->mainOutVolume = (float)volume / (float)maxVolume;
    }
    bool ret = fileLoader.ReadStrmInfo(&info);
    if (ret) {
        //sound->strmPlayer.channelsNeeded = ut::Max(2U, ut::Min(sound->strmPlayer.channelsNeeded, info.channelCount));
        //sound->strmPlayer.trackCount = ut::Max(1U, ut::Min(sound->strmPlayer.trackCount, info.channelCount / 2));

        snd::detail::StrmPlayer& player = sound->strmPlayer;
        u32 brsarChannel = player.channelsNeeded;
        u32 actual = ut::Min(sound->strmPlayer.channelsNeeded, info.channelCount);
        for (int index = actual; index < brsarChannel; ++index) {
            if (player.channels[index].bufferAddress == nullptr) continue;
            player.strmBufferPool->Free(player.channels[index].bufferAddress);
            player.channels[index].bufferAddress = nullptr;
        }
        player.channelsNeeded = actual;
        sound->strmPlayer.trackCount = ut::Min(sound->strmPlayer.trackCount, (info.channelCount + 1) / 2);
    }
    return ret;
}
kmCall(0x800a66f4, LoadBRSTMVolumeAndFixTrackCount);
//kmWrite32(0x800a66f0, 0x389DFF00);


//Automatic BRSAR patching from Elias_
void BRSAREntrySizePatch(snd::DVDSoundArchive::DVDFileStream* stream, s32 offset, u32 origin) {
    stream->size = 0x7FFFFFFF;
    stream->Seek(offset, origin);
}
kmCall(0x80091354, BRSAREntrySizePatch);




}//namespace Sound
}//namespace Pulsar