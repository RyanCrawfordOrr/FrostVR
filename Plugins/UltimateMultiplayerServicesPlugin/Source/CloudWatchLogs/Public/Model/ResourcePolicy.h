/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/ResourcePolicy.h"

#endif

#include "ResourcePolicy.generated.h"

USTRUCT(BlueprintType)
struct FResourcePolicy {
GENERATED_BODY()

    /**
    *  <p>The name of the resource policy.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString policyName;

    /**
    *  <p>The details of the policy.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString policyDocument;

    /**
    *  <p>Timestamp showing when this policy was last updated, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 lastUpdatedTime = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FResourcePolicy &fromAWS(const Aws::CloudWatchLogs::Model::ResourcePolicy &awsResourcePolicy) {
        this->policyName = UTF8_TO_TCHAR(awsResourcePolicy.GetPolicyName().c_str());

        this->policyDocument = UTF8_TO_TCHAR(awsResourcePolicy.GetPolicyDocument().c_str());

        this->lastUpdatedTime = (int64)awsResourcePolicy.GetLastUpdatedTime();

        return *this;
    }
#endif
};
