#ifndef _NW4R_SNDSEQTRACK_
#define _NW4R_SNDSEQTRACK_
#include <types.hpp>
#include <core/nw4r/snd/Channel.hpp>
#include <core/nw4r/snd/Misc.hpp>


namespace nw4r {
namespace snd {
namespace detail {
class SeqPlayer;

class SeqTrack {
public:
    struct ParserTrackParam {
        u8 _[0x40];
    };
    void SeqTrack::SetPlayerTrackNo(int playerTrackNo); //8009ae00
    SeqTrack::SeqTrack(); //8009ae10
    virtual ~SeqTrack(); //8009aea0 vtable 80274908
    void SeqTrack::InitParam(); //8009afb0
    void SeqTrack::SetSeqData(const void* seqBase, s32 seqOffset); //8009b150
    void SeqTrack::Open(); //8009b160
    void SeqTrack::Close(); //8009b180
    void SeqTrack::UpdateChannelLength(); //8009b250
    int SeqTrack::ParseNextTick(bool doNoteOn); //8009b320
    void SeqTrack::ReleaseAllChannel(int release); //8009b4a0
    void SeqTrack::PauseAllChannel(bool pauseOrRestart); //8009b530


    void SeqTrack::UpdateChannelParam(); //8009b5d0
    void SeqTrack::FreeAllChannel(); //8009bba0
    void SeqTrack::ChannelCallbackFunc(Channel* channel, Channel::ChannelCallbackStatus status, u32 seqTrack); //8009bc10
    void SeqTrack::SetMute(SeqMute ute); //8009bd00
    void SeqTrack::SetVolume(float volume); //8009be70
    void SeqTrack::SetPitch(float pitch); //8009be80
    s16* SeqTrack::GetVariablePtr(int varNo); //8009be90
    Channel* SeqTrack::NoteOn(int key, int velocity, s32 length, bool tieFlag); //8009beb0

    u8 playerTrackNbr; //0x4
    bool openFlag;
    float extVolume; //0x8
    float extPitch; //0xc
    float extPan; //0x10
    float extSurroundPan; //0x14
    float panRange; //0x18
    float unknown_0x1c[13];
    ParserTrackParam parserTrackParam; //0x50
    s16 trackVariable[16]; //0xcc
    SeqPlayer* seqPlayer; //0xec
    Channel* channelList; //0xf0

};
size_assert(SeqPlayer, 0x178);
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif