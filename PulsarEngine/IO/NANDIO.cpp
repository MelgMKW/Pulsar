#include <kamek.hpp>
#include <PulsarSystem.hpp>
#include <IO/NANDIO.hpp>

namespace Pulsar {

//Virtual Funcs
bool NANDIO::CreateAndOpen(const char* path, u32 mode) {
    this->GetCorrectPath(this->filePath, path);
    ISFS::CreateFile(this->filePath, 0, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE);
    return this->OpenFileDirectly(this->filePath, mode);
}

bool NANDIO::OpenFile(const char* path, u32 mode) {
    this->GetCorrectPath(this->filePath, path);
    return this->OpenFileDirectly(this->filePath, mode);
}

void NANDIO::GetCorrectPath(char* realPath, const char* path) const {
    snprintf(realPath, IOS::ipcMaxPath, "%s%s", "/shared2/Pulsar", path);
    //nand::GenerateAbsPath(realPath, path);
}

//FOLDER
//Virtual funcs
bool NANDIO::FolderExists(const char* path) const {
    char realPath[IOS::ipcMaxPath];
    this->GetCorrectPath(realPath, path);
    u32 count;
    return ISFS::ReadDir(realPath, nullptr, &count) >= 0;
}

bool NANDIO::CreateFolder(const char* path) {
    if(type != IOType_ISO) {
        this->Bind(path);
        char realPath[IOS::ipcMaxPath];
        this->GetCorrectPath(realPath, path);
        s32 error = ISFS::CreateDir(realPath, 0, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE, IOS::MODE_READ_WRITE);
        return error >= 0 || error == ISFS::ERROR_FILE_EXISTS;
    }
    return false;
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

bool NANDIO::RenameFile(const char* oldPath, const char* newPath) const {
    char realOldPath[IOS::ipcMaxPath];
    char realNewPath[IOS::ipcMaxPath];
    this->GetCorrectPath(realOldPath, oldPath);
    this->GetCorrectPath(realNewPath, newPath);
    return ISFS::Rename(realOldPath, realNewPath) >= 0;
}

}//namespace Pulsar