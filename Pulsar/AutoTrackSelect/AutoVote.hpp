#ifndef _AUTOVOTE_
#define _AUTOVOTE_

#include <kamek.hpp>
#include <game/UI/Page/Other/CountDownTimer.hpp>
#include <game/UI/Page/Other/FriendRoom.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/RKNet/RKNetController.hpp>
#include <game/RKNet/Select.hpp>

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