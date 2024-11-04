/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#include "EmbeddedVoiceChatChannelId.h"
#include "GenericPlatform/GenericPlatformOutputDevices.h"
#include "Misc/OutputDeviceFile.h"
#include "Engine/Engine.h"

#if WITH_EMBEDDEDVOICECHAT
EmbeddedVoiceChat::ChannelId FEmbeddedVoiceChatChannelId::toEmbeddedVoiceChat() const {
    return EmbeddedVoiceChat::ChannelId(TCHAR_TO_UTF8(*this->id));
}
#endif