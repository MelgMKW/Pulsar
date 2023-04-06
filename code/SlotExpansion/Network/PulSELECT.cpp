#include <kamek.hpp>
#include <game/Network/RKNetController.hpp>
#include <game/Network/RKNetSelect.hpp>
#include <game/Network/RKNetPlayerInfo.hpp>
#include <game/System/random.hpp>
#include <SlotExpansion/Network/PulSELECT.hpp>
#include <Pulsar.hpp>


namespace PulsarSELECT {


//Swap of rank and courseVote
//CourseVote
//Get
kmWrite32(0x8066059c, 0xA0630018);
kmWrite32(0x806605a0, 0x7C630734); //extsh
kmWrite32(0x8066141c, 0xA01C0018);
kmWrite32(0x80661810, 0xA0180018);
kmWrite32(0x80661e8c, 0xA01F0018);
kmWrite32(0x80661e90, 0x7C000734); //extsh
kmWrite32(0x806618e4, 0xA01C0050);
kmWrite32(0x806605b8, 0xA0630050);
kmWrite32(0x806605bc, 0x7C630734); //extsh
kmWrite32(0x80661eec, 0xA0030050);
kmWrite32(0x80661ef0, 0x7C000734); //extsh
//Store
kmWrite32(0x80660004, 0xB3540018);
kmWrite32(0x80660760, 0xB0C30018);
kmWrite32(0x80660908, 0xB3B80018);
kmWrite32(0x80660140, 0xB3730050);

//Rank
//Get
kmWrite32(0x80651374, 0x88030006); //lha -> lbz
//Store
kmWrite32(0x806600b0, 0x9813001E);
kmWrite32(0x806600c0, 0x9B73001E);
kmWrite32(0x806609b0, 0x981F001E);
kmWrite32(0x806609c0, 0x9B9F001E);


//Winning course u8->u16
//Get

kmWrite32(0x8066045c, 0xA063003C);
kmWrite32(0x80661f08, 0xA01F003C);
kmWrite32(0x8066147c, 0xA01C003C);
kmWrite32(0x80661644, 0xA018003C);
kmWrite32(0x80661750, 0xA018003C);
kmWrite32(0x80661654, 0xA01C0074);
kmWrite32(0x80661840, 0xA0DC0074);

//Store
kmWrite32(0x80661878, 0xB0D8003C);
kmWrite32(0x80661e94, 0xB01F003C);
kmWrite32(0x80661ef4, 0xB01F003C);
kmWrite32(0x80660020, 0xB07F003C);
kmWrite32(0x80660924, 0xB07F003C);
kmWrite32(0x80661f94, 0xB3DF003C);
kmWrite32(0x80662008, 0xB01F003C);
kmWrite32(0x80660150, 0xB3D50074);

//Merging
GetPhase(0x80660450, 0x3D, 0, 3);
GetPhase(0x80660470, 0x3D, 0, 3);
GetPhase(0x8066048c, 0x3D, 0, 3);
GetPhase(0x806604a8, 0x3D, 0, 3);
GetPhase(0x80660654, 0x3D, 0, 3);
GetPhase(0x80660710, 0x3D, 0, 3);
GetPhase(0x80661578, 0x3D, 0, 24);
GetPhase(0x806617b8, 0x3D, 0, 24);
GetPhase(0x806617e8, 0x75, 0, 28);
GetPhase(0x80661880, 0x75, 0, 28);

StorePhase(0x8066003c, 0x3D, 27, 31);
StorePhase(0x8066093c, 0x3D, 28, 31);
StorePhase(0x8066163c, 0x3D, 30, 24);
StorePhase(0x806617f4, 0x3D, 30, 24);
StorePhase(0x806617a8, 0x3D, 31, 24);
StorePhase(0x8066188c, 0x3D, 31, 24);
StorePhase(0x80661908, 0x3D, 31, 24);
StorePhase(0x80660168, 0x75, 28, 21);

GetWinningAid(0x80661664, 0x3E, 3, 24);
GetWinningAid(0x80661668, 0x76, 0, 28);
GetWinningAid(0x8066183c, 0x76, 4, 28);


StoreWinningAid(0x80661e20, 0x3E, 4, 31);
StoreWinningAid(0x80661868, 0x3E, 4, 24);
StoreWinningAid(0x8066016c, 0x76, 29, 21);
StoreWinningAid(0x80660954, 0x3E, 0, 31);
StoreWinningAid(0x80660054, 0x3E, 0, 31);

u32 GetWinningVoter(Handler *handler) {
    if (handler->toSendPacket.phase == 2) return handler->toSendPacket.winningVoterAid;
    return 0xFF;
}
kmBranch(0x80660434, GetWinningVoter);

CourseId FixRandom(Random *random) {
    return Pulsar::sInstance->RandomizeTrack(random);
}
kmCall(0x80661f34, FixRandom);

void DecideTrack(Handler *select) {
    Random random;
    Pulsar *pulsar = Pulsar::sInstance;
    RKNetController *controller = RKNetController::sInstance;
    if (select->mode == ONLINEMODE_PUBLIC_VS) {

        u32 availableAids = controller->subs[controller->currentSub].availableAids;
        u8 aids[12];
        u8 newVotesAids[12];
        int playerCount = 0;
        int newVoters = 0;
        for (u8 aid = 0; aid < 12; aid++) {
            if ((1 << aid & availableAids) == 0) continue;
            aids[playerCount] = aid;
            playerCount++;
            bool isRepeat = false;
            Packet *aidPacket = &select->receivedPackets[aid];
            for (int i = 0; i < pulsar->GetTrackBlocking(); i++) if (pulsar->lastTracks[i] == aidPacket->pulSELPlayerData[0].pulCourseVote) {
                isRepeat = true;
            }
            if (!isRepeat) {
                newVotesAids[newVoters] = aid;
                newVoters++;
            }
        }
        u8 winner;
        if (newVoters > 0) winner = newVotesAids[random.NextLimited(newVoters)];
        else winner = aids[random.NextLimited(playerCount)];
        u16 vote = select->receivedPackets[winner].pulSELPlayerData[0].pulCourseVote;
        if (vote == 0xFF) vote = pulsar->RandomizeTrack(&random);
        select->toSendPacket.pulWinningCourse = vote;
        select->toSendPacket.winningVoterAid = winner;
        pulsar->lastTracks[pulsar->curArrayIdx] = vote;
        pulsar->curArrayIdx = (pulsar->curArrayIdx + 1) % 16;
    }
    if (select->mode == ONLINEMODE_PRIVATE_VS && pulsar->hasHAW) {
        u8 hostAid = controller->subs[controller->currentSub].hostAid;
        select->toSendPacket.winningVoterAid = hostAid;
        u16 hostVote = select->toSendPacket.pulSELPlayerData[0].pulCourseVote;
        if (hostVote == 0xFF) hostVote = pulsar->RandomizeTrack(&random);
        select->toSendPacket.pulWinningCourse = hostVote;
    }
    else ((RKNetSELECTHandler *)select)->DecideTrack();
}
kmCall(0x80661490, DecideTrack);

//Patches GetWinningCOURSE call so that non-hosts prepare the correct track
CourseId SetCorrectTrack(Handler *select) {
    CourseId id = ((RKNetSELECTHandler *)select)->GetWinningCourse();
    if (select->toSendPacket.engineClass != 0) {
        Pulsar *pulsar = Pulsar::sInstance;
        pulsar->lastTracks[pulsar->curArrayIdx] = id;
        pulsar->winningCourse = id;
        pulsar->curArrayIdx = (pulsar->curArrayIdx + 1) % 16;
        id = pulsar->GetCorrectTrackSlot();
    }
    return id;
}
kmCall(0x80650ea8, SetCorrectTrack);

}//namespace PulsarSELECT