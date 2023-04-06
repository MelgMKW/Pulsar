#include <File/File.hpp>
#include <Pulsar.hpp>


namespace PulsarIO {
File *File::sInstance = NULL;
File *File::CreateStaticInstance(EGG::TaskThread *taskThread) {
    EGG::Heap *heap = RKSystem::mInstance.EGGSystem;
    s32 ret = Pulsar::Open("file", IOS::MODE_NONE);
    File *file;
    bool valid = false; //For ISO users on console, we don't want anything to be saved on a real NAND
    if (ret < 0) {
        ret = Pulsar::Open("/dev/dolphin", IOS::MODE_NONE);
        if (ret >= 0) {
            valid = true;
            IOS::Close(ret);
        }
        file = new (heap) File(taskThread);
    }
    else {
        valid = true;
        IOS::Close(ret);
        file = new (heap) RiivoFile(taskThread);
    }
    file->isValid = valid;
    File::sInstance = file;
    return file;
}



s32 File::Open(const char *path, u32 mode) {

    char realPath[IPCMAXPATH];
    this->GetCorrectPath(this->path, path);
    this->fd = Pulsar::Open(this->path, (IOS::Mode)mode);
    s32 ret = IOS::Seek(this->fd, 0, IOS::SEEK_END);
    if (ret < 0) ret = 0;
    this->fileSize = ret;
    IOS::Seek(this->fd, 0, IOS::SEEK_START);
    return this->fd;
}

s32 File::CreateAndOpen(const char *path, u32 mode) {
    char realPath[IPCMAXPATH];
    this->GetCorrectPath(realPath, path);
    ISFS::CreateFile(realPath, 0, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE);
    return this->Open(path, mode);
}

void File::GetCorrectPath(char *realPath, const char *path) const {
    snprintf(realPath, IPCMAXPATH, "%s%s", "/title/00010004", path);
}

s32 File::GetDevice_fd() const {
    return IOS::fs_fd;
}

s32 File::Read(void *buffer, u32 length) {
    if (this->fd < 0) return -1;
    return IOS::Read(this->fd, buffer, length);
}

s32 File::Write(u32 length, void *buffer) {
    if (this->fd < 0) return -1;
    return IOS::Write(this->fd, buffer, length);
}

s32 File::Overwrite(u32 length, void *buffer) {
    if (this->fd < 0) return -1;
    IOS::Seek(this->fd, 0, IOS::SEEK_START);
    return IOS::Write(this->fd, buffer, length);
}

void File::Close() {
    if (this->fd >= 0) IOS::Close(this->fd);
    this->fd = -1;
    this->fileSize = 0;
}

s32 RiivoFile::Open(const char *path, u32 mode) {
    return File::Open(path, this->GetRiivoMode(mode));
}

s32 RiivoFile::CreateAndOpen(const char *path, u32 mode) {
    s32 riivo_fd = this->GetDevice_fd();
    IOS::IOCtl(riivo_fd, (IOS::IOCtlType)RIIVO_IOCTL_CREATEFILE, (void *)path, strlen(path) + 1, NULL, 0);
    IOS::Close(riivo_fd);
    return this->Open(path, mode);
}

s32 RiivoFile::GetDevice_fd() const {
    return Pulsar::Open("file", IOS::MODE_NONE);
}

void RiivoFile::GetCorrectPath(char *realPath, const char *path) const {
    snprintf(realPath, IPCMAXPATH, "%s%s", "file", path);
}

RiivoMode RiivoFile::GetRiivoMode(u32 mode) const {
    if ((mode & 0x3) != 0) mode -= 1;
    return (RiivoMode)mode;
}
}//namespace PulsarIO










