/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DeleteMetricFilterRequest.h"

#endif

#include "DeleteMetricFilterRequest.generated.h"

USTRUCT(BlueprintType)
struct FDeleteMetricFilterRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The name of the metric filter.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterName;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DeleteMetricFilterRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DeleteMetricFilterRequest awsDeleteMetricFilterRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsDeleteMetricFilterRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->filterName.IsEmpty())) {
            awsDeleteMetricFilterRequest.SetFilterName(TCHAR_TO_UTF8(*this->filterName));
        }

        return awsDeleteMetricFilterRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->filterName.IsEmpty();
    }
#endif
};
