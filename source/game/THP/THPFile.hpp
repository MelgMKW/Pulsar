#ifndef _THPFILE_
#define _THPFILE_
#include <kamek.hpp>

namespace THP {
struct Header {
    char magic[4]; //''
    u32 version; //0x11000 in mkw
    u32 maxBufferSize; //0x8
    u32 maxAudioSamples; //0xc
    float framerate; //0x10
    u32 frameCount; //0x14
    u32 firstFrameLength;
    u32 movieDataSize;
    u32 offsetToComponent;
    u32 offsetData;
    u32 offsetTo1stFrame;
    u32 offsetToLastFrame;
}; //total size 0x30

struct VideoInfo {
    u32 width;
    u32 height;
    u32 format;
}; //0xC

struct AudioInfo {
    u32 channelCount;
    u32 frequency;
    u32 sampleCount;
    u32 trackCount;
}; //0x10

struct Params {
    VideoInfo movieParams;
    AudioInfo audioParams;
};

struct FrameCompInfo {
    u32 componentCount;
    s8 componentTypes[16];
};

struct File {
    Header header;
    FrameCompInfo frameCompInfo;
    VideoInfo videoInfo;
    AudioInfo audioInfo;
};

}//namespace THP
#endif