#include <kamek.hpp>
#include <MarioKartWii/Audio/AudioManager.hpp>
#include <MarioKartWii/Audio/Other/AudioStreamsMgr.hpp>

namespace Pulsar {
namespace Sound {
/*Allows players to avoid multi BRSTMs if they desire. When a sound trigger KCL that'd lead to a channel switch is encountered,
the game will check the BRASR's entry channel count against the current BRSTM's, and if the latter has fewert than needed,
the channel switch will not happen*/

int CheckChannelCount(const Audio::StreamsMgr&, u32 channel, const nw4r::snd::detail::BasicSound& sound) {
    if(Audio::Manager::sInstance->soundArchivePlayer->soundArchive->GetSoundType(sound.soundId) !=
        snd::SoundArchive::SOUND_TYPE_STRM) return sound.soundId;
    const nw4r::snd::detail::StrmSound& strmSound = static_cast<const nw4r::snd::detail::StrmSound&>(sound);
    const u32 need = strmSound.strmPlayer.channelsNeeded;
    const u32 channelCount = strmSound.strmPlayer.strmInfo.channelCount;
    return (channelCount < need) ? -1 : sound.soundId;
}

asmFunc ConditionalChannelSwitch() {
    ASM(
        nofralloc;
    mr r27, r3;
    mr r28, r4;
    mflr r29;
    bl CheckChannelCount;
    mr r0, r3;
    mr r3, r27;
    mr r4, r28;
    mtlr r29;
    blr;
    );
}
kmCall(0x806fab78, ConditionalChannelSwitch);
}//namespace Audio
}//namespace Pulsar