#include <include/c_string.h>
#include <dev/Sdi.hpp>
#include <core/rvl/ipc/ipc.hpp>
#include <core/rvl/OS/OS.hpp>

#include <IO/IO.hpp>

namespace Pulsar {

void FATIO::Convert(wchar_t* dest, const char* src) const {
    swprintf(dest, IOS::ipcMaxPath, L"%s", src);
}

void FATIO::CreateFolder(const char* path) {
    wchar_t convPath[IOS::ipcMaxPath];
    Convert(convPath, path);
    FRESULT ret = f_mkdir(convPath);
    //return ret == FR_OK;
}

void FATIO::ReadFolder(const char* path) {
    this->Bind(path);
    wchar_t convPath[IOS::ipcMaxPath];
    Convert(convPath, path);

    FRESULT ret = f_opendir(&dir, convPath);
    if(ret == FR_OK) {
        FILINFO info;
        int idx = 0;
        do {
            ret = f_readdir(&dir, &info);
            if(ret != FR_OK) break;
            this->dir_ofs[idx] = info.dir_ofs;
            idx++;
        } while(info.fname[0] != 0);
        this->fileCount = idx - 1;
    }

    //return ret == FR_OK;
}

s32 FATIO::ReadFolderFile(void* buffer, u32 index, u32 mode, u32 maxLength) {
    FRESULT ret = f_fastopen(&file, &m_fs, this->dir_ofs[index]);

    if(ret == FR_OK) {
        u32 br;
        f_read(&file, buffer, maxLength, &br);
        f_close(&file);
        return br;
    }
    return -1;
}

bool FATIO::FolderExists(const char* path) const {
    wchar_t convPath[IOS::ipcMaxPath];
    Convert(convPath, path);

    DIR tmpDir;
    FRESULT ret = f_opendir(&tmpDir, convPath);
    if(ret == FR_OK) f_closedir(&tmpDir);
    return ret == FR_OK;
}

void FATIO::CloseFolder() {
    f_closedir(&dir);
}

bool FATIO::OpenModFile(const char* path, u32 mode) {
    u32 f_mode = FA_OPEN_EXISTING;

    switch(mode) {
        case FILE_MODE_READ:
            f_mode |= FA_READ;
        case FILE_MODE_WRITE:
            f_mode |= FA_WRITE;
        case FILE_MODE_READ_WRITE:
            f_mode |= FA_READ | FA_WRITE;
    }
    wchar_t convPath[IOS::ipcMaxPath];
    Convert(convPath, path);
    return f_open(&file, convPath, f_mode) == FR_OK;
}

bool FATIO::CreateAndOpen(const char* path, u32 mode) {
    u32 f_mode = FA_CREATE_NEW;

    switch(mode) {
        case FILE_MODE_READ:
            f_mode |= FA_READ;
        case FILE_MODE_WRITE:
            f_mode |= FA_WRITE;
        case FILE_MODE_READ_WRITE:
            f_mode |= FA_READ | FA_WRITE;
    }
    wchar_t convPath[IOS::ipcMaxPath];
    Convert(convPath, path);
    return f_open(&file, convPath, f_mode) == FR_OK;

}


s32 FATIO::Read(u32 size, void* bufferIn) {
    u32 br;
    FRESULT ret = f_read(&file, bufferIn, size, &br);
    if(ret != FR_OK) return -1;
    return br;
}
void FATIO::Seek(u32 offset) {
    f_lseek(&file, offset);
}
s32 FATIO::Write(u32 length, const void* buffer) {
    u32 bw;
    FRESULT ret = f_write(&file, buffer, length, &bw);
    if(ret != FR_OK) return -1;
    return bw;
}

s32 FATIO::Overwrite(u32 length, const void* buffer) {
    FATIO::Seek(0);
    return FATIO::Write(length, buffer);
}

void FATIO::Close() {
    f_close(&file);
}







}//namespace Pulsar
