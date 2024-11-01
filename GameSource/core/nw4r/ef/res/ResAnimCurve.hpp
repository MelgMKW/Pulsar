#ifndef _NW4R_EF_RESANIMCURVEE_
#define _NW4R_EF_RESANIMCURVEE_
#include <types.hpp>
#include <core/nw4r/ef/res/Resource.hpp>
#include <core/nw4r/ef/res/ResTexture.hpp>

namespace nw4r {
namespace ef {

class ResAnimCurve {
public:
    u8* animCurveData;
    void SetStop(bool b); //8004bcb0 stop animation evaluation

};
}
}
#endif