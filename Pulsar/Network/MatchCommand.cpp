#include <game/RKNet/RKNetController.hpp>
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
        || roomType == RKNet::ROOMTYPE_VS_REGIONAL;

    if(type == DWC::MATCH_COMMAND_RESV_OK && isCustom) {
        const ResvPacket* packet = reinterpret_cast<const ResvPacket*>(data);
        System* system = System::sInstance;
        if(dataSize != (sizeof(ResvPacket) / sizeof(u32)) || packet->pulInfo.roomKey != Info::GetKey()
            || strcmp(packet->pulInfo.modFolderName, system->GetModFolder()) != 0
            || !system->CheckUserInfo(packet->pulInfo.userInfo)) {
            type = DWC::MATCH_COMMAND_RESV_DENY;
        }
    }
    return type;
}

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
        || roomType == RKNet::ROOMTYPE_VS_REGIONAL;
    if(type == DWC::MATCH_COMMAND_RESERVATION && isCustom) {
        ResvPacket packet(*reinterpret_cast<const DWC::Reservation*>(data));
        System::sInstance->SetUserInfo(packet.pulInfo.userInfo);
        data = &packet;
        dataSize = sizeof(ResvPacket) / sizeof(u32);
    }
    SendMatchCommand(type, pid, ip, port, data, dataSize);
}
kmCall(0x800df078, Send);
}
}


