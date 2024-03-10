/*
#include <PulsarSystem.hpp>
#include <MarioKartWii/File/RKG.hpp>

void FixRKG(RKG* rkg, RKG* decompressed){
    rkg->DecompressTo(*decompressed);
    for (int i = 0; i < decompressed->inputs.actionInputsCount; i++) decompressed->inputs.actionInputs[i].value &= ~0x20;
    rkg->ClearBuffer();
    decompressed->CompressTo(*rkg);
}

void FixAllRKGs(){
    const char* modFolderName = Pulsar::System::sInstance->GetModFolder();
    char folderPath[64];
    snprintf(folderPath, 64, "%s/temp", modFolderName);
    Pulsar::IO* io = Pulsar::IO::sInstance;
    io->ReadFolder(folderPath);
    int fileCount = io->GetFileCount();
    char filePath[64];
    RKG* compressed = io->Alloc<RKG>(sizeof(RKG));
    RKG* decompressed = io->Alloc<RKG>(sizeof(RKG));
    for (int i = 0; i < fileCount; i++)
    {
        compressed->ClearBuffer();
        decompressed->ClearBuffer();
        io->ReadFolderFile(compressed, i, sizeof(RKG));
        FixRKG(compressed, decompressed);
        io->GetFolderFilePath(filePath, i);
        io->OpenFile(filePath, Pulsar::FILE_MODE_WRITE);
        io->Overwrite(compressed->GetLength(), compressed);
        io->Close();
    }
    delete compressed;
    delete decompressed;
}

BootHook FixRKGsHook(FixAllRKGs, 4);
*/