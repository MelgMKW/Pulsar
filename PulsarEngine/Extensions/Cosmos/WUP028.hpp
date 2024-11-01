/*
 * This file is part of Cosmos and was taken from https://github.com/Gabriela-Orzechowska/MKW-Cosmos/blob/main/code/System/WUP028.hpp
 * Copyright (c) 2023-2024 Gabriela Orzechowska
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * This code is based on Alexandra "Chadderz" Chadwick implementation of the module
 * for "BrainSlug".
 *
 * https://github.com/Chadderz121/wup-028-bslug
 *
 * The original license goes as follows:
 *
 *
 *  Copyright (C) 2017, Alex Chadwick
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef _WUP028_
#define _WUP028_

#include <kamek.hpp>
#include <core/RK/RKSystem.hpp>
#include <core/rvl/OS/OS.hpp>
#include <core/rvl/ipc/ipc.hpp>
#include <core/rvl/WPAD.hpp>
#include <core/rvl/PAD.hpp>

namespace Cosmos {
const u32 GCN_CONTROLLER_COUNT = 4;
const u32 GCN_TRIGGER_THRESHOLD = 170;
const u32 GCN_TIMEOUT_MS = 1500;

const u32 USB_DESCRIPTOR_SIZE = 0x44;

enum WUP_VAL {
    CMD_INIT = 0x13,
    CMD_RUMBLE = 0x11,
    POLL_SIZE = 0x25,
    DEVICE_ID = 0x057e0337,
    ENDPOINT_OUT = 0x2,
    ENDPOINT_IN = 0x81,
};

struct InterruptMsg4 {
    u32 padding[4];
    u32 device;
    u32 endpoint;
    u32 size;
    void* ptr;
};

class WUP028Manager {
public:
    WUP028Manager() : isStarted(false), isWorking(false), isInit(false), adapterId(-1U) {}
    static void CreateStaticInstance();
    static WUP028Manager* GetStaticInstance() { return sInstance; }
    void CustomPADRead(PAD::Status* status);

private:
    void OnInit();
    void OnError() {
        isWorking = false;
        this->hidFd = -1U;
    }

    static void OnUsbPollCallback(s32 ret, void* arg) {
        sInstance->OnUsbPoll(ret);
    }
    void OnUsbPoll(s32 ret);

    // Version 4
    void OnInitVer4();
    static void OnUsbChangeVer4Callback(s32 hid, void* arg) {
        sInstance->OnUsbChangeVer4(hid);
    }
    void OnUsbChangeVer4(s32 hid);

    static void OnUsbInitVer4Callback(s32 ret, void* arg) {
        sInstance->OnUsbInitVer4(ret);
    }
    void OnUsbInitVer4(s32 ret);

    bool isStarted;
    bool isWorking;
    bool isInit;
    u8 hidVersion;
    u64 lastDataWrite;
    u32 hidFd;
    u32 adapterId;

    alignas(0x20) u32 deviceChangeSizeBuffer[0x180];
    alignas(0x20) u32 tmpBufferSize[0x20];
    PAD::Status status[4];

    static WUP028Manager* sInstance;
};
}//namespace Cosmos
#endif