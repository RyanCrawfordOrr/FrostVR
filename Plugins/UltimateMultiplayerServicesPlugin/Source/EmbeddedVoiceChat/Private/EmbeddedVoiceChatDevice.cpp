/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#include "EmbeddedVoiceChatDevice.h"
#include "EmbeddedVoiceChatGlobals.h"
#include "GenericPlatform/GenericPlatformOutputDevices.h"
#include "Misc/OutputDeviceFile.h"
#include "Engine/Engine.h"

void UEmbeddedVoiceChatDeviceHandler::onStarted_Implementation() {
}

void UEmbeddedVoiceChatDeviceHandler::onStopped_Implementation() {
}

void UEmbeddedVoiceChatDeviceHandler::onInterruptionBegan_Implementation() {
}

void UEmbeddedVoiceChatDeviceHandler::onInterruptionEnded_Implementation() {
}

#if WITH_EMBEDDEDVOICECHAT
class UnrealDeviceHandler : public EmbeddedVoiceChat::DeviceHandler {
public:
    TWeakObjectPtr<UEmbeddedVoiceChatDeviceHandler> handler;

    virtual void onStarted() override {
        if (this->handler.IsValid()) {
            this->handler->onStarted();
        }
    };

    virtual void onStopped() override {
        if (this->handler.IsValid()) {
            this->handler->onStopped();
        }
    };

    virtual void onInterruptionBegan() override {
        if (this->handler.IsValid()) {
            this->handler->onInterruptionBegan();
        }
    };

    virtual void onInterruptionEnded() override {
        if (this->handler.IsValid()) {
            this->handler->onInterruptionEnded();
        }
    };
};

std::weak_ptr<EmbeddedVoiceChat::DeviceHandler> UEmbeddedVoiceChatDeviceHandler::toEmbeddedVoiceChat() {
    std::shared_ptr<UnrealDeviceHandler> deviceHandler = std::make_shared<UnrealDeviceHandler>();
    deviceHandler->handler = this;
    this->handler = deviceHandler;
    return this->handler;
}
#endif

FString UEmbeddedVoiceChatDevice::getName() const {
#if WITH_EMBEDDEDVOICECHAT
    if (std::shared_ptr<EmbeddedVoiceChat::Device> spt = this->EmbeddedVoiceChatDevice.lock()) {
        return UTF8_TO_TCHAR(spt->getName().c_str());
    }
#endif
    return FString();
}

bool UEmbeddedVoiceChatDevice::isValid() const {
#if WITH_EMBEDDEDVOICECHAT
    return !this->EmbeddedVoiceChatDevice.expired();
#endif
    return false;
}

void UEmbeddedVoiceChatDevice::registerDeviceHandler(UEmbeddedVoiceChatDeviceHandler *deviceHandler) {
#if WITH_EMBEDDEDVOICECHAT
    if (std::shared_ptr<EmbeddedVoiceChat::Device> spt = this->EmbeddedVoiceChatDevice.lock()) {
        spt->registerDeviceHandler(deviceHandler->toEmbeddedVoiceChat());
    }
#endif
}