#ifndef _NW4R_SNDMOVEVALUE_
#define _NW4R_SNDMOVEVALUE_
#include <types.hpp>


template< typename ValueType, typename CountType >
class MoveValue { //used for fades (volume for ex)
    ValueType initialValue;
    ValueType targetValue;
    CountType frame;
    CountType counter;
}; //ValueType * 2 + CountType * 2

#endif