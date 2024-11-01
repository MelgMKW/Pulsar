#ifndef _KARTPART_
#define _KARTPART_
#include <kamek.hpp>
#include <MarioKartWii/Kart/KartValues.hpp>
#include <MarioKartWii/Kart/KartLink.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>

namespace Kart {

class Part : public Link {
public:
    Part(const Values& kartValues, u32 r5); //80592848

    virtual ~Part(); //offset 0xc 8056c0cc vtable 808b6450
    virtual void vf_0xC(); //0xC 80592cbc
    virtual void Load(); //0x10 80592b54
    virtual void CreateModelDirectors(BRRESHandle& handle); //0x14 80592920

    virtual bool LoadModel(BRRESHandle& handle); //0x18 80592a28
    virtual void UpdateMatrix(); //0x1c 80592b64
    virtual void vf_0x20(); //0x20 80592db0
    virtual void vf_0x24(); //0x24 8056e46c
    virtual void ApplyStarColors(); //0x28 80592df8
    virtual void vf_0x2c(); //0x2c 80592e5c
    virtual void SetTEVSwapMode(); //0x30 80592ee0
    virtual void UpdateModelDrawPriority(u32 scnObjDrawOptionsIdx); //0x34 80592f4c
    virtual void SetModelScale(const Vec3& scale); //0x38 80592cdc
    virtual void SetModelMtx(const Mtx34& mtx); //0x3c 80592d04
    virtual void ToggleModelVisible(bool insert); //0x40 80592d88 see ModelDirector's ToggleVisible

    //80592920
    void Create2ndModelDirector(BRRESHandle& handle, u32 r5); //80592a30

    Vec3 unknown_0x10;
    Mtx34 transfoMtx; //0x1c
    Mtx34 translationMtx; //0x4c
    ModelDirector* model; //0x7c
    u8 unknown_0x80[8];
    ModelDirector* secondModel; //0x88
    bool isModelLoaded; //0x8c
    u8 padding[3];
}; //Total size 0x90

}//namespace kart

#endif