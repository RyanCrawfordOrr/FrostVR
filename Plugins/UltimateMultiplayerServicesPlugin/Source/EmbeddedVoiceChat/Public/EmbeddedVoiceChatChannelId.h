/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#pragma once

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatChannelId.h"

#endif

#include "EmbeddedVoiceChatChannelId.generated.h"

/*
 * The unique identifier for a channel. Channels are created and destroyed automatically on demand.
 */
USTRUCT(BlueprintType)
struct FEmbeddedVoiceChatChannelId {
    GENERATED_BODY()

    /*
     * The unique channel id you assigned to the channel
     * */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Embedded Voice Chat")
    FString id;

public:
#if WITH_EMBEDDEDVOICECHAT
    EmbeddedVoiceChat::ChannelId toEmbeddedVoiceChat() const;
#endif
};