/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/InvalidSequenceTokenException.h"

#endif

#include "InvalidSequenceTokenException.generated.h"

USTRUCT(BlueprintType)
struct FInvalidSequenceTokenException {
GENERATED_BODY()

    /**
     *
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString expectedSequenceToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
#endif
};
