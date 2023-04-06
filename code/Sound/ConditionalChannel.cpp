#include <kamek.hpp>
#include <game/Sound/AudioManager.hpp>

/*Allows players to avoid multi BRSTMs if they desire. When a sound trigger KCL that'd lead to a channel switch is encountered,
the game will check the BRASR's entry channel count against the current BRSTM's, and if the latter has fewert than needed,
the channel switch will not happen*/

int CheckChannelCount(AudioStreamsMgr *streamMgr, u32 channel, nw4r::snd::detail::BasicSound *sound) {
    u32 id = sound->soundId;
    if (AudioManager::sInstance->soundArchivePlayer->soundArchive->GetSoundType(id) != SOUND_TYPE_STRM) return id;
    nw4r::snd::detail::StrmSound *strmSound = (nw4r::snd::detail::StrmSound *)sound;
    u32 need = strmSound->strmPlayer.channelsNeeded;
    u32 channelCount = strmSound->strmPlayer.strmInfo.channelCount;
    return (channelCount < need) ? -1 : id;
}

asm int ConditionalChannelSwitch() {
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