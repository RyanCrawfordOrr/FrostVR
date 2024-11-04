/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, Feb 2022
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LatentActionManager.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatInputDevices.h"

#endif

#include "EmbeddedVoiceChatDevice.h"
#include "EmbeddedVoiceChatDevices.h"

#include "EmbeddedVoiceChatInputDevices.generated.h"

/**
 * input device list of a client
**/
UCLASS(BlueprintType)
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatInputDevices : public UEmbeddedVoiceChatDevices {
    GENERATED_BODY()

public:
};
