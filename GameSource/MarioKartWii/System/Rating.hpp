#ifndef _RATING_
#define _RATING_
#include <kamek.hpp>

class Rating {
public:
    Rating(); //805444d0
    virtual ~Rating(); //8052da10 vtable 808b32a0
    void AddPoints(u16 points); //8052d270

    u16 points;
    u8 padding[2];
}; //0x8
#endif