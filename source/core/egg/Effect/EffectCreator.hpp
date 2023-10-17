#ifndef _EGG_EFFECT_CREATOR_
#define _EGG_EFFECT_CREATOR_
#include <types.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/nw4r/ef.hpp>

using namespace nw4r;
namespace EGG {

class EffectCreator : public EGG::Disposer {
public:

    EffectCreator(int idx); //80224348
    ~EffectCreator() override; //802243b4 vtable 802a2e50
    virtual void StopAllEffect(); //8022443c
    virtual void CalcAll(); //802244b4
    virtual void CalcGroup(int groupID); //8022450c
    virtual void Draw(const nw4r::ef::DrawInfo& drawInfo, int additionalGroupID); //80224558
    virtual void CreateEffect(const char* name); //802245ac

    int idx; //0x10
    int groupID; //0x14
}; //total size 0x18
size_assert(EGG::EffectCreator, 0x18);

}//namespace EGG
#endif