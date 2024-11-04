/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#include "EmbeddedVoiceChatCommon.h"
#include "GenericPlatform/GenericPlatformOutputDevices.h"
#include "Misc/OutputDeviceFile.h"
#include "Engine/Engine.h"

void UEmbeddedVoiceChatFunctionLibrary::setChannelTypeAnd3DProperties(EEmbeddedVoiceChatChannelType type, FEmbeddedVoiceChatChannel3DProperties properties) {
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::channelType = (EmbeddedVoiceChat::ChannelType)type;
    EmbeddedVoiceChat::channel3DProperties = properties.toEmbeddedVoiceChat();
#endif
}

void UEmbeddedVoiceChatFunctionLibrary::setSampleRate(int sampleRate) {
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::sampleRate = sampleRate;
#endif
}

int UEmbeddedVoiceChatFunctionLibrary::getSampleRate() {
#if WITH_EMBEDDEDVOICECHAT
    return EmbeddedVoiceChat::sampleRate;
#endif
    return 0;
}

void UEmbeddedVoiceChatFunctionLibrary::setVoiceRatio(int voiceRatio) {
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::voiceRatio = voiceRatio;
#endif
}

int UEmbeddedVoiceChatFunctionLibrary::getVoiceRatio() {
#if WITH_EMBEDDEDVOICECHAT
    return EmbeddedVoiceChat::voiceRatio;
#endif
    return -1;
}

void UEmbeddedVoiceChatFunctionLibrary::setIsClientTalkingThreshold(int isClientTalkingThreshold) {
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::isClientTalkingThreshold = isClientTalkingThreshold;
#endif
}

int UEmbeddedVoiceChatFunctionLibrary::getIsClientTalkingThreshold() {
#if WITH_EMBEDDEDVOICECHAT
    return EmbeddedVoiceChat::isClientTalkingThreshold;
#endif
    return -1;
}

void UEmbeddedVoiceChatFunctionLibrary::setIsChannelTalkingThreshold(int isChannelTalkingThreshold) {
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::isChannelTalkingThreshold = isChannelTalkingThreshold;
#endif
}

int UEmbeddedVoiceChatFunctionLibrary::getIsChannelTalkingThreshold() {
#if WITH_EMBEDDEDVOICECHAT
    return EmbeddedVoiceChat::isChannelTalkingThreshold;
#endif
    return -1;
}

void UEmbeddedVoiceChatFunctionLibrary::mute() {
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::muted = true;
#endif
}

void UEmbeddedVoiceChatFunctionLibrary::unmute() {
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::muted = false;
#endif
}

bool UEmbeddedVoiceChatFunctionLibrary::isMuted() {
#if WITH_EMBEDDEDVOICECHAT
    return EmbeddedVoiceChat::muted;
#endif
    return false;
}

void UEmbeddedVoiceChatFunctionLibrary::deafen() {
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::deafened = true;
#endif
}

void UEmbeddedVoiceChatFunctionLibrary::undeafen() {
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::deafened = false;
#endif
}

bool UEmbeddedVoiceChatFunctionLibrary::isDeafened() {
#if WITH_EMBEDDEDVOICECHAT
    return EmbeddedVoiceChat::deafened;
#endif
    return false;
}

void UEmbeddedVoiceChatFunctionLibrary::enableNoiseSuppression(bool enableNoiseSuppression) {
#if WITH_EMBEDDEDVOICECHAT
	if (enableNoiseSuppression) {
		EmbeddedVoiceChat::enableNoiseSuppression();
	} else {
		EmbeddedVoiceChat::disableNoiseSuppression();
	}
#endif
}

bool UEmbeddedVoiceChatFunctionLibrary::isNoiseSuppressionEnabled() {
#if WITH_EMBEDDEDVOICECHAT
    return EmbeddedVoiceChat::denoiseState != nullptr;
#endif
    return false;
}

void UEmbeddedVoiceChatFunctionLibrary::enableVoiceDebug(bool enableVoiceDebug) {
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::bEnableVoiceDebug = enableVoiceDebug;
#endif
}

bool UEmbeddedVoiceChatFunctionLibrary::isVoiceDebugEnabled() {
#if WITH_EMBEDDEDVOICECHAT
    return EmbeddedVoiceChat::bEnableVoiceDebug;
#endif
    return false;
}