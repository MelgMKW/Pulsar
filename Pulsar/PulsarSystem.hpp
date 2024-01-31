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

class Config {
public:
    void Destroy(u32 size) {
        memset(this, 0, size);
        delete(this);
    }
    static const char error[];
    static Config* LoadConfig(u32* readBytes);
    template <typename T>
    inline const T& GetSection() const;

    template <class T>
    inline void CheckSection(const T& t) const { if(t.header.magic != T::magic) Debug::FatalError(error); }

    static const u32 magic = 'PULS';
    BinaryHeader header;
    InfoHolder infoHolder;
    CupsHolder cupsHolder;
    //BMGHeader rawBmg;
};

template<>
inline void Config::CheckSection<BMGHeader>(const BMGHeader& bmg) const {
    if(bmg.magic != 0x4D455347626D6731) Debug::FatalError(error);
}

template<>
inline const Config& Config::GetSection() const {
    return *this;
}
template<>
inline const InfoHolder& Config::GetSection<InfoHolder>() const {
    const InfoHolder& infoHolder = *reinterpret_cast<const InfoHolder*>(ut::AddU32ToPtr(this, this->header.offsetToInfo));
    CheckSection(infoHolder);
    return infoHolder;
}
template<>
inline const CupsHolder& Config::GetSection<CupsHolder>() const {
    const CupsHolder& cupsHolder =  *reinterpret_cast<const CupsHolder*>(ut::AddU32ToPtr(this, this->header.offsetToCups));
    CheckSection(cupsHolder);
    return cupsHolder;
}
template<>
inline const BMGHeader& Config::GetSection<BMGHeader>() const {
    const BMGHeader& bmg = *reinterpret_cast<const BMGHeader*>(ut::AddOffsetToPtr(this, this->header.offsetToBMG));
    CheckSection(bmg);
    return bmg;
}


class System {
protected:
    System();
private:
    //System functions
    void Init(const Config& bin);
    void InitInstances(const Config& bin) const {
        CupsDef::sInstance = new CupsDef(bin.GetSection<CupsHolder>().cups);
        Info::sInstance = new Info(bin.GetSection<InfoHolder>().info);
        this->InitIO();
        this->InitSettings(defaultSettingsPageCount, &bin.GetSection<CupsHolder>().cups.trophyCount[0]);
    }
    void InitIO() const;
    void InitCups(const Config& bin);

protected:
    static const u32 defaultSettingsPageCount = 5;
    //Virtual
    virtual void InitSettings(u32 pageCount, const u16* totalTrophyCount) const;
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
    bool isCustomDeny;
    u8 deniesCount;
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