#include <IO/File.hpp>
#include <PulsarSystem.hpp>
#include <IO/IO.hpp>

namespace Pulsar {
namespace IO {
File* File::sInstance = nullptr;
File* File::CreateStaticInstance(IOType type, EGG::Heap* heap, EGG::TaskThread* const taskThread) {
    File* file;
    if(type != IOType_RIIVO) file = new(heap) File(type, heap, taskThread);
    else file = new (heap) RiivoFile(heap, taskThread);
    File::sInstance = file;
    return file;
}



s32 File::Open(const char* path, u32 mode) {
    if(type == IOType_ISO) return -1;
    this->GetCorrectPath(this->path, path);
    this->fd = IO::Open(this->path, static_cast<IOS::Mode>(mode));
    s32 ret = IOS::Seek(this->fd, 0, IOS::SEEK_END);
    if(ret < 0) ret = 0;
    this->fileSize = ret;
    IOS::Seek(this->fd, 0, IOS::SEEK_START);
    return this->fd;
}

s32 File::CreateAndOpen(const char* path, u32 mode) {
    char realPath[IOS::ipcMaxPath];
    this->GetCorrectPath(realPath, path);
    ISFS::CreateFile(realPath, 0, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE);
    return this->Open(path, mode);
}

void File::GetCorrectPath(char* realPath, const char* path) const {
    snprintf(realPath, IOS::ipcMaxPath, "%s%s", "/title/00010004", path);
}

s32 File::GetDevice_fd() const {
    return IOS::fs_fd;
}

s32 File::Read(u32 size, void* bufferIn) {
    if(this->fd < 0) return -1;
    return IOS::Read(this->fd, bufferIn, size);
}


s32 File::Write(u32 length, const void* buffer) {
    if(this->fd < 0) return -1;
    return IOS::Write(this->fd, const_cast<void*>(buffer), length);
}

s32 File::Overwrite(u32 length, const void* buffer) {
    if(this->fd < 0) return -1;
    IOS::Seek(this->fd, 0, IOS::SEEK_START);
    return IOS::Write(this->fd, const_cast<void*>(buffer), length);
}

void File::Close() {
    if(this->fd >= 0) IOS::Close(this->fd);
    this->fd = -1;
    this->fileSize = 0;
}

s32 RiivoFile::Open(const char* path, u32 mode) {
    return File::Open(path, this->GetRiivoMode(mode));
}

s32 RiivoFile::CreateAndOpen(const char* path, u32 mode) {
    const s32 riivo_fd = this->GetDevice_fd();
    IOS::IOCtl(riivo_fd, static_cast<IOS::IOCtlType>(RIIVO_IOCTL_CREATEFILE), (void*)path, strlen(path) + 1, nullptr, 0);
    IOS::Close(riivo_fd);
    return this->Open(path, mode);
}

s32 RiivoFile::GetDevice_fd() const {
    return IO::Open("file", IOS::MODE_NONE);
}

void RiivoFile::GetCorrectPath(char* realPath, const char* path) const {
    snprintf(realPath, IOS::ipcMaxPath, "%s%s", "file", path);
}

RiivoMode RiivoFile::GetRiivoMode(u32 mode) const {
    if((mode & 0x3) != 0) mode -= 1;
    return static_cast<RiivoMode>(mode);
}

}//namespace IO
}//namespace Pulsar










