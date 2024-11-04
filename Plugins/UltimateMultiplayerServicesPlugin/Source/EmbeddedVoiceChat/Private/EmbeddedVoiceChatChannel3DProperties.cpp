/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#include "EmbeddedVoiceChatChannel3DProperties.h"
#include "GenericPlatform/GenericPlatformOutputDevices.h"
#include "Misc/OutputDeviceFile.h"
#include "Engine/Engine.h"

#if WITH_EMBEDDEDVOICECHAT
EmbeddedVoiceChat::Channel3DProperties FEmbeddedVoiceChatChannel3DProperties::toEmbeddedVoiceChat() const {
    return EmbeddedVoiceChat::Channel3DProperties(this->audibleDistance, this->conversationalDistance, this->audioFadeIntensityByDistance, (EmbeddedVoiceChat::AudioFadeModel)this->audioFadeModel);
}
#endif