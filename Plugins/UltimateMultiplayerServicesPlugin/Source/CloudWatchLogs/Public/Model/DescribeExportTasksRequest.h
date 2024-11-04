/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeExportTasksRequest.h"

#endif

#include "Model/ExportTaskStatusCode.h"

#include "DescribeExportTasksRequest.generated.h"

USTRUCT(BlueprintType)
struct FDescribeExportTasksRequest {
GENERATED_BODY()

    /**
    *  <p>The ID of the export task. Specifying a task ID filters the results to zero or one export tasks.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString taskId;

    /**
    *  <p>The status code of the export task. Specifying a status code filters the results to zero or more export tasks.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    EAWSExportTaskStatusCode statusCode = EAWSExportTaskStatusCode::NOT_SET;

    /**
    *  <p>The token for the next set of items to return. (You received this token from a previous call.)</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

    /**
    *  <p>The maximum number of items returned. If you don't specify a value, the default is up to 50 items.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int limit = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DescribeExportTasksRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DescribeExportTasksRequest awsDescribeExportTasksRequest;

		if (!(this->taskId.IsEmpty())) {
            awsDescribeExportTasksRequest.SetTaskId(TCHAR_TO_UTF8(*this->taskId));
        }

        switch(this->statusCode) {
            case EAWSExportTaskStatusCode::CANCELLED:
                awsDescribeExportTasksRequest.SetStatusCode(Aws::CloudWatchLogs::Model::ExportTaskStatusCode::CANCELLED);
                break;
            case EAWSExportTaskStatusCode::COMPLETED:
                awsDescribeExportTasksRequest.SetStatusCode(Aws::CloudWatchLogs::Model::ExportTaskStatusCode::COMPLETED);
                break;
            case EAWSExportTaskStatusCode::FAILED:
                awsDescribeExportTasksRequest.SetStatusCode(Aws::CloudWatchLogs::Model::ExportTaskStatusCode::FAILED);
                break;
            case EAWSExportTaskStatusCode::PENDING:
                awsDescribeExportTasksRequest.SetStatusCode(Aws::CloudWatchLogs::Model::ExportTaskStatusCode::PENDING);
                break;
            case EAWSExportTaskStatusCode::PENDING_CANCEL:
                awsDescribeExportTasksRequest.SetStatusCode(Aws::CloudWatchLogs::Model::ExportTaskStatusCode::PENDING_CANCEL);
                break;
            case EAWSExportTaskStatusCode::RUNNING:
                awsDescribeExportTasksRequest.SetStatusCode(Aws::CloudWatchLogs::Model::ExportTaskStatusCode::RUNNING);
                break;
            default:
                break;
		}

		if (!(this->nextToken.IsEmpty())) {
            awsDescribeExportTasksRequest.SetNextToken(TCHAR_TO_UTF8(*this->nextToken));
        }

        if (!(this->limit == 0)) {
            awsDescribeExportTasksRequest.SetLimit(this->limit);
        }

        return awsDescribeExportTasksRequest;
    }

    bool IsEmpty() const {
        return this->taskId.IsEmpty() && statusCode == EAWSExportTaskStatusCode::NOT_SET && this->nextToken.IsEmpty() && this->limit == 0;
    }
#endif
};
