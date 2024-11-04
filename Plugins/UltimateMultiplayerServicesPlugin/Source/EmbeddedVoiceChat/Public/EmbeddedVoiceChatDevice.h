/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, Feb 2022
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LatentActionManager.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatDevice.h"

#endif

#include "EmbeddedVoiceChatDevice.generated.h"

/**
 * device notification handler
 **/
UCLASS(Blueprintable)
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatDeviceHandler : public UObject {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onStarted();

    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onStopped();

    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onInterruptionBegan();

    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onInterruptionEnded();

#if WITH_EMBEDDEDVOICECHAT
    std::weak_ptr<EmbeddedVoiceChat::DeviceHandler> toEmbeddedVoiceChat();
    std::shared_ptr<EmbeddedVoiceChat::DeviceHandler> handler;
#endif
};

/**
 * a device
**/
UCLASS(BlueprintType)
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatDevice : public UObject {
    GENERATED_BODY()

public:
#if WITH_EMBEDDEDVOICECHAT
    std::weak_ptr<EmbeddedVoiceChat::Device> EmbeddedVoiceChatDevice;
#endif

    /**
     * get the human-readable name of the device
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    FString getName() const;

    /**
     * get the human-readable name of the device
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    bool isValid() const;

    /**
     * bind a device handler
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void registerDeviceHandler(UEmbeddedVoiceChatDeviceHandler *deviceHandler);
};
