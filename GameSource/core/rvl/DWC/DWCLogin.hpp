#ifndef _DWCLOGIN_ //to split into multiple files ultimately
#define _DWCLOGIN_

#include <types.hpp>
#include <core/rvl/DWC/DWCAccount.hpp>
#include <core/rvl/DWC/DWCError.hpp>
#include <core/rvl/os/OS.hpp>

//Credit Seeky

namespace DWC { //this is C, but don't care

enum LoginState {
    DWC_LOGIN_STATE_INIT,         //Initial state
    DWC_LOGIN_STATE_REMOTE_AUTH,      //Currently performing remote authentication
    DWC_LOGIN_STATE_CONNECTING,       //Connecting to GP server
    DWC_LOGIN_STATE_GPGETINFO,        //When getting lastname upon login to GP
    DWC_LOGIN_STATE_GPSETINFO,        //lastname setting upon the first login to GP
    DWC_LOGIN_STATE_CONNECTED,        //Connected status
    DWC_LOGIN_STATE_NUM
};

//Login complete callback
typedef void (*LoginCallback)(Error error, int profileID, void* param);

struct LoginControl {
    static LoginControl* sInstance; //803862E8
    GP::Connection** gpConnection;
    LoginState state; //0x4
    int  gameID; //gamespy
    u32  gamecode; //nintendo
    const u16* playerName; //0x10
    LoginCallback callback; //0x14
    void* param; //0x18

    AccUserData* userdata; //0x1c
    u8 unknown_0x20[0x8];
    //void* bmwork; //0x20
    //void* http; //0x24
    OS::Time startTime; //0x28
    u32 connectFlag; //0x30
    u8 timeAlignmentPadding[4];
    OS::Time connectTime; //0x38
    AccLoginId tempLoginId; //0x40
    char authToken[256];  //0x4c Token for authentication
    char partnerChallenge[256];  //0x14c Challenge value for authentication
    char username[21]; //0x24c
    u8 padding[3];
}; //0x268

void iLoginInit(LoginControl* control, AccUserData* userdata, GP::Connection** gpConnection, int productID, u32 gamecode, const u16* playerName, LoginCallback callback, void* param); //800cff58
void iLoginAsync(void); //800d00ac
AccUserData* iGetUserData(); //800d0274
}//namespace DWC


#endif