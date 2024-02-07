#ifndef _NW4R_EF_DRAWORDER_
#define _NW4R_EF_DRAWORDER_
#include <types.hpp>
#include <core/nw4r/ef/DrawInfo.hpp>

namespace nw4r {
namespace ef {

class Effect;
class ParticleManager;

class DrawOrderBase {
public:
    DrawOrderBase();

    virtual void Add(Effect* ef, ParticleManager* pm) = 0;
    virtual void Remove(Effect* ef, ParticleManager* pm) = 0;
    virtual void Draw(Effect* ef, const DrawInfo& drawInfo) = 0;
};


class DrawOrder : public DrawOrderBase {
public:
    virtual void Add(Effect* ef, ParticleManager* pm); //800262b0 vtable 803860e8
    virtual void Remove(Effect* ef, ParticleManager* pm); //80026330
    virtual void Draw(Effect* ef, const DrawInfo& drawInfo); //80026220
};

}//namespace ef
}//namespace nw4r
#endif