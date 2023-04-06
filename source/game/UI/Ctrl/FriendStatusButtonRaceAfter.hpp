#ifndef _FriendStatusButtonRaceAfter_
#define _FriendStatusButtonRaceAfter_
#include <kamek.hpp>
#include <game/UI/Ctrl/PushButton.hpp>

/*
Contributors:
-stebler, kHacker35000vr, Melg
*/

//_sinit_ at
class FriendStatusButtonRaceAfter : public PushButton {
public:
    FriendStatusButtonRaceAfter(); //8064db68
    ~FriendStatusButtonRaceAfter() override; //8064dba4 vtable 808c0350
    void InitSelf() override; //0x18 8064dd38
    void OnUpdate() override; //0x1c 8064dd3c
    int GetRuntimeTypeInfo() const override; //0x28 8064fb28
    const char *GetClassName() const override; //0x2c 8064db5c

    void Load(); //8064dbfc
};//Total Size 0x254
size_assert(FriendStatusButtonRaceAfter, 0x254);


#endif