#ifndef _THP_
#define _THP_
#include <kamek.hpp>

struct THPHeader {
    char magic[4]; //"THP"
    u32 version; //0x11000 in mkw
    u32 maxBufferSize; //0x8
    u32 maxAudioSamples; //0xc
    float framerate; //0x10
    u32 frameCount; //0x14
    u32 firstFrameLength;
    u32 offsetToComponent;
    u32 offsetData;
    u32 offsetTo1stFrame;
    u32 offsetToLastFrame;
}; //total size 0x30

struct THPMovieParams {
    u32 width;
    u32 height;
    u32 format;
}; //0xC

struct THPAudioParams {
    u32 channelCount;
    u32 frequency;
    u32 sampleCount;
    u32 trackCount;
}; //0x10

struct THPParams {
    THPMovieParams movieParams;
    THPAudioParams audioParams;
};

struct THPComponent {
    u32 componentCount;
    s16 componentTypes[16];
    THPParams params;
};

#endif