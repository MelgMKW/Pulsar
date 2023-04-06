#ifndef _MESSAGEWINDOWCONTROL_
#define _MESSAGEWINDOWCONTROL_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>

class MessageWindowControl : public LayoutUIControl {
    MessageWindowControl(); //805f9700
    ~MessageWindowControl() override; //805f973c vtable 808b9ee0
    int GetRuntimeTypeInfo() const override; //0x28 805f9e40
    const char *GetClassName() const override; //0x2c 805f96f4
    void Load(const char *folderName, const char *ctrName, const char *variant); //805f9794
}; //total size 0x174

class MessageWindowControlScaleFade : public LayoutUIControl {
    MessageWindowControlScaleFade(); //805f9820
    ~MessageWindowControlScaleFade() override; //805f985c vtable 808b9ea4
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //805f98b8 0x20
    int GetRuntimeTypeInfo() const override; //0x28 805f9e34
    const char *GetClassName() const override; //0x2c 805f9810
}; //total size 0x174

class SimpleMessageWindowControl : public LayoutUIControl {
    SimpleMessageWindowControl(); //805f9900
    ~SimpleMessageWindowControl() override; //805f993c virtual 808b9e68
    void InitSelf() override; //0x18 805f9a48
    int GetRuntimeTypeInfo() const override; //0x28 805f9e28
    const char *GetClassName() const override; //0x2c 805f98f0
    void Load(const char *folderName, const char *ctrName, const char *variant); //805f9994
}; //total size 0x174

class BlackBackControlForMessage : public LayoutUIControl {
    BlackBackControlForMessage(); //805f9abc
    ~BlackBackControlForMessage() override; //805f9af8 vtable 808b9e2c
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //805f9bc4
    int GetRuntimeTypeInfo() const override; //0x28 805f9e1c
    const char *GetClassName() const override; //0x2c 805f9aac
    void Load(const char *folderName, const char *ctrName, const char *variant); //805f9b50
}; //total size 0x174

class BusySymbol : public LayoutUIControl {
    BusySymbol(); //805f9c34
    ~BusySymbol() override; //805f9c70 vtable 808b9df0
    void InitSelf() override; //805f9d5c 0x18
    void OnUpdate() override; //805f9df4 0x1c
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //805f9d94
    int GetRuntimeTypeInfo() const override; //0x28 805f9e10
    const char *GetClassName() const override; //0x2c 805f9c24
    void Load(const char *folderName, const char *ctrName, const char *variant); //805f9cc8
}; //total size 0x174

#endif