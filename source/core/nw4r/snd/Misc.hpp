#ifndef _NW4R_SNDMISC_
#define _NW4R_SNDMISC_
#include <types.hpp>


namespace nw4r {
namespace snd {

enum SampleFormat {
    SAMPLE_FORMAT_PCM_S32,
    SAMPLE_FORMAT_PCM_S16,
    SAMPLE_FORMAT_PCM_S8,
    SAMPLE_FORMAT_DSP_ADPCM
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


}//namespace detail

}//namespace snd
}//namespace nw4r
#endif

