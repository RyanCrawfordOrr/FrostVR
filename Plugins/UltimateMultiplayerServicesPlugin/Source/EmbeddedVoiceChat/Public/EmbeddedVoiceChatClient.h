/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, Feb 2022
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LatentActionManager.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatClient.h"

#endif

#include "EmbeddedVoiceChatInputDevices.h"
#include "EmbeddedVoiceChatOutputDevices.h"
#include "EmbeddedVoiceChatChannel.h"

#include "EmbeddedVoiceChatClient.generated.h"

/**
**/
UCLASS(BlueprintType)
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatClient : public UObject {
    GENERATED_BODY()

public:
#if WITH_EMBEDDEDVOICECHAT
    std::shared_ptr<EmbeddedVoiceChat::Client> EmbeddedVoiceChatClient;
#endif
    UEmbeddedVoiceChatClient() {
#if WITH_EMBEDDEDVOICECHAT
        EmbeddedVoiceChatClient = std::make_shared<EmbeddedVoiceChat::Client>();
#endif
    }

    /**
    * initialize. This function must be called first before accessing any Embedded Voice Chat client functions.
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void initialize(bool &success, FString &errorMessage, bool enableNoiseSuppression = true);

    /**
     * terminate. This function must be called after you don't want to access any Embedded Voice Chat client functions any more. Each Initialize should be paired with a terminate.
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void terminate(bool &success, FString &errorMessage);

    /**
     * get input devices list. it doesn't support hot plug for now. if you plugged in a new device and want to get device list refreshed, call refresh for audio devices.
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    UEmbeddedVoiceChatInputDevices *getInputDevices();

    /**
     * get output devices list. it doesn't support hot plug for now. if you plugged in a new device and want to get device list refreshed, call restart audio device.
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    UEmbeddedVoiceChatOutputDevices *getOutputDevices();

    /**
     * \return true if this client's active device has detected voice input in the last isDeviceTalkingThreshold milliseconds
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    bool isTalking();
};
