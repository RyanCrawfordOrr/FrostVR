/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, Feb 2022
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LatentActionManager.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatOutputDevices.h"

#endif

#include "EmbeddedVoiceChatDevice.h"
#include "EmbeddedVoiceChatDevices.h"

#include "EmbeddedVoiceChatOutputDevices.generated.h"

/**
 * output device list of a client
**/
UCLASS(BlueprintType)
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatOutputDevices : public UEmbeddedVoiceChatDevices {
    GENERATED_BODY()

public:
};
