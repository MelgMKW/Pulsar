#ifndef _CTRLRACE2DMAP_
#define _CTRLRACE2DMAP_
#include <kamek.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>

//_sinit_ at 807ebeec

class CtrlRace2DMapObject : public CtrlRaceBase { //used as a base for other objects but also used for the start line as is
    ~CtrlRace2DMapObject() override; //807ea930 vtable 808d3900
    void InitSelf() override; //0x18 807eac2c
    void OnUpdate() override; //0x1c 807eac88
    int GetRuntimeTypeInfo() const override; //0x28 807ebe78
    const char *GetClassName() const override; //0x2c 807eac1c
    virtual void CalculatePosition(); //0x50 807eacfc
    virtual void SetMapPosition(Vec3 *translation); //0x54 807eaa88
    virtual void SetMapRotation(Vec3 *rotation); //0x58 807eaaa4
    virtual char *GetPaneName() const; //0x5c 807eac7c
    nw4r::lyt::Pane *pane;
    Vec3 mapPosition; //0x19c
    Vec3 mapRotation; //0x1a0
}; //0x1b4

class CtrlRace2DMapCharacter : public CtrlRace2DMapObject {
    CtrlRace2DMapCharacter(); //807ea89c
    ~CtrlRace2DMapCharacter() override; //807ea98c vtable 808d389c
    void InitSelf() override; //0x18 807eaecc
    void OnUpdate() override; //0x1c 807eb250
    int GetRuntimeTypeInfo() const override; //0x28 807ebe6c
    const char *GetClassName() const override; //0x2c 807eadf0
    void CalculatePosition() override; //0x50 807eb3cc
    char *GetPaneName() const override; //0x5c 807ebe60
    virtual void Load(u8 index); //0x60 807eae00
    u8 unknown_0x1b4[0x1CC - 0x1B4];
}; //total size 0x1cc

class CtrlRace2DMapBossObj : public CtrlRace2DMapObject {
    CtrlRace2DMapBossObj(); //807ea9ec
    ~CtrlRace2DMapBossObj() override; //807eaa28 vtable 808d3838
    void InitSelf() override; //0x18 807eba60
    void OnUpdate() override; //0x1c 807ebd50
    int GetRuntimeTypeInfo() const override; //0x28 807ebe54
    const char *GetClassName() const override; //0x2c 807eb9f8
    char *GetPaneName() const override; //0x5c 807ebe48
    virtual void Load(u8 index); //0x60 807eba08
    u8 unknown_0x1b4[0x1bc - 0x1b4];
}; //total size 0x1bc

class CtrlRace2DMap : public CtrlRaceBase { //has children controls such as start line
    ~CtrlRace2DMap() override; //807ebe84 vtable 808d3960
    void InitSelf() override; //807eaac0
    void OnUpdate() override; //807eab3c
    int GetRuntimeTypeInfo() const override; //807ebee0
    const char *GetClassName() const override; //807ea270
    void Load(const char *variant); //807ea27c
    nw4r::lyt::TexMap *texMap; //0x198
    CtrlRace2DMapCharacter *characters; //0x19c size playerCount
    CtrlRace2DMapBossObj *boosObjs; //0x1a0
}; //0x1a4
size_assert(CtrlRace2DMap, 0x1a4);

#endif