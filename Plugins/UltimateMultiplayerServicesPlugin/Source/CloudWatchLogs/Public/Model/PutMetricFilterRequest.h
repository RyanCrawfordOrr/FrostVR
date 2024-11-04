/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutMetricFilterRequest.h"

#endif

#include "Model/MetricTransformation.h"

#include "PutMetricFilterRequest.generated.h"

USTRUCT(BlueprintType)
struct FPutMetricFilterRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>A name for the metric filter.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterName;

    /**
    *  <p>A filter pattern for extracting metric data out of ingested log events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterPattern;

    /**
    *  <p>A collection of information that defines how metric data gets emitted.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FMetricTransformation> metricTransformations;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::PutMetricFilterRequest toAWS() const {
        Aws::CloudWatchLogs::Model::PutMetricFilterRequest awsPutMetricFilterRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsPutMetricFilterRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->filterName.IsEmpty())) {
            awsPutMetricFilterRequest.SetFilterName(TCHAR_TO_UTF8(*this->filterName));
        }

		if (!(this->filterPattern.IsEmpty())) {
            awsPutMetricFilterRequest.SetFilterPattern(TCHAR_TO_UTF8(*this->filterPattern));
        }

        for (const FMetricTransformation& elem : this->metricTransformations) {
            awsPutMetricFilterRequest.AddMetricTransformations(elem.toAWS());
        }

        return awsPutMetricFilterRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->filterName.IsEmpty() && this->filterPattern.IsEmpty() && this->metricTransformations.Num() == 0;
    }
#endif
};
