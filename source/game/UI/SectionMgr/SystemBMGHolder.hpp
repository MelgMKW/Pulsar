#ifndef _SYSTEMBMGHOLDER_
#define _SYSTEMBMGHOLDER_
#include <kamek.hpp>
#include <game/UI/Text.hpp>

class SystemBMGHolder : public BMGHolder { //Mario Kart wii, "Mario Kart Channel" etc... based on SystemManager game language
    SystemBMGHolder(); //80637998
    ~SystemBMGHolder(); //806379c8
    void Init(); //80637a20
    wchar_t *GetMessage(s32 bmgId); //80637a8c
};

#endif