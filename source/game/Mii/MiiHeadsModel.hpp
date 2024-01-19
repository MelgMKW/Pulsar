#ifndef _MIIHEADSMODEL_
#define _MIIHEADSMODEL_
#include <kamek.hpp>
#include <game/Mii/Mii.hpp>
#include <game/3D/Model/ModelDirector.hpp>

class MiiHeadsModel;

class MiiDriverModel : public ModelDirector {
public:
    void UpdateParams(MiiHeadsModel* headsModel); //807d0b5c
};

class MiiHeadsModel : public ModelDirector {
public:
    MiiHeadsModel(u32 r4, MiiDriverModel* driverModel, MiiId id, Mii* mii, u32 r8); //807dbd80
    MiiHeadsModel(u32 r4, MiiDriverModel* driverModel, MiiId id, u32 miiIdx, u32 r8, u32 r9); //807dbe0c
    MiiHeadsModel(u32 r4, MiiDriverModel* driverModel, MiiId id, Mii* mii, u32 r8, u32 r9); //807dbfbc
    ~MiiHeadsModel() override; //807dc860 vtable  808d2e10
    void Init(u32 r4, u32 r5, u32 r6, u32 r7); //807dc048
    void* InitModel(Mii* mii, MiiDriverModel* driverModel, u32 r6, g3d::ScnMdl::BufferOption option, u32 r8, u32 id); //8055c580
    void UpdateParams(u32 r4, MiiDriverModel* driverModel, u32 r6, Mii* mii); //807dc2c0
    Mii* mii; //0x4c
    MiiDriverModel* driverModel; //0x50
    MiiId id; //0x54
    u8 unknown_0x58[0x70 - 0x58];
}; //total size 0x70
#endif