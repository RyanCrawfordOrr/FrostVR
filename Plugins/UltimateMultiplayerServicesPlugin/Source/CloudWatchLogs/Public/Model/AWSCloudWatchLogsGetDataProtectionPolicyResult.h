/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, December 2022
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/GetDataProtectionPolicyResult.h"

#endif

#include "AWSCloudWatchLogsGetDataProtectionPolicyResult.generated.h"

USTRUCT(BlueprintType)
struct FAWSCloudWatchLogsGetDataProtectionPolicyResult {
GENERATED_BODY()

    /**
    *  <p>The log group name or ARN that you specified in your request.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupIdentifier;
    /**
    *  <p>The data protection policy document for this log group.</p>
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
    FAWSCloudWatchLogsGetDataProtectionPolicyResult &fromAWS(const Aws::CloudWatchLogs::Model::GetDataProtectionPolicyResult &awsGetDataProtectionPolicyResult) {
        this->logGroupIdentifier = UTF8_TO_TCHAR(awsGetDataProtectionPolicyResult.GetLogGroupIdentifier().c_str());

        this->policyDocument = UTF8_TO_TCHAR(awsGetDataProtectionPolicyResult.GetPolicyDocument().c_str());

        this->lastUpdatedTime = (int64)awsGetDataProtectionPolicyResult.GetLastUpdatedTime();

        return *this;
    }
#endif
};
