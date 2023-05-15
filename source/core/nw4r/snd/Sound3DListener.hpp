#ifndef _NW4R_SND3DLISTENER_
#define _NW4R_SND3DLISTENER_
#include <types.hpp>
#include <core/nw4r/math/math.hpp>
namespace nw4r {
namespace snd {

class Sound3DListener {
public:
    Sound3DListener(); //8009d550
    void SetMatrix(const math::MTX34& mtx); //8009d5c0
    void ResetMatrix(); //8009d820
    void SetInteriorSize(float interiorSize); //8009d870
    void SetMaxVolumeDistance(float maxVolumeDistance); //8009d870
    void SetUnitDistance(float unitDistance); //8009d870
    math::MTX34 mat;
    math::VEC3 velocity; //0x30
    float interiorSize; //0x3c
    float maxVolumeDistance; //0x40
    float unitDistance; //0x44
    u32 unknown_0x48;
    bool resetMatrix; //0x4C
    u8 padding[3];
    ut::LinkListNode link;
}; //total size 0x58

}//namespace snd
}//namespace nw4r
#endif