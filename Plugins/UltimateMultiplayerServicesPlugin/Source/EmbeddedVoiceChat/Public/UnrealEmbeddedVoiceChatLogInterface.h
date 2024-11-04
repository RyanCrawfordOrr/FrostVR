/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#pragma once

#include "CoreMinimal.h"

#if WITH_EMBEDDEDVOICECHAT
#include "EmbeddedVoiceChat/EmbeddedVoiceChatCommon.h"
#endif

#if WITH_EMBEDDEDVOICECHAT
class EMBEDDEDVOICECHAT_API UnrealEmbeddedVoiceChatLogInterface : public EmbeddedVoiceChat::LogInterface
{
public:
    virtual ~UnrealEmbeddedVoiceChatLogInterface() = default;
    
    /**
     * Does a printf style output to ProcessFormattedStatement. Don't use this, it's unsafe. See LogStream
     */
    virtual void Log(EmbeddedVoiceChat::LogLevel logLevel, const char *tag, const char *formatStr, ...) override;
    
};
#endif
