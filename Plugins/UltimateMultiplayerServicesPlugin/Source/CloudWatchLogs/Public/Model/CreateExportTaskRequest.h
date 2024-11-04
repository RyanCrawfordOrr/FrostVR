/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/CreateExportTaskRequest.h"

#endif

#include "CreateExportTaskRequest.generated.h"

USTRUCT(BlueprintType)
struct FCreateExportTaskRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the export task.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString taskName;

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>Export only log streams that match the provided prefix. If you don't specify a value, no prefix filter is applied.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logStreamNamePrefix;

    /**
    *  <p>The start time of the range for the request, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC. Events with a timestamp earlier than this time are not exported.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 from = 0;

    /**
    *  <p>The end time of the range for the request, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC. Events with a timestamp later than this time are not exported.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 to = 0;

    /**
    *  <p>The name of S3 bucket for the exported log data. The bucket must be in the same AWS region.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString destination;

    /**
    *  <p>The prefix used as the start of the key for every object exported. If you don't specify a value, the default is <code>exportedlogs</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString destinationPrefix;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::CreateExportTaskRequest toAWS() const {
        Aws::CloudWatchLogs::Model::CreateExportTaskRequest awsCreateExportTaskRequest;

		if (!(this->taskName.IsEmpty())) {
            awsCreateExportTaskRequest.SetTaskName(TCHAR_TO_UTF8(*this->taskName));
        }

		if (!(this->logGroupName.IsEmpty())) {
            awsCreateExportTaskRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->logStreamNamePrefix.IsEmpty())) {
            awsCreateExportTaskRequest.SetLogStreamNamePrefix(TCHAR_TO_UTF8(*this->logStreamNamePrefix));
        }

        if (!(this->from == 0)) {
            awsCreateExportTaskRequest.SetFrom(this->from);
        }

        if (!(this->to == 0)) {
            awsCreateExportTaskRequest.SetTo(this->to);
        }

		if (!(this->destination.IsEmpty())) {
            awsCreateExportTaskRequest.SetDestination(TCHAR_TO_UTF8(*this->destination));
        }

		if (!(this->destinationPrefix.IsEmpty())) {
            awsCreateExportTaskRequest.SetDestinationPrefix(TCHAR_TO_UTF8(*this->destinationPrefix));
        }

        return awsCreateExportTaskRequest;
    }

    bool IsEmpty() const {
        return this->taskName.IsEmpty() && this->logGroupName.IsEmpty() && this->logStreamNamePrefix.IsEmpty() && this->from == 0 && this->to == 0 && this->destination.IsEmpty() && this->destinationPrefix.IsEmpty();
    }
#endif
};
