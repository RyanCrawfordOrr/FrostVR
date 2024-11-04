/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DeleteSubscriptionFilterRequest.h"

#endif

#include "DeleteSubscriptionFilterRequest.generated.h"

USTRUCT(BlueprintType)
struct FDeleteSubscriptionFilterRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The name of the subscription filter.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterName;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DeleteSubscriptionFilterRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DeleteSubscriptionFilterRequest awsDeleteSubscriptionFilterRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsDeleteSubscriptionFilterRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->filterName.IsEmpty())) {
            awsDeleteSubscriptionFilterRequest.SetFilterName(TCHAR_TO_UTF8(*this->filterName));
        }

        return awsDeleteSubscriptionFilterRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->filterName.IsEmpty();
    }
#endif
};
