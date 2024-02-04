#ifndef _EGG_GXRELATED_
#define _EGG_GXRELATED_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/mem/Heap.hpp>

namespace EGG {

class UnknownGX2 {
public:
    UnknownGX2(); //8023e724
    u8 unknown_0x0;
    u8 padding[3];
    virtual ~UnknownGX2(); //8021c330 vtable 802a3f20
}; //0x48

class UnknownGX : public UnknownGX2 {
public:
    UnknownGX(); //8023e748
    ~UnknownGX() override; //8023e86c vtable 802a3f30
    u8 unknown_0x8[2];
    u8 padding2[2];
    u32 unknown_0xC;
    float unknown_0x14[6];
    u8 unknown_0x2c[4];
    void* bloom; //0x30
    void* blur; //0x34
    u32 unknown_0x38;
}; //0x3c

class GraphicsFifo {
public:
    static GraphicsFifo* Create(u32 size, EGG::Heap* heap); //80229540
    static GraphicsFifo* sInstance; //80386E90
    GraphicsFifo(u32 size, EGG::Heap* heap); //80229640
    virtual ~GraphicsFifo(); //802295a8 vtable 802a30b0

    GX::FifoObj* fifoObj; //0x4
    void* rawBuffer;
    u32 bufferSize; //0xC 32-bits aligned
}; //0x10


namespace DrawGX {
struct ZModes {
    bool compare_enable;
    u8 padding[3];
    GX::Compare func;
    bool update_enable;
    u8 padding2[3];
}; //0xC

struct BlendModes {
    GX::BlendMode type;
    GX::BlendFactor src_factor;
    GX::BlendFactor dst_factor;
    GX::LogicOp op;
}; //0x10

extern ZModes zModes; //80257558
/*
false GX_ALWAYS false //0
true  GX_LEQUAL true  //1
true  GX_LEQUAL false //2
true  GX_ALWAYS true  //3
*/
extern BlendModes blendModes; //80257588
/*
GX_BM_BLEND    GX_BL_SRCALPHA     GX_BL_INVSRCALPHA GX_LO_CLEAR //0
GX_BM_BLEND    GX_BL_INVSRCALPHA  GX_BL_SRCALPHA    GX_LO_CLEAR //1
GX_BM_BLEND    GX_BL_ONE          GX_BL_ONE         GX_LO_CLEAR //2
GX_BM_BLEND    GX_BL_SRCALPHA     GX_BL_ONE         GX_LO_CLEAR //3
GX_BM_BLEND    GX_BL_SRCCLR       GX_BL_ONE         GX_LO_CLEAR //4
GX_BM_BLEND    GX_BL_INVSRCCLR    GX_BL_ONE         GX_LO_CLEAR //5
GM_BM_SUBTRACT GX_BL_ONE          GX_BL_ONE         GX_LO_CLEAR //6
GX_BM_BLEND    GX_BL_ZERO         GX_BL_SRCCLR      GX_LO_CLEAR //7
GX_BM_BLEND    GX_BL_ZERO         GX_BL_INVSRCCLR   GX_LO_CLEAR //8
GX_BM_BLEND    GX_BL_ONE          GX_BL_ZERO        GX_LO_CLEAR //9
GX_BM_BLEND    GX_BL_DSTALPHA     GX_BL_INVDSTALPHA GX_LO_CLEAR //a
GX_BM_BLEND    GX_BL_INVDSTALPHA  GX_BL_DSTALPHA    GX_LO_CLEAR //b
GM_BM_NONE     GX_BL_ONE          GX_BL_ONE         GX_LO_CLEAR //c
GM_BM_LOGIC    GX_BL_INVSRCALPHA  GX_BL_INVDSTALPHA GX_LO_AND   //d
*/


void SetZMode(u32 zModesIdx); //8021c0f8
void SetBlendMode(u32 blendModesIdx); //8021c118
void SetupTranslucent(bool cullFrontFaces); //8021c13c will cull back faces otherwise



}//namespace DrawGX

}//namespace EGG
#endif