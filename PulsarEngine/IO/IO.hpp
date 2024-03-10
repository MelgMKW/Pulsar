#ifndef _PULSARIO_
#define _PULSARIO_

#include <kamek.hpp>

namespace Pulsar {

const int maxFileCount = 100;
typedef char FileName[255];

enum IOType {
    IOType_RIIVO = 0,
    IOType_ISO = 1,
    IOType_DOLPHIN = 2
};

enum FileMode {
    FILE_MODE_NONE,
    FILE_MODE_READ,
    FILE_MODE_WRITE,
    FILE_MODE_READ_WRITE = FILE_MODE_READ | FILE_MODE_WRITE
};

class IO {
    struct CreateRequest {
        CreateRequest() : isFree(true) {};
        bool isFree;
        char path[IOS::ipcMaxPath];
    };
    static void CreateFolderAsync(CreateRequest* request);

public:
    static inline s32 OpenFix(const char* path, IOS::Mode mode) {
        asmVolatile(stwu sp, -0x0020 (sp););
        IOS::Open2ndInst(path, mode);
    }

    virtual bool OpenFile(const char* path, u32 mode) = 0;
    virtual bool CreateAndOpen(const char* path, u32 mode) = 0;
    virtual void GetCorrectPath(char* realPath, const char* path) const = 0;
    virtual bool RenameFile(const char* oldPath, const char* newPath) const = 0;

    virtual bool FolderExists(const char* path) const = 0;
    virtual bool CreateFolder(const char* path) = 0;
    virtual void ReadFolder(const char* path) = 0;

    static IO* sInstance;
    static IO* CreateInstance(IOType type, EGG::Heap* heap, EGG::TaskThread* const taskThread);
    template<typename T>
    T* Alloc(u32 size) const { return EGG::Heap::alloc<T>(nw4r::ut::RoundUp(size, 0x20), 0x20, this->heap); }
    s32 GetFileSize();

    bool OpenFileDirectly(const char* path, u32 mode);
    s32 Read(u32 size, void* bufferIn);
    void Seek(u32 offset) { IOS::Seek(this->fd, offset, IOS::SEEK_START); }
    s32 Write(u32 length, const void* buffer);
    s32 Overwrite(u32 length, const void* buffer);
    void Close();

    const int GetFileCount() const { return this->fileCount; }
    const char* GetFolderName() const { return this->folderName; };
    //void RequestCreateFolder(const char* path); //up to 2 simultaneous
    void CloseFolder();
    void GetFolderFilePath(char* dest, u32 index) const;
    s32 ReadFolderFile(void* buffer, u32 index, u32 maxLength);

    const IOType type;

protected:
    IO(IOType type, EGG::Heap* heap, EGG::TaskThread* taskThread) : type(type), fd(-1), heap(heap), taskThread(taskThread) {
        filePath[0] = '\0';
        folderName[0] = '\0';
    }
    void Bind(const char* path) { strncpy(this->folderName, path, IOS::ipcMaxPath); }
    void CloseFile() { this->Close(); }

    EGG::Heap* heap;
    EGG::TaskThread* const taskThread;
    bool isBusy;
    s32 fd;
    s32 fileSize;
    char filePath[IOS::ipcMaxPath];
    char folderName[IOS::ipcMaxPath];
    u32 fileCount;
    IOS::IPCPath* fileNames;
    CreateRequest requests[2];
};



}//namespace Pulsar

#endif