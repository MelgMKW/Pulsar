#ifndef _AUTOVOTE_
#define _AUTOVOTE_

#include <kamek.hpp>
#include <game/UI/Page/Other/CountDownTimer.hpp>
#include <game/UI/Page/Other/FriendRoom.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/Network/RKNetController.hpp>
#include <game/Network/RKNetSelect.hpp>

namespace PulsarUI {
class AutoVote : public Pages::CountDownTimer {
public:
    void OnInit() override;
    void OnDispose() override;
    void OnActivate() override;
    void BeforeControlUpdate() override;
    void OnResume() override;
    void OnUpdate() override;
};
}//namespace PulsarUI

#endif