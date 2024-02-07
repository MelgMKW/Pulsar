#ifndef _EGG_EXPPARTICLEMANAGER_
#define _EGG_EXPPARTICLEMANAGER_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/Math/Vector.hpp>
#include <core/nw4r/ef.hpp>

namespace EGG {

class ExpParticleManager : public nw4r::ef::ParticleManager {
public:

    ExpParticleManager(); //802261f8
    bool Initialize(nw4r::ef::Emitter* parent, nw4r::ef::EmitterResource* resource) override; //0x10 802262a8 vtable 802a2fb0
    void Calc() override; //0x18 80226308
    virtual ~ExpParticleManager(); //0x20 80226250
    virtual void SetLife(u16 life); //0x24 802263dc
    virtual void vf_0x28(Vector2f& vec); //0x28 802263f0
    virtual void vf_0x2c(Vector3f& vec); //0x2c 80226410
    virtual void Reset(); //0x30 80226438 resets vecs

    u32 bitfield; //0xc0
    u16 life; //0xc4
    u8 padding[2];
    Vector2f vec_0xc8; //0xc8
    Vector3f vec_0xd0; //0xd0

}; //total size 0xdc
size_assert(ExpParticleManager, 0x30);
}//namespace EGG
#endif