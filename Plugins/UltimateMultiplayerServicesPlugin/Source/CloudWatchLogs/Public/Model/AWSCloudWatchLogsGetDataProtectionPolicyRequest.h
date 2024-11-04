/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, December 2022
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/GetDataProtectionPolicyRequest.h"

#endif

#include "AWSCloudWatchLogsGetDataProtectionPolicyRequest.generated.h"

USTRUCT(BlueprintType)
struct FAWSCloudWatchLogsGetDataProtectionPolicyRequest {
GENERATED_BODY()

    /**
    *  <p>The name or ARN of the log group that contains the data protection policy that you want to see.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupIdentifier;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::GetDataProtectionPolicyRequest toAWS() const {
        Aws::CloudWatchLogs::Model::GetDataProtectionPolicyRequest awsGetDataProtectionPolicyRequest;

        if (!(this->logGroupIdentifier.IsEmpty())) {
            awsGetDataProtectionPolicyRequest.SetLogGroupIdentifier(TCHAR_TO_UTF8(*this->logGroupIdentifier));
        }

        return awsGetDataProtectionPolicyRequest;
    }

    bool IsEmpty() const {
        return this->logGroupIdentifier.IsEmpty();
    }
#endif
};
