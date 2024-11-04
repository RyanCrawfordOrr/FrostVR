/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/MetricFilter.h"

#endif

#include "Model/MetricTransformation.h"

#include "MetricFilter.generated.h"

USTRUCT(BlueprintType)
struct FMetricFilter {
GENERATED_BODY()

    /**
    *  <p>The name of the metric filter.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterName;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterPattern;

    /**
    *  <p>The metric transformations.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FMetricTransformation> metricTransformations;

    /**
    *  <p>The creation time of the metric filter, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 creationTime = 0;

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FMetricFilter &fromAWS(const Aws::CloudWatchLogs::Model::MetricFilter &awsMetricFilter) {
        this->filterName = UTF8_TO_TCHAR(awsMetricFilter.GetFilterName().c_str());

        this->filterPattern = UTF8_TO_TCHAR(awsMetricFilter.GetFilterPattern().c_str());

        this->metricTransformations.Empty();
        for (const Aws::CloudWatchLogs::Model::MetricTransformation& elem : awsMetricFilter.GetMetricTransformations()) {
            this->metricTransformations.Add(FMetricTransformation().fromAWS(elem));
        }

        this->creationTime = (int64)awsMetricFilter.GetCreationTime();

        this->logGroupName = UTF8_TO_TCHAR(awsMetricFilter.GetLogGroupName().c_str());

        return *this;
    }
#endif
};
