#include <IO/Folder.hpp>
#include <PulsarSystem.hpp>


namespace Pulsar {
namespace IO {
Folder* Folder::sInstance = nullptr;
Folder* Folder::CreateStaticInstance(IOType type, EGG::Heap* heap, EGG::TaskThread* const taskThread) {
    Folder* folder;
    if(type != IOType_RIIVO) {
        folder = new (heap) Folder(type, heap, taskThread);
        folder->curFile = new (heap) File(type, taskThread);
    }
    else {
        folder = new (heap) RiivoFolder(heap, taskThread);
        folder->curFile = new(heap) RiivoFile(taskThread);
    }
    Folder::sInstance = folder;
    return folder;
}

void Folder::RequestCreateFolder(const char* path) {
    if(!this->FolderExists(path)) {
        CreateRequest* request = &this->requests[0];
        if(!request->isFree) request = &this->requests[1];
        if(request->isFree) {
            request->isFree = false;
            strncpy(request->path, path, IOS::ipcMaxPath);
            System::sInstance->taskThread->Request(&Folder::CreateFolderAsync, request, 0);
        }
    }
}

void Folder::CreateFolderAsync(CreateRequest* request) {
    Folder* folder = Folder::sInstance;
    folder->CreateFolder(request->path);
    request->isFree = true;
}

void Folder::CloseFolder() {
    isBusy = false;
    this->curFile->Close();
    if(this->fileNames != nullptr) delete[](this->fileNames);
    this->fileNames = nullptr;
    this->folderName[0] = '\0';
    this->fileCount = 0;
}

s32 Folder::ReadFile(void* bufferIn, u32 index, u32 mode, u32 maxLength) {
    char path[IOS::ipcMaxPath];
    this->GetFilePath(path, index);
    this->curFile->Open(path, mode);
    const u32 size = this->curFile->GetFileSize();
    const u32 length = size <= maxLength ? size : maxLength;
    s32 ret = this->curFile->Read(bufferIn, length);
    this->curFile->Close();
    return ret;
}

void Folder::GetFilePath(char* path, u32 index) const {
    snprintf(path, IOS::ipcMaxPath, "%s/%s", &this->folderName, &this->fileNames[index]);
}

//Virtual funcs
bool Folder::FolderExists(const char* path) {
    char realPath[IOS::ipcMaxPath];
    this->GetCorrectPath(realPath, path);
    u32 count;
    return ISFS::ReadDir(realPath, nullptr, &count) >= 0;
}

void Folder::CreateFolder(const char* path) {
    if(type != IOType_ISO) {
        this->Bind(path);
        char realPath[IOS::ipcMaxPath];
        this->GetCorrectPath(realPath, path);
        ISFS::CreateDir(realPath, 0, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE);
    }
}

void Folder::ReadFolder(const char* path) {
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
    }
    EGG::Heap::free(originalPtr, this->heap);
}

bool RiivoFolder::FolderExists(const char* path) {
    s32 riivo_fd = this->curFile->GetDevice_fd();
    alignas(0x20) s32 folder_fd = IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_OPENDIR),
        (void*)path, strlen(path) + 1, nullptr, 0);
    IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_CLOSEDIR), (void*)&folder_fd, sizeof(s32), nullptr, 0);
    IOS::Close(riivo_fd);
    return folder_fd >= 0;
}

void RiivoFolder::CreateFolder(const char* path) {
    this->Bind(path);
    s32 riivo_fd = this->curFile->GetDevice_fd();
    s32 error = IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_CREATEDIR), (void*)path, strlen(path) + 1, nullptr, 0);
    IOS::Close(riivo_fd);
}

void RiivoFolder::ReadFolder(const char* path) {
    this->Bind(path);
    s32 riivo_fd = this->curFile->GetDevice_fd();
    alignas(0x20) IOS::IOCtlvRequest request[3];
    alignas(0x20) s32 folder_fd = IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_OPENDIR),
        (void*)path, strlen(path) + 1, nullptr, 0);
    if(folder_fd >= 0 && !isBusy) {
        isBusy = true;
        alignas(0x20) char fileName[riivoMaxPath];
        alignas(0x20) RiivoStats stats;
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
            if((stats.Mode & S_IFDIR) == S_IFDIR) continue; //if the next entry is a directory, skip

            //snprintf(tmpArray[count], IOS::ipcMaxPath, "/mnt/identifier/%016llX", stats.Identifier);
            strncpy(tmpArray[count], fileName, IOS::ipcMaxPath);
            ++count;
        }

        IOS::IPCPath* namesArray = new (this->heap) IOS::IPCPath[count]; //here
        memcpy(namesArray, tmpArray, sizeof(IOS::IPCPath) * count);
        this->fileCount = count;
        this->fileNames = namesArray;
        delete[](tmpArray);
        s32 folder_fd = IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_CLOSEDIR), (void*)&folder_fd, sizeof(s32), nullptr, 0);
    }

    IOS::Close(riivo_fd);
}

}//namespace IO
}//namespace Pulsar