#include <kamek.hpp>
#include <MarioKartWii/Audio/AudioManager.hpp>
#include <MarioKartWii/Audio/Other/AudioStreamsMgr.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>

namespace Pulsar {
namespace Sound {
/*Allows players to avoid multi BRSTMs if they desire. When a sound trigger KCL that'd lead to a channel switch is encountered,
the game will check the BRASR's entry channel count against the current BRSTM's, and if the latter has fewert than needed,
the channel switch will not happen*/

int CheckChannelCount(const Audio::StreamsMgr&, u32 channel, const nw4r::snd::detail::BasicSound& sound) {

    u32 soundId = sound.soundId;
    const snd::SoundArchive* soundArchive = Audio::Manager::sInstance->soundArchivePlayer->soundArchive;
    if(soundArchive->GetSoundType(soundId) != snd::SoundArchive::SOUND_TYPE_STRM) return soundId;

    //cannot use StrmPlayer::channelsNeeded because it may have been overwritten by LoadBRSTMVolumeAndFixTrackCount; therefore, must fetch from the BRSAR entry again
    snd::SoundArchive::StrmSoundInfo info;
    soundArchive->detail_ReadStrmSoundInfo(soundId, &info);
    const u32 need = info.allocChannelCount;
    const u32 channelCount =  static_cast<const nw4r::snd::detail::StrmSound&>(sound).strmPlayer.strmInfo.channelCount;
    if(soundId == SOUND_ID_KC) {
        const SectionId section = SectionMgr::sInstance->curSection->sectionId;
        if(section >= SECTION_SINGLE_P_FROM_MENU && section <= SECTION_SINGLE_P_LIST_RACE_GHOST || section == SECTION_LOCAL_MULTIPLAYER) soundId = SOUND_ID_OFFLINE_MENUS;
        else if(section >= SECTION_P1_WIFI && section <= SECTION_P2_WIFI_FROOM_COIN_VOTING) soundId = SOUND_ID_WIFI_MUSIC;
    }
    return (channelCount < need) ? -1 : soundId;
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