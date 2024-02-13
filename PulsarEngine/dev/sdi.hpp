#ifndef _SDI_
#define _SDI_

#include <IO/IO.hpp>
#include <dev/ff.hpp>


namespace Pulsar {

class FATIO : public IO {
public:
    typedef TCHAR FatFileName[13];
    static const u32 SECTOR_SIZE = 512;
    static const u32 TMP_SECTOR_COUNT = 8;

    FATIO(IOType type, EGG::Heap* heap, EGG::TaskThread* taskThread) : IO(type, heap, taskThread), fatFd(-1), rca(0) {}
    bool Init() override;
    void Convert(wchar_t* dest, const char* path) const;


    s32 GetDevice_fd() const;


    u32 Sdi_sectorSize() const { return SECTOR_SIZE; }
    bool Sdi_resetCard();
    bool Sdi_getStatus(u32* status);
    bool Sdi_read(u32 firstSector, u32 sectorCount, void* buffer);
    bool Sdi_write(u32 firstSector, u32 sectorCount, const void* buffer);
    bool Sdi_readHcr(u8 reg, u8 size, u32* val);
    bool Sdi_writeHcr(u8 reg, u8 size, u32 val);
    bool Sdi_setClock(u32 clock);
    bool Sdi_sendCommand(u32 command, u32 commandType, u32 responseType, u32 arg, u32 blockCount,
        u32 blockSize, void* buffer, u32* response);
    bool Sdi_enable4BitBus();
    bool Sdi_select();
    bool Sdi_deselect();
    bool Sdi_enableCard4BitBus();
    bool Sdi_transferAligned(bool isWrite, u32 firstSector, u32 sectorCount, void* buffer);
    bool Sdi_transfer(bool isWrite, u32 firstSector, u32 sectorCount, void* buffer);
    bool Sdi_setCardBlockLength(u32 blockLength);

    //DEAL WITH CHAR/WCHAR
    //OVERRIDES
    bool OpenModFile(const char* path, u32 mode) override;
    bool CreateAndOpen(const char* path, u32 mode) override;

    s32 Read(u32 size, void* bufferIn) override;
    void Seek(u32 offset) override;
    s32 Write(u32 length, const void* buffer) override;
    s32 Overwrite(u32 length, const void* buffer) override;
    void Close() override;

    void CreateFolder(const char* path) override;
    void ReadFolder(const char* path) override;
    s32 ReadFolderFile(void* buffer, u32 index, u32 mode, u32 maxLength) override;
    bool FolderExists(const char* path) const override;
    void CloseFolder() override;

    void GetCorrectPath(char* realPath, const char* path) const override {}

public:

    OS::Mutex mutex;
    s32 fatFd;
    u16 rca;
    bool isSdhc;
    alignas(0x20) u8 tmpBuffer[TMP_SECTOR_COUNT * SECTOR_SIZE];

    FATFS m_fs;
    DIR dir;
    FIL file;
    FatFileName names[100];

    friend IO* IO::CreateInstance(IOType type, EGG::Heap* heap, EGG::TaskThread* const taskThread);
};

}//namespace Pulsar
#endif