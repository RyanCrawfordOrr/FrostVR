/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/MetricFilterMatchRecord.h"

#endif

#include "MetricFilterMatchRecord.generated.h"

USTRUCT(BlueprintType)
struct FMetricFilterMatchRecord {
GENERATED_BODY()

    /**
    *  <p>The event number.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 eventNumber = 0;

    /**
    *  <p>The raw event data.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString eventMessage;

    /**
    *  <p>The values extracted from the event data by the filter.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TMap<FString, FString> extractedValues;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FMetricFilterMatchRecord &fromAWS(const Aws::CloudWatchLogs::Model::MetricFilterMatchRecord &awsMetricFilterMatchRecord) {
        this->eventNumber = (int64)awsMetricFilterMatchRecord.GetEventNumber();

        this->eventMessage = UTF8_TO_TCHAR(awsMetricFilterMatchRecord.GetEventMessage().c_str());

        this->extractedValues.Empty();
        for (const auto& elem : awsMetricFilterMatchRecord.GetExtractedValues()) {
            this->extractedValues.Add(UTF8_TO_TCHAR(elem.first.c_str()), UTF8_TO_TCHAR(elem.second.c_str()));
        }

        return *this;
    }
#endif
};
