
#ifndef _INPUT_GHOST_WRITER_
#define _INPUT_GHOST_WRITER_
#include <kamek.hpp>

namespace Input {

class GhostStream {
public:
    struct Input {
        u8 value;
        u8 duration;
    };
    enum Mode {
        MODE_WRITE,
        MODE_READ,
        MODE_OFF
    };

    virtual void Write(u8 value) = 0; //0x8 
    virtual u8 Read() = 0; //0xC 
    virtual int GetInputSize() const = 0; //0x10 always returns 2 as each input is a value and a duration
    virtual void WriteNewValue(Input* buffer, u8 value) const = 0; //0x14 
    virtual void IncrementDuration(Input* buffer) const = 0; //0x18 
    virtual bool IsNewInput(const Input* buffer, u8 value) const = 0; //0x1C returns true if curBuffer.value != value && curBuffer.duration < 255
    virtual u8 ReadValue(const Input* buffer) const = 0; //0x20 
    virtual bool IsCurReadInputFinished(const Input* buffer) const = 0; //0x24 
    Input* bufferStart; //0x4 size 0x276c
    s32 curBufferPosition; //0x8 ie written/read inputs
    u32 bufferSize; //0xC 0x276c in write mode, actual rkg buffer size in read mode
    s16 curReadInputDuration; //0x10 incremented by 1 until it reaches the duration of the currently read input and gets reset
    u8 padding[2];
    Mode mode; //0x14
}; //0x18

class GhostActionStream : public GhostStream { //size 0x276c value = buttonAction
    void Write(u8 value) override; //0x8 80522dcc vtable 808b30c8
    u8 Read() override; //0xC 80522f40   
    int GetInputSize() const override; //0x10 805230a8   
    void WriteNewValue(Input* buffer, u8 value) const override; //0x14 80524f78   
    void IncrementDuration(Input* buffer) const override; //0x18 80524f88 increments 2nd u8 by 1 
    bool IsNewInput(const Input* buffer, u8 value) const override; //0x1C 80524f98 returns true if buffer[0] != actions && buffer[1] == FF  
    u8 ReadValue(const Input* buffer) const override; //0x20 80524fbc   
    bool IsCurReadInputFinished(const Input* buffer) const override; //0x24 80524fc4   

}; //0x18

class GhostDirectionStream : public GhostStream { //0x0x276c value = stickX + stickY
    void Write(u8 value) override; //0x8 80522974 vtable 808b30a0
    u8 Read() override; //0xC 80520d4c
    int GetInputSize() const override; //0x10 80520eb4
    void WriteNewValue(Input* buffer, u8 value) const override; //0x14 80524fe0
    void IncrementDuration(Input* buffer) const override; //0x18 80524ff0
    bool IsNewInput(const Input* buffer, u8 value) const override; //0x1C 80525000
    u8 ReadValue(const Input* buffer) const override; //0x20 80525024
    bool IsCurReadInputFinished(const Input* buffer) const override; //0x24 8052502c
}; //0x18

class GhostTrickStream : public GhostStream { //0x4ed8 = 0x276c * 2
    void Write(u8 value) override; //0x8 80522ae8 vtable 808b3078
    u8 Read() override; //0xC 80522c5c
    int GetInputSize() const override; //0x10 80522dc4
    void WriteNewValue(Input* buffer, u8 value) const override; //0x14 80525048
    void IncrementDuration(Input* buffer) const override; //0x18 8052505c
    bool IsNewInput(const Input* buffer, u8 value) const override; //0x1C 80525074
    u8 ReadValue(const Input* buffer) const override; //0x20 8052509c
    bool IsCurReadInputFinished(const Input* buffer) const override; //0x24 805250a8
}; //0x18

struct RKGInputs {
    u16 actionInputsCount;
    u16 directionInputsCount;
    u16 trickInputsCount;
    u16 unused; //presumably for a 4th section.
    GhostStream::Input actionInputs[1]; //0x14 real size  actionInputscount
    //GhostStream::Input directionInputs
    //GhostStream::Input trickInputsCount
    GhostStream::Input padding[0x13b5]; //0x14 actually padded until total length 0x2774
};
//size 0x2774
size_assert(RKGInputs, 0x2774);

class GhostWriter {
public:
    enum Status {
        STATUS_ENABLED = 1,
        STATUS_DISABLED = 2
    };
    GhostWriter(); //0x14 80524ac4
    virtual ~GhostWriter(); //0x14 80524c2c vtable 808b3068
    void WriteFrame(u16 buttonActions, u8 quantisedStickX, u8 quantisedStickY, u8 motionControlFlickUnmirrored); //0x14 80524e74
    void Init(); //80524ca8
    bool IsInputsSumSmallEnough(); //80524dd0 checks that the total buffer size is < 0x2774 bytes, the max rkg size
    u32 CopyToRKGInputBuffer(RKGInputs* rkgBuffer); //80524d20 returns size of buffer
    GhostActionStream* actionStream; //0x14 0x4
    GhostDirectionStream* directionStream; //0x14 0x8
    GhostTrickStream* trickStream; //0x14 0xc
    GhostStream::Input* fullInputBuffer; //0x14 0x10 0x276c * 3
    Status status; //0x14
    u8 unknown_0x18[4];
}; //0x1C 
size_assert(GhostWriter, 0x1c);



}//namespace Input
#endif