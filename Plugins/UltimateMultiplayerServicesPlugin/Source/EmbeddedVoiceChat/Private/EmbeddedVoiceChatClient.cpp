/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#include "EmbeddedVoiceChatClient.h"
#include "GenericPlatform/GenericPlatformOutputDevices.h"
#include "Misc/OutputDeviceFile.h"
#include "Engine/Engine.h"

#include "EmbeddedVoiceChatGlobals.h"

void UEmbeddedVoiceChatClient::initialize(bool &success, FString &errorMessage, bool enableNoiseSuppression) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatClient) {
        EmbeddedVoiceChat::Result result = this->EmbeddedVoiceChatClient->initialize(enableNoiseSuppression);
        success = result.ok();
        errorMessage = UTF8_TO_TCHAR(("Client initialize: " + result.getText()).c_str());
    }
#endif
}

void UEmbeddedVoiceChatClient::terminate(bool &success, FString &errorMessage) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatClient) {
        EmbeddedVoiceChat::Result result = this->EmbeddedVoiceChatClient->terminate();
        success = result.ok();
        errorMessage = UTF8_TO_TCHAR(("Client terminate: " + result.getText()).c_str());
    }
#endif
}

UEmbeddedVoiceChatInputDevices *UEmbeddedVoiceChatClient::getInputDevices() {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatClient) {
        UEmbeddedVoiceChatInputDevices *devices = NewObject<UEmbeddedVoiceChatInputDevices>();
        devices->EmbeddedVoiceChatDevices = this->EmbeddedVoiceChatClient->getInputDevices();
        this->EmbeddedVoiceChatClient->getInputDevices()->onRefreshCompleted.emplace(devices->GetUniqueID(), [](void *userData) -> void {
            try {
                UEmbeddedVoiceChatInputDevices *devices = (UEmbeddedVoiceChatInputDevices *)userData;

                if (devices->onRefreshCompleted.IsBound()) {
                    devices->onRefreshCompleted.Broadcast();
                }
            } catch (const std::exception& e) {
				(void)e;
                LOG_EMBEDDEDVOICECHAT_ERROR(FString::Printf(TEXT("failed to boardcast on refresh completed delegate: %s"), e.what()));
            }
        });
        this->EmbeddedVoiceChatClient->getInputDevices()->onRefreshCompletedUserData.emplace(devices->GetUniqueID(), devices);
        return devices;
    }
#endif
    return nullptr;
}

UEmbeddedVoiceChatOutputDevices *UEmbeddedVoiceChatClient::getOutputDevices() {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatClient) {
        UEmbeddedVoiceChatOutputDevices *devices = NewObject<UEmbeddedVoiceChatOutputDevices>();
        devices->EmbeddedVoiceChatDevices = this->EmbeddedVoiceChatClient->getOutputDevices();
        this->EmbeddedVoiceChatClient->getOutputDevices()->onRefreshCompleted.emplace(devices->GetUniqueID(), [](void *userData) -> void {
            try {
                UEmbeddedVoiceChatInputDevices *devices = (UEmbeddedVoiceChatInputDevices *)userData;

                if (devices->onRefreshCompleted.IsBound()) {
                    devices->onRefreshCompleted.Broadcast();
                }
            } catch (const std::exception& e) {
				(void)e;
                LOG_EMBEDDEDVOICECHAT_ERROR(FString::Printf(TEXT("failed to boardcast on refresh completed delegate: %s"), e.what()));
            }
        });
        this->EmbeddedVoiceChatClient->getOutputDevices()->onRefreshCompletedUserData.emplace(devices->GetUniqueID(), devices);
        return devices;
    }
#endif
    return nullptr;
}

bool UEmbeddedVoiceChatClient::isTalking() {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatClient) {
        return this->EmbeddedVoiceChatClient->isTalking();
    }
#endif
    return false;
}