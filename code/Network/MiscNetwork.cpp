#include <kamek.hpp>
#include <game/Network/RKNetController.hpp>
#include <game/Network/RKNetSelect.hpp>
#include <game/System/random.hpp>
#include <Settings/PlayerData.hpp>

//No disconnect for being idle (Bully)
kmWrite32(0x80521408, 0x38000000);
kmWrite32(0x8053EF6C, 0x38000000);
kmWrite32(0x8053F0B4, 0x38000000);
kmWrite32(0x8053F124, 0x38000000);

//Overwrites CC rules -> 10% 200, 65% 150, 25% mirror and/or in frooms, overwritten by host setting
void DecideCC(RKNetSELECTHandler *handler) {
    u8 ccSetting = PulsarSettings::GetInstance()->GetSettings()->pages[OPT_HOST_SETTINGS].radioSetting[OPT_RADIO_CC];
    u8 ccClass = 1; //1 200, 2 150, 3 mirror
    if (ccSetting == OPT_RADIO_CC_150) ccClass = 2;
    if (handler->mode == ONLINEMODE_PUBLIC_VS || handler->mode == ONLINEMODE_PUBLIC_BATTLE || ccSetting == OPT_RADIO_CC_NORMAL) {
        Random random;
        u32 result = random.NextLimited(100);
        if (result > 10) ccClass = 2;
        if (result > 75) ccClass = 3;
    }
    handler->toSendPacket.engineClass = ccClass;
}
kmCall(0x80661404, DecideCC);