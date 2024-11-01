#ifndef _PUL_SELECT_
#define _PUL_SELECT_


#include <kamek.hpp>
#include <MarioKartWii/RKNet/Select.hpp>
#include <Network/Network.hpp>
namespace Pulsar {
namespace Network {

#define GetRecvPulSELECTPacket(addr) \
asmFunc GetRecvPulSELECTPacket##addr(){ \
    ASM( \
        nofralloc;\
        mulli r4, r4, sizeof(PulSELECT);\
        lwz r3, ExpSELECTHandler.receivedPackets(r3);\
        subi r4, r4, 0x40;\
        blr;\
)}; \
kmBranch(##addr, GetRecvPulSELECTPacket##addr); \
kmPatchExitPoint(GetRecvPulSELECTPacket##addr, ##addr + 4);

}//namespace Network
}//namespace Pulsar


#endif