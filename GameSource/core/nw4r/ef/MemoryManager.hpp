#ifndef _NW4R_EF_MEMORYMANAGER_
#define _NW4R_EF_MEMORYMANAGER_
#include <types.hpp>
#include <core/nw4r/ut/List.hpp>

namespace nw4r {
namespace ef {

class Effect;
class Emitter;
class ParticleManager;
class Particle;

class MemoryManagerBase {
public:
    MemoryManagerBase(); //8022500c used by EGG only hence the addresses
    virtual ~MemoryManagerBase(); //80224bc4 vtable 802a2f08
    virtual void GarbageCollection() = 0; //0xc
    virtual Effect* AllocEffect() = 0; //0x10
    virtual void FreeEffect(void* ptr) = 0; //0x14
    virtual u32 GetNumAllocEffect() const = 0; //0x18
    virtual u32 GetNumActiveEffect() const = 0; //0x1c
    virtual u32 GetNumFreeEffect() const = 0; //0x20
    virtual Emitter* AllocEmitter() = 0; //0x24
    virtual void FreeEmitter(void* ptr) = 0; //0x28
    virtual u32 GetNumAllocEmitter() const = 0; //0x2c
    virtual u32 GetNumActiveEmitter() const = 0; //0x30
    virtual u32 GetNumFreeEmitter() const = 0; //0x34
    virtual ParticleManager* AllocParticleManager() = 0; //0x38
    virtual void FreeParticleManager(void* ptr) = 0; //0x3c
    virtual u32 GetNumAllocParticleManager() const = 0; //0x40
    virtual u32 GetNumActiveParticleManager() const = 0; //0x44
    virtual u32 GetNumFreeParticleManager() const = 0; //0x48
    virtual Particle* AllocParticle() = 0; //0x4c
    virtual void FreeParticle(void* ptr) = 0; //0x50
    virtual u32 GetNumAllocParticle() const = 0; //0x54
    virtual u32 GetNumActiveParticle() const = 0; //0x58
    virtual u32 GetNumFreeParticle() const = 0; //0x5c
    virtual void* AllocHeap(u32 size) = 0; //0x60
    virtual void FreeHeap(void* ptr) = 0; //0x64
};

template<class T>
class MemoryManagerTmp {
    MemoryManagerTmp(int count, T* block);
    virtual void AssignObjectID(void* obj);

    T* block;
    ut::List freeList;
    ut::List usedList;
    int size;

};


class MemoryManager : public MemoryManagerBase {
public:
    MemoryManager(void* startAddress, u32 size, int maxEffects, int maxEmitters, int maxParticleManagers, int maxParticles); //inlined

    ~MemoryManager() override; //80225314 vtable 802a2e70
    void GarbageCollection() override; //0xc 80225354
    Effect* AllocEffect() override; //0x10 802255d4
    void FreeEffect(void* ptr) override; //0x14 80225668
    u32 GetNumAllocEffect() const override; //0x18 802256b8
    u32 GetNumActiveEffect() const override; //0x1c 802256dc
    u32 GetNumFreeEffect() const override; //0x20 802256f8
    Emitter* AllocEmitter() override; //0x24 80225714
    void FreeEmitter(void* ptr) override; //0x28 802257a8
    u32 GetNumAllocEmitter() const override; //0x2c 802257f8
    u32 GetNumActiveEmitter() const override; //0x30 8022581c
    u32 GetNumFreeEmitter() const override; //0x34 80225838
    ParticleManager* AllocParticleManager() override; //0x38 80225854
    void FreeParticleManager(void* ptr) override; //0x3c 802258e8
    u32 GetNumAllocParticleManager() const override; //0x40 80225938
    u32 GetNumActiveParticleManager() const override; //0x44 8022595c
    u32 GetNumFreeParticleManager() const override; //0x48 80225978
    Particle* AllocParticle() override; //0x4c 80225994
    void FreeParticle(void* ptr) override; //0x50 80225a28
    u32 GetNumAllocParticle() const override; //0x54 80225a78
    u32 GetNumActiveParticle() const override; //0x58 80225a9c
    u32 GetNumFreeParticle() const override; //0x5c 80225ab8
    void* AllocHeap(u32 size) override; //0x60 80224ea4
    void FreeHeap(void* ptr) override; //0x64 80225ad4

    int maxEffects;
    int maxEffects2;
    MemoryManagerTmp<Effect>* effectMemMgr;

    int maxEmitters;
    int maxEmitters2;
    MemoryManagerTmp<Emitter>* emitterMemMgr;

    int maxParticleManagers;
    int maxParticleManagers2;
    MemoryManagerTmp<ParticleManager>* particlesMgrMemMgr;

    int maxParticles;
    int maxParticles2;
    MemoryManagerTmp<Particle>* particlesMemMgr;

}; //0x34

}//namespace ef
}//namespace nw4r
#endif