#ifndef _NW4R_SNDMISC_
#define _NW4R_SNDMISC_
#include <types.hpp>

namespace nw4r {
namespace snd {

enum SeqMute {
    MUTE_OFF,       //Unmute
    MUTE_NO_STOP,   //Mute SEQ and don't stop
    MUTE_RELEASE,   //Mute SEQ and stop after release
    MUTE_STOP       //Mute SEQ and stop immediately
};
enum AuxBus {
    AUX_A = 0,
    AUX_B = 1,
    AUX_C = 2
};
enum SampleFormat {
    SAMPLE_FORMAT_PCM_S32,
    SAMPLE_FORMAT_PCM_S16,
    SAMPLE_FORMAT_PCM_S8,
    SAMPLE_FORMAT_DSP_ADPCM
};

enum OutputMode {
    OUTPUT_MODE_STEREO,
    OUTPUT_MODE_SURROUND,
    OUTPUT_MODE_DPL2,
    OUTPUT_MODE_MONO
};

struct AdpcmParam {
    u16 coef[16];
    u16 gain;
    u16 predScale;
    u16 sampleHistory1;
    u16 sampleHistory2;
};

namespace detail {

struct AdpcmLoopParam {
    u16 loopPredScale;
    u16 loop_History1;
    u16 loop_History2;
};

struct WaveInfo {
    struct ChannelParam {
        const void* dataAddr;
        AdpcmParam adpcmParam;
        AdpcmLoopParam adpcmLoopParam;
    };
    SampleFormat sampleFormat;
    bool loopFlag;
    int numChannels;
    int sampleRate;
    ul loopStart;
    ul loopEnd;
    ChannelParam channelParam[2];
};

struct VoiceOutParam {
    float volume;
    float pitch;
    float pan;
    float surroundPan;
    float fxSend;
    float lpf;
}; //0x18

}//namespace detail

}//namespace snd
}//namespace nw4r
#endif

