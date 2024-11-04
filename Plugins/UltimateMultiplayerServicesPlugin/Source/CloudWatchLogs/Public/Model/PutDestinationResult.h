/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutDestinationResult.h"

#endif

#include "Model/CloudWatchLogsDestination.h"

#include "PutDestinationResult.generated.h"

USTRUCT(BlueprintType)
struct FPutDestinationResult {
GENERATED_BODY()

    /**
    *  <p>The destination.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FCloudWatchLogsDestination destination;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FPutDestinationResult &fromAWS(const Aws::CloudWatchLogs::Model::PutDestinationResult &awsPutDestinationResult) {
        this->destination.fromAWS(awsPutDestinationResult.GetDestination());

        return *this;
    }
#endif
};
