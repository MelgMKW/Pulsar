#ifndef _NW4R_SND3DLISTENER_
#define _NW4R_SND3DLISTENER_
#include <types.hpp>
#include <core/nw4r/math/math.hpp>
namespace nw4r {
namespace snd {

class Sound3DListener {
public:
    Sound3DListener(); //8009d550
    math::MTX34 mat;
    float unknown_0x30[6];
    u32 unknown_0x48;
    u8 unknown_0x4C[4];
    ut::LinkListNode link;
}; //total size 0x58

}//namespace snd
}//namespace nw4r
#endif