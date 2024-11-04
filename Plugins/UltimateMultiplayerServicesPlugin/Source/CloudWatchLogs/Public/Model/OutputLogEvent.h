/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/OutputLogEvent.h"

#endif

#include "OutputLogEvent.generated.h"

USTRUCT(BlueprintType)
struct FOutputLogEvent {
GENERATED_BODY()

    /**
    *  <p>The time the event occurred, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 timestamp = 0;

    /**
    *  <p>The data contained in the log event.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString message;

    /**
    *  <p>The time the event was ingested, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 ingestionTime = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FOutputLogEvent &fromAWS(const Aws::CloudWatchLogs::Model::OutputLogEvent &awsOutputLogEvent) {
        this->timestamp = (int64)awsOutputLogEvent.GetTimestamp();

        this->message = UTF8_TO_TCHAR(awsOutputLogEvent.GetMessage().c_str());

        this->ingestionTime = (int64)awsOutputLogEvent.GetIngestionTime();

        return *this;
    }
#endif
};
