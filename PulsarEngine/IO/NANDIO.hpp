#ifndef _NANDIO_
#define _NANDIO_

#include <kamek.hpp>
#include <PulsarSystem.hpp>
#include <IO/IO.hpp>

namespace Pulsar {

typedef char FileName[255];


class NANDIO : public IO {

    NANDIO(IOType type, EGG::Heap* heap, EGG::TaskThread* taskThread) : IO(type, heap, taskThread) {}

    bool OpenFile(const char* path, u32 mode) override;
    bool CreateAndOpen(const char* path, u32 mode) override;
    void GetCorrectPath(char* realPath, const char* path) const override;
    bool RenameFile(const char* oldPath, const char* newPath) const override;

    bool FolderExists(const char* path) const override;
    bool CreateFolder(const char* path) override;
    void ReadFolder(const char* path) override;

    friend IO* IO::CreateInstance(IOType type, EGG::Heap* heap, EGG::TaskThread* const taskThread);




};


}//namespace Pulsar

#endif