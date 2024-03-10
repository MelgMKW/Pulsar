#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <Network/MatchCommand.hpp>
#include <PulsarSystem.hpp>

namespace Pulsar {
namespace Network {

ResvPacket::ResvPacket(const DWC::Reservation& src) {
    memcpy(this, &src, sizeof(DWC::Reservation));
    const System* system = System::sInstance;
    pulInfo.roomKey = Info::GetKey();
    strncpy(pulInfo.modFolderName, system->GetModFolder(), IOS::ipcMaxFileName);
}

asmFunc MoveSize() { //needed to get datasize later
    ASM(
        nofralloc;
    mr r25, r28;
    li r28, 255;
    blr;
    )
}
kmCall(0x800dc3bc, MoveSize);

DWC::MatchCommand Process(DWC::MatchCommand type, const void* data, u32 dataSize) {
    const RKNet::RoomType roomType = RKNet::Controller::sInstance->roomType;
    const bool isCustom = roomType == RKNet::ROOMTYPE_FROOM_NONHOST || roomType == RKNet::ROOMTYPE_FROOM_HOST
        || roomType == RKNet::ROOMTYPE_VS_REGIONAL || roomType == RKNet::ROOMTYPE_JOINING_REGIONAL;

    Pulsar::System* system = Pulsar::System::sInstance;
    system->isCustomDeny = false;

    if(type == DWC::MATCH_COMMAND_RESV_OK && isCustom) {
        const ResvPacket* packet = reinterpret_cast<const ResvPacket*>(data);
        System* system = System::sInstance;
        if(dataSize != (sizeof(ResvPacket) / sizeof(u32)) || packet->pulInfo.roomKey != Info::GetKey()
            || strcmp(packet->pulInfo.modFolderName, system->GetModFolder()) != 0
            || !system->CheckUserInfo(packet->pulInfo.userInfo)) {
            system->isCustomDeny = true;
            if(roomType == RKNet::ROOMTYPE_VS_REGIONAL) system->deniesCount++;
            type = DWC::MATCH_COMMAND_RESV_DENY;
        }
    }
    return type;
}


static int GetSuspendType(int r3, const char* string) {
    DWC::Printf(r3, string);
    int errorType = 0x12000000;
    if(Pulsar::System::sInstance->isCustomDeny) errorType = 0x13000000;
    return errorType;
}
kmCall(0x800dc9e8, GetSuspendType);
kmWrite32(0x800dc9f4, 0x906100d8);

static void HasBeenPulsarDenied(int r3, const char* string) {
    register u32 error;
    asm(mr error, r0);
    bool isCustomDeny = false;
    Pulsar::System* system = Pulsar::System::sInstance;
    if(error == 0x13) {
        isCustomDeny = true;
        if(RKNet::Controller::sInstance->roomType == RKNet::ROOMTYPE_VS_REGIONAL) system->deniesCount++;
    }
    Pulsar::System::sInstance->isCustomDeny = isCustomDeny;
    DWC::Printf(r3, string);
}
kmCall(0x800dd054, HasBeenPulsarDenied);
kmWrite32(0x800dd044, 0x60000000);

asmFunc ProcessWrapper() {
    ASM(
        nofralloc;
    mr r4, r31;
    mr r5, r25;
    mflr r31;
    bl Process;
    mtlr r31;
    rlwinm r0, r3, 0, 24, 31;
    blr;
    )
}
kmCall(0x800dc4a0, ProcessWrapper);

void Send(DWC::MatchCommand type, u32 pid, u32 ip, u16 port, void* data, u32 dataSize) {
    const RKNet::RoomType roomType = RKNet::Controller::sInstance->roomType;
    const bool isCustom = roomType == RKNet::ROOMTYPE_FROOM_NONHOST || roomType == RKNet::ROOMTYPE_FROOM_HOST
        || roomType == RKNet::ROOMTYPE_VS_REGIONAL || roomType == RKNet::ROOMTYPE_JOINING_REGIONAL;
    if(type == DWC::MATCH_COMMAND_RESERVATION && isCustom) {
        ResvPacket packet(*reinterpret_cast<const DWC::Reservation*>(data));
        System::sInstance->SetUserInfo(packet.pulInfo.userInfo);
        data = &packet;
        dataSize = sizeof(ResvPacket) / sizeof(u32);
    }
    SendMatchCommand(type, pid, ip, port, data, dataSize);
}
kmCall(0x800df078, Send);

static void ResetDenyCounter(UIControl* control, u32 soundId, u32 r5) {
    control->PlaySound(soundId, r5);
    if(RKNet::Controller::sInstance->roomType == RKNet::ROOMTYPE_VS_REGIONAL) {
        Pulsar::System::sInstance->deniesCount = 0;
    }
}
kmCall(0x80609110, ResetDenyCounter);

}
}


