#ifndef _VOLCANOROCK1_
#define _VOLCANOROCK1_
#include <kamek.hpp>
#include <MarioKartWii/Objects/KCL/ExternalKCL/ObjectExternKCL.hpp>

namespace Objects {
class VolcanoRock1 : public ObjectExternKCL { //ObjectNum 0x1f7 = 503
    explicit VolcanoRock1(const KMP::Holder<GOBJ>& gobjHolder); //8081a198
    ~VolcanoRock1() override; //8081a690 vtable 808d6868
    void Update() override; //0x14 8081a370
    u32 GetPropertiesBitfield() override; //0x2c 8081a688
    const char* GetSubFileName() const override; //0x38 8081a668
    const Mtx34& GetTransformationMatrix(u32 framesOffset)override; //0x12c 8081a60c
    float GetPeriod() const override; //0x134 8081a5d0


    Vec3 CalcTranslation(u32 timeInFrames); //8081a414

    Vec3 position2; //0x104
    Vec3 transMtxRow0; //0x110
    Vec3 scale2; //0x11c
    u16 offsetZAxis; //0x128 setting4
    u16 zPeriod; //0x12a setting2
    u16 yPeriod; //0x12c setting5
    u16 zCosAmplitude; //0x12e setting3
    u16 yCosAmplitude; //0x130 setting6
    u8 padding4[2];
    float zFrequency; //0x134 2pi / period
    float yFrequency; //0x138 2pi / period
    bool usesModel1; //0x13c setting0 converted to a bool
    u8 padding5[3];

    Mtx34 transMtx2; //0x140

}; //0x170

}//namespace Objects
#endif