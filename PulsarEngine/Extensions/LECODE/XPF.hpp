#ifndef _LECODE_XPF_
#define _LECODE_XPF_
#include <kamek.hpp>
#include <MarioKartWii/Objects/ObjectsMgr.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>

//Total copy of https://github.com/Gabriela-Orzechowska/LE-CODE-XPF/tree/main all credits goes to Gabriela

namespace LECODE {
enum DEF_OBJ_MODE {
    DEF_OBJ_BITS = 0x0,
    DEF_OBJ_OR = 0x1,
    DEF_OBJ_AND = 0x2,
};

class XPFMgr {
public:
    XPFMgr() : randScenario(0) {}
    static void EvaluateXPFAndCreateObjs(ObjectsMgr* mgr, bool isMii);
private:
    void EvaluateConditions();
    GOBJ* GetDefinitionObject(u16 id);
    bool CalcDefinitionObjectCondition(GOBJ* gobj, bool neg);
    bool CalcPredefinedCondition(u16 value);
    bool CalcConditionBits(u16 val, u8 field);
    s32 randScenario;
};
}//namespace LECODE

#endif