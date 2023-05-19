#ifndef _NW4R_SND_AXMANAGER_
#define _NW4R_SND_AXMANAGER_
#include <types.hpp>
#include <core/nw4r/snd/Channel.hpp>
#include <core/nw4r/snd/Misc.hpp>


namespace nw4r {
namespace snd {
namespace detail {

class AxManager {
public:
    typedef void (*AxCallback)();
    struct CallbackListNode {
        ut::LinkListNode link;
        AxCallback callback;
    };

    static AxManager mInstance; //802d5730


};

}//namespace detail
}//namespace snd
}//namespace nw4r
#endif