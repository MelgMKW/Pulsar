#ifndef _AI_
#define _AI_
#include <kamek.hpp>

/*
Contributors:
-Melg
*/

namespace AI {
class Base;

class Actions {
    //Actions(); inlined, sets the ptmfs to 0,0,0 and the subject to nullptr
    virtual ~Actions(); //80721c54 vtable 808cbc30
    virtual void OnStart(); //0xc 8074afec
    virtual void Update(); //0x10 8074b034
    virtual void OnEnd(); //0x14 8074b064

    Base* subject;
    Ptmf_0A<Base, void> actionStartPtmf; //0x8 
    Ptmf_0A<Base, void> updatePtmf; //0x14     
    Ptmf_0A<Base, void> actionEndPtmf; //0x20  
}; //0x2c

class Base {
    Base(); //8074ae2c
    bool SetInitialActions(); //8074afb4 uses the default action contained
    bool HasSameActions(Actions* actions); //8074afcc returns curActions == actions
    bool SetNextActions(Actions* actions); //8074afe0
    Actions* curActions; //0x0
    Actions* nextActions; //0x4
    Actions defaultActions; //0x8 ptmfs values: virtual func 0x10/0x34 | values virtual func 0x14 / 0x34 | virtual invalid
    virtual ~Base(); //offset 0x34 80721c14 vtable 808cbc18
    virtual void UpdateActions(); //0xc 8074af38
    virtual void OnStartDefaultAction(); //0x10 807255ac
    virtual void UpdateDefaultAction(); //0x14 807255a8
}; //0x38

}//namespace AI

#endif