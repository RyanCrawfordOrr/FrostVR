/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#pragma once

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatChannel3DProperties.h"

#endif

#include "EmbeddedVoiceChatChannel3DProperties.generated.h"

/**
* \brief The type of channel
*/
UENUM(BlueprintType)
enum class EEmbeddedVoiceChatChannelType : uint8 {
    /**
     * \brief A typical conferencing channel
     */
    NonPositional,
    /**
     * \brief A conferencing channel where users' voices are rendered with distance.
     */
    Proximity,
    /**
     * \brief A conferencing channel where users' voices are rendered with 3D positional effects.
     */
    Positional
};

/**
  * \brief The distance model for a Positional channel, which determines the algorithm to use when computing attenuation
  */
UENUM(BlueprintType)
enum class EEmbeddedVoiceChatAudioFadeModel : uint8 {
    /**
     * \brief conversationalDistance / (conversationalDistance + audioFadeIntensityByDistance * (clamp(distance, conversationalDistance, audibleDistance) - conversationalDistance))
     */
    InverseByDistance,
    /**
     * \brief 1 - audioFadeIntensityByDistance * (clamp(distance, conversationalDistance, audibleDistance) - conversationalDistance) / (audibleDistance - conversationalDistance)
     */
    LinearByDistance,
    /**
     * \brief powd(clamp(distance, conversationalDistance, audibleDistance) / conversationalDistance, -audioFadeIntensityByDistance);
     */
    ExponentialByDistance
};

USTRUCT(BlueprintType)
struct FEmbeddedVoiceChatChannel3DProperties {
    GENERATED_BODY()

    /*
     * The maximum distance from the listener that a speaker can be heard. Must be > 0.
     * */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Embedded Voice Chat")
    int audibleDistance = 5000;

    /*
     * The distance from the listener within which a speaker’s voice is heard at its original volume. Must be >= 0 and <= audibleDistance.
     * */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Embedded Voice Chat")
    int conversationalDistance= 1000;

    /*
     * How strong the effect of the audio fade is as the speaker moves away from the listener. Must be >= 0.
     * */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Embedded Voice Chat")
    float audioFadeIntensityByDistance = 1.0f;

    /*
     * The model used to determine how loud a voice is at different distances.
     * */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Embedded Voice Chat")
	EEmbeddedVoiceChatAudioFadeModel audioFadeModel = EEmbeddedVoiceChatAudioFadeModel::LinearByDistance;

public:
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::Channel3DProperties toEmbeddedVoiceChat() const;
#endif
};