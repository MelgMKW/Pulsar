#ifndef _EGG_EFFECT_RESSOURCE_
#define _EGG_EFFECT_RESSOURCE_
#include <types.hpp>
#include <core/nw4r/ef.hpp>
#include <core/nw4r/ut/List.hpp>
#include <core/egg/mem/Disposer.hpp>

using namespace nw4r;
namespace EGG {
class EffectResource : public EGG::Disposer {
public:
    EffectResource(void *breff, void *breft); //80225c98
    ~EffectResource() override; //80225d34 vtable 802a2f70
    virtual void SetResource(void *breff, void *breft); //80225de8
    virtual void ResetResource(); //80225e74
    void Initialize();
    ef::EffectProject *breff; //0x10
    ef::TextureProject *breft;  //0x14
    ut::Link resourceLink; //0x18

}; //total size 0x20
size_assert(EGG::EffectResource, 0x20);
}//namespace EGG
#endif