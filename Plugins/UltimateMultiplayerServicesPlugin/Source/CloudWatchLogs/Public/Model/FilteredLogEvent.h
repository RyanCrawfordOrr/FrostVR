/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/FilteredLogEvent.h"

#endif

#include "FilteredLogEvent.generated.h"

USTRUCT(BlueprintType)
struct FFilteredLogEvent {
GENERATED_BODY()

    /**
    *  <p>The name of the log stream to which this event belongs.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logStreamName;

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

    /**
    *  <p>The ID of the event.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString eventId;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FFilteredLogEvent &fromAWS(const Aws::CloudWatchLogs::Model::FilteredLogEvent &awsFilteredLogEvent) {
        this->logStreamName = UTF8_TO_TCHAR(awsFilteredLogEvent.GetLogStreamName().c_str());

        this->timestamp = (int64)awsFilteredLogEvent.GetTimestamp();

        this->message = UTF8_TO_TCHAR(awsFilteredLogEvent.GetMessage().c_str());

        this->ingestionTime = (int64)awsFilteredLogEvent.GetIngestionTime();

        this->eventId = UTF8_TO_TCHAR(awsFilteredLogEvent.GetEventId().c_str());

        return *this;
    }
#endif
};
