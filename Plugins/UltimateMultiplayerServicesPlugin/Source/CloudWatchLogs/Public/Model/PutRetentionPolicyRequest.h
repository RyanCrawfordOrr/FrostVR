/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutRetentionPolicyRequest.h"

#endif

#include "PutRetentionPolicyRequest.generated.h"

USTRUCT(BlueprintType)
struct FPutRetentionPolicyRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int retentionInDays = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::PutRetentionPolicyRequest toAWS() const {
        Aws::CloudWatchLogs::Model::PutRetentionPolicyRequest awsPutRetentionPolicyRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsPutRetentionPolicyRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

        if (!(this->retentionInDays == 0)) {
            awsPutRetentionPolicyRequest.SetRetentionInDays(this->retentionInDays);
        }

        return awsPutRetentionPolicyRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->retentionInDays == 0;
    }
#endif
};
