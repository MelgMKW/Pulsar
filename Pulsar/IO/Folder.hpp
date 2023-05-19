#ifndef _FOLDERLOADER_
#define _FOLDERLOADER_
#include <kamek.hpp>
#include <IO/File.hpp>

namespace Pulsar {
namespace IO {
class Folder { //Wraps around File and is also able to Create/Read folders
public:

    struct CreateRequest {
        CreateRequest() : isFree(true) {};
        bool isFree;
        char path[IOS::ipcMaxPath];
    };
    
    Folder(IOType type, EGG::Heap* heap, EGG::TaskThread* const taskThread) : isBusy(false), fileCount(0), fileNames(nullptr),
        heap(heap), taskThread(taskThread), type(type) {}
    static Folder* sInstance;
    static Folder* CreateStaticInstance(IOType type, EGG::Heap* heap, EGG::TaskThread* const taskThread);

    virtual bool FolderExists(const char* path) const;
    virtual void CreateFolder(const char* path);
    virtual void ReadFolder(const char* path);

    void RequestCreateFolder(const char* path); //up to 2 simultaneous
    void CloseFolder();
    void GetCorrectPath(char* realPath, const char* path) const { this->curFile->GetCorrectPath(realPath, path); }
    const char* GetName() const { return this->folderName; };
    const int GetFileCount() const { return this->fileCount; }
    void GetFilePath(char* dest, u32 index) const;
    s32 ReadFile(void* buffer, u32 index, u32 mode, u32 maxLength);
    void CloseFile() { this->curFile->Close(); }

private:
    static void CreateFolderAsync(CreateRequest* request);
protected:
    void Bind(const char* path) { strncpy(this->folderName, path, IOS::ipcMaxPath); }

private:
    EGG::Heap* const heap;
    EGG::TaskThread* const taskThread;
    CreateRequest requests[2];
    const IOType type;

protected:
    u32 fileCount;
    IOS::IPCPath* fileNames;
    bool isBusy;
    char folderName[IOS::ipcMaxPath];
    File* curFile;

};

class RiivoFolder : public Folder {
public:
    RiivoFolder(EGG::Heap* heap, EGG::TaskThread* const taskThread) : Folder(IOType_RIIVO, heap, taskThread) {}
    bool FolderExists(const char* path) const override;
    void CreateFolder(const char* path) override;
    //virtual void GetFilePath(char *path, u32 index);
    void ReadFolder(const char* path) override;
};

}//namespace IO
}//namespace Pulsar
#endif