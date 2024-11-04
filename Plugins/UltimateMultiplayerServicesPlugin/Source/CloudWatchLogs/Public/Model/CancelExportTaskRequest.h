/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/CancelExportTaskRequest.h"

#endif

#include "CancelExportTaskRequest.generated.h"

USTRUCT(BlueprintType)
struct FCancelExportTaskRequest {
GENERATED_BODY()

    /**
    *  <p>The ID of the export task.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString taskId;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::CancelExportTaskRequest toAWS() const {
        Aws::CloudWatchLogs::Model::CancelExportTaskRequest awsCancelExportTaskRequest;

		if (!(this->taskId.IsEmpty())) {
            awsCancelExportTaskRequest.SetTaskId(TCHAR_TO_UTF8(*this->taskId));
        }

        return awsCancelExportTaskRequest;
    }

    bool IsEmpty() const {
        return this->taskId.IsEmpty();
    }
#endif
};
