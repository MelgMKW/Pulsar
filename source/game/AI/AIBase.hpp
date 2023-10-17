#ifndef _AI_
#define _AI_
#include <kamek.hpp>

/*
Contributors:
-Melg
*/

namespace AI {
class Base;

class ActionsBase {
    virtual ~ActionsBase() = 0;
    virtual void OnStart() = 0;
    virtual void Update() = 0;
    virtual void OnEnd() = 0;
};

template<class T = Base>
class Actions {
    //Actions(); inlined, sets the ptmfs to 0,0,0 and the subject to nullptr
    virtual ~Actions(); //80721c54 vtable 808cbc30
    virtual void OnStart(); //0xc 8074afec
    virtual void Update(); //0x10 8074b034
    virtual void OnEnd(); //0x14 8074b064

    T* subject; //0x4
    Ptmf_0A<T, void> actionStartPtmf; //0x8 
    Ptmf_0A<T, void> updatePtmf; //0x14     
    Ptmf_0A<T, void> actionEndPtmf; //0x20  
}; //0x2c

class Base {
    Base(); //8074ae2c
    bool SetInitialActions(); //8074afb4 uses the default action contained
    bool HasSameActions(ActionsBase* actions); //8074afcc returns curActions == actions
    bool SetNextActions(ActionsBase* actions); //8074afe0
    ActionsBase* curActions; //0x0
    ActionsBase* nextActions; //0x4
    Actions<> defaultActions; //0x8 ptmfs values: virtual func 0x10/0x34 | values virtual func 0x14 / 0x34 | virtual invalid
    virtual ~Base(); //offset 0x34 80721c14 vtable 808cbc18
    virtual void UpdateActions(); //0xc 8074af38
    virtual void OnStartDefaultAction(); //0x10 807255ac blr
    virtual void UpdateDefaultAction(); //0x14 807255a8 blr
}; //0x38

//returns (1 + slope%)*(point - fixedPoint) + fixedPoint, ie the function of slope (1 + slope%) such that f(point) = point
//for example used as lakitu flies down from the skies before countdown actually starts
static Vec3 CalcLinearTransfo(const Vec3& fixedPoint, const Vec3& point, float slopePercent); //8071f044

}//namespace AI

#endif