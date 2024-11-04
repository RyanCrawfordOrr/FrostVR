/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#include "EmbeddedVoiceChatDevices.h"
#include "GenericPlatform/GenericPlatformOutputDevices.h"
#include "Misc/OutputDeviceFile.h"
#include "Engine/Engine.h"

#include "EmbeddedVoiceChatGlobals.h"

TArray<UEmbeddedVoiceChatDevice *> UEmbeddedVoiceChatDevices::getAvailableDevices() {
#if WITH_EMBEDDEDVOICECHAT
    if (std::shared_ptr<EmbeddedVoiceChat::Devices> spt = this->EmbeddedVoiceChatDevices.lock()) {
        TArray<UEmbeddedVoiceChatDevice *> result;
        for (const auto &elem : spt->getAvailableDevices()) {
            UEmbeddedVoiceChatDevice *device = NewObject<UEmbeddedVoiceChatDevice>();
            device->EmbeddedVoiceChatDevice = elem;
            if (std::shared_ptr<EmbeddedVoiceChat::Device> deviceSpt = elem.lock()) {
                LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("Device: %s"), UTF8_TO_TCHAR(deviceSpt->getName().c_str())));
            }
            result.Add(device);
        }
        return result;
    }
#endif
    return TArray<UEmbeddedVoiceChatDevice *>();
}

UEmbeddedVoiceChatDevice *UEmbeddedVoiceChatDevices::getDefaultDevice() {
    UEmbeddedVoiceChatDevice *device = NewObject<UEmbeddedVoiceChatDevice>();
#if WITH_EMBEDDEDVOICECHAT
    if (std::shared_ptr<EmbeddedVoiceChat::Devices> spt = this->EmbeddedVoiceChatDevices.lock()) {
        device->EmbeddedVoiceChatDevice = spt->getDefaultDevice();
    }
#endif
    return device;
}

void UEmbeddedVoiceChatDevices::setActiveDevice(UEmbeddedVoiceChatDevice* device, bool &success, FString &errorMessage) {
#if WITH_EMBEDDEDVOICECHAT
    if (std::shared_ptr<EmbeddedVoiceChat::Devices> spt = this->EmbeddedVoiceChatDevices.lock()) {
        EmbeddedVoiceChat::Result result = spt->setActiveDevice(device->EmbeddedVoiceChatDevice);
        success = result.ok();
        errorMessage = UTF8_TO_TCHAR(("input devices setActiveDevice: " + result.getText()).c_str());
    }
#endif
}

UEmbeddedVoiceChatDevice *UEmbeddedVoiceChatDevices::getActiveDevice() {
    UEmbeddedVoiceChatDevice *device = NewObject<UEmbeddedVoiceChatDevice>();
#if WITH_EMBEDDEDVOICECHAT
    if (std::shared_ptr<EmbeddedVoiceChat::Devices> spt = this->EmbeddedVoiceChatDevices.lock()) {
        device->EmbeddedVoiceChatDevice = spt->getActiveDevice();
    }
#endif
    return device;
}

void UEmbeddedVoiceChatDevices::refresh(bool &success, FString &errorMessage) {
#if WITH_EMBEDDEDVOICECHAT
    if (std::shared_ptr<EmbeddedVoiceChat::Devices> spt = this->EmbeddedVoiceChatDevices.lock()) {
        EmbeddedVoiceChat::Result result = spt->refresh();
        success = result.ok();
        errorMessage = UTF8_TO_TCHAR(("input devices refresh: " + result.getText()).c_str());
    }
#endif
}
