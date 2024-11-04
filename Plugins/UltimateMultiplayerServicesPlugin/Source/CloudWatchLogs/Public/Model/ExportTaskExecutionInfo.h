/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/ExportTaskExecutionInfo.h"

#endif

#include "ExportTaskExecutionInfo.generated.h"

USTRUCT(BlueprintType)
struct FExportTaskExecutionInfo {
GENERATED_BODY()

    /**
    *  <p>The creation time of the export task, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 creationTime = 0;

    /**
    *  <p>The completion time of the export task, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 completionTime = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FExportTaskExecutionInfo &fromAWS(const Aws::CloudWatchLogs::Model::ExportTaskExecutionInfo &awsExportTaskExecutionInfo) {
        this->creationTime = (int64)awsExportTaskExecutionInfo.GetCreationTime();

        this->completionTime = (int64)awsExportTaskExecutionInfo.GetCompletionTime();

        return *this;
    }
#endif
};
