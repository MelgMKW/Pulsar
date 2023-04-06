#ifndef _NW4R_SNDWAVEPLAYER_
#define _NW4R_SNDWAVEPLAYER_
#include <types.hpp>

#include <core/nw4r/snd/BasicPlayer.hpp>


namespace nw4r {
namespace snd {
namespace detail {
class WsdPlayer : public BasicPlayer {
    WsdPlayer(); //800add80
    ~WsdPlayer(); //800ad510 vtable 80274bb8
    bool Start() override; //800ae040
    void Stop() override; //800ae0b0
    void Pause(bool flag) override; //800ae1e0
    bool IsActive() const override; //800aee50
    bool IsStarted() const override; //800aee30
    bool IsPause() const override; //800aee10
};
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif