
#ifndef _LECODE_MGR_
#define _LECODE_MGR_
#include <kamek.hpp>
#include <Extensions/LECODE/Lex.hpp>
#include <Extensions/LECODE/XPF.hpp>

namespace LECODE {
class Mgr {
public:
    LexMgr lexMgr;
    XPFMgr xpfMgr;
};


}//namespace LECODE
#endif