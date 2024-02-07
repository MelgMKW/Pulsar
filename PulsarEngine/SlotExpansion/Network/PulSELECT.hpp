#include <kamek.hpp>
#include <MarioKartWii/RKNet/Select.hpp>

namespace Pulsar {
namespace Network {

struct PlayerData { //+0x18 to all offsets
    u16 pulCourseVote; //0x0 swapped with rank
    u16 sumPoints; //0x2
    u8 character; //0x4
    u8 kart; //0x5
    u8 prevRaceRank; //0x6 swapped with coursevote
    u8 starRank; //0x8 1st bit of 2nd p is also used to specify customPacket
}; //total size 0x8
size_assert(PlayerData, 0x8);


struct CustomSELECTPacket {
    u64 timeSender;
    u64 timeReceived;
    PlayerData pulSELPlayerData[2]; //0x10
    u32 selectId; //0x20
    u8 battleType; //0x24
    u32 teams : 24; //0x25 idk how to do an array of 2 bits variables
    u8 playerIdToAid[12]; //0x28
    u16 pulWinningCourse; //0x34
    u8 winningVoterAid; //0x36
    u8 phase : 4; //0x37 0 prepare, 1 wait, 2 lottery merged with voterAid
    u8 engineClass : 4; //0x37 
}; //total size 0x38
size_assert(CustomSELECTPacket, 0x38);


class CustomSELECTHandler { //Exists just for functions purposes
public:
    static CustomSELECTHandler* sInstance; //0x809c2100   
    RKNet::OnlineMode mode; //from page 0x90 OnInit SectionId Switch
    u32 unknown_0x4;
    CustomSELECTPacket toSendPacket; //0x8
    CustomSELECTPacket receivedPackets[12]; //0x40
    u8 lastSentToAid; //0x2e0
    u8 unknown_0x2e4[7];
    u64 lastSentTime; //0x2e8
    u64 lastReceivedTimes[12]; //0x2f0
    u64 unknown_0x350[12]; //0x350
    u32 unknown_0x3b0[12]; //0x3b0
    u32 hasNewSELECT; //0x3e0 bitflag
    u32 hasNewRACEHEADER_1; //0x3e4 bitflag
    u32 unknown_aidBitflag; //0x3e8
    u32 unknown_aidBitFlag2; //0x3ec
    u32 hasVoted; //0x3f0
    u8 unknown_0x3F4[4];
}; //total size 0x3F8

}//namespace Network
}//namespace Pulsar




//Merging of phase
#define StorePhase(addr, off, destReg, srcReg) \
asmFunc StorePhase##addr(){ \
    ASM( \
        nofralloc;\
        lbz r12, off + 2 (r##srcReg);\
        rlwimi r12, r##destReg, 4, 24, 27;\
        stb r12, off + 2 (r##srcReg);\
        blr;\
    )};\
kmCall(##addr, StorePhase##addr);

#define StoreEngine(addr, off, destReg, srcReg) \
asmFunc StoreEngine##addr(){ \
    ASM( \
        nofralloc;\
        lbz r12, off (r##srcReg);\
        rlwimi r12, r##destReg, 0, 28, 31;\
        stb r12, off (r##srcReg);\
        blr;\
    )};\
kmCall(##addr, StoreEngine##addr);

#define GetPhase(addr, off, destReg, srcReg) \
asmFunc GetPhase##addr(){ \
    ASM( \
        nofralloc;\
        lbz r##destReg, off + 2 (r##srcReg);\
        rlwinm r##destReg, r##destReg, 28, 28, 31;\
        blr;\
    )};\
kmBranch(##addr, GetPhase##addr);\
kmPatchExitPoint(GetPhase##addr, ##addr+4);

#define GetEngine(addr, off, destReg, srcReg) \
asmFunc GetEngine##addr(){ \
    ASM( \
        nofralloc;\
        lbz r##destReg, off (r##srcReg);\
        rlwinm r##destReg, r##destReg, 0, 28, 31;\
        blr;\
    )};\
kmCall(##addr, GetEngine##addr);