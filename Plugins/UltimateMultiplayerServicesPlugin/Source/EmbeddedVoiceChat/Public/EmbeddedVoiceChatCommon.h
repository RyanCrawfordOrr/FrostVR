/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatCommon.h"

#endif

#include "EmbeddedVoiceChatChannel3DProperties.h"

#include "EmbeddedVoiceChatCommon.generated.h"

/**
 *
 */
UCLASS()
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatFunctionLibrary : public UBlueprintFunctionLibrary {
GENERATED_BODY()

public:
    /**
    * @return set the default channel type and 3d properties
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void setChannelTypeAnd3DProperties(EEmbeddedVoiceChatChannelType type, FEmbeddedVoiceChatChannel3DProperties properties);

    /**
    * set sample rate
     * \param sampleRate sample rate must be one of 8000, 12000, 16000, 24000, or 48000.
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void setSampleRate(int sampleRate = 48000);

    /**
    * get sample rate
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static int getSampleRate();

    /**
    * set voice ratio
     * \param voiceRatio a percentage value that tell voice recognition that if the possibility of it's human voice, will treat it as a human voice. this plugin will only set human voice.
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void setVoiceRatio(int voiceRatio = 78);

    /**
     * a percentage value that tell voice recognition that if the possibility of it's human voice, will treat it as a human voice. this plugin will only set human voice.
    * get voice ratio
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static int getVoiceRatio();

    /**
    * set is client talking threshold
     * \param isClientTalkingThreshold after passing a few milliseconds without any voice chat detected from the client, is talking will return false.
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void setIsClientTalkingThreshold(int isClientTalkingThreshold = 100);

    /**
     * after passing a few milliseconds without any voice chat detected from the client, is talking will return false.
    * get is client talking threshold
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static int getIsClientTalkingThreshold();

    /**
    * set is device talking threshold
     * \param isChannelTalkingThreshold after passing a few milliseconds without any voice passing received from the channel, is talking will return false.
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void setIsChannelTalkingThreshold(int isChannelTalkingThreshold = 1000);

    /**
     * after passing a few milliseconds without any voice passing received from the channel, is talking will return false.
    * get is device talking threshold
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static int getIsChannelTalkingThreshold();

    /**
    * mute
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void mute();

    /**
    * unmute
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void unmute();

    /**
    * @return is muted or not
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static bool isMuted();

    /**
    * deafen
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void deafen();

    /**
    * undeafen
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void undeafen();

    /**
    * @return is deafened or not
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static bool isDeafened();

    /**
    * enable noise suppression
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void enableNoiseSuppression(bool enableNoiseSuppression);

    /**
    * @return is noise suppression enabled or not
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static bool isNoiseSuppressionEnabled();

    /**
    * enable voice debug will record the recorded voice and output voice as wave files
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void enableVoiceDebug(bool enableVoiceDebug);

    /**
    * @return is voice debug enabled or not
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static bool isVoiceDebugEnabled();
};