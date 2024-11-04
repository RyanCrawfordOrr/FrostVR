/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeSubscriptionFiltersRequest.h"

#endif

#include "DescribeSubscriptionFiltersRequest.generated.h"

USTRUCT(BlueprintType)
struct FDescribeSubscriptionFiltersRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The prefix to match. If you don't specify a value, no prefix filter is applied.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterNamePrefix;

    /**
    *  <p>The token for the next set of items to return. (You received this token from a previous call.)</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

    /**
    *  <p>The maximum number of items returned. If you don't specify a value, the default is up to 50 items.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int limit = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DescribeSubscriptionFiltersRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DescribeSubscriptionFiltersRequest awsDescribeSubscriptionFiltersRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsDescribeSubscriptionFiltersRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->filterNamePrefix.IsEmpty())) {
            awsDescribeSubscriptionFiltersRequest.SetFilterNamePrefix(TCHAR_TO_UTF8(*this->filterNamePrefix));
        }

		if (!(this->nextToken.IsEmpty())) {
            awsDescribeSubscriptionFiltersRequest.SetNextToken(TCHAR_TO_UTF8(*this->nextToken));
        }

        if (!(this->limit == 0)) {
            awsDescribeSubscriptionFiltersRequest.SetLimit(this->limit);
        }

        return awsDescribeSubscriptionFiltersRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->filterNamePrefix.IsEmpty() && this->nextToken.IsEmpty() && this->limit == 0;
    }
#endif
};
