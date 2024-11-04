/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeExportTasksResult.h"

#endif

#include "Model/ExportTask.h"

#include "DescribeExportTasksResult.generated.h"

USTRUCT(BlueprintType)
struct FDescribeExportTasksResult {
GENERATED_BODY()

    /**
    *  <p>The export tasks.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FExportTask> exportTasks;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FDescribeExportTasksResult &fromAWS(const Aws::CloudWatchLogs::Model::DescribeExportTasksResult &awsDescribeExportTasksResult) {
        this->exportTasks.Empty();
        for (const Aws::CloudWatchLogs::Model::ExportTask& elem : awsDescribeExportTasksResult.GetExportTasks()) {
            this->exportTasks.Add(FExportTask().fromAWS(elem));
        }

        this->nextToken = UTF8_TO_TCHAR(awsDescribeExportTasksResult.GetNextToken().c_str());

        return *this;
    }
#endif
};
