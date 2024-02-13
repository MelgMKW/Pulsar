
#include <dev/Sdi.hpp>

#include <core/rvl/ipc/ipc.hpp>
#include <core/rvl/OS/OS.hpp>

#include <include/c_string.h>

#include <IO/IO.hpp>

namespace Pulsar {
enum {
    IOCTL_WRITE_HCR = 0x1,
    IOCTL_READ_HCR = 0x2,
    IOCTL_RESET_CARD = 0x4,
    IOCTL_SET_CLOCK = 0x6,
    IOCTL_SEND_COMMAND = 0x7,
    IOCTL_GET_STATUS = 0xb,
};

enum {
    IOCTLV_SEND_COMMAND = 0x7,
};

enum {
    STATUS_CARD_INSERTED = 1 << 0,
    STATUS_TYPE_MEMORY = 1 << 16,
    STATUS_TYPE_SDHC = 1 << 20,
};

enum {
    HCR_HOST_CONTROL_1 = 0x28,
};

enum {
    HCR_HOST_CONTROL_1_4_BIT = 1 << 1,
};

typedef struct {
    u32 reg;
    u32 _04;
    u32 _08;
    u32 size;
    u32 val;
    u32 _14;
} RegOp;

enum {
    CMD_SELECT = 7,
    CMD_SET_BLOCKLEN = 16,
    CMD_READ_MULTIPLE_BLOCK = 18,
    CMD_WRITE_MULTIPLE_BLOCK = 25,
    CMD_APP_CMD = 55,
};

enum {
    ACMD_SET_BUS_WIDTH = 6,
};

enum {
    RESPONSE_TYPE_R1 = 0x1,
    RESPONSE_TYPE_R1B = 0x2,
};

typedef struct {
    u32 command;
    u32 commandType;
    u32 responseType;
    u32 arg;
    u32 blockCount;
    u32 blockSize;
    void* buffer;
    u32 isDma;
    u32 _20;
} Request;
size_assert(Request, 0x24);

enum {
    SECTOR_SIZE = 512,
};

enum {
    TMP_SECTOR_COUNT = 8,
};

/*
static s32 fd = -1;
static u16 rca = 0;
bool FATIO::isSdhc;
static alignas(0x20) u8 tmpBuffer[TMP_SECTOR_COUNT * SECTOR_SIZE];
*/

bool FATIO::Sdi_resetCard() {
    alignas(0x20) u32 out;

    if(IOS::IOCtl(fd, static_cast<IOS::IOCtlType>(IOCTL_RESET_CARD), nullptr, 0, &out, sizeof(out)) < 0) {
        OS::Report("%s", "Failed to reset interface");
        return false;
    }

    OS::Report("%s", "Successfully reset interface");
    rca = out >> 16;
    return true;
}

bool FATIO::Sdi_getStatus(u32* status) {
    alignas(0x20) u32 out;

    if(IOS::IOCtl(fd, static_cast<IOS::IOCtlType>(IOCTL_GET_STATUS), nullptr, 0, &out, sizeof(out)) < 0) {
        OS::Report("%s", "Failed to get status");
        return false;
    }

    OS::Report("%s", "Got status 0x%x", out);
    *status = out;
    return true;
}

bool FATIO::Sdi_readHcr(u8 reg, u8 size, u32* val) {
    alignas(0x20) RegOp regOp = {
            regOp.reg = reg,
            regOp._04 = 0,
            regOp._08 = 0,
            regOp.size = size,
            regOp.val = 0,
            regOp._14 = 0,
    };
    alignas(0x20) u32 out;

    if(IOS::IOCtl(fd, static_cast<IOS::IOCtlType>(IOCTL_READ_HCR), &regOp, sizeof(regOp), &out, sizeof(out)) < 0) {
        OS::Report("%s", "Failed to read host controller register 0x%x", reg);
        return false;
    }

    *val = out;
    return true;
}

bool FATIO::Sdi_writeHcr(u8 reg, u8 size, u32 val) {
    alignas(0x20) RegOp regOp = {
            regOp.reg = reg,
            regOp._04 = 0,
            regOp._08 = 0,
            regOp.size = size,
            regOp.val = val,
            regOp._14 = 0,
    };

    if(IOS::IOCtl(fd, static_cast<IOS::IOCtlType>(IOCTL_WRITE_HCR), &regOp, sizeof(regOp), nullptr, 0) < 0) {
        OS::Report("%s", "Failed to write to host controller register 0x%x", reg);
        return false;
    }

    return true;
}

bool FATIO::Sdi_setClock(u32 clock) {
    alignas(0x20) u32 in = clock;

    if(IOS::IOCtl(fd, static_cast<IOS::IOCtlType>(IOCTL_SET_CLOCK), &in, sizeof(in), nullptr, 0) < 0) {
        OS::Report("%s", "Failed to set clock");
        return false;
    }

    return true;
}

bool FATIO::Sdi_sendCommand(u32 command, u32 commandType, u32 responseType, u32 arg, u32 blockCount,
    u32 blockSize, void* buffer, u32* response) {
    alignas(0x20) Request request = {
            request.command = command,
            request.commandType = commandType,
            request.responseType = responseType,
            request.arg = arg,
            request.blockCount = blockCount,
            request.blockSize = blockSize,
            request.buffer = buffer,
            request.isDma = !!buffer,
            request._20 = 0,
    };
    alignas(0x20) u32 out[4];

    if(buffer || isSdhc) {
        alignas(0x20) IOS::IOCtlvRequest vec[] = {
                {
                        &request,
                        sizeof(request),
                },
                {
                        buffer,
                        blockCount * blockSize,
                },
                {
                        out,
                        sizeof(out),
                },
        };
        if(IOS::IOCtlv(fd, static_cast<IOS::IOCtlType>(IOCTLV_SEND_COMMAND), 2, 1, vec) < 0) {
            if(command != CMD_SELECT) {
                OS::Report("%s", "Failed to send command 0x%x", command);
            }
            return false;
        }
    }
    else {
        if(IOS::IOCtl(fd, static_cast<IOS::IOCtlType>(IOCTL_SEND_COMMAND), &request, sizeof(request), &out, sizeof(out)) < 0) {
            if(command != CMD_SELECT) {
                OS::Report("%s", "Failed to send command 0x%x", command);
            }
            return false;
        }
    }

    if(response) {
        *response = out[0];
    }
    return true;
}

bool FATIO::Sdi_enable4BitBus() {
    u32 val;
    if(!Sdi_readHcr(HCR_HOST_CONTROL_1, sizeof(u8), &val)) {
        return false;
    }

    val |= HCR_HOST_CONTROL_1_4_BIT;

    return Sdi_writeHcr(HCR_HOST_CONTROL_1, sizeof(u8), val);
}

bool FATIO::Sdi_select() {
    return Sdi_sendCommand(CMD_SELECT, 3, RESPONSE_TYPE_R1B, rca << 16, 0, 0, nullptr, nullptr);
}

bool FATIO::Sdi_deselect() {
    return Sdi_sendCommand(CMD_SELECT, 3, RESPONSE_TYPE_R1B, 0, 0, 0, nullptr, nullptr);
}

bool FATIO::Sdi_setCardBlockLength(u32 blockLength) {
    return Sdi_sendCommand(CMD_SET_BLOCKLEN, 3, RESPONSE_TYPE_R1, blockLength, 0, 0, nullptr, nullptr);
}

bool FATIO::Sdi_enableCard4BitBus() {
    if(!Sdi_sendCommand(CMD_APP_CMD, 3, RESPONSE_TYPE_R1, rca << 16, 0, 0, nullptr, nullptr)) {
        return false;
    }

    return Sdi_sendCommand(ACMD_SET_BUS_WIDTH, 3, RESPONSE_TYPE_R1, 0x2, 0, 0, nullptr, nullptr);
}

bool FATIO::Sdi_transferAligned(bool isWrite, u32 firstSector, u32 sectorCount, void* buffer) {
    u32 command = isWrite ? CMD_WRITE_MULTIPLE_BLOCK : CMD_READ_MULTIPLE_BLOCK;
    u32 firstBlock = isSdhc ? firstSector : firstSector * SECTOR_SIZE;
    return Sdi_sendCommand(command, 3, RESPONSE_TYPE_R1, firstBlock, sectorCount, SECTOR_SIZE,
        buffer, nullptr);
}

bool FATIO::Sdi_transfer(bool isWrite, u32 firstSector, u32 sectorCount, void* buffer) {

    if(!Sdi_select()) {
        return false;
    }

    if((u32)buffer & 0x1f) {
        while(sectorCount > 0) {
            u32 chunkSectorCount = nw4r::ut::Min(sectorCount, (u32)TMP_SECTOR_COUNT);
            if(isWrite) {
                memcpy(tmpBuffer, buffer, chunkSectorCount * SECTOR_SIZE);
            }
            if(!Sdi_transferAligned(isWrite, firstSector, chunkSectorCount, tmpBuffer)) {
                Sdi_deselect();
                return false;
            }
            if(!isWrite) {
                memcpy(buffer, tmpBuffer, chunkSectorCount * SECTOR_SIZE);
            }
            firstSector += chunkSectorCount;
            sectorCount -= chunkSectorCount;
            buffer = (void*)((u8*)buffer + chunkSectorCount * SECTOR_SIZE);
        }
    }
    else {
        if(!Sdi_transferAligned(isWrite, firstSector, sectorCount, buffer)) {
            Sdi_deselect();
            return false;
        }
    }

    Sdi_deselect();

    return true;
}

static u32 Sdi_sectorSize() {
    return SECTOR_SIZE;
}

bool FATIO::Sdi_read(u32 firstSector, u32 sectorCount, void* buffer) {
    return Sdi_transfer(false, firstSector, sectorCount, buffer);
}

bool FATIO::Sdi_write(u32 firstSector, u32 sectorCount, const void* buffer) {
    return Sdi_transfer(true, firstSector, sectorCount, (void*)buffer);
}


bool FATIO::Init() {
    if(fd < 0) fd = IOS::Open("/dev/sdio/slot0", IOS::MODE_NONE);
    if(fd < 0) {
        OS::Report("%s", "Failed to open /dev/sdio/slot0: Returned error %i", fd);
        return false;
    }
    else {
        OS::Report("%s", "Successfully opened interface: ID: %i", fd);
    }

    if(!Sdi_resetCard()) {
        return false;
    }

    u32 status;
    if(!Sdi_getStatus(&status)) {
        return false;
    }

    if(!(status & STATUS_CARD_INSERTED)) {
        OS::Report("%s", "No card inserted");
        return false;
    }

    if(!(status & STATUS_TYPE_MEMORY)) {
        OS::Report("%s", "Not a memory card");
        return false;
    }

    isSdhc = !!(status & STATUS_TYPE_SDHC);

    if(!Sdi_enable4BitBus()) {
        OS::Report("%s", "Failed to enable 4-bit bus");
        return false;
    }

    if(!Sdi_setClock(1)) {
        return false;
    }

    if(!Sdi_select()) {
        return false;
    }

    if(!Sdi_setCardBlockLength(SECTOR_SIZE)) {
        Sdi_deselect();
        return false;
    }

    if(!Sdi_enableCard4BitBus()) {
        Sdi_deselect();
        return false;
    }

    Sdi_deselect();

    if(f_mount(&this->m_fs, "", 1) != FR_OK)  return false;

    OS::Report("%s", "Successfully completed initialization");
    return true;
}
}
