/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/LogStream.h"

#endif

#include "LogStream.generated.h"

USTRUCT(BlueprintType)
struct FLogStream {
GENERATED_BODY()

    /**
    *  <p>The name of the log stream.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logStreamName;

    /**
    *  <p>The creation time of the stream, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 creationTime = 0;

    /**
    *  <p>The time of the first event, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 firstEventTimestamp = 0;

    /**
    *  <p>The time of the most recent log event in the log stream in CloudWatch Logs. This number is expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC. The <code>lastEventTime</code> value updates on an eventual consistency basis. It typically updates in less than an hour from ingestion, but in rare situations might take longer.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 lastEventTimestamp = 0;

    /**
    *  <p>The ingestion time, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 lastIngestionTime = 0;

    /**
    *  <p>The sequence token.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString uploadSequenceToken;

    /**
    *  <p>The Amazon Resource Name (ARN) of the log stream.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString arn;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FLogStream &fromAWS(const Aws::CloudWatchLogs::Model::LogStream &awsLogStream) {
        this->logStreamName = UTF8_TO_TCHAR(awsLogStream.GetLogStreamName().c_str());

        this->creationTime = (int64)awsLogStream.GetCreationTime();

        this->firstEventTimestamp = (int64)awsLogStream.GetFirstEventTimestamp();

        this->lastEventTimestamp = (int64)awsLogStream.GetLastEventTimestamp();

        this->lastIngestionTime = (int64)awsLogStream.GetLastIngestionTime();

        this->uploadSequenceToken = UTF8_TO_TCHAR(awsLogStream.GetUploadSequenceToken().c_str());

        this->arn = UTF8_TO_TCHAR(awsLogStream.GetArn().c_str());

        return *this;
    }
#endif
};
