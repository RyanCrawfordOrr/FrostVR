/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, Feb 2022
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LatentActionManager.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatDevices.h"

#endif

#include "EmbeddedVoiceChatDevice.h"

#include "EmbeddedVoiceChatDevices.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRefreshCompleted);

/**
 * output device list of a client
**/
UCLASS(BlueprintType)
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatDevices : public UObject {
    GENERATED_BODY()

public:
#if WITH_EMBEDDEDVOICECHAT
    std::weak_ptr<EmbeddedVoiceChat::Devices> EmbeddedVoiceChatDevices;
#endif
    UPROPERTY(BlueprintAssignable, Category = "Embedded Voice Chat")
    FOnRefreshCompleted onRefreshCompleted;

    ~UEmbeddedVoiceChatDevices() {
#if WITH_EMBEDDEDVOICECHAT
    if (std::shared_ptr<EmbeddedVoiceChat::Devices> spt = this->EmbeddedVoiceChatDevices.lock()) {
        spt->onRefreshCompleted.erase(this->GetUniqueID());
    }
#endif
    }

    /**
     * get available input device
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    TArray<UEmbeddedVoiceChatDevice *> getAvailableDevices();

    /**
     * get default input device
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    UEmbeddedVoiceChatDevice* getDefaultDevice();

    /**
     * set active device
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void setActiveDevice(UEmbeddedVoiceChatDevice* device, bool &success, FString &errorMessage);

    /**
     * get active device
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    UEmbeddedVoiceChatDevice* getActiveDevice();

    /**
     * refresh the device list. if there is active device, will stop and restart it. if the active device can't be found, will start default device instead.
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void refresh(bool &success, FString &errorMessage);
};
