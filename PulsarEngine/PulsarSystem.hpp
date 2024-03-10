#ifndef _PULSAR_
#define _PULSAR_

#include <kamek.hpp>
#include <core/rvl/ipc/ipc.hpp>
#include <core/RK/RKSystem.hpp>
#include <MarioKartWii/UI/Text.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <Debug/Debug.hpp>
#include <IO/IO.hpp>
#include <Info.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <Network/MatchCommand.hpp>

namespace Pulsar {

enum TTMode {
    TTMODE_150,
    TTMODE_200,
    TTMODE_150_FEATHER,
    TTMODE_200_FEATHER
};

enum SectionIndexes {
    SECTION_INFO,
    SECTION_CUPS,
    SECTION_BMG
};

struct BinaryHeader {
    static const u32 curVersion = 2;
    u32 magic;
    s32 version;
    s32 offsets[3];
    //s32 offsetToInfo; //from start of the header
    //s32 offsetToCups;
    //s32 offsetToBMG;
    char modFolderName[IOS::ipcMaxFileName + 1];
};

struct SectionHeader {
    u32 magic;
    u32 version;
    u32 size;
}; //0xc

struct InfoHolder {
    static const u32 magic = 'INFO';
    static const u32 index = SECTION_INFO;
    static const u32 curVersion = 1;
    SectionHeader header;
    Info info;
};
struct CupsHolder {
    static const u32 magic = 'CUPS';
    static const u32 index = SECTION_CUPS;
    static const u32 curVersion = 2;
    SectionHeader header;
    u16 ctsCupCount;
    u8 regsMode;
    u8 padding[1];
    u16 trophyCount[4];
    Track tracks[1];
    //u16 alphabeticalIdx[1]; //slot 0's value = track index of the first track by alphabetical order
};

struct PulBMG {
    static const u32 index = SECTION_BMG;
    BMGHeader header;
};

struct ConfigFile {
    void Destroy(u32 size) {
        memset(this, 0, size);
        delete(this);
    }
    static const char error[];
    static ConfigFile* LoadConfig(u32* readBytes);
    template <typename T>
    inline const T& GetSection() const {
        const T& section = *reinterpret_cast<const T*>(ut::AddU32ToPtr(this, this->header.offsets[T::index]));
        return section;
    }

    template <class T>
    static inline void CheckSection(const T& t) { if(t.header.magic != T::magic || t.header.version != T::curVersion) Debug::FatalError(error); }

    static const u32 magic = 'PULS';
    BinaryHeader header;
    //InfoHolder infoHolder;
    //CupsHolder cupsHolder;
    //BMGHeader rawBmg;
};

template<>
static inline void ConfigFile::CheckSection<PulBMG>(const PulBMG& bmg) {
    if(bmg.header.magic != 0x4D455347626D6731) Debug::FatalError(error);
}

class System {
protected:
    System();
private:
    //System functions
    void Init(const ConfigFile& bin);
    void InitInstances(const ConfigFile& bin, IOType type) const {
        CupsConfig::sInstance = new CupsConfig(bin.GetSection<CupsHolder>());
        Info::sInstance = new Info(bin.GetSection<InfoHolder>().info);
        this->InitIO(type);
        this->InitSettings(defaultSettingsPageCount, &bin.GetSection<CupsHolder>().trophyCount[0]);
    }
    void InitIO(IOType type) const;
    void InitCups(const ConfigFile& bin);
    void InitSettings(u32 pageCount, const u16* totalTrophyCount) const;

protected:
    static const u32 defaultSettingsPageCount = 5;
    //Virtual
    virtual void AfterInit() {};

public:
    virtual void SetUserInfo(Network::ResvInfo::UserInfo& userInfo) {};
    virtual bool CheckUserInfo(const Network::ResvInfo::UserInfo& userInfo) { return true; };
    virtual u8 SetPackROOMMsg() { return 0; } //Only called for hosts
    virtual void ParsePackROOMMsg(u8 msg) {}  //Only called for non-hosts

    static System* sInstance;
    const char* GetModFolder() const { return modFolderName; }
    static void CreateSystem();

    //Network
    static asmFunc GetRaceCount();

    //BMG
    const BMGHolder& GetBMG() const { return customBmgs; }

    EGG::ExpHeap* const heap;
    EGG::TaskThread* const taskThread;
    //Constants

private:
    char modFolderName[IOS::ipcMaxFileName + 1];

public:
    //Network
    bool hasHAW;
    bool disableMiiHeads;
    bool isCustomDeny;
    u8 deniesCount;
    u8 curBlockingArrayIdx;
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
    static const char CommonAssets[];
    static const char breff[];
    static const char breft[];
    static const char* ttModeFolders[];

    struct Inherit {
        //static_assert(is_base_of<System, Child>::value, "Pulsar::System is not a parent of your class");
        typedef System* (*CreateFunc)();
        Inherit(CreateFunc func) {
            //static_assert(inherit == nullptr, "Can only inherit once from Pulsar::System");
            create = func;
            inherit = this;
        }
        CreateFunc create;
    };
    static Inherit* inherit;
    friend class Info;
};
} //namespace Pulsar

#endif