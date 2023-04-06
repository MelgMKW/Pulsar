#ifndef _NW4R_SNDACTOR_
#define _NW4R_SNDACTOR_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/SoundArchivePlayer.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
#include <core/nw4r/snd/ExternalSoundPlayer.hpp>
#include <core/nw4r/snd/BasicSound.hpp>

namespace nw4r {
namespace snd {
class SoundActor : public SoundStartable {
public:
    typedef detail::ExternalSoundPlayer ActorPlayer;
    SoundActor(SoundArchivePlayer *soundArchivePlayer); //8009dbe0
    ~SoundActor() override; //8009dca0 vtable 802749a0
    SoundStartable::StartResult detail_SetupSound(SoundHandle *handle, u32 soundId, bool holdFlag, SoundArchive::SoundInfo *soundInfo) override; //8009dd90
    u32 ConvertLabelStringToSoundId(const char *label) override; //8009ddd0
    virtual StartResult SetupSound(SoundHandle *handle, u32 soundId, const StartInfo *startInfo, void *setupArg); //8009dd50
    virtual SoundStartable::StartResult detail_SetupSoundWithAmbientInfo(SoundHandle *handle, u32 soundId, const StartInfo *startInfo, detail::BasicSound::AmbientInfo *ambientInfo, void *setupArg); //8009dd70
    SoundArchivePlayer &soundArchivePlayer;
    ActorPlayer actorPlayers[4];
    detail::SoundActorParam actorParam;
}; //0x54
size_assert(SoundActor, 0x54);
}//namespace snd
}//namespace nw4r


#endif