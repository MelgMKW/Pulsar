#ifndef _GSAVAILABLE_
#define _GSAVAILABLE_
#include <types.hpp>


namespace GS {
enum  IACResult {
    GSIACWaiting,
    GSIACAvailable,
    GSIACUnavailable,
    GSIACTemporarilyUnavailable
};

//start an available check for a particular game
void IStartAvailableCheck(const char* gamename); //800f38a4

//let the available check think, continue to call this while it returns GSIACWaiting
IACResult GSIAvailableCheckThink(); //800f3a20

extern const char availableURLFmt[]; //8027ad58
}//namespace GS


#endif