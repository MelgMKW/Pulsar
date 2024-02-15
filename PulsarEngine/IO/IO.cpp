#include <kamek.hpp>
#include <PulsarSystem.hpp>
#include <IO/IO.hpp>
#include <IO/NANDIO.hpp>
#include <IO/RiivoIO.hpp>

namespace Pulsar {

IO* IO::sInstance = nullptr;

IO* IO::CreateInstance(IOType type, EGG::Heap* heap, EGG::TaskThread* const taskThread) {
    IO* io;
    if(type != IOType_RIIVO) io = new (heap) NANDIO(type, heap, taskThread);
    else io = new (heap) RiivoIO(type, heap, taskThread);
    IO::sInstance = io;
    return io;
}

//FILE
#pragma suppress_warnings on
bool IO::OpenFileDirectly(const char* path, u32 mode) {
    if(type == IOType_ISO) return -1;
    this->fd = IO::OpenFix(path, static_cast<IOS::Mode>(mode));
    return this->fd >= 0;
}

#pragma suppress_warnings reset

s32 IO::Read(u32 size, void* bufferIn) {
    if(this->fd < 0) return 0;
    return IOS::Read(this->fd, bufferIn, size);
}

s32 IO::Write(u32 length, const void* buffer) {
    if(this->fd < 0) return -1;
    return IOS::Write(this->fd, buffer, length);
}

s32 IO::Overwrite(u32 length, const void* buffer) {
    if(this->fd < 0) return -1;
    IOS::Seek(this->fd, 0, IOS::SEEK_START);
    return IOS::Write(this->fd, buffer, length);
}

void IO::Close() {
    if(this->fd >= 0) IOS::Close(this->fd);
    this->fd = -1;
    this->fileSize = -1;
}

s32 IO::GetFileSize() {
    if(this->fileSize < 0 && this->fd >= 0) {
        s32 size = IOS::Seek(this->fd, 0, IOS::SEEK_END);
        if(size >= 0) {
            this->fileSize = size;
            IOS::Seek(this->fd, 0, IOS::SEEK_START);
        }
    }
    return this->fileSize;
}


//FOLDER
/*
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
*/

void IO::CreateFolderAsync(CreateRequest* request) {
    IO* io = IO::sInstance;
    io->CreateFolder(request->path);
    request->isFree = true;
}

void IO::CloseFolder() {
    isBusy = false;
    this->Close();
    if(this->fileNames != nullptr) delete[](this->fileNames);
    this->fileNames = nullptr;
    this->folderName[0] = '\0';
    this->fileCount = 0;
}

s32 IO::ReadFolderFile(void* bufferIn, u32 index, u32 maxLength) {
    char path[IOS::ipcMaxPath];
    this->GetFolderFilePath(path, index);
    this->OpenFile(path, FILE_MODE_READ);
    const u32 size = this->GetFileSize();
    const u32 length = size <= maxLength ? size : maxLength;
    s32 ret = this->Read(length, bufferIn);
    this->Close();
    return ret;
}

void IO::GetFolderFilePath(char* path, u32 index) const {
    snprintf(path, IOS::ipcMaxPath, "%s/%s", &this->folderName, &this->fileNames[index]);
}




}//namespace Pulsar