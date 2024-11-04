/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/QueryCompileErrorLocation.h"

#endif

#include "QueryCompileErrorLocation.generated.h"

USTRUCT(BlueprintType)
struct FQueryCompileErrorLocation {
GENERATED_BODY()

    /**
     * <p>Reserved.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int startCharOffset = 0;

    /**
     * <p>Reserved.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int endCharOffset = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
#endif
};
