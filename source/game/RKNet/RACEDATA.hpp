#ifndef _RKNETRACEDATA_
#define _RKNETRACEDATA_
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>



namespace RKNet {

#pragma pack(push, 1)

struct RACEDATAPacket {
    u8 _[0x40];
};
/*
struct RACEDATAPacket {


    s16 speed; //0x11
    float tiltAngle; //0x

    u8 nunchuckXAxis : 4; //0x25
    u8 nunchuckYAxis : 4; //0x26
    u8 tc;
    u8 lakitu;
    u8 oob;
    u8 buttons;


    //flipping values
    u8 MTstart : 1;   //0x28
    u8 shroom : 1;
    u8 blooper_ink : 1;
    u8 megamushroom : 1;
    u8 star : 1;
    u8 twanwan : 1;
    u8 thwomp_hit : 1;
    u8 fire : 1;
    u8 cataquack : 1;
    u8 star_hit : 1;
    u8 fakebox_hit : 1;
    u8 bomb_blue_hit : 1;
    u8 bomb_blue_half : 1;
    u8 goomba_hit : 1;
    u8 collision : 1;
    u8 wheelie_start : 1;
    u8 stunt : 1;
    u8 hop : 1;
    u8 cannon : 1;


    u8 drift : 1;
    u8 already_drifted : 1;
    u8 rank : 1;
};
#pragma pack(pop)
size_assert(RACEDATAPacket, 0x40);
*/

}//namespace RKNet
#endif