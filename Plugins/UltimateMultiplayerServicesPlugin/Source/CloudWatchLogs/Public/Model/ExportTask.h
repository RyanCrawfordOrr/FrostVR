/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/ExportTask.h"

#endif

#include "Model/ExportTaskStatus.h"
#include "Model/ExportTaskExecutionInfo.h"

#include "ExportTask.generated.h"

USTRUCT(BlueprintType)
struct FExportTask {
GENERATED_BODY()

    /**
    *  <p>The ID of the export task.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString taskId;

    /**
    *  <p>The name of the export task.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString taskName;

    /**
    *  <p>The name of the log group from which logs data was exported.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The start time, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC. Events with a timestamp before this time are not exported.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 from = 0;

    /**
    *  <p>The end time, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC. Events with a timestamp later than this time are not exported.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 to = 0;

    /**
    *  <p>The name of the S3 bucket to which the log data was exported.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString destination;

    /**
    *  <p>The prefix that was used as the start of Amazon S3 key for every object exported.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString destinationPrefix;

    /**
    *  <p>The status of the export task.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FExportTaskStatus status;

    /**
    *  <p>Execution information about the export task.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FExportTaskExecutionInfo executionInfo;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FExportTask &fromAWS(const Aws::CloudWatchLogs::Model::ExportTask &awsExportTask) {
        this->taskId = UTF8_TO_TCHAR(awsExportTask.GetTaskId().c_str());

        this->taskName = UTF8_TO_TCHAR(awsExportTask.GetTaskName().c_str());

        this->logGroupName = UTF8_TO_TCHAR(awsExportTask.GetLogGroupName().c_str());

        this->from = (int64)awsExportTask.GetFrom();

        this->to = (int64)awsExportTask.GetTo();

        this->destination = UTF8_TO_TCHAR(awsExportTask.GetDestination().c_str());

        this->destinationPrefix = UTF8_TO_TCHAR(awsExportTask.GetDestinationPrefix().c_str());

        this->status.fromAWS(awsExportTask.GetStatus());

        this->executionInfo.fromAWS(awsExportTask.GetExecutionInfo());

        return *this;
    }
#endif
};
