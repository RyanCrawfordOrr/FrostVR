/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DeleteLogStreamRequest.h"

#endif

#include "DeleteLogStreamRequest.generated.h"

USTRUCT(BlueprintType)
struct FDeleteLogStreamRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The name of the log stream.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logStreamName;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DeleteLogStreamRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DeleteLogStreamRequest awsDeleteLogStreamRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsDeleteLogStreamRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->logStreamName.IsEmpty())) {
            awsDeleteLogStreamRequest.SetLogStreamName(TCHAR_TO_UTF8(*this->logStreamName));
        }

        return awsDeleteLogStreamRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->logStreamName.IsEmpty();
    }
#endif
};
