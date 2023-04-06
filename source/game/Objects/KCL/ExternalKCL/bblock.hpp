#ifndef _BBLOCK_
#define _BBLOCK_
#include <kamek.hpp>
#include <game/Objects/KCL/ExternalKCL/VolcanoPiece.hpp>

namespace Objects {
class bblock : public VolcanoPiece { //0x20d = 525
    explicit bblock(KMP::GOBJHolder *gobjHolder); //80803d40
    ~bblock() override; //80805a0c vtable 808d5150
    void OnStart() override; //0xC 80803f74
    char *GetBRRESName() const override; //0x34 808043c0
    void LoadModels() override; //0x44 80803de8
    void LoadAnimations() override; //0x5c 80804054
    void LoadCollision() override; //0x60 80804108
    void UpdateModelMatrix() override; //0x6c 80803fcc
    void UpdateModelScale() override; //0x78 8080597c

    void Init_eAnm() override; //0x154 80804418
    void SetCollisionType(u32 type) override; //0x158 808043cc type = 3 = enable_b, 4 = disable _b collision, others = enable normal collision        

    ObjectKCLHandler *bblock_b_kclHandler; //0x16c
    ModelDirector *bblock_e; //0x178
}; //0x17c

}//namespace Objects
#endif