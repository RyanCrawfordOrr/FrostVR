/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/ExportTaskStatus.h"

#endif

#include "Model/ExportTaskStatusCode.h"

#include "ExportTaskStatus.generated.h"

USTRUCT(BlueprintType)
struct FExportTaskStatus {
GENERATED_BODY()

    /**
    *  <p>The status code of the export task.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    EAWSExportTaskStatusCode code = EAWSExportTaskStatusCode::NOT_SET;

    /**
    *  <p>The status message related to the status code.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString message;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FExportTaskStatus &fromAWS(const Aws::CloudWatchLogs::Model::ExportTaskStatus &awsExportTaskStatus) {
        switch(awsExportTaskStatus.GetCode()) {
            case Aws::CloudWatchLogs::Model::ExportTaskStatusCode::NOT_SET:
                this->code = EAWSExportTaskStatusCode::NOT_SET;
                break;
            case Aws::CloudWatchLogs::Model::ExportTaskStatusCode::CANCELLED:
                this->code = EAWSExportTaskStatusCode::CANCELLED;
                break;
            case Aws::CloudWatchLogs::Model::ExportTaskStatusCode::COMPLETED:
                this->code = EAWSExportTaskStatusCode::COMPLETED;
                break;
            case Aws::CloudWatchLogs::Model::ExportTaskStatusCode::FAILED:
                this->code = EAWSExportTaskStatusCode::FAILED;
                break;
            case Aws::CloudWatchLogs::Model::ExportTaskStatusCode::PENDING:
                this->code = EAWSExportTaskStatusCode::PENDING;
                break;
            case Aws::CloudWatchLogs::Model::ExportTaskStatusCode::PENDING_CANCEL:
                this->code = EAWSExportTaskStatusCode::PENDING_CANCEL;
                break;
            case Aws::CloudWatchLogs::Model::ExportTaskStatusCode::RUNNING:
                this->code = EAWSExportTaskStatusCode::RUNNING;
                break;
            default:
                this->code = EAWSExportTaskStatusCode::NOT_SET;
                break;
        }

        this->message = UTF8_TO_TCHAR(awsExportTaskStatus.GetMessage().c_str());

        return *this;
    }
#endif
};
