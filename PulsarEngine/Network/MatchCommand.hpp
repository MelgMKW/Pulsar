#ifndef _PUL_MATCH_COMMAND_
#define _PUL_MATCH_COMMAND_
#include <core/rvl/DWC/MatchCommand.hpp>
#include <core/rvl/ipc/ipc.hpp>

namespace Pulsar {
namespace Network {


struct ResvInfo {
    struct UserInfo {
        UserInfo() {
            info[0] = -1;
            info[1] = -1;
            info[2] = -1;
            info[3] = -1;
        }
        u32 info[4];
    };
    ResvInfo() {
        padding[0] = 0;
        padding[1] = 0;
        padding[2] = 0;
    }
    u32 roomKey;
    char modFolderName[IOS::ipcMaxFileName];
    u8 padding[3];
    UserInfo userInfo;
};
size_assert(ResvInfo, 0x24);

struct ResvPacket : DWC::Reservation {
    ResvPacket(const DWC::Reservation& src);
    ResvInfo pulInfo;
};
size_assert(ResvPacket, 0x48);

}//namespace Network
}//namespace Pulsar

#endif

