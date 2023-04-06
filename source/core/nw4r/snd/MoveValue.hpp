#ifndef _NW4R_SNDMOVEVALUE_
#define _NW4R_SNDMOVEVALUE_
#include <types.hpp>


template< typename ValueType, typename CountType >
class MoveValue {
    ValueType mOrigin;
    ValueType mTarget;
    CountType mFrame;
    CountType mCounter;
}; //0x10

#endif