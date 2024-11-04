/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DeleteResourcePolicyRequest.h"

#endif

#include "DeleteResourcePolicyRequest.generated.h"

USTRUCT(BlueprintType)
struct FDeleteResourcePolicyRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the policy to be revoked. This parameter is required.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString policyName;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DeleteResourcePolicyRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DeleteResourcePolicyRequest awsDeleteResourcePolicyRequest;

		if (!(this->policyName.IsEmpty())) {
            awsDeleteResourcePolicyRequest.SetPolicyName(TCHAR_TO_UTF8(*this->policyName));
        }

        return awsDeleteResourcePolicyRequest;
    }

    bool IsEmpty() const {
        return this->policyName.IsEmpty();
    }
#endif
};
