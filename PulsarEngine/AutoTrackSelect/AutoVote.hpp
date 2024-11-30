#ifndef _AUTOVOTE_
#define _AUTOVOTE_

#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Other/SELECTStageMgr.hpp>
#include <UI/UI.hpp>


namespace Pulsar {
namespace UI {
class AutoVote : public Pages::SELECTStageMgr {
public:

    AutoVote();
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