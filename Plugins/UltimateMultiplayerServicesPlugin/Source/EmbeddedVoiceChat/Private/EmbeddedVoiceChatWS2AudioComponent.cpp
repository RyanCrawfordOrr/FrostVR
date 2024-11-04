/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Jan 2023
 */

#include "EmbeddedVoiceChatWS2AudioComponent.h"
#include "EmbeddedVoiceChatWS2Group.h"
#include "EmbeddedVoiceChatGlobals.h"

#include "Math/UnrealMathUtility.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatCommon.h"

#endif

void UVoiceChatWS2SoundWave::Init(UEmbeddedVoiceChatWS2Group *tempGroup, const FString &tempPlayerId) {
	check(tempGroup);

	this->group = tempGroup;
	this->playerId = tempPlayerId;
	VirtualizationMode = EVirtualizationMode::PlayWhenSilent;
	NumChannels = 1;
	NumSamplesToGeneratePerCallback = DEFAULT_PROCEDURAL_SOUNDWAVE_BUFFER_SIZE;
	bCanProcessAsync = true;

	Duration = INDEFINITELY_LOOPING_DURATION;
	bLooping = true;
	SoundGroup = SOUNDGROUP_Voice;
#if WITH_EMBEDDEDVOICECHAT
	SampleRate = EmbeddedVoiceChat::sampleRate;
#endif
}

int32 UVoiceChatWS2SoundWave::OnGeneratePCMAudio(TArray<uint8>& OutAudio, int32 NumSamples) {
	LLM_SCOPE(ELLMTag::AudioSynthesis);

	OutAudio.Reset();

	// If running with audio mixer, the output audio buffer will be in floats already
	OutAudio.AddZeroed(NumSamples * sizeof(float));
#if WITH_EMBEDDEDVOICECHAT
	if (this->group == nullptr) {
        LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("please get voice chat sound wave by calling getSoundWave with embedded voice chat group component. ")));
        return 0;
    }

	UEmbeddedVoiceChatChannel * channel = this->group->getChannel(this->playerId);
	if (channel == nullptr) {
        LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("channel is not ready yet. ")));
        return 0;
    }

	if (!(channel->EmbeddedVoiceChatChannel)) {
        LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("channel is not created correctly or may be destroyed. ")));
        return 0;
    }

    std::vector<float> cache;

    cache.reserve(NumSamples);
    channel->EmbeddedVoiceChatChannel->getCacheOnly(cache, NumSamples);

    LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("got cached %d frames, remaining %d"), cache.size(), channel->EmbeddedVoiceChatChannel->getCacheSize()));

    for (int i = 0; i < NumSamples; i++) {
        if (i < cache.size() && !EmbeddedVoiceChat::deafened) {
            OutAudio[i] = FMath::Clamp<float>(cache[i] * VolumeMultiplier, -1.0, 1.0);
        } else {
            OutAudio[i] = 0;
        }
    }

    return NumSamples;
#endif
	return NumSamples;
}

Audio::EAudioMixerStreamDataFormat::Type UVoiceChatWS2SoundWave::GetGeneratedPCMDataFormat() const {
	// Only audio mixer supports return float buffers
	return Audio::EAudioMixerStreamDataFormat::Float;
}

UEmbeddedVoiceChatWS2AudioComponent::UEmbeddedVoiceChatWS2AudioComponent(const FObjectInitializer& ObjectInitializer)
        : Super(ObjectInitializer)
{
    NumChannels = 1;
}

int32 UEmbeddedVoiceChatWS2AudioComponent::OnGenerateAudio(float* OutAudio, int32 NumSamples) {
#if WITH_EMBEDDEDVOICECHAT
	if (this->group == nullptr) {
        LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("please get voice chat sound wave by calling getSoundWave with embedded voice chat group component. ")));
        return 0;
    }

	UEmbeddedVoiceChatChannel * channel = this->group->getChannel(this->playerId);
	if (channel == nullptr) {
        LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("channel is not ready yet. ")));
        return 0;
    }

	if (!(channel->EmbeddedVoiceChatChannel)) {
        LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("channel is not created correctly or may be destroyed. ")));
        return 0;
    }

    std::vector<float> cache;

    cache.reserve(NumSamples);
    channel->EmbeddedVoiceChatChannel->getCacheOnly(cache, NumSamples);

    LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("got cached %d frames, remaining %d"), cache.size(), channel->EmbeddedVoiceChatChannel->getCacheSize()));

    for (int i = 0; i < NumSamples; i++) {
        if (i < cache.size() && !EmbeddedVoiceChat::deafened) {
            OutAudio[i] = FMath::Clamp<float>(cache[i] * VolumeMultiplier, -1.0, 1.0);
        } else {
            OutAudio[i] = 0;
        }
    }

    return NumSamples;
#endif
    return 0;
}

bool UEmbeddedVoiceChatWS2AudioComponent::Init(int32& SampleRate) {
#if WITH_EMBEDDEDVOICECHAT
    SampleRate = EmbeddedVoiceChat::sampleRate;
#endif
    return true;
}

void UEmbeddedVoiceChatWS2AudioComponent::setGroup(UEmbeddedVoiceChatWS2Group *tempGroup, const FString &tempPlayerId) {
    if (tempGroup == nullptr) {
        return;
    }

    this->group = tempGroup;
    this->playerId = tempPlayerId;
}