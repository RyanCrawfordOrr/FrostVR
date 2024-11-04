/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/QueryCompileError.h"

#endif

#include "Model/QueryCompileError.h"

#include "MalformedQueryException.generated.h"

USTRUCT(BlueprintType)
struct FMalformedQueryException {
GENERATED_BODY()

    /**
     *
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FQueryCompileError queryCompileError;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
#endif
};
