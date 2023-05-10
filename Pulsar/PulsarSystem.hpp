#ifndef _PULSAR_
#define _PULSAR_

#include <kamek.hpp>
#include <core/rvl/ipc/ipc.hpp>
#include <core/RK/RKSystem.hpp>
#include <game/UI/Text.hpp>
#include <game/System/Identifiers.hpp>
#include <Debug/Debug.hpp>
#include <Info.hpp>
#include <SlotExpansion/CupsDef.hpp>
#include <Network/MatchCommand.hpp>

namespace Pulsar {

enum TTMode {
    TTMODE_150,
    TTMODE_200,
    TTMODE_150_FEATHER,
    TTMODE_200_FEATHER
};

struct BinaryHeader {
    u32 magic;
    u32 version;
    s32 offsetToInfo; //from start of the header
    s32 offsetToCups;
    s32 offsetToBMG;
    char modFolderName[IOS::ipcMaxFileName + 1];
};
struct SectionHeader {
    u32 magic;
    u32 version;
    u32 dataSize; //size without the header
}; //0xc

struct InfoHolder {
    static const u32 magic = 'INFO';
    SectionHeader header;
    Info info;
};
struct CupsHolder {
    static const u32 magic = 'CUPS';
    SectionHeader header;
    Cups cups;
};

class Binary {
public:
    void Destroy(u32 size) {
        memset(this, 0, size);
        delete(this);
    }
    static const char error[];
    static Binary* LoadBinary(u32* readBytes);
    template <typename T>
    const T& GetSection() const;

    template <class T>
    void CheckSection(const T& t) const { if(t.header.magic != T::magic) Debug::FatalError(error); }

    static const u32 magic = 'PULS';
    BinaryHeader header;
    InfoHolder infoHolder;
    CupsHolder cupsHolder;
    //BMGHeader rawBmg;
};


class System {
protected:
    System();
private:
    //System functions
    void Init(const Binary& bin);
    void InitInstances(const Binary& bin) {
        CupsDef::sInstance = new CupsDef(bin.GetSection<CupsHolder>().cups);
        Info::sInstance    = new Info(bin.GetSection<InfoHolder>().info);
        this->InitIO();
        this->InitSettings(&bin.GetSection<CupsHolder>().cups.trophyCount[0]);
    }
    void InitIO();
    void InitCups(const Binary& bin);

protected:
    //Virtual
    virtual void InitSettings(const u16* totalTrophyCount);
    virtual void AfterInit() {};
public:
    virtual void SetUserInfo(Network::ResvInfo::UserInfo& userInfo) const {};
    virtual bool CheckUserInfo(const Network::ResvInfo::UserInfo& userInfo) const { return true; };
    virtual u8 SetPackROOMMsg() const { return 0; }
    virtual void ParsePackROOMMsg(u8 msg) const {}

    static System* sInstance;
    const char* GetModFolder() const { return modFolderName; }
    static void CreateSystem();

    //Network
    static asm void GetRaceCount();

    //BMG
    const BMGHolder& GetBMG() const { return customBmgs; }

    //Constants
    EGG::ExpHeap* const heap;
    EGG::TaskThread* const taskThread;

private:
    char modFolderName[IOS::ipcMaxFileName + 1];

public:

    //Network
    bool hasHAW;
    u8 curArrayIdx;
    u8 racesPerGP;
    PulsarId* lastTracks;


    TTMode ttMode;

private:
    //Custom BMGS
    BMGHolder customBmgs;
    BMGHeader* rawBmg;

public:
    //string pool
    static const char pulsarString[];
    static const char UIAssets[];
    static const char CommonAssets[];
    static const char breff[];
    static const char breft[];
    static const char* ttModeFolders[];

    struct Inherit {
        Inherit(System* (*ptr)()) {
            //static_assert(inherit == nullptr, "Can only inherit once from Pulsar::System");
            Create = ptr;
            inherit = this;
        }
        System* (*Create)();
    };
    static Inherit* inherit;
    friend class Info;
};
} //namespace Pulsar

#endif