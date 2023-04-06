#ifndef _FOLDERLOADER_
#define _FOLDERLOADER_
#include <kamek.hpp>
#include <File/File.hpp>

namespace PulsarIO {
class Folder { //Wraps around Handler and is also able to Create/Read folders
public:
    struct CreateRequest {
        CreateRequest(): isFree(true) {};
        bool isFree;
        char path[IPCMAXPATH];
    };
    Folder(EGG::TaskThread *taskThread): isBusy(false), fileCount(0), fileNames(NULL),
        heap(RKSystem::mInstance.EGGSystem), taskThread(taskThread) {}
    ~Folder() {
        this->CloseFolder();
        delete(this->curFile);
    };
    static Folder *sInstance;
    static Folder *CreateStaticInstance(EGG::TaskThread *taskThread);

    virtual bool FolderExists(const char *path);
    virtual void CreateFolder(const char *path);
    virtual s32 ReadFolder(const char *path);


    void RequestCreateFolder(const char *path); //up to 2 simultaneous
    static void CreateFolderAsync(void *request);
    void Bind(const char *path) { strncpy(this->folderName, path, IPCMAXPATH); }
    void CloseFolder();
    void GetCorrectPath(char *realPath, const char *path) const { this->curFile->GetCorrectPath(realPath, path); }
    const char *GetName() const { return this->folderName; };
    const int GetFileCount() const { return this->fileCount; }
    void GetFilePath(char *dest, u32 index) const;
    s32 ReadFile(void *buffer, u32 index, u32 mode/*, u32 maxLength = 0xFFFFFFFF*/);
    void CloseFile() { this->curFile->Close(); }




protected:
    EGG::Heap *heap;
    EGG::TaskThread *taskThread;
    bool isBusy;
    char folderName[IPCMAXPATH];
    u32 fileCount;
    IOS::IPCPath *fileNames;
    File *curFile;
    CreateRequest requests[2];
};

class RiivoFolder : public Folder {
public:
    RiivoFolder(EGG::TaskThread *taskThread): Folder(taskThread) {}
    bool FolderExists(const char *path) override;
    void CreateFolder(const char *path) override;
    //virtual void GetFilePath(char *path, u32 index);
    s32 ReadFolder(const char *path) override;
};
}//namespace PulsarIO
#endif