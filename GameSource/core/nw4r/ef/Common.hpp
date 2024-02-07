#ifndef _NW4R_EF_COMMON_
#define _NW4R_EF_COMMON_
#include <types.hpp>
#include <core/nw4r/ef/LinkedObject.hpp>
#include <core/nw4r/ef/DrawInfo.hpp>

namespace nw4r {
namespace ef {

typedef void (*ForeachFunc)(void*, u32);
enum CalcOption {
    CALC_TYPE_NORMAL = 0,
    CALC_TYPE_BILLBOARD = 1,
    CALC_TYPE_EXTENDED = 2
};

enum EvaluateStatus {
    NW4R_EF_ES_WAIT = 0,
    NW4R_EF_ES_DONE,
    NW4R_EF_ES_STOP,
    NW4R_EF_ES_SKIP
};

}//namespace ef
}//namespace nw4r
#endif