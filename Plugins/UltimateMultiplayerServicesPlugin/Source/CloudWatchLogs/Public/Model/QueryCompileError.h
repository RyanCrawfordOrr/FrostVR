/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/QueryCompileError.h"

#endif

#include "Model/QueryCompileErrorLocation.h"

#include "QueryCompileError.generated.h"

USTRUCT(BlueprintType)
struct FQueryCompileError {
GENERATED_BODY()

    /**
     * <p>Reserved.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FQueryCompileErrorLocation location;

    /**
     * <p>Reserved.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString message;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
#endif
};
