/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DataAlreadyAcceptedException.h"

#endif

#include "DataAlreadyAcceptedException.generated.h"

/**
   * <p>The event was already logged.</p><p><h3>See Also:</h3>   <a href="http://docs.aws.amazon.com/goto/WebAPI/logs-2014-03-28/DataAlreadyAcceptedException">AWS API Reference</a></p>
*/
USTRUCT(BlueprintType)
struct FDataAlreadyAcceptedException {
GENERATED_BODY()

    /**
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString expectedSequenceToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
#endif
};
