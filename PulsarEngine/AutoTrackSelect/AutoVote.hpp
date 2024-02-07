#ifndef _AUTOVOTE_
#define _AUTOVOTE_

#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Other/CountDownTimer.hpp>
#include <MarioKartWii/UI/Page/Other/FriendRoom.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/RKNet/Select.hpp>

namespace Pulsar {
namespace UI {
class AutoVote : public Pages::CountDownTimer {
public:
    AutoVote() : readyDuration(0) {}
    void OnInit() override;
    void OnDispose() override;
    void OnActivate() override;
    void BeforeControlUpdate() override;
    void OnResume() override;
    void OnUpdate() override;
private:
    u32 readyDuration;
};
}//namespace UI
}//namespace Pulsar

#endif