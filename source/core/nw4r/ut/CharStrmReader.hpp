#ifndef _NW4R_UT_CHARSTRMREADER_
#define _NW4R_UT_CHARSTRMREADER_
#include <types.hpp>
namespace nw4r {
namespace ut {

class CharStrmReader {
public:
    typedef u16(CharStrmReader:: *ReadNextCharFunc)();
    //ReadNextChar functions
    u16 ReadNextCharUTF8(); //800af420
    u16 ReadNextCharUTF16(); //800af4a0
    u16 ReadNextCharCP1252(); //800af4c0
    u16 ReadNextCharSJIS(); //800af4e0

    const void *charStream;
    const ReadNextCharFunc  readFunction;
};

}//namespace ut
}//namespace nw4r
#endif