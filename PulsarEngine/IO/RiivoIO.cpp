#include <kamek.hpp>
#include <PulsarSystem.hpp>
#include <IO/RiivoIO.hpp>

namespace Pulsar {

bool RiivoIO::OpenFile(const char* path, u32 mode) {
    RiivoMode riivoMode = this->GetRiivoMode(mode);
    this->GetCorrectPath(this->filePath, path);
    return IO::OpenFileDirectly(this->filePath, riivoMode);
}

bool RiivoIO::CreateAndOpen(const char* path, u32 mode) {
    const s32 riivo_fd = this->GetDevice_fd();
    IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_CREATEFILE), (void*)path, strlen(path) + 1, nullptr, 0);
    IOS::Close(riivo_fd);
    return RiivoIO::OpenFile(path, mode);
}

void RiivoIO::GetCorrectPath(char* realPath, const char* path) const {
    snprintf(realPath, IOS::ipcMaxPath, "%s%s", "file", path);
}

#pragma suppress_warnings on
//Riivo specific funcs
s32 RiivoIO::GetDevice_fd() const {
    return IO::OpenFix("file", IOS::MODE_NONE);
}
#pragma suppress_warnings reset

RiivoMode RiivoIO::GetRiivoMode(u32 mode) const {
    if((mode & 0x3) != 0) mode -= 1;
    return static_cast<RiivoMode>(mode);
}


//FOLDER
bool RiivoIO::FolderExists(const char* path) const {
    s32 riivo_fd = this->GetDevice_fd();
    alignas(0x20) s32 folder_fd = IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_OPENDIR), (void*)path, strlen(path) + 1, nullptr, 0);

    if(folder_fd >= 0) {
        IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_CLOSEDIR), (void*)&folder_fd, sizeof(s32), nullptr, 0);
    }
    IOS::Close(riivo_fd);
    return folder_fd >= 0;
}

bool RiivoIO::CreateFolder(const char* path) {
    this->Bind(path);
    s32 riivo_fd = this->GetDevice_fd();
    s32 error = IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_CREATEDIR), (void*)this->folderName, strlen(this->folderName) + 1, nullptr, 0);
    IOS::Close(riivo_fd);
    return error >= 0;
}

void RiivoIO::ReadFolder(const char* path) {
    s32 riivo_fd = this->GetDevice_fd();
    this->Bind(path);
    alignas(0x20) IOS::IOCtlvRequest request[3];
    alignas(0x20) s32 folder_fd  = IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_OPENDIR),
        (void*)this->folderName, strlen(this->folderName) + 1, nullptr, 0);
    alignas(0x20) char fileName[riivoMaxPath];
    alignas(0x20) RiivoStats stats;
    if(folder_fd >= 0 && !this->isBusy) {
        this->isBusy = true;
        IOS::IPCPath* tmpArray = new (this->heap) IOS::IPCPath[maxFileCount];

        u32 count = 0;
        while(count < maxFileCount) {
            request[0].address = &folder_fd;
            request[0].size = 4;
            request[1].address = &fileName;
            request[1].size = riivoMaxPath;
            request[2].address = &stats;
            request[2].size = sizeof(RiivoStats);
            s32 retIOCtlv = IOS::IOCtlv(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_NEXTDIR), 1, 2, request);
            if(retIOCtlv != 0) break;
            if((stats.mode & S_IFDIR) == S_IFDIR) continue; //if the next entry is a directory, skip

            //snprintf(tmpArray[count], IPCMAXPATH, "/mnt/identifier/%016llX", stats.identifier);
            strncpy(tmpArray[count], fileName, IOS::ipcMaxPath);
            count++;
        }

        IOS::IPCPath* namesArray = new (RKSystem::mInstance.EGGSystem) IOS::IPCPath[count]; //here
        memcpy(namesArray, tmpArray, sizeof(IOS::IPCPath) * count);
        this->fileCount = count;
        this->fileNames = namesArray;
        delete[](tmpArray);

        IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_CLOSEDIR), (void*)&folder_fd, sizeof(s32), nullptr, 0);
    }
    IOS::Close(riivo_fd);
    this->isBusy = false;
}



}//namespace Pulsar