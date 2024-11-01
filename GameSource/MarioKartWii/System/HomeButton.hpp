#ifndef _HOMEMENUMGR_
#define _HOMEMENUMGR_
#include <kamek.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/rvl/HBM/HBM.hpp>

class HomeMenuMgr {
public:
    static HomeMenuMgr* sInstance; //809bd6f8
    static HomeMenuMgr* CreateInstance(EGG::Heap* heap); //8051d4d4
    static void DestroyInstance(); //8051d534

    HomeMenuMgr(EGG::Heap* heap); //8051d6a0
    virtual ~HomeMenuMgr(); //8051d584 vtable 808b2d80
    //HomeBtn_ENG.szs/SpeakerSe.arc/home.csv/config.txt/homeBtnIcon.tpl

    void* LoadHBMArc(const char* name, EGG::Heap* heap, bool decode, u32* decodedSize = nullptr); //8051d5e8
    void ResetControllerData(); //8051d894 inlined
    void Open(); //8051d918 inlined
    void Close(); //8051d9f4

    void UpdateControllerData(HBM::ControllerData& controllerData); //8051dd70
    void UpdateLockParams(); //8051df78
    void Calc(); //8051e114
    void Draw(); //8051e7e8

    HBM::DataInfo dataInfo; //0x8
    void* homeBtnIconTPL; //0x48
    bool isActive; //0x4c
    bool isAllowed; //0x4d if false, home button cannot be opened
    u8 padding[2];
    u32 lastTickButtonWasPressedWhileLocked; //0x50 time hbm was pressed and rejected
    u8 lockStuff[0x8]; //0x54
    HBM::ControllerData controllerData; //0x5c
    KPAD::Status status[4]; //0x9c

    HBM::SelectBtnNum selectBtnNum; //0x2ac
    bool pointerStatusBeforeActivation[4]; //0x2b0 so that they can be restored
}; //0x2b4


#endif