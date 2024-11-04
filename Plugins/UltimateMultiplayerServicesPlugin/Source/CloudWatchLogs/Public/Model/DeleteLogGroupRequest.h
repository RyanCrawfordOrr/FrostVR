/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DeleteLogGroupRequest.h"

#endif

#include "DeleteLogGroupRequest.generated.h"

USTRUCT(BlueprintType)
struct FDeleteLogGroupRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DeleteLogGroupRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DeleteLogGroupRequest awsDeleteLogGroupRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsDeleteLogGroupRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

        return awsDeleteLogGroupRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty();
    }
#endif
};
