#include <kamek.hpp>
#include <PulsarSystem.hpp>
#include <IO/IO.hpp>
#include <dev/sdi.hpp>

namespace Pulsar {

IO* IO::sInstance = nullptr;

IO* IO::CreateInstance(IOType type, EGG::Heap* heap, EGG::TaskThread* const taskThread) {
    IO* io;
    if(type != IOType_RIIVO) io = new (heap) FATIO(type, heap, taskThread);
    else io = new (heap) RiivoIO(type, heap, taskThread);
    IO::sInstance = io;
    io->Init();
    return io;
}


//Virtual Funcs
//FILE
#pragma suppress_warnings on
bool NANDIO::OpenIOSFile(const char* path, u32 mode) {
    if(type == IOType_ISO) return -1;
    this->fd = IO::OpenFix(path, static_cast<IOS::Mode>(mode));
    return this->fd >= 0;
}
bool NANDIO::OpenModFile(const char* path, u32 mode) {
    this->GetCorrectPath(this->filePath, path);
    return this->OpenIOSFile(this->filePath, mode);
}
#pragma suppress_warnings reset

s32 NANDIO::Read(u32 size, void* bufferIn) {
    if(this->fd < 0) return 0;
    return IOS::Read(this->fd, bufferIn, size);
}

s32 NANDIO::Write(u32 length, const void* buffer) {
    if(this->fd < 0) return -1;
    return IOS::Write(this->fd, buffer, length);
}

s32 NANDIO::Overwrite(u32 length, const void* buffer) {
    if(this->fd < 0) return -1;
    IOS::Seek(this->fd, 0, IOS::SEEK_START);
    return IOS::Write(this->fd, buffer, length);
}

void NANDIO::Close() {
    if(this->fd >= 0) IOS::Close(this->fd);
    this->fd = -1;
    this->fileSize = -1;
}

s32 NANDIO::GetFileSize() {
    if(this->fileSize < 0 && this->fd >= 0) {
        s32 size = IOS::Seek(this->fd, 0, IOS::SEEK_END);
        if(size >= 0) {
            this->fileSize = size;
            IOS::Seek(this->fd, 0, IOS::SEEK_START);
        }
    }
    return this->fileSize;
}

bool NANDIO::CreateAndOpen(const char* path, u32 mode) {
    char realPath[IOS::ipcMaxPath];
    this->GetCorrectPath(realPath, path);
    ISFS::CreateFile(realPath, 0, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE);
    return NANDIO::OpenModFile(path, mode);
}

void NANDIO::GetCorrectPath(char* realPath, const char* path) const {
    snprintf(realPath, IOS::ipcMaxPath, "%s%s", "/title/00010004", path);
}


bool RiivoIO::OpenModFile(const char* path, u32 mode) {
    return NANDIO::OpenModFile(path, this->GetRiivoMode(mode));
}

bool RiivoIO::CreateAndOpen(const char* path, u32 mode) {
    const s32 riivo_fd = this->GetDevice_fd();
    IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_CREATEFILE), (void*)path, strlen(path) + 1, nullptr, 0);
    IOS::Close(riivo_fd);
    return RiivoIO::OpenModFile(path, mode);
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
void IO::RequestCreateFolder(const char* path) {
    if(!this->FolderExists(path)) {
        CreateRequest* request = &this->requests[0];
        if(!request->isFree) request = &this->requests[1];
        if(request->isFree) {
            request->isFree = false;
            strncpy(request->path, path, IOS::ipcMaxPath);
            System::sInstance->taskThread->Request(&IO::CreateFolderAsync, request, 0);
        }
    }
}

void IO::CreateFolderAsync(CreateRequest* request) {
    IO* io = IO::sInstance;
    io->CreateFolder(request->path);
    request->isFree = true;
}

void NANDIO::CloseFolder() {
    isBusy = false;
    this->Close();
    if(this->fileNames != nullptr) delete[](this->fileNames);
    this->fileNames = nullptr;
    this->folderName[0] = '\0';
    this->fileCount = 0;
}

s32 NANDIO::ReadFolderFile(void* bufferIn, u32 index, u32 mode, u32 maxLength) {
    char path[IOS::ipcMaxPath];
    this->GetFolderFilePath(path, index);
    this->OpenModFile(path, mode);
    const u32 size = this->GetFileSize();
    const u32 length = size <= maxLength ? size : maxLength;
    s32 ret = this->Read(length, bufferIn);
    this->Close();
    return ret;
}

void NANDIO::GetFolderFilePath(char* path, u32 index) const {
    snprintf(path, IOS::ipcMaxPath, "%s/%s", &this->folderName, &this->fileNames[index]);
}

//Virtual funcs
bool NANDIO::FolderExists(const char* path) const {
    char realPath[IOS::ipcMaxPath];
    this->GetCorrectPath(realPath, path);
    u32 count;
    return ISFS::ReadDir(realPath, nullptr, &count) >= 0;
}

void NANDIO::CreateFolder(const char* path) {
    if(type != IOType_ISO) {
        this->Bind(path);
        char realPath[IOS::ipcMaxPath];
        this->GetCorrectPath(realPath, path);
        ISFS::CreateDir(realPath, 0, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE);
    }
}

void NANDIO::ReadFolder(const char* path) {
    this->Bind(path);
    char realPath[IOS::ipcMaxPath];
    this->GetCorrectPath(realPath, path);

    u32 count = maxFileCount;
    char* tmpArray = new(this->heap, 0x20) char[255 * (count + 1)];
    void* originalPtr = tmpArray;
    s32 error = ISFS::ReadDir(realPath, tmpArray, &count);
    if(error >= 0 && !isBusy) {
        isBusy = true;
        strncpy(this->folderName, path, IOS::ipcMaxPath);
        IOS::IPCPath* namesArray = new(this->heap, 0x20) IOS::IPCPath[count];
        u32 realCount = 0;
        char curFile[IOS::ipcMaxPath];
        while(tmpArray[0] != '\0') {
            u32 length = strlen(tmpArray);
            if(length > 255) break;
            if(length <= IOS::ipcMaxFileName) {
                snprintf(curFile, IOS::ipcMaxPath, "%s/%s", realPath, tmpArray);
                s32 curFilefd = ISFS::Open(curFile, ISFS::MODE_NONE);
                if(curFilefd >= 0) {
                    strcpy(namesArray[realCount], tmpArray);
                    ++realCount;
                    ISFS::Close(curFilefd);
                }
            }
            tmpArray = tmpArray + length + 1;
        }
        this->fileCount = realCount;
        this->fileNames = namesArray;
        this->isBusy = false;
    }
    EGG::Heap::free(originalPtr, this->heap);
}


bool RiivoIO::FolderExists(const char* path) const {
    s32 riivo_fd = this->GetDevice_fd();
    alignas(0x20) s32 folder_fd = IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_OPENDIR), (void*)path, strlen(path) + 1, nullptr, 0);

    if(folder_fd >= 0) {
        IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_CLOSEDIR), (void*)&folder_fd, sizeof(s32), nullptr, 0);
    }
    IOS::Close(riivo_fd);
    return folder_fd >= 0;
}

void RiivoIO::CreateFolder(const char* path) {
    this->Bind(path);
    s32 riivo_fd = this->GetDevice_fd();
    s32 error = IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_CREATEDIR), (void*)this->folderName, strlen(this->folderName) + 1, nullptr, 0);
    IOS::Close(riivo_fd);
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