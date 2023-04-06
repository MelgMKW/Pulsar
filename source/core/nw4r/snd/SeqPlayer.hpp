#ifndef _NW4R_SNDSEQPLAYER_
#define _NW4R_SNDSEQPLAYER_
#include <core/nw4r/snd/BasicPlayer.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class SeqPlayer : BasicPlayer {
    SeqPlayer(); //80098db0
    ~SeqPlayer() override; //80098ef0
    bool Start() override; //800994c0
    void Stop() override; //80099530
    void Pause(bool flag) override; //80099680
    bool IsActive() const override; //80096290
    bool IsStarted() const override; //80096280
    bool IsPause() const override; //80096270
    void SetLocalVariable(int varIdx, s16 var); //80099800
};
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif