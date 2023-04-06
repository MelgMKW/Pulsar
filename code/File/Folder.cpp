#include <File/Folder.hpp>
#include <Pulsar.hpp>

namespace PulsarIO {
Folder *Folder::sInstance = NULL;
Folder *Folder::CreateStaticInstance(EGG::TaskThread *taskThread) {
    s32 riivo_fd = Pulsar::Open("file", IOS::MODE_NONE);
    EGG::Heap *heap = RKSystem::mInstance.EGGSystem;
    Folder *folder;
    if (riivo_fd < 0) {
        folder = new (heap) Folder(taskThread);
        folder->curFile = new (heap) File(taskThread);
    }
    else {
        IOS::Close(riivo_fd);
        folder = new (heap) RiivoFolder(taskThread);
        folder->curFile = new (heap) RiivoFile(taskThread);
    }
    Folder::sInstance = folder;
    return folder;
}

void Folder::RequestCreateFolder(const char *path) {
    if (!this->FolderExists(path)) {
        CreateRequest *request = &this->requests[0];
        if (!request->isFree) request = &this->requests[1];
        if (request->isFree) {
            request->isFree = false;
            strncpy(request->path, path, IPCMAXPATH);
            Pulsar::sInstance->taskThread->Request(&Folder::CreateFolderAsync, request, 0);
        }
    }
}

void Folder::CreateFolderAsync(void *requestArg) {
    Folder *folder = Folder::sInstance;
    CreateRequest *request = (CreateRequest *)requestArg;
    folder->CreateFolder(request->path);
    request->isFree = true;
}

void Folder::CloseFolder() {
    isBusy = false;
    this->curFile->Close();
    if (this->fileNames != NULL) delete[](this->fileNames);
    this->fileNames = NULL;
    this->folderName[0] = '\0';
    this->fileCount = 0;
}

s32 Folder::ReadFile(void *bufferIn, u32 index, u32 mode) {
    char path[IPCMAXPATH];
    this->GetFilePath(path, index);
    this->curFile->Open(path, mode);
    s32 ret = this->curFile->Read(bufferIn, this->curFile->GetFileSize()); //
    return ret;
}

void Folder::GetFilePath(char *path, u32 index) const {
    snprintf(path, IPCMAXPATH, "%s/%s", &this->folderName, &this->fileNames[index]);
}

//Virtual funcs
bool Folder::FolderExists(const char *path) {
    char realPath[IPCMAXPATH];
    this->GetCorrectPath(realPath, path);
    u32 count;
    return ISFS::ReadDir(realPath, NULL, &count) >= 0;
}

void Folder::CreateFolder(const char *path) {
    this->Bind(path);
    char realPath[IPCMAXPATH];
    this->GetCorrectPath(realPath, path);
    ISFS::CreateDir(realPath, 0, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE);
}

s32 Folder::ReadFolder(const char *path) {
    this->Bind(path);
    char realPath[IPCMAXPATH];
    this->GetCorrectPath(realPath, path);

    u32 count = MAXFILECOUNT;
    char *tmpArray = new(this->heap, 0x20) char[255 * (count + 1)];
    void *originalPtr = tmpArray;
    s32 error = ISFS::ReadDir(realPath, tmpArray, &count);
    if (error >= 0 && !isBusy) {
        isBusy = true;
        strncpy(this->folderName, path, IPCMAXPATH);
        IOS::IPCPath *namesArray = new(this->heap, 0x20) IOS::IPCPath[count];
        u32 realCount = 0;
        char curFile[IPCMAXPATH];
        while (tmpArray[0] != '\0') {
            u32 length = strlen(tmpArray);
            if (length > 255) break;
            if (length <= IPCMAXFILENAME) {
                snprintf(curFile, IPCMAXPATH, "%s/%s", realPath, tmpArray);
                s32 curFilefd = ISFS::Open(curFile, ISFS::MODE_NONE);
                if (curFilefd >= 0) {
                    strcpy(namesArray[realCount], (char *)tmpArray);
                    realCount++;
                    ISFS::Close(curFilefd);
                }
            }
            tmpArray = tmpArray + length + 1;
        }
        this->fileCount = realCount;
        this->fileNames = namesArray;
    }
    EGG::Heap::free(originalPtr, this->heap);
    return error;
}

bool RiivoFolder::FolderExists(const char *path) {
    s32 riivo_fd = this->curFile->GetDevice_fd();
    s32 folder_fd __attribute((aligned(0x20))) = IOS::IOCtl(riivo_fd, (IOS::IOCtlType)RIIVO_IOCTL_OPENDIR, (void *)path, strlen(path) + 1, NULL, 0);
    IOS::IOCtl(riivo_fd, (IOS::IOCtlType)RIIVO_IOCTL_CLOSEDIR, (void *)&folder_fd, sizeof(s32), NULL, 0);
    IOS::Close(riivo_fd);
    return folder_fd >= 0;
}

void RiivoFolder::CreateFolder(const char *path) {
    this->Bind(path);
    s32 riivo_fd = this->curFile->GetDevice_fd();
    s32 error = IOS::IOCtl(riivo_fd, (IOS::IOCtlType)RIIVO_IOCTL_CREATEDIR, (void *)path, strlen(path) + 1, NULL, 0);
    IOS::Close(riivo_fd);
}

s32 RiivoFolder::ReadFolder(const char *path) {
    this->Bind(path);
    s32 riivo_fd = this->curFile->GetDevice_fd();
    IOS::IOCtlvRequest request[3] __attribute((aligned(0x20)));
    s32 folder_fd __attribute((aligned(0x20))) = IOS::IOCtl(riivo_fd, (IOS::IOCtlType)RIIVO_IOCTL_OPENDIR, (void *)path, strlen(path) + 1, NULL, 0);
    if (folder_fd >= 0 && !isBusy) {
        isBusy = true;
        char fileName[RIIVOMAXPATH] __attribute((aligned(0x20)));
        RiivoStats stats __attribute((aligned(0x20)));
        IOS::IPCPath *tmpArray = new (this->heap) IOS::IPCPath[MAXFILECOUNT];
        u32 count = 0;
        while (count < MAXFILECOUNT) {
            request[0].address = &folder_fd;
            request[0].size = 4;
            request[1].address = &fileName;
            request[1].size = RIIVOMAXPATH;
            request[2].address = &stats;
            request[2].size = sizeof(RiivoStats);
            s32 retIOCtlv = IOS::IOCtlv(riivo_fd, (IOS::IOCtlType)RIIVO_IOCTL_NEXTDIR, 1, 2, request);
            if (retIOCtlv != 0) break;
            if ((stats.Mode & S_IFDIR) == S_IFDIR) continue; //if the next entry is a directory, skip

            //snprintf(tmpArray[count], IPCMAXPATH, "/mnt/identifier/%016llX", stats.Identifier);
            strncpy(tmpArray[count], fileName, IPCMAXPATH);
            count++;
        }

        IOS::IPCPath *namesArray = new (this->heap) IOS::IPCPath[count]; //here
        memcpy(namesArray, tmpArray, sizeof(IOS::IPCPath) * count);
        this->fileCount = count;
        this->fileNames = namesArray;
        delete[](tmpArray);
        s32 folder_fd = IOS::IOCtl(riivo_fd, (IOS::IOCtlType)RIIVO_IOCTL_CLOSEDIR, (void *)&folder_fd, sizeof(s32), NULL, 0);
    }

    IOS::Close(riivo_fd);
    return folder_fd;
}

}//namespace PulsarIO