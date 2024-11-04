/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/CreateExportTaskResult.h"

#endif

#include "CreateExportTaskResult.generated.h"

USTRUCT(BlueprintType)
struct FCreateExportTaskResult {
GENERATED_BODY()

    /**
    *  <p>The ID of the export task.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString taskId;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FCreateExportTaskResult &fromAWS(const Aws::CloudWatchLogs::Model::CreateExportTaskResult &awsCreateExportTaskResult) {
        this->taskId = UTF8_TO_TCHAR(awsCreateExportTaskResult.GetTaskId().c_str());

        return *this;
    }
#endif
};
