/*
 * This file is part of Cosmos and was taken from https://github.com/Gabriela-Orzechowska/MKW-Cosmos/blob/main/code/System/WUP028.cpp
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

#include <core/rvl/OS/OSCache.hpp>
#include <Extensions/Cosmos/WUP028.hpp>
#include <PulsarSystem.hpp>

namespace Cosmos {

WUP028Manager* WUP028Manager::sInstance = nullptr;

void WUP028Manager::OnInit() {
    this->lastDataWrite = OS::GetTime();
    this->isStarted = true;
    s32 ret = IOS::Open("/dev/usb/hid", IOS::MODE_NONE);
    if (ret < 0) {
        this->isWorking = false;
        return;
    }

    this->hidFd = ret;
    s32 ret4 = IOS::IOCtl(this->hidFd, IOS::IOCTL_HID4_GET_VERSION, nullptr, 0, nullptr, 0);

    if (ret4 == 0x40001) {
        this->hidVersion = 4;
        OnInitVer4();
    }
    else {
        s32 ret5 = IOS::IOCtl(this->hidFd, IOS::IOCTL_HID5_GET_VERSION, nullptr, 0, nullptr, 0);
        if (ret5 == 0x50001) {
            this->hidVersion = 5;
            //OnInitVer5();
        }
        else {
            this->hidVersion = -1;
        }
    }
}

void WUP028Manager::CustomPADRead(PAD::Status* status) {
    if (!this->isStarted) return;
    if (this->isWorking && this->isInit) {
        if (OS::TicksToMilliseconds(OS::GetTime() - this->lastDataWrite) > GCN_TIMEOUT_MS) {
            for (int i = 0; i < 4; i++) this->status[i].error = -1;
        }
        for (int i = 0; i < 4; i++) {
            {
                const u32 compareVal = 3;
                if (
                    ut::Abs(status[i].triggerL - this->status[i].triggerL) > compareVal ||
                    ut::Abs(status[i].triggerR - this->status[i].triggerR) > compareVal ||
                    ut::Abs(status[i].stickX - this->status[i].stickX) > compareVal ||
                    ut::Abs(status[i].stickY - this->status[i].stickY) > compareVal ||
                    ut::Abs(status[i].cStickX - this->status[i].cStickX) > compareVal ||
                    ut::Abs(status[i].cStickY - this->status[i].cStickY) > compareVal ||
                    status[i].buttons != this->status[i].buttons) {
                    VI::ResetSIIdle();
                }
            }

            status[i] = this->status[i];
        }
    }
    else PAD::Read(status);
}

void PatchPADRead(PAD::Status* status) {
    WUP028Manager* mgr = WUP028Manager::GetStaticInstance();
    if (mgr) mgr->CustomPADRead(status);
}
kmCall(0x80523910, PatchPADRead);
kmCall(0x805237c4, PatchPADRead);
kmCall(0x80217464, PatchPADRead);
kmCall(0x80007880, PatchPADRead);

static alignas(0x20) u8 InitMsgBuffer[1] = { CMD_INIT, };
static alignas(0x20) u8 PollMsgBuffer[(POLL_SIZE + 0x1f) & ~0x1f];
static alignas(0x20) u8 RumbleMsgBuffer[5]  = { CMD_RUMBLE, };
static alignas(0x20) InterruptMsg4 InitMsg4  = { 0, 0, 0, 0, -1, ENDPOINT_OUT, sizeof(InitMsgBuffer), InitMsgBuffer };
static alignas(0x20) InterruptMsg4 PollMsg4  = { 0, 0, 0, 0, -1, ENDPOINT_IN, POLL_SIZE, PollMsgBuffer };
static alignas(0x20) InterruptMsg4 RumbleMsg4  = { 0, 0, 0, 0, -1, ENDPOINT_OUT, sizeof(RumbleMsgBuffer), RumbleMsgBuffer };

void WUP028Manager::OnUsbPoll(s32 ret) {
    if (ret >= 0) {
        this->isWorking = true;
        if (*PollMsgBuffer == 0x21) {
            s32 isr = OS::DisableInterrupts();
            for (int i = 0; i < 4; i++) {
                u8* data = PollMsgBuffer + (i * 9 + 1);
                u8 status = data[0] >> 4;
                if (status != 1 && status != 2) {
                    this->status[i].error = -1;
                    continue;
                }
                u16 buttonData = ((data[1] >> 0) & 1 ? PAD::PAD_BUTTON_A : 0);
                buttonData |= ((data[1] >> 1) & 1 ? PAD::PAD_BUTTON_B : 0);
                buttonData |= ((data[1] >> 2) & 1 ? PAD::PAD_BUTTON_X : 0);
                buttonData |= ((data[1] >> 3) & 1 ? PAD::PAD_BUTTON_Y : 0);
                buttonData |= ((data[1] >> 4) & 1 ? PAD::PAD_BUTTON_LEFT : 0);
                buttonData |= ((data[1] >> 5) & 1 ? PAD::PAD_BUTTON_RIGHT : 0);
                buttonData |= ((data[1] >> 6) & 1 ? PAD::PAD_BUTTON_DOWN : 0);
                buttonData |= ((data[1] >> 7) & 1 ? PAD::PAD_BUTTON_UP : 0);
                buttonData |= ((data[2] >> 0) & 1 ? PAD::PAD_BUTTON_START : 0);
                buttonData |= ((data[2] >> 1) & 1 ? PAD::PAD_BUTTON_Z : 0);
                buttonData |= (data[7] >= GCN_TRIGGER_THRESHOLD ? PAD::PAD_BUTTON_L : 0);
                buttonData |= (data[8] >= GCN_TRIGGER_THRESHOLD ? PAD::PAD_BUTTON_R : 0);

                PAD::Status& gcn = this->status[i];
                gcn.buttons = buttonData;
                gcn.stickX = data[3] - 128;
                gcn.stickY = data[4] - 128;
                gcn.cStickX = data[5] - 128;
                gcn.cStickY = data[6] - 128;
                gcn.triggerL = data[7];
                gcn.triggerR = data[8];
                gcn.analogA = 0;
                gcn.analogB = 0;
                gcn.error = 0;
            }
            this->lastDataWrite = OS::GetTime();
            OS::RestoreInterrupts(isr);
        }
        OS::DCFlushRange(PollMsgBuffer, sizeof(PollMsgBuffer));
        ret = IOS::IOCtlAsync(this->hidFd, IOS::IOCTL_HID4_INTERRUPT_IN,
            &PollMsg4, sizeof(PollMsg4), nullptr, 0,
            WUP028Manager::OnUsbPollCallback, nullptr);
    }
    if (ret) OnError();
}

void WUP028Manager::OnInitVer4() {
    s32 ret = IOS::IOCtlAsync(this->hidFd, IOS::IOCTL_HID4_GET_DEVICE_CHANGE,
        nullptr, 0, &this->deviceChangeSizeBuffer, 0x600,
        WUP028Manager::OnUsbChangeVer4Callback, nullptr);
}

void WUP028Manager::OnUsbChangeVer4(s32 hid) {

    if (hid >= 0) {
        bool found = false;
        for (int i = 0; i < 0x180 && this->deviceChangeSizeBuffer[i] < 0x600; i += this->deviceChangeSizeBuffer[i] / 4) {
            if (this->deviceChangeSizeBuffer[i] == USB_DESCRIPTOR_SIZE &&
                this->deviceChangeSizeBuffer[i + 4] == DEVICE_ID) {
                found = true;
                u32 deviceId = this->deviceChangeSizeBuffer[i + 1];
                if (adapterId != deviceId) {
                    this->adapterId = deviceId;
                    InitMsg4.device = this->adapterId;
                    (void)IOS::IOCtlAsync(this->hidFd, IOS::IOCTL_HID4_INTERRUPT_OUT,
                        &InitMsg4, sizeof(InitMsg4), nullptr, 0,
                        WUP028Manager::OnUsbInitVer4Callback, nullptr);
                }
                break;
            }
            if (!found) {
                this->adapterId = -1U;
                this->isInit = true;
                this->isWorking = false;
            }
            hid = IOS::IOCtlAsync(this->hidFd, IOS::IOCTL_HID4_GET_DEVICE_CHANGE,
                nullptr, 0, this->deviceChangeSizeBuffer, 0x600,
                WUP028Manager::OnUsbChangeVer4Callback, nullptr);
        }
    }
    if (hid) OnError();
}

void WUP028Manager::OnUsbInitVer4(s32 ret) {
    if (ret >= 0) {
        this->isInit = true;
        PollMsg4.device = this->adapterId;
        OS::DCFlushRange(PollMsgBuffer, sizeof(PollMsgBuffer));
        ret = IOS::IOCtlAsync(this->hidFd, IOS::IOCTL_HID4_INTERRUPT_IN,
            &PollMsg4, sizeof(PollMsg4), nullptr, 0,
            WUP028Manager::OnUsbPollCallback, nullptr);
    }
    else OnError();
}

void WUP028Manager::CreateStaticInstance() {
    sInstance = new (Pulsar::System::sInstance->heap, 0x40) WUP028Manager;
    if (sInstance) {
        sInstance->OnInit();
    }
}
static BootHook CreateWUP(WUP028Manager::CreateStaticInstance, 4);
}//namespace Cosmos