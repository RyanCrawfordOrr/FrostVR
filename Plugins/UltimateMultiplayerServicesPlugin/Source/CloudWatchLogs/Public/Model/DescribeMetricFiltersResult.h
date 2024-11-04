/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeMetricFiltersResult.h"

#endif

#include "Model/MetricFilter.h"

#include "DescribeMetricFiltersResult.generated.h"

USTRUCT(BlueprintType)
struct FDescribeMetricFiltersResult {
GENERATED_BODY()

    /**
    *  <p>The metric filters.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FMetricFilter> metricFilters;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FDescribeMetricFiltersResult &fromAWS(const Aws::CloudWatchLogs::Model::DescribeMetricFiltersResult &awsDescribeMetricFiltersResult) {
        this->metricFilters.Empty();
        for (const Aws::CloudWatchLogs::Model::MetricFilter& elem : awsDescribeMetricFiltersResult.GetMetricFilters()) {
            this->metricFilters.Add(FMetricFilter().fromAWS(elem));
        }

        this->nextToken = UTF8_TO_TCHAR(awsDescribeMetricFiltersResult.GetNextToken().c_str());

        return *this;
    }
#endif
};
