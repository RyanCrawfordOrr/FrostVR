/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeSubscriptionFiltersResult.h"

#endif

#include "Model/SubscriptionFilter.h"

#include "DescribeSubscriptionFiltersResult.generated.h"

USTRUCT(BlueprintType)
struct FDescribeSubscriptionFiltersResult {
GENERATED_BODY()

    /**
    *  <p>The subscription filters.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FSubscriptionFilter> subscriptionFilters;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FDescribeSubscriptionFiltersResult &fromAWS(const Aws::CloudWatchLogs::Model::DescribeSubscriptionFiltersResult &awsDescribeSubscriptionFiltersResult) {
        this->subscriptionFilters.Empty();
        for (const Aws::CloudWatchLogs::Model::SubscriptionFilter& elem : awsDescribeSubscriptionFiltersResult.GetSubscriptionFilters()) {
            this->subscriptionFilters.Add(FSubscriptionFilter().fromAWS(elem));
        }

        this->nextToken = UTF8_TO_TCHAR(awsDescribeSubscriptionFiltersResult.GetNextToken().c_str());

        return *this;
    }
#endif
};
