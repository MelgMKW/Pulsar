#ifndef _NW4R_G3D_ANMOBJ_
#define _NW4R_G3D_ANMOBJ_
#include <types.hpp>
#include <core/nw4r/g3d/g3dObj.hpp>
#include <core/nw4r/g3d/res/ResMdl.hpp>

namespace nw4r {
namespace g3d {


class AnmObj : public G3dObj { //abstract class for animation classes
public:
    virtual void SetFrame(float frame) = 0; //0x1c
    virtual float GetFrame() const = 0; //0x20
    virtual void UpdateFrame() = 0; //0x24
    virtual void SetUpdateRate(float rate) = 0; //0x28 
    virtual float GetUpdateRate() const = 0; //0x2c
    virtual bool Bind(const ResMdl resMdl) = 0; //0x30
    virtual void Release() = 0; //0x34


    void SetAnmFlag(u32 flag, bool set); //80060570
    bool TestAnmFlag(u32 flag) const; //800605a0
    u32 flags;
}; //0x10

class FrameCtrl {
    float frame;
    float updateRate;
    float startFrame;
    float endFrame;
    void *playPolicyFunc;
}; //0x14
}//namespace g3d   
}//namespace nw4r


#endif