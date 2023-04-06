#include <kamek.hpp>
#include <game/Network/RKNetController.hpp>
#include <game/Network/RKNetSelect.hpp>
#include <game/Network/RKNetPlayerInfo.hpp>
#include <game/System/random.hpp>
#include <Pulsar.hpp>
#include <Settings/PlayerData.hpp>



//Implements Host Always Wins, TrackBlocking (16) and fixes random







//Fixes for spectating
void CorrectRH1(PacketHolder *packetHolder, RACEHEADER1Packet *rh1Packet, u32 len) {
    Pulsar *pulsar = Pulsar::sInstance;
    rh1Packet->trackId = (u8)pulsar->winningCourse;
    packetHolder->Copy(rh1Packet, len);
}
kmCall(0x80655458, CorrectRH1);
kmCall(0x806550e4, CorrectRH1);

CourseId ReturnCorrectId(RKNetRH1Handler *rh1Handler) {
    Pulsar *pulsar = Pulsar::sInstance;
    for (int i = 0; i < 12; i++) {
        RH1Data *curRH1 = &rh1Handler->rh1Data[i];
        if (curRH1->trackId != 0x42 && curRH1->trackId != 0x43 && curRH1->trackId != 0xff && curRH1->timer != 0) {
            pulsar->winningCourse = curRH1->trackId;
            return pulsar->GetCorrectTrackSlot();
        }
    }
    return (CourseId)-1;
}
kmBranch(0x80664560, ReturnCorrectId);
kmWrite32(0x80663f2c, 0x280500fe);
kmWrite32(0x80663f54, 0x280500fe);
kmWrite32(0x80663f80, 0x280500fe);
kmWrite32(0x80663fa8, 0x280500fe);
kmWrite32(0x80663fd4, 0x280500fe);
kmWrite32(0x80663ffc, 0x280500fe);
kmWrite32(0x80664028, 0x280500fe);
kmWrite32(0x80664050, 0x280500fe);
kmWrite32(0x80664250, 0x280500fe);
kmWrite32(0x80664278, 0x280500fe);
kmWrite32(0x806642a4, 0x280500fe);
kmWrite32(0x806642cc, 0x280500fe);
kmWrite32(0x806642f8, 0x280500fe);
kmWrite32(0x80664320, 0x280500fe);
kmWrite32(0x8066434c, 0x280500fe);
kmWrite32(0x80664374, 0x280500fe);

kmWrite32(0x80664b50, 0x280400fe);
kmWrite32(0x80664b88, 0x280400fe);
kmWrite32(0x80664bc0, 0x280400fe);
kmWrite32(0x80664bf8, 0x280400fe);


//Bunch of patches related to "usual" IDs not going over 0x43
kmWrite32(0x80644338, 0x2C03FFFF);
kmWrite32(0x8064433c, 0x418200dc);
kmWrite32(0x806440cc, 0x2C0300FF);
kmWrite32(0x806440d4, 0x41820008);
kmWrite32(0x80660460, 0x60000000);


