/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, December 2022
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DeleteDataProtectionPolicyRequest.h"

#endif

#include "AWSCloudWatchLogsDeleteDataProtectionPolicyRequest.generated.h"

USTRUCT(BlueprintType)
struct FAWSCloudWatchLogsDeleteDataProtectionPolicyRequest {
GENERATED_BODY()

    /**
    *  <p>The name or ARN of the log group that you want to delete the data protection policy for.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logs Client")
    FString logGroupIdentifier;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DeleteDataProtectionPolicyRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DeleteDataProtectionPolicyRequest awsDeleteDataProtectionPolicyRequest;

		if (!(this->logGroupIdentifier.IsEmpty())) {
            awsDeleteDataProtectionPolicyRequest.SetLogGroupIdentifier(TCHAR_TO_UTF8(*this->logGroupIdentifier));
        }

        return awsDeleteDataProtectionPolicyRequest;
    }

    bool IsEmpty() const {
        return this->logGroupIdentifier.IsEmpty();
    }
#endif
};
