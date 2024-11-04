/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DeleteRetentionPolicyRequest.h"

#endif

#include "DeleteRetentionPolicyRequest.generated.h"

USTRUCT(BlueprintType)
struct FDeleteRetentionPolicyRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DeleteRetentionPolicyRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DeleteRetentionPolicyRequest awsDeleteRetentionPolicyRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsDeleteRetentionPolicyRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

        return awsDeleteRetentionPolicyRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty();
    }
#endif
};
