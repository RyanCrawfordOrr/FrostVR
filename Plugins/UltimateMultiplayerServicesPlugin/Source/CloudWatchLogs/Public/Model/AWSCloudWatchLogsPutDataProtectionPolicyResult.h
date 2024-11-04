/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, December 2022
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutDataProtectionPolicyResult.h"

#endif

#include "AWSCloudWatchLogsPutDataProtectionPolicyResult.generated.h"

USTRUCT(BlueprintType)
struct FAWSCloudWatchLogsPutDataProtectionPolicyResult {
GENERATED_BODY()

    /**
    *  <p>The log group name or ARN that you specified in your request.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupIdentifier;

    /**
    *  <p>The data protection policy used for this log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString policyDocument;

    /**
    *  <p>The date and time that this policy was most recently updated.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 lastUpdatedTime = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FAWSCloudWatchLogsPutDataProtectionPolicyResult &fromAWS(const Aws::CloudWatchLogs::Model::PutDataProtectionPolicyResult &awsPutDataProtectionPolicyResult) {
        this->logGroupIdentifier = UTF8_TO_TCHAR(awsPutDataProtectionPolicyResult.GetLogGroupIdentifier().c_str());

        this->policyDocument = UTF8_TO_TCHAR(awsPutDataProtectionPolicyResult.GetPolicyDocument().c_str());

        this->lastUpdatedTime = (int64)awsPutDataProtectionPolicyResult.GetLastUpdatedTime();

        return *this;
    }
#endif
};
