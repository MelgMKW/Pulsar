#include <kamek.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/RKNet/Select.hpp>
#include <MarioKartWii/System/random.hpp>
#include <MarioKartWii/Archive/ArchiveRoot.hpp>
#include <SlotExpansion/Network/PulSELECT.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <PulsarSystem.hpp>
#include <Info.hpp>


namespace Pulsar {
namespace Network {


void BeforeSELECTSend(RKNet::PacketHolder* packetHolder, CustomSELECTPacket* src, u32 len) {
    if(CupsConfig::IsRegsSituation()) {
        CustomSELECTPacket copy = *src;
        RKNet::SELECTPacket* normalPacket = reinterpret_cast<RKNet::SELECTPacket*>(&copy);
        normalPacket->playersData[0].courseVote = (u8)CupsConfig::ConvertTrack_PulsarIdToRealId(static_cast<PulsarId>(src->pulSELPlayerData[0].pulCourseVote));
        normalPacket->playersData[1].courseVote = (u8)CupsConfig::ConvertTrack_PulsarIdToRealId(static_cast<PulsarId>(src->pulSELPlayerData[1].pulCourseVote));
        normalPacket->winningCourse = CupsConfig::ConvertTrack_PulsarIdToRealId(static_cast<PulsarId>(src->pulWinningCourse));
        normalPacket->playersData[0].prevRaceRank = src->pulSELPlayerData[0].prevRaceRank;
        normalPacket->playersData[1].prevRaceRank = src->pulSELPlayerData[1].prevRaceRank;
        normalPacket->phase = src->phase;
        normalPacket->engineClass = src->engineClass;
        src = reinterpret_cast<CustomSELECTPacket*>(&copy);
    }
    else src->pulSELPlayerData[1].starRank += 0x80; //set leftmost bit to specify PULPacket
    packetHolder->Copy(src, len);
}
kmCall(0x80661040, BeforeSELECTSend);

static void AfterSELECTReception(CustomSELECTPacket* dest, CustomSELECTPacket* src, u32 packetSize) {
    if(CupsConfig::IsRegsSituation() || (src->pulSELPlayerData[1].starRank & 0x80 == 0)) {
        RKNet::SELECTPacket* normalPacket = reinterpret_cast<RKNet::SELECTPacket*>(src);
        const u8 courseVoteHud0 = CupsConfig::ConvertTrack_RealIdToPulsarId(static_cast<CourseId>(normalPacket->playersData[0].courseVote));
        const u8 courseVoteHud1 = CupsConfig::ConvertTrack_RealIdToPulsarId(static_cast<CourseId>(normalPacket->playersData[1].courseVote));
        const u8 winningId = CupsConfig::ConvertTrack_RealIdToPulsarId(static_cast<CourseId>(normalPacket->winningCourse));
        const u8 prevRaceRankHud0 = normalPacket->playersData[0].prevRaceRank;
        const u8 prevRaceRankHud1 = normalPacket->playersData[1].prevRaceRank;
        const u8 phase = normalPacket->phase;
        const u8 engineClass = normalPacket->engineClass;
        src->pulSELPlayerData[0].pulCourseVote = courseVoteHud0;
        src->pulSELPlayerData[1].pulCourseVote = courseVoteHud1;
        src->pulSELPlayerData[0].prevRaceRank = prevRaceRankHud0;
        src->pulSELPlayerData[1].prevRaceRank = prevRaceRankHud1;
        src->pulWinningCourse = winningId;
        src->phase = phase;
        src->engineClass = engineClass;
    }
    else src->pulSELPlayerData[1].starRank -= 0x80;
    memcpy(dest, src, sizeof(CustomSELECTPacket));
}
kmCall(0x80661130, AfterSELECTReception);

static u8 GetEngineClass(const CustomSELECTHandler& select) {
    if(select.toSendPacket.phase != 0) return select.toSendPacket.engineClass;
    return 0;
}
kmBranch(0x8066048c, GetEngineClass);

static u16 GetWinningCourse(const CustomSELECTHandler& select) {
    if(select.toSendPacket.phase == 2) return select.toSendPacket.pulWinningCourse;
    else return 0xFF;
}
kmBranch(0x80660450, GetWinningCourse);

static bool IsTrackDecided(CustomSELECTHandler* select) {
    return select->toSendPacket.pulWinningCourse != 0xFF;
}
kmBranch(0x80660d40, IsTrackDecided);


PulsarId FixRandom(Random& random) {
    return CupsConfig::sInstance->RandomizeTrack(&random);
}
kmCall(0x80661f34, FixRandom);

static void DecideTrack(CustomSELECTHandler* select) {
    Random random;
    System* system = System::sInstance;
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    const RKNet::Controller* controller = RKNet::Controller::sInstance;
    const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
    if(select->mode == RKNet::ONLINEMODE_PUBLIC_VS && !CupsConfig::IsRegsSituation()) {

        const u32 availableAids = sub.availableAids;
        u8 aids[12];
        u8 newVotesAids[12];
        int playerCount = 0;
        int newVoters = 0;
        for(u8 aid = 0; aid < 12; aid++) {
            if((1 << aid & availableAids) == 0) continue;
            aids[playerCount] = aid;
            ++playerCount;
            bool isRepeatVote = false;
            const PulsarId aidVote = static_cast<PulsarId>(aid == sub.localAid ? select->toSendPacket.pulSELPlayerData[0].pulCourseVote : select->receivedPackets[aid].pulSELPlayerData[0].pulCourseVote);
            for(int i = 0; i < Info::GetTrackBlocking(); ++i) {
                if(system->lastTracks[i] == aidVote) {
                    isRepeatVote = true;
                }
            }
            if(!isRepeatVote) {
                newVotesAids[newVoters] = aid;
                ++newVoters;
            }
        }
        u8 winner;
        if(newVoters > 0) winner = newVotesAids[random.NextLimited(newVoters)];
        else winner = aids[random.NextLimited(playerCount)];
        u16 vote = static_cast<PulsarId>(winner == sub.localAid ? select->toSendPacket.pulSELPlayerData[0].pulCourseVote : select->receivedPackets[winner].pulSELPlayerData[0].pulCourseVote);
        if(vote == 0xFF) vote = cupsConfig->RandomizeTrack(&random);
        select->toSendPacket.pulWinningCourse = vote;
        select->toSendPacket.winningVoterAid = winner;
        system->lastTracks[system->curBlockingArrayIdx] = static_cast<PulsarId>(vote);
        system->curBlockingArrayIdx = (system->curBlockingArrayIdx + 1) % Info::GetTrackBlocking();
    }
    else if(select->mode == RKNet::ONLINEMODE_PRIVATE_VS && Info::IsHAW(true)) {
        const u8 hostAid = controller->subs[controller->currentSub].hostAid;
        select->toSendPacket.winningVoterAid = hostAid;
        u16 hostVote = select->toSendPacket.pulSELPlayerData[0].pulCourseVote;
        if(hostVote == 0xFF) hostVote = cupsConfig->RandomizeTrack(&random);
        select->toSendPacket.pulWinningCourse = hostVote;
    }
    else reinterpret_cast<RKNet::SELECTHandler*>(select)->DecideTrack();
}
kmCall(0x80661490, DecideTrack);

//Patches GetWinningCOURSE call so that non-hosts prepare the correct track
CourseId SetCorrectSlot(CustomSELECTHandler* select) {
    CourseId id = reinterpret_cast<RKNet::SELECTHandler*>(select)->GetWinningCourse();
    if(select->toSendPacket.engineClass != 0) id = CupsConfig::sInstance->GetCorrectTrackSlot();
    return id;
}
kmCall(0x80650ea8, SetCorrectSlot);

static void SetCorrectTrack(ArchiveRoot* root, PulsarId winningCourse) {
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    //System* system = System::sInstance; ONLY STORE IF NON HOST
    //system->lastTracks[system->curBlockingArrayIdx] = winningCourse;
    //system->curBlockingArrayIdx = (system->curBlockingArrayIdx + 1) % Info::GetTrackBlocking();
    cupsConfig->winningCourse = winningCourse;
    root->RequestLoadCourseAsync(static_cast<CourseId>(winningCourse));
}
kmCall(0x80644414, SetCorrectTrack);

//Swap of rank and courseVote
//CourseVote
//Get
//GetCourseVote
kmWrite32(0x8066059c, 0xA0630018);
kmWrite32(0x806605a0, 0x60000000); //nop extsb
kmWrite32(0x806605b8, 0xA0630050);
kmWrite32(0x806605bc, 0x60000000); //nop extsb
//EveryoneHasVoted
kmWrite32(0x80660de0, 0xA0030018);
//PrepareAndExportPacket
kmWrite32(0x8066141c, 0xA01C0018);
//ProcessNewPacketVoting
kmWrite32(0x80661810, 0xA0180018);
kmWrite32(0x806618e4, 0xA01C0050);
//Decide Track
kmWrite32(0x80661e90, 0xA01F0018); //extsb -> lhz
kmWrite32(0x80661ef0, 0xA0030050); //extsb -> lhz

//Set
//InitPackets
kmWrite32(0x80660004, 0xB3540018);
kmWrite32(0x80660140, 0xB3730050);
//SetPlayerData
kmWrite32(0x80660760, 0xB0C30018);
//ResetSendPacket
kmWrite32(0x80660908, 0xB3B80018);

//Fixes
kmWrite32(0x806440c0, 0x2c030100); //if id >= 0x100 or id <= 31 -> correct courseId
kmWrite32(0x806440c8, 0x40a00020);
kmWrite32(0x8064411c, 0x2c0300FF); //cmpwi 0xFFFF -> 0xFF for battle
kmWrite32(0x80644150, 0x386000ff); //li r3, 0xFF for battle
kmWrite32(0x80644154, 0x2c0300FF); //cmpwi 0xFFFF -> 0xFF for battle
kmWrite32(0x80644338, 0x2C0300FF); //cmpwi 0xFFFF -> 0xFF
kmWrite32(0x8064433c, 0x418200dc);

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
//EveryoneHasAccurateAidPidMap
kmWrite32(0x80660e54, 0xA003003C); //extsb -> lhz
kmWrite32(0x80660e58, 0x2c0000ff); //cmpwi 0xFFFF -> 0xFF
//PrepareAndExportPacket
kmWrite32(0x80661480, 0xA01C003C); //extsb -> lhz
kmWrite32(0x80661484, 0x2c0000ff); //cmpwi 0xFFFF -> 0xFF
//ProcessNewPacketVoting
kmWrite32(0x80661648, 0xa078003c); //extsb -> lhz
kmWrite32(0x8066164c, 0x2c0300ff); //cmpwi 0xFFFF -> 0xFF
kmWrite32(0x80661658, 0xA01C0074); //extsb -> lhz
kmWrite32(0x80661754, 0xA018003C); //extsb -> lhz
kmWrite32(0x80661758, 0x2c0000ff); //cmpwi 0xFFFF -> 0xFF
kmWrite32(0x8066184c, 0xA0DC0074); //extsb -> lhz
kmWrite32(0x80661854, 0x2c0600ff); //cmpwi 0xFFFF -> 0xF
//DecideTrack
kmWrite32(0x80661f0c, 0xA01F003C); //extsb -> lhz
kmWrite32(0x80661f10, 0x2c0000ff); //cmpwi 0xFFFF -> 0xFF

//Store
//InitPackets
kmWrite32(0x80660018, 0x386000ff);
kmWrite32(0x80660020, 0xB07F003C);
kmWrite32(0x80660150, 0xB3D50074);

//ResetPacket
kmWrite32(0x80660b48, 0xB3D90010);
kmWrite32(0x80660b5c, 0x388000ff);
kmWrite32(0x80660b64, 0xB0980034);

//ResetSendPacket
kmWrite32(0x80660924, 0xB07F003C);
//ProcessNewPacketVoting
kmWrite32(0x80661878, 0xB0D8003C);
//DecideTrack
kmWrite32(0x80661e94, 0xB01F003C);
kmWrite32(0x80661ef4, 0xB01F003C);
kmWrite32(0x80661f94, 0xB3DF003C);
kmWrite32(0x8066200c, 0xB01F003C);

//Merging
asmFunc GetPhase_3D_r0_r24() {
    ASM(
        nofralloc;
    lbz r0, 0x3D + 2 (r24);
    rlwinm r0, r0, 28, 28, 31;
    blr;
    )
}
kmCall(0x80661578, GetPhase_3D_r0_r24);
kmCall(0x806617b8, GetPhase_3D_r0_r24);

asmFunc GetPhase_75_r0_r28() {
    ASM(
        nofralloc;
    lbz r0, 0x75 + 2 (r28);
    rlwinm r0, r0, 28, 28, 31;
    blr;
    )
}
//kmCall(0x806617e8, GetPhase_75_r0_r28);
kmCall(0x80661880, GetPhase_75_r0_r28);

asmFunc StorePhase_3D_r30_r24() {
    ASM(
        nofralloc;
    lbz r12, 0x3D + 2 (r24);
    rlwimi r12, r30, 4, 24, 27;
    stb r12, 0x3D + 2 (r24);
    blr;
    )
}
kmCall(0x8066163c, StorePhase_3D_r30_r24);
//kmCall(0x806617f4, StorePhase_3D_r30_r24);

asmFunc StorePhase_3D_r31_r24() {
    ASM(
        nofralloc;
    lbz r12, 0x3D + 2 (r24);
    rlwimi r12, r31, 4, 24, 27;
    stb r12, 0x3D + 2 (r24);
    blr;
    )
}
kmCall(0x806617a8, StorePhase_3D_r31_r24);
kmCall(0x8066188c, StorePhase_3D_r31_r24);
kmCall(0x80661908, StorePhase_3D_r31_r24);

GetPhase(0x80660434, 0x3d, 0, 3);
GetPhase(0x80660470, 0x3D, 0, 3);
GetPhase(0x806604a8, 0x3D, 0, 3);
GetPhase(0x80660654, 0x3D, 0, 3);
GetPhase(0x80660710, 0x3D, 0, 3);


kmWrite32(0x8066003c, 0x60000000); //nop because it's already being init to 0 via the engine class
//StorePhase(0x8066003c, 0x3D, 27, 31);
kmWrite32(0x80660168, 0x60000000); //nop because it's already being init to 0 via the engine class
//StorePhase(0x80660168, 0x75, 28, 21);

//StorePhase(0x8066093c, 0x3D, 28, 31);   //inlined funcs
//StorePhase(0x80660b70, 0x35, 3, 24);    //inlined funcs

asmFunc GetEngine_3D_r0_r28() {
    ASM(
        nofralloc;
    lbz r0, 0x77 (r28);
    rlwinm r0, r0, 0, 28, 31;
    blr;
    )
}
kmCall(0x806615bc, GetEngine_3D_r0_r28);
//kmCall(0x806617e0, GetEngine_3D_r0_r28);

GetEngine(0x806615b8, 0x3f, 3, 24);


//StoreEngine(0x80660040, 0x3F, 27, 31); //uneeded, this is an init to 0
//StoreEngine(0x80660170, 0x77, 28, 21); //uneeded, this is an init to 0
//StoreEngine(0x80660940, 0x3f, 28, 31); //inlined   
//StoreEngine(0x80660b74, 0x37, 3, 24);  //inlined  
//StoreEngine(0x806617e4, 0x3f, 0, 24);
StoreEngine(0x80661cb8, 0x3f, 28, 29);

asmFunc CheckEngineClass() { //copies the engineclass part of the engine/phase bitfield, then checks if phase of host == 0, and if it isn't, changes own phase to r30 (1)
    //r24 == rkNetSelectHandler, r28 == receivedPackets[loopIdx] - 0x40
    ASM(
        nofralloc;
    lbz r0, 0x77 (r28);
    lbz r12, 0x3F (r24);
    rlwimi r12, r0, 0, 28, 31; //r12.engineClass = r0.engineClass
    rlwinm.r0, r0, 28, 28, 31;
    beq + end;
    rlwimi r12, r30, 4, 24, 27; //r12.phase = r30
end:
    stb r12, 0x3F (r24);
    li r0, 0;
    blr;
    )
}
kmCall(0x806617e8, CheckEngineClass);

}//namespace Network
}//namespace Pulsar